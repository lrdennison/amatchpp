#ifndef __GENERAL_H__
#define __GENERAL_H__

#include "rice/Module.hpp"
#include "rice/Class.hpp"
#include "rice/Object.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Array.hpp"

#include "utils.h"

namespace Amatchpp
{
  template<class T> class General {
  public:
    typedef double (T::*member_func)(const std::string &text);

    General() {
    }

    Rice::Object apply(T *self, member_func mf, Rice::Object arg)
    {
      std::cout << "In the apply function" << std::endl;

      double result =  0.0;

      int arg_type = arg.rb_type();

      if( arg_type == T_STRING) {
	std::cout << "This is a string" << std::endl;
	result = (self->*mf)( from_ruby<std::string>( arg));
	return to_ruby( result);
      }


      if( arg_type == T_ARRAY) {
	std::cout << "This is an array" << std::endl;

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
