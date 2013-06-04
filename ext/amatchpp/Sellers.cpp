#include <algorithm> 
#include <iostream>
#include "Sellers.h"

namespace Amatchpp
{

  Sellers::Sellers()
  {
    reset_weights();
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

  void Sellers::reset_weights()
  {
    substitution = 1.0;
    deletion     = 1.0;
    insertion    = 1.0;
  }


  void Sellers::setup(const std::string &text)
  {
    a_ptr = pattern.c_str();
    a_len = pattern.length();
    b_ptr = text.c_str();
    b_len = text.length();

    for( int ix=0; ix<2; ++ix) {
      v[ix] = ALLOC_N(double, b_len + 1);
      MEMZERO(v[ix], double, b_len + 1);
    }
  }

  void Sellers::setup_v_deletion()
  {
    for (int i = 0; i <= b_len; i++) {
      v[0][i] = i * deletion;
      v[1][i] = i * deletion;
    }
  }

  void Sellers::teardown()
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


  double Sellers::max_weight()
  {
    double r = std::max(substitution, deletion);
    r = std::max( r, insertion);
    return r;
  }


  void Sellers::compute()
  {
    int i, j;
    double weight;

    for (i = 1, c = 0, p = 1; i <= a_len; i++) {				
      c = i % 2;                      /* current row */                   
      p = (i + 1) % 2;                /* previous row */                  
      v[c][0] = i * deletion; /* first column */                  
      for (j = 1; j <= b_len; j++) {                                      
	/* Bellman's principle of optimality: */				
	weight = v[p][j - 1] +						
	  (a_ptr[i - 1] == b_ptr[j - 1] ? 0 : substitution);	
	if (weight > v[p][j] + insertion) {			
	  weight = v[p][j] + insertion;				
	}									
	if (weight > v[c][j - 1] + deletion) {			
	  weight = v[c][j - 1] + deletion;			
	}									
	v[c][j] = weight;							
      }                                                                   
      p = c;                                                              
      c = (c + 1) % 2;                                                    
    }
  }




  double Sellers::_match(const std::string &text)
  {
    setup( text);
    setup_v_deletion();

    compute();

    double result = v[p][b_len];
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
      compute();

      if (b_len > a_len) {
        result = 1.0 - v[p][b_len] / (b_len * max_weight());
      } else {
        result = 1.0 - v[p][b_len] / (a_len * max_weight());
      }

    }

    teardown();
    return result;
  }


  double Sellers::_search(const std::string &text)
  {
    setup( text);
    compute();

    double min = a_len;
    for (int i = 0; i <= b_len; i++) {
      if (v[p][i] < min) {
	min = v[p][i];
      }
    }

    teardown();
    return( min);
  }

  
}
