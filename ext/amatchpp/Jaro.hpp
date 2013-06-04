#ifndef __JARO_H__
#define __JARO_H__

#include <ctype.h>
#include "General.hpp"

namespace Amatchpp
{

  class Jaro : public General {
  public:

    Jaro(const std::string pat);

    CPP_DECL_RW_ATTR( bool, ignore_case)

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
