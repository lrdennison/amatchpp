#ifndef __GENERAL_H__
#define __GENERAL_H__

#include <iostream>

#include "rice/Module.hpp"
#include "rice/Class.hpp"
#include "rice/Object.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Array.hpp"

#include "utils.hpp"

namespace Amatchpp
{
  /* 
   * Document-class: Amatchpp::General
   *
   * The base class for all approximate matchers.
   */

  class General {
  public:

    /*
     * Document-attr: pattern
     *
     * The pattern string used in calculations
     */
    CPP_DECL_RW_ATTR( std::string, pattern)

    // The two strings. A is corresponds to the pattern, B to the larger text
    const char *a_ptr, *b_ptr;
    int a_len, b_len;

    General(const std::string pat);

    virtual ~General() {}

    void setup(const std::string &text)
    {
      a_ptr = pattern.c_str();
      a_len = pattern.length();
      b_ptr = text.c_str();
      b_len = text.length();
    }

    void teardown() {
      a_ptr = 0;
      a_len = 0;
      b_ptr = 0;
      b_len = 0;
    }

    void order_by_length()
    {
      if( a_len > b_len) {
	int t;
	t = a_len;
	a_len = b_len;
	b_len = t;
	const char *p;
	p = a_ptr;
	a_ptr = b_ptr;
	b_ptr = p;
      }
    }


    template<class T>
    Rice::Object apply(T *self, double (T::*mf)(const std::string &text), Rice::Object arg)
    {
      // std::cout << "In the apply function" << std::endl;

      double result =  0.0;

      int arg_type = arg.rb_type();

      if( arg_type == T_STRING) {
	// std::cout << "This is a string" << std::endl;
	result = (self->*mf)( from_ruby<std::string>( arg));
	return to_ruby( result);
      }


      if( arg_type == T_ARRAY) {
	// std::cout << "This is an array" << std::endl;

	Rice::Array a( arg);

	// Typecheck first
	for( unsigned int ix=0; ix<a.size(); ++ix) {
	  Rice::Object elt = a[ix];
	  if( elt.rb_type() != T_STRING) {
	    const char *s = NIL_P(elt) ? "NilClass" : rb_class2name(elt.class_of());
	    rb_raise(rb_eTypeError,			    
		     "array has to contain only strings (%s given)",
		     s);

	  }
	}
	
	Rice::Array b;

	for( unsigned int ix=0; ix<a.size(); ++ix) {
	  Rice::Object elt = a[ix];
	  result = (self->*mf)( from_ruby<std::string>( elt));
	  b.push( result);
	}

	return to_ruby( b);
      }

      
      const char *s = NIL_P(arg) ? "NilClass" : rb_class2name(arg.class_of());
      std::cout << "Unknown type " << s << std::endl;
      return to_ruby( result);
    }

  };

}

#endif
