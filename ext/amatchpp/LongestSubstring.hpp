#ifndef __LONGESTSUBSTRING_H__
#define __LONGESTSUBSTRING_H__

#include "General.hpp"

namespace Amatchpp
{

  /* 
   * Document-class: Amatchpp::LongestSubstring
   *
   * The longest common substring is the longest substring, that is part of
   * two strings. A substring is contiguous, while a subsequence need not to
   * be. The longer the common substring is, the more similar the two strings
   * will be.
   *
   * The longest common substring between 'string' and 'string' is 'string'
   * again, thus the longest common substring length is 6. The longest common
   * substring between 'string' and 'storing' is 'ring', thus the longest common
   * substring length is 4. 
   */

  class LongestSubstring : public General {
  public:

    /*
     * Document-method: initialize
     * call-seq: new(pattern)
     *
     * Creates a new Amatchpp::LongestSubstring instance from <code>pattern</code>.
     */
    LongestSubstring(const std::string pat);

    /*
     * Document-method: match
     * call-seq: match(strings) -> results
     * 
     * Uses this Amatchpp::LongestSubstring instance to match
     * LongestSubstring#pattern against <code>strings</code>, that is compute the
     * length of the longest common substring. <code>strings</code> has to be
     * either a String or an Array of Strings. The returned <code>results</code>
     * are either a Fixnum or an Array of Fixnums respectively.
     */
    Rice::Object match(Rice::Object arg);

    /*
     * Document-method: similar
     * call-seq: similar(strings) -> results
     * 
     * Uses this Amatchpp::LongestSubstring instance to match
     * Amatchpp::LongestSubstring#pattern against <code>strings</code>, and compute a
     * longest substring distance metric number between 0.0 for very unsimilar
     * strings and 1.0 for an exact match. <code>strings</code> has to be either a
     * String or an Array of Strings. The returned <code>results</code> are either
     * a Fixnum or an Array of Fixnums
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
