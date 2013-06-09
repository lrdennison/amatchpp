#ifndef __JARO_H__
#define __JARO_H__

#include <ctype.h>
#include "General.hpp"

namespace Amatchpp
{

  /*
   * Document-class: Amatchpp::Jaro < Amatchpp::General
   *
   * This class computes the Jaro metric for two strings.
   * The Jaro metric computes the similarity between 0 (no match)
   * and 1 (exact match) by looking for matching and transposed characters.
   */
  class Jaro : public General {
  public:

    /*
     * Document-method: initialize
     * call-seq: new(pattern)
     *
     * Creates a new Amatchpp::Jaro instance from <code>pattern</code>.
     */
    Jaro(const std::string pat);

    /*
     * Document-attr: ignore_case
     *
     * Ignore the case of the strings
     */
    CPP_DECL_RW_ATTR( bool, ignore_case)

    /*
     * Document-method: match
     * call-seq: match(strings) -> results
     *
     * Uses this Amatchpp::Jaro instance to match
     * Jaro#pattern against <code>strings</code>, that is compute the
     * jaro metric with the strings. <code>strings</code> has to be
     * either a String or an Array of Strings. The returned <code>results</code>
     * are either a Float or an Array of Floats respectively.
     */
    Rice::Object match(Rice::Object arg);

  protected:
    char *sa_ptr, *sb_ptr;

    double compute();

    double _match(const std::string &text);

    char *lowercase_string( const char *ptr, int len)
    {
      int i;
      char *s = ALLOC_N(char, len);
      MEMCPY(s, ptr, char, len);

      for (i = 0; i < len; i++) {
	if (islower(s[i])) s[i] = toupper(s[i]);
      }

      return s;
    }

    void lowercase_strings() {
      a_ptr = sa_ptr = lowercase_string( a_ptr, a_len);
      b_ptr = sb_ptr = lowercase_string( b_ptr, b_len);
    }

  };

}


#endif
