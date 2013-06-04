#include <algorithm> 
#include <iostream>
#include "LongestSubsequence.hpp"

namespace Amatchpp
{

  LongestSubsequence::LongestSubsequence(const std::string pat) : General( pat)
  {
  }

  Rice::Object LongestSubsequence::match(Rice::Object arg) {
    return apply<LongestSubsequence>( this, &LongestSubsequence::_match, arg);
  }

  Rice::Object LongestSubsequence::similar(Rice::Object arg) {
    return apply<LongestSubsequence>( this, &LongestSubsequence::_similar, arg);
  }



  int LongestSubsequence::compute()
  {
    order_by_length();
    int result;
    int *l[2];
    int c, p, i, j;

    l[0] = ALLOC_N(int, b_len + 1);
    l[1] = ALLOC_N(int, b_len + 1);
    for (i = a_len, c = 0, p = 1; i >= 0; i--) {
        for (j = b_len; j >= 0; j--) {
            if (i == a_len || j == b_len) {
                l[c][j] = 0;
            } else if (a_ptr[i] == b_ptr[j]) {
                l[c][j] = 1 + l[p][j + 1];
            } else {
                int x = l[p][j], y = l[c][j + 1];
                if (x > y) l[c][j] = x; else l[c][j] = y;
            }
        }
        p = c;
        c = (c + 1) % 2;
    }
    result = l[p][0];
    free(l[0]);
    free(l[1]);

    return result;
  }



  double LongestSubsequence::_match(const std::string &text)
  {
    double result;

    setup( text);
    result = compute();
    teardown();
    return( result);
  }


  double LongestSubsequence::_similar(const std::string &text)
  {
    setup( text);
    double result = 0.0;

    if (a_len == 0 && b_len == 0) {
      result = 1.0;
    }
    else if (a_len == 0 || b_len == 0) {
      result = 0.0;
    }
    else {
      result = (double)compute();
      result = result / b_len;
    }

    teardown();
    return result;
  }

}
