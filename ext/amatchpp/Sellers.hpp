#ifndef __SELLERS_H__
#define __SELLERS_H__

#include "DynProg.hpp"

namespace Amatchpp
{

  /* 
   * Document-class: Amatchpp::Sellers < Amatchpp::DynProg
   *
   * The Sellers edit distance is very similar to the Levenshtein edit distance.
   * The difference is, that you can also specify different weights for every
   * operation to prefer special operations over others. This extension of the
   * Sellers edit distance is also known under the names: Needleman-Wunsch
   * distance.
   */
  class Sellers : public DynProg {
  public:

    /*
     * Document-method: initialize
     * call-seq: new(pattern)
     *
     * Creates a new Amatch::Sellers instance from <code>pattern</code>,
     * with all weights initially set to 1.0.
     */
    Sellers(const std::string pat);

    /*
     * Document-method: Sellers#match
     * call-seq: match(strings) -> results
     * 
     * Uses this Amatch::Sellers instance to match Sellers#pattern against
     * <code>strings</code>, while taking into account the given weights. It
     * returns the number of weighted character operations, the Sellers distance.
     * <code>strings</code> has to be either a String or an Array of Strings. The
     * returned <code>results</code> are either a Float or an Array of Floats
     * respectively.
     */
    Rice::Object match(Rice::Object arg);

    /*
     * Document-method: Sellers#similar
     * call-seq: similar(strings) -> results
     * 
     * Uses this Amatch::Sellers instance to match Amatch::Sellers#pattern
     * against <code>strings</code> (taking into account the given weights), and
     * compute a Sellers distance metric number between 0.0 for very unsimilar
     * strings and 1.0 for an exact match. <code>strings</code> has to be either a
     * String or an Array of Strings. The returned <code>results</code> are either
     * a Fixnum or an Array of Fixnums
     * respectively.
     */
    Rice::Object similar(Rice::Object arg);

    /*
     * Document-method: Sellers#search
     * call-seq: search(strings) -> results
     *
     * searches Sellers#pattern in <code>strings</code> and returns the edit
     * distance (the sum of weighted character operations) as a Float value, by
     * greedy trimming prefixes or postfixes of the match. <code>strings</code> has
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
