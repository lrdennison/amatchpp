#ifndef __DYNAMICPROGRAMMING_H__
#define __DYNAMICPROGRAMMING_H__

#include "General.hpp"

namespace Amatchpp
{

  /*
   * Document-class: Amatchpp::DynProg < Amatchpp::General
   *
   * The base class for algorithms ( Sellers, Levenshtein) that are based up dynamic programming.
   *
   * This class will be enhanced.
   */

  class DynProg : public General {
  public:

    /*
     * Document-attr: substitution
     *
     * The weight of the substitution operation, that is used to compute
     * the Sellers distance. The <code>weight</code>
     * should be a Float value >= 0.0.
     */

    CPP_DECL_RW_ATTR( double, substitution)

    /*
     * Document-attr: deletion
     *
     * The weight of the deletion operation that is used to compute
     * the Sellers distance. The <code>weight</code>
     * should be a Float value >= 0.0.
     */
    CPP_DECL_RW_ATTR( double, deletion)

    /*
     * Document-attr: insertion
     *
     * The weight of the insertion operation that is used to compute
     * the Sellers distance. The <code>weight</code>
     * should be a Float value >= 0.0.
     */
    CPP_DECL_RW_ATTR( double, insertion)
    ;
    
    /*
     * Document-attr: start_pos
     *
     * Within the text, the starting position of pattern after a search
     */
    CPP_DECL_RW_ATTR( int, start_pos)

    /*
     * Document-attr: end_pos
     *
     * Within the text, the position of the first character after the pattern
     */
    CPP_DECL_RW_ATTR( int, end_pos)

    ;
    
    /*
     * Document-attr: edit_cmd
     *
     * The edit command used to transform text (or a substring of the text)
     * into the pattern
     */
    CPP_DECL_RW_ATTR( std::string, edit_cmd)

    int rows_allocated;
    double **v;
    double *v_store;

    char **step;
    char *step_store;
    enum {eqv=0x1, sub=0x2, ins=0x4, del=0x8};
    
    int  c, p;

    inline void set_c_p( int row)
    {
      c = row % rows_allocated;
      p = ((rows_allocated-1) + row) % rows_allocated;
    }

    /*
     * Document-method: initialize
     * call-seq: new(pattern)
     *
     * Creates a new Amatchpp::DynProg instance from <code>pattern</code>,
     * with all weights initially set to 1.0.
     */
    DynProg(const std::string pat);
    virtual ~DynProg();

    void compute();

    void backtrace(int i,int j, int num_steps=0);

    /*
     * Document-method: reset_weights
     * call-seq: reset_weights
     *
     * Resets all weights (substitution, deletion, and insertion) to 1.0.
     */
    void reset_weights();

    double max_weight();

    void setup(const std::string &text);
    void setup_v_deletion();
    void teardown();

    
  };

}


#endif
