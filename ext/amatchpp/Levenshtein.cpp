#include <algorithm>
#include <iostream>
#include "Levenshtein.hpp"

namespace Amatchpp
{

  Levenshtein::Levenshtein(const std::string pat) : DynProg( pat)
  {
  }

  Rice::Object Levenshtein::search(Rice::Object arg) {
    return apply<Levenshtein>( this, &Levenshtein::_search, arg);
  }

  Rice::Object Levenshtein::match(Rice::Object arg) {
    return apply<Levenshtein>( this, &Levenshtein::_match, arg);
  }

  Rice::Object Levenshtein::similar(Rice::Object arg) {
    return apply<Levenshtein>( this, &Levenshtein::_similar, arg);
  }



  // TODO Levenshtein appears to be the same as Sellers with all weights
  // set to one.  Verify that and then move compute to DynProg

  void Levenshtein::compute()
  {
    reset_weights();
    DynProg::compute();

    return;
  }




  double Levenshtein::_match(const std::string &text)
  {
    setup( text);
    setup_v_deletion();

    compute();

    double result = v[c][b_len];
    teardown();
    return( result);
  }


  double Levenshtein::_similar(const std::string &text)
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
      compute();

      if (b_len > a_len) {
        result = 1.0 - v[c][b_len] / (b_len * max_weight());
      } else {
        result = 1.0 - v[c][b_len] / (a_len * max_weight());
      }

    }

    teardown();
    return result;
  }


  double Levenshtein::_search(const std::string &text)
  {
    setup( text);
    compute();

    double min = a_len;
    for (int i = 0; i <= b_len; i++) {
      if (v[c][i] < min) {
	min = v[c][i];
      }
    }

    teardown();
    return( min);
  }


}
