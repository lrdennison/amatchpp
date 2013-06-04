#include <algorithm>
#include <iostream>
#include "JaroWinkler.hpp"

namespace Amatchpp
{

  JaroWinkler::JaroWinkler(const std::string pat) : Jaro( pat)
  {
    scaling_factor = 0.1;
  }

  Rice::Object JaroWinkler::match(Rice::Object arg) {
    return apply<JaroWinkler>( this, &JaroWinkler::_match, arg);
  }

  double JaroWinkler::_match(const std::string &text)
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

      int n = 0;
      for (int i = 0; i < (a_len >= 4 ? 4 : a_len); i++) {
        if (a_ptr[i] == b_ptr[i]) {
	  n++;
        } else {
	  break;
        }
      }
      result = result + n*scaling_factor*(1.0-result);
    }

    if( ignore_case) {
      free( sa_ptr);
      free( sb_ptr);
    }

    teardown();
    return( result);
  }


}
