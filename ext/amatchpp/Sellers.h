#ifndef __SELLERS_H__
#define __SELLERS_H__

#include "General.h"

namespace Amatchpp
{

  class Sellers : public General {
  public:

    CPP_DECL_RW_ATTR( double, substitution)
    CPP_DECL_RW_ATTR( double, deletion)
    CPP_DECL_RW_ATTR( double, insertion)
    ;
    
  private:
    // Local variables
    const char *a_ptr, *b_ptr;
    int a_len, b_len;

    double *v[2];
    int  c, p;


  public:

    Sellers();

    Rice::Object match(Rice::Object arg);
    Rice::Object similar(Rice::Object arg);
    Rice::Object search(Rice::Object arg);

    void reset_weights();

  private:
    void setup(const std::string &text);
    void setup_v_deletion();
    void teardown();

    double max_weight();
    void compute();

    double _match(const std::string &text);
    double _similar(const std::string &text);
    double _search(const std::string &text);
    
  };

}


#endif
