#include <algorithm> 
#include <iostream>
#include "Sellers.hpp"

namespace Amatchpp
{

  Sellers::Sellers(const std::string pat) : DynProg( pat)
  {
  }

  Rice::Object Sellers::search(Rice::Object arg) {
    return apply<Sellers>( this, &Sellers::_search, arg);
  }

  Rice::Object Sellers::match(Rice::Object arg) {
    return apply<Sellers>( this, &Sellers::_match, arg);
  }

  Rice::Object Sellers::similar(Rice::Object arg) {
    return apply<Sellers>( this, &Sellers::_similar, arg);
  }


  double Sellers::_match(const std::string &text)
  {
    setup( text);
    setup_v_deletion();

    DynProg::compute();

    double result = v[c][b_len];
    teardown();
    return( result);
  }


  double Sellers::_similar(const std::string &text)
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
      setup_v_deletion();
      DynProg::compute();

      if (b_len > a_len) {
        result = 1.0 - v[c][b_len] / (b_len * max_weight());
      } else {
        result = 1.0 - v[c][b_len] / (a_len * max_weight());
      }

    }

    teardown();
    return result;
  }


  double Sellers::_search(const std::string &text)
  {
    setup( text);
    DynProg::compute();

    double min = a_len;
    for (int i = 0; i <= b_len; i++) {
      if (v[c][i] < min) {
	min = v[c][i];
	end_pos = i;
      }
    }

    backtrace( a_len, end_pos);

    teardown();
    return( min);
  }

  
}
