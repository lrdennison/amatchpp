#include <algorithm>
#include <iostream>
#include "Jaro.hpp"

namespace Amatchpp
{

  Jaro::Jaro(const std::string pat) : General( pat)
  {
    ignore_case = true;
  }

  Rice::Object Jaro::match(Rice::Object arg) {
    return apply<Jaro>( this, &Jaro::_match, arg);
  }


  double Jaro::compute()
  {
    int max_dist, m, t, i, j, k, low, high;
    int *l[2];
    double result;

    order_by_length();

    l[0] = ALLOC_N(int, a_len);
    MEMZERO(l[0], int, a_len);
    l[1] = ALLOC_N(int, b_len);
    MEMZERO(l[1], int, b_len);

    max_dist = ((a_len > b_len ? a_len : b_len) / 2) - 1;
    m = 0;
    for (i = 0; i < a_len; i++) {
      low = (i > max_dist ? i - max_dist : 0);
      high = (i + max_dist < b_len ? i + max_dist : b_len);
      for (j = low; j <= high; j++) {
	if (!l[1][j] && a_ptr[i] == b_ptr[j]) {
	  l[0][i] = 1;
	  l[1][j] = 1;
	  m++;
	  break;
	}
      }
    }
    if (m == 0) {
      result = 0.0;
    } else {
      k = t = 0;
      for (i = 0; i < a_len; i++) {
	if (l[0][i]) {
	  for (j = k; j < b_len; j++) {
	    if (l[1][j]) {
	      k = j + 1;
	      break;
	    }
	  }
	  if (a_ptr[i] != b_ptr[j]) {
	    t++;
	  }
	}
      }
      t = t / 2;
      result = (((double)m)/a_len + ((double)m)/b_len + ((double)(m-t))/m)/3.0;
    }
    
    free( l[0]);
    free( l[1]);
    return result;
  }

    

  double Jaro::_match(const std::string &text)
  {
    setup( text);
    if( ignore_case) {
      lowercase_strings();
    }

    double result = 0.0;
    if (a_len == 0 && b_len == 0) {
      result = 1.0;
    }
    else if (a_len == 0 || b_len == 0) {
      result = 0.0;
    }
    else {
      result = compute();
    }

    if( ignore_case) {
      free( sa_ptr);
      free( sb_ptr);
    }

    teardown();
    return( result);
  }



}
