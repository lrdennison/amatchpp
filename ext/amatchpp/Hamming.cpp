#include <algorithm> 
#include <iostream>
#include "Hamming.hpp"

namespace Amatchpp
{

  Hamming::Hamming(const std::string pat) : General( pat)
  {
  }

  Rice::Object Hamming::match(Rice::Object arg) {
    return apply<Hamming>( this, &Hamming::_match, arg);
  }

  Rice::Object Hamming::similar(Rice::Object arg) {
    return apply<Hamming>( this, &Hamming::_similar, arg);
  }



  int Hamming::compute()
  {
    order_by_length();

    int result = b_len - a_len;

    for (int i = 0; i < a_len; i++) {
      if (b_ptr[i] != a_ptr[i])
	result++;
    }

    return result;
  }



  double Hamming::_match(const std::string &text)
  {
    int result;

    setup( text);
    result = compute();
    teardown();
    return( result);
  }


  double Hamming::_similar(const std::string &text)
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
      result = 1.0 - result / b_len;
    }

    teardown();
    return result;
  }

}
