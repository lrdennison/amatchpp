#include <algorithm> 
#include <iostream>
#include "DynProg.hpp"

namespace Amatchpp
{

  DynProg::DynProg(const std::string pat) : General( pat)
  {
    reset_weights();
  }


  void DynProg::reset_weights()
  {
    substitution = 1.0;
    deletion     = 1.0;
    insertion    = 1.0;
  }


  void DynProg::setup(const std::string &text)
  {
    General::setup( text);

    for( int ix=0; ix<2; ++ix) {
      v[ix] = ALLOC_N(double, b_len + 1);
      MEMZERO(v[ix], double, b_len + 1);
    }
  }

  void DynProg::setup_v_deletion()
  {
    for (int i = 0; i <= b_len; i++) {
      v[0][i] = i * deletion;
      v[1][i] = i * deletion;
    }
  }

  void DynProg::teardown()
  {
    a_ptr = 0;
    a_len = 0;
    b_ptr = 0;
    b_len = 0;
  
    for( int ix=0; ix<2; ++ix) {
      if( v[ix]) {
	free(v[ix]);
	v[ix] = 0;
      }
    }
  }


  double DynProg::max_weight()
  {
    double r = std::max(substitution, deletion);
    r = std::max( r, insertion);
    return r;
  }



  
}
