#ifndef __HAMMING_H__
#define __HAMMING_H__

#include "General.hpp"

namespace Amatchpp
{

  /* 
   * Document-class: Amatchpp::Hamming < Amatchpp::General
   *
   *  This class computes the Hamming distance between two strings.
   *
   *  The Hamming distance between two strings is the number of characters, that
   *  are different. Thus a hamming distance of 0 means an exact
   *  match, a hamming distance of 1 means one character is different, and so on.
   *  If one string is longer than the other string, the missing characters are
   *  counted as different characters.
   */
  class Hamming : public General {
  public:

    /*
     * Document-method: Hamming::initialize
     * call-seq: new(pattern)
     *
     * Creates a new Amatchpp::Hamming instance from <code>pattern</code>.
     */
    Hamming(const std::string pat);

    /*
     * Document-method: Hamming#match
     * call-seq: match(strings) -> results
     * 
     * Uses this Amatchpp:::Hamming instance to match Amatch::Hamming#pattern against
     * <code>strings</code>, that is compute the hamming distance between
     * <code>pattern</code> and <code>strings</code>. <code>strings</code> has to
     * be either a String or an Array of Strings. The returned <code>results</code>
     * are either a Fixnum or an Array of Fixnums respectively.
     */
    Rice::Object match(Rice::Object arg);

    /*
     * Document-method: Hamming#similar
     * call-seq: similar(strings) -> results
     *
     * Uses this Amatchpp::Hamming instance to match  Amatch::Hamming#pattern against
     * <code>strings</code>, and compute a Hamming distance metric number between
     * 0.0 for very unsimilar strings and 1.0 for an exact match.
     * <code>strings</code> has to be either a String or an Array of Strings. The
     * returned <code>results</code> are either a Fixnum or an Array of Fixnums
     * respectively.
     */
    
    Rice::Object similar(Rice::Object arg);

  private:
    int compute();

    double _match(const std::string &text);
    double _similar(const std::string &text);
    
  };

}


#endif
