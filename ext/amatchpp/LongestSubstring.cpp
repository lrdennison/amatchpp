#include <algorithm>
#include <iostream>
#include "LongestSubstring.hpp"

namespace Amatchpp
{

  LongestSubstring::LongestSubstring(const std::string pat) : General( pat)
  {
  }

  Rice::Object LongestSubstring::match(Rice::Object arg) {
    return apply<LongestSubstring>( this, &LongestSubstring::_match, arg);
  }

  Rice::Object LongestSubstring::similar(Rice::Object arg) {
    return apply<LongestSubstring>( this, &LongestSubstring::_similar, arg);
  }



  int LongestSubstring::compute()
  {
    order_by_length();
    int result;
    int *l[2];
    int c, p, i, j;

    l[0] = ALLOC_N(int, b_len);
    MEMZERO(l[0], int, b_len);
    l[1] = ALLOC_N(int, b_len);
    MEMZERO(l[1], int, b_len);
    result = 0;
    for (i = 0, c = 0, p = 1; i < a_len; i++) {
        for (j = 0; j < b_len; j++) {
            if (a_ptr[i] == b_ptr[j]) {
                l[c][j] = j == 0 ? 1 : 1 + l[p][j - 1];
                if (l[c][j] > result) result = l[c][j];
            } else {
                l[c][j] = 0;
            }
        }
        p = c;
        c = (c + 1) % 2;
    }
    free(l[0]);
    free(l[1]);

    return result;
  }



  double LongestSubstring::_match(const std::string &text)
  {
    double result;

    setup( text);
    result = compute();
    teardown();
    return( result);
  }


  double LongestSubstring::_similar(const std::string &text)
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
