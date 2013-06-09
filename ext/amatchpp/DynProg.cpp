#include <algorithm> 
#include <iostream>
#include "DynProg.hpp"

namespace Amatchpp
{

  DynProg::DynProg(const std::string pat) : General( pat)
  {
    v = 0;
    v_store = 0;
    step = 0;
    step_store = 0;

    reset_weights();
  }

  DynProg::~DynProg()
  {
    if( v) {
      free( v);
      v = 0;
    }
    if( v_store) {
      free( v_store);
      v_store = 0;
    }
    if( step) {
      free( step);
      step = 0;
    }
    if( step_store) {
      free( step_store);
      step_store = 0;
    }
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

    rows_allocated = a_len+1;
    if( rows_allocated < 2)
      rows_allocated = 2;

    int row_len = b_len+1;
    int num_elts = rows_allocated * row_len;

    v = ALLOC_N(double *, rows_allocated);

    v_store = ALLOC_N(double, num_elts);
    MEMZERO(v_store, double, num_elts);

    double *dp = v_store;
    for( int ix=0; ix<rows_allocated; ++ix) {
      v[ix] = dp;
      dp += row_len;
    }

    step = ALLOC_N(char *, rows_allocated);

    step_store = ALLOC_N(char, num_elts);
    MEMZERO(step_store, char, num_elts);

    char *sp = step_store;
    for( int ix=0; ix<rows_allocated; ++ix) {
      step[ix] = sp;
      sp += row_len;
    }

  }

  

  void DynProg::setup_v_deletion()
  {
    for (int i = 0; i <= b_len; i++) {
      v[0][i] = i * deletion;
      v[1][i] = i * deletion;
    }
  }



  void DynProg::compute()
  {
    int i, j;
    double weight;

    // We use c & p after the loop but the loop
    // body might not execute so we need to set c and p
    // beforehand

    set_c_p( 1);
    for (i = 1; i <= a_len; i++) {
      set_c_p( i);

      v[c][0] = i * deletion; /* first column */

      for (j = 1; j <= b_len; j++) {
	/* Bellman's principle of optimality: */

	double w_eqv, w_sub, w_ins, w_del;

	w_eqv = v[p][j - 1];
	w_sub = v[p][j - 1] + substitution;
	w_ins = v[p][j + 0] + insertion;
	w_del = v[c][j - 1] + deletion;

	// If there is no match, adjust w_eqv so it can't be a binding constraint
	if( a_ptr[i - 1] != b_ptr[j - 1])
	  w_eqv += 2.0*substitution;

	weight = std::min( w_eqv, w_sub);
	weight = std::min( weight, w_ins);
	weight = std::min( weight, w_del);

	step[c][j] = 0;
	if( weight == w_eqv) step[c][j] |= eqv;
	if( weight == w_sub) step[c][j] |= sub;
	if( weight == w_ins) step[c][j] |= ins;
	if( weight == w_del) step[c][j] |= del;

	v[c][j] = weight;
      }
    }
  }


  void DynProg::backtrace(int i, int j, int num_steps)
  {
    if( i==0 || j==0) {
      start_pos = j;
      edit_cmd = "";
      return;
    }

    char buf[16];
    buf[0] = 0;

    if( step[i][j] & eqv) {
      backtrace(i-1, j-1, num_steps+1);
      sprintf( buf, " %c:%c", a_ptr[i-1], b_ptr[j-1]);
    }
    else if( step[i][j] & sub) {
      backtrace(i-1, j-1, num_steps+1);
      sprintf( buf, " %c#%c", a_ptr[i-1], b_ptr[j-1]);
    }
    else if( step[i][j] & ins) {
      backtrace(i-1, j-0, num_steps+1);
      sprintf( buf, "+%c: ", a_ptr[i-1]);
    }
    else if( step[i][j] & del) {
      backtrace(i-0, j-1, num_steps+1);
      sprintf( buf, "- :%c", b_ptr[j-1]);
    }

    edit_cmd += "|" + std::string( buf);
  }


  void DynProg::teardown()
  {
    if( v) {
      free( v);
      v = 0;
    }
    if( v_store) {
      free( v_store);
      v_store = 0;
    }

    General::teardown();
  }


  double DynProg::max_weight()
  {
    double r = std::max(substitution, deletion);
    r = std::max( r, insertion);
    return r;
  }

  
}
