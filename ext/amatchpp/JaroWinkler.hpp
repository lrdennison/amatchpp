#ifndef __JAROWINKLER_H__
#define __JAROWINKLER_H__

#include <ctype.h>
#include "Jaro.hpp"

namespace Amatchpp
{

  /*
   * Document-class: Amatchpp::JaroWinkler
   *
   * This class computes the Jaro-Winkler metric for two strings.
   * The Jaro-Winkler metric computes the similarity between 0 (no match)
   * and 1 (exact match) by looking for matching and transposed characters.
   *
   * It is a variant of the Jaro metric, with additional weighting towards
   * common prefixes.
   */
  class JaroWinkler : public Jaro {
  public:

    /*
     * Document-method: initialize
     * call-seq: new(pattern)
     *
     * Creates a new Amatchpp::JaroWinkler instance from <code>pattern</code>.
     */
    JaroWinkler(const std::string pat);

    /*
     * Document-attr: scaling_factor
     *
     * The scaling factor is how much weight to give common prefixes.
     * Default is 0.1.
     */
    CPP_DECL_RW_ATTR( double, scaling_factor)

    /*
     * Document-method: match
     * call-seq: match(strings) -> results
     *
     * Uses this Amatchpp::JaroWinkler instance to match
     * JaroWinkler#pattern against <code>strings</code>, that is compute the
     * Jaro-Winkler metric with the strings. <code>strings</code> has to be
     * either a String or an Array of Strings. The returned <code>results</code>
     * are either a Float or an Array of Floats respectively.
     */
    Rice::Object match(Rice::Object arg);

  private:

    double _match(const std::string &text);


  };

}


#endif
