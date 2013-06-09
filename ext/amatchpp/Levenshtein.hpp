#ifndef __LEVENSHTEIN_H__
#define __LEVENSHTEIN_H__

#include "DynProg.hpp"

namespace Amatchpp
{


  /* 
   * Document-class: Amatchpp::Levenshtein < Amatchpp::DynProg
   *
   * The Levenshtein edit distance is defined as the minimal costs involved to
   * transform one string into another by using three elementary operations:
   * deletion, insertion and substitution of a character. To transform "water"
   * into "wine", for instance, you have to substitute "a" -> "i": "witer", "t"
   * -> "n": "winer" and delete "r": "wine". The edit distance between "water"
   * and "wine" is 3, because you have to apply three operations. The edit
   * distance between "wine" and "wine" is 0 of course: no operation is
   * necessary for the transformation -- they're already the same string. It's
   * easy to see that more similar strings have smaller edit distances than
   * strings that differ a lot.
   */
  class Levenshtein : public DynProg {
  public:

    /*
     * Document-method: initialize
     * call-seq: new(pattern)
     *
     * Creates a new Amatchpp::Levenshtein instance from <code>pattern</code>.
     */
    Levenshtein(const std::string pat);

    /*
     * Document-method: Levenshtein#match
     * call-seq: match(strings) -> results
     * 
     * Uses this Amatchpp::Levenshtein instance to match Amatch::Levenshtein#pattern
     * against <code>strings</code>. It returns the number operations, the Sellers
     * distance. <code>strings</code> has to be either a String or an Array of
     * Strings. The returned <code>results</code> are either a Float or an Array of
     * Floats respectively.
     */
    Rice::Object match(Rice::Object arg);

    /*
     * Document-method: Levenshtein#similar
     * call-seq: similar(strings) -> results
     * 
     * Uses this Amatch::Levenshtein instance to match  Amatch::Levenshtein#pattern
     * against <code>strings</code>, and compute a Levenshtein distance metric
     * number between 0.0 for very unsimilar strings and 1.0 for an exact match.
     * <code>strings</code> has to be either a String or an Array of Strings. The
     * returned <code>results</code> are either a Fixnum or an Array of Fixnums
     * respectively.
     */
    Rice::Object similar(Rice::Object arg);

    /*
     * Document-method: Levenshtein#search
     * call-seq: search(strings) -> results
     * 
     * searches Amatch::Levenshtein#pattern in <code>strings</code> and returns the
     * edit distance (the sum of character operations) as a Fixnum value, by greedy
     * trimming prefixes or postfixes of the match. <code>strings</code> has
     * to be either a String or an Array of Strings. The returned
     * <code>results</code> are either a Float or an Array of Floats respectively.
     */
    Rice::Object search(Rice::Object arg);

  private:
    void compute();

    double _match(const std::string &text);
    double _similar(const std::string &text);
    double _search(const std::string &text);
    
  };

}

#endif
