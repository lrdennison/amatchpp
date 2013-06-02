#include "rice/Module.hpp"
#include "rice/Class.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"

#include "Sellers.h"

using namespace Rice;


Data_Type<Amatchpp::Sellers> rb_cSellers;

extern "C"
void Init_amatchpp()
{
  Rice::Module rb_mAmatchpp = define_module("Amatchpp");

  rb_cSellers = define_class_under<Amatchpp::Sellers>(rb_mAmatchpp, "Sellers");
  rb_cSellers.define_constructor(Constructor<Amatchpp::Sellers>());
  rb_cSellers.define_method("hello", &Amatchpp::Sellers::hello);
  rb_cSellers.define_method("search", &Amatchpp::Sellers::search);

  RUBY_DECL_RW_ATTR( Amatchpp::Sellers, rb_cSellers, std::string, pattern)

  RUBY_DECL_RW_ATTR( Amatchpp::Sellers, rb_cSellers, double, substitution)
  RUBY_DECL_RW_ATTR( Amatchpp::Sellers, rb_cSellers, double, deletion)
  RUBY_DECL_RW_ATTR( Amatchpp::Sellers, rb_cSellers, double, insertion)
}
