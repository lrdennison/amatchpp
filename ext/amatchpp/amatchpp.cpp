#include "rice/Module.hpp"
#include "rice/Class.hpp"
#include "rice/Object.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Array.hpp"

#include "Sellers.h"

using namespace Rice;


Data_Type<Amatchpp::General> rb_cGeneral;
Data_Type<Amatchpp::Sellers> rb_cSellers;


extern "C"
void Init_amatchpp()
{
  Rice::Module rb_mAmatchpp = define_module("Amatchpp");

  rb_cGeneral = define_class_under<Amatchpp::General>(rb_mAmatchpp, "General");
  rb_cGeneral.define_constructor(Constructor<Amatchpp::General>());
  RUBY_DECL_RW_ATTR( Amatchpp::General, rb_cGeneral, std::string, pattern)

  rb_cSellers = define_class_under<Amatchpp::Sellers, Amatchpp::General>(rb_mAmatchpp, "Sellers");
  rb_cSellers.define_constructor(Constructor<Amatchpp::Sellers>());

  RUBY_DECL_RW_ATTR( Amatchpp::Sellers, rb_cSellers, double, substitution)
  RUBY_DECL_RW_ATTR( Amatchpp::Sellers, rb_cSellers, double, deletion)
  RUBY_DECL_RW_ATTR( Amatchpp::Sellers, rb_cSellers, double, insertion)

  rb_cSellers.define_method("reset_weights", &Amatchpp::Sellers::reset_weights);
  rb_cSellers.define_method("search", &Amatchpp::Sellers::search);
  rb_cSellers.define_method("match", &Amatchpp::Sellers::match);
  rb_cSellers.define_method("similar", &Amatchpp::Sellers::similar);

}
