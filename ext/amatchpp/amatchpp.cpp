#include "rice/Module.hpp"
#include "rice/Class.hpp"
#include "rice/Object.hpp"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
#include "rice/Array.hpp"
#include "rice/Arg.hpp"

#include "Sellers.hpp"
#include "Levenshtein.hpp"
#include "Hamming.hpp"
#include "LongestSubsequence.hpp"
#include "LongestSubstring.hpp"
#include "Jaro.hpp"
#include "JaroWinkler.hpp"

using namespace Rice;

Rice::Module rb_mAmatchpp;

Data_Type<Amatchpp::General> rb_cGeneral;
Data_Type<Amatchpp::DynProg> rb_cDynProg;
Data_Type<Amatchpp::Sellers> rb_cSellers;
Data_Type<Amatchpp::Levenshtein> rb_cLevenshtein;
Data_Type<Amatchpp::Hamming> rb_cHamming;
Data_Type<Amatchpp::LongestSubsequence> rb_cLongestSubsequence;
Data_Type<Amatchpp::LongestSubstring> rb_cLongestSubstring;
Data_Type<Amatchpp::Jaro> rb_cJaro;
Data_Type<Amatchpp::JaroWinkler> rb_cJaroWinkler;

  // rb_cPairDistance,


/*
 * Document-module: Amatchpp
 *
 * This module supplies the following classes:
 * * General
 * * DynProg
 * * Sellers
 * * Levenshtein
 * * Hamming
 * * LongestSubsequence
 * * LongestSubstring
 * * Jaro
 * * JaroWinkler
 */


extern "C"
void Init_amatchpp()
{
  rb_mAmatchpp = define_module("Amatchpp");

  rb_cGeneral = define_class_under<Amatchpp::General>(rb_mAmatchpp, "General");
  rb_cGeneral.define_constructor(Constructor<Amatchpp::General, std::string>() );
  RUBY_DECL_RW_ATTR( Amatchpp::General, rb_cGeneral, std::string, pattern);

  rb_cDynProg = define_class_under<Amatchpp::DynProg, Amatchpp::General>(rb_mAmatchpp, "DynProg");
  rb_cDynProg.define_constructor(Constructor<Amatchpp::DynProg, std::string>()) ;

  RUBY_DECL_RW_ATTR( Amatchpp::DynProg, rb_cDynProg, double, substitution);
  RUBY_DECL_RW_ATTR( Amatchpp::DynProg, rb_cDynProg, double, deletion);
  RUBY_DECL_RW_ATTR( Amatchpp::DynProg, rb_cDynProg, double, insertion);
  RUBY_DECL_RW_ATTR( Amatchpp::DynProg, rb_cDynProg, int, start_pos);
  RUBY_DECL_RW_ATTR( Amatchpp::DynProg, rb_cDynProg, int, end_pos);
  RUBY_DECL_RW_ATTR( Amatchpp::DynProg, rb_cDynProg, std::string, edit_cmd);

  rb_cDynProg.define_method("reset_weights", &Amatchpp::DynProg::reset_weights);


  rb_cSellers = define_class_under<Amatchpp::Sellers, Amatchpp::DynProg>(rb_mAmatchpp, "Sellers");
  rb_cSellers.define_constructor(Constructor<Amatchpp::Sellers, std::string>() );

  rb_cSellers.define_method("search", &Amatchpp::Sellers::search);
  rb_cSellers.define_method("match", &Amatchpp::Sellers::match);
  rb_cSellers.define_method("similar", &Amatchpp::Sellers::similar);


  rb_cLevenshtein = define_class_under<Amatchpp::Levenshtein, Amatchpp::DynProg>(rb_mAmatchpp, "Levenshtein");
  rb_cLevenshtein.define_constructor(Constructor<Amatchpp::Levenshtein, std::string>() );

  rb_cLevenshtein.define_method("search", &Amatchpp::Levenshtein::search);
  rb_cLevenshtein.define_method("match", &Amatchpp::Levenshtein::match);
  rb_cLevenshtein.define_method("similar", &Amatchpp::Levenshtein::similar);


  rb_cHamming = define_class_under<Amatchpp::Hamming, Amatchpp::General>(rb_mAmatchpp, "Hamming");
  rb_cHamming.define_constructor(Constructor<Amatchpp::Hamming, std::string>() );

  rb_cHamming.define_method("match", &Amatchpp::Hamming::match);
  rb_cHamming.define_method("similar", &Amatchpp::Hamming::similar);


  rb_cLongestSubsequence = define_class_under<Amatchpp::LongestSubsequence, Amatchpp::General>(rb_mAmatchpp, "LongestSubsequence");
  rb_cLongestSubsequence.define_constructor(Constructor<Amatchpp::LongestSubsequence, std::string>() );

  rb_cLongestSubsequence.define_method("match", &Amatchpp::LongestSubsequence::match);
  rb_cLongestSubsequence.define_method("similar", &Amatchpp::LongestSubsequence::similar);


  rb_cLongestSubstring = define_class_under<Amatchpp::LongestSubstring, Amatchpp::General>(rb_mAmatchpp, "LongestSubstring");
  rb_cLongestSubstring.define_constructor(Constructor<Amatchpp::LongestSubstring, std::string>() );

  rb_cLongestSubstring.define_method("match", &Amatchpp::LongestSubstring::match);
  rb_cLongestSubstring.define_method("similar", &Amatchpp::LongestSubstring::similar);



  rb_cJaro = define_class_under<Amatchpp::Jaro, Amatchpp::General>(rb_mAmatchpp, "Jaro");
  rb_cJaro.define_constructor(Constructor<Amatchpp::Jaro, std::string>() );
  RUBY_DECL_RW_ATTR( Amatchpp::Jaro, rb_cJaro, bool, ignore_case);

  rb_cJaro.define_method("match", &Amatchpp::Jaro::match);


  rb_cJaroWinkler = define_class_under<Amatchpp::JaroWinkler, Amatchpp::Jaro>(rb_mAmatchpp, "JaroWinkler");
  rb_cJaroWinkler.define_constructor(Constructor<Amatchpp::JaroWinkler, std::string>() );
  RUBY_DECL_RW_ATTR( Amatchpp::JaroWinkler, rb_cJaroWinkler, double, scaling_factor);

  rb_cJaroWinkler.define_method("match", &Amatchpp::JaroWinkler::match);

}
