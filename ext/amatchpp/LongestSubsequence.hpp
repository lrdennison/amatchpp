#ifndef __LongestSubsequence_H__
#define __Longestsubsequence_H__

#include "General.hpp"

namespace Amatchpp
{

  /* 
   * Document-class: Amatchpp::LongestSubsequence
   *
   *  This class computes the length of the longest subsequence common to two
   *  strings. A subsequence doesn't have to be contiguous. The longer the common
   *  subsequence is, the more similar the two strings will be.
   *
   *  The longest common subsequence between "test" and "test" is of length 4,
   *  because "test" itself is this subsequence. The longest common subsequence
   *  between "test" and "east" is "e", "s", "t" and the length of the
   *  sequence is 3.
   */
  class LongestSubsequence : public General {
  public:

    /*
     * Document-method: initialize
     * call-seq: new(pattern)
     *
     * Creates a new Amatchpp::LongestSubsequence instance from <code>pattern</code>.
     */
    LongestSubsequence(const std::string pat);

    /*
     * Document-method: match
     * call-seq: match(strings) -> results
     * 
     * Uses this Amatchpp::LongestSubsequence instance to match
     * LongestSubsequence#pattern against <code>strings</code>, that is compute the
     * length of the longest common subsequence. <code>strings</code> has to be
     * either a String or an Array of Strings. The returned <code>results</code>
     * are either a Fixnum or an Array of Fixnums respectively.
     */
    Rice::Object match(Rice::Object arg);

    /*
     * Document-method: similar
     * call-seq: similar(strings) -> results
     * 
     * Uses this Amatchpp::LongestSubsequence instance to match
     * Amatchpp::LongestSubsequence#pattern against <code>strings</code>, and compute
     * a longest substring distance metric number between 0.0 for very unsimilar
     * strings and 1.0 for an exact match. <code>strings</code> has to be either a
     * String or an Array of Strings. The returned <code>results</code> are either
     * a Fixnum or an Array of Fixnums
     */
    Rice::Object similar(Rice::Object arg);

  private:
    int compute();

    double _match(const std::string &text);
    double _similar(const std::string &text);
    
  };

}


#endif
