#ifndef SATGALAXY_CADICAL_H
#define SATGALAXY_CADICAL_H
#include <stdint.h>
//=================================================================================================

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CaDiCaLSolver CaDiCaLSolver;
CaDiCaLSolver *cadical_new_solver ();
const char *cadical_error_message(int code);
int cadical_error(CaDiCaLSolver *solver);
void cadical_add_clause (CaDiCaLSolver *solver, const int ps[],
                         unsigned long length);
void cadical_add_empty_clause (CaDiCaLSolver *solver);
// This function can be used to check if the formula is already
// inconsistent (contains the empty clause or was proven to be
// root-level unsatisfiable).
void cadical_add (CaDiCaLSolver *, int lit);
/// @brief Assume valid non zero literal for next call to 'solve'. These
/// assumptions are reset after the call to 'solve' as well as after
///returning from 'simplify' and 'lookahead.
/// @param s Pointer to CaDiCaLSolver instance
/// @param lit Literal to assume
void cadical_assume (CaDiCaLSolver *, int lit);
/// @brief Solve formula.
/// @param s Pointer to CaDiCaLSolver instance
/// @return 10 for sat, 20 for unsat, 30 for unkown
int cadical_solve (CaDiCaLSolver *);
/// @brief Get value of literal.
/// @param s Pointer to CaDiCaLSolver instance
/// @param lit Literal to get value
/// @return (-lit=false, lit=true)
int cadical_val (CaDiCaLSolver *, int lit);
/// @brief Determine whether the valid non-zero literal is in the core.
/// @param s Pointer to CaDiCaLSolver instance
/// @param lit Literal to get failed
/// @return bool value, Returns '1' if the literal is in the core and '0' otherwise.
int cadical_failed (CaDiCaLSolver *, int lit);
/// @brief Add call-back which is checked regularly for termination if terminate is nonull
/// @param s Pointer to CaDiCaLSolver instance
/// @param state Pointer to state
/// @param terminate Pointer to termination function
void cadical_set_terminate (CaDiCaLSolver *, void *state,
                             int (*terminate) (void *state));

/// @brief Add call-back which is called when a new clause is learned.
/// @param s Pointer to CaDiCaLSolver instance
/// @param state Pointer to state
/// @param max_length Maximum length of learned clause
/// @param learn Pointer to learn function
void cadical_set_learn (CaDiCaLSolver *, void *state, int max_length,
                         void (*learn) (void *state, int *clause));

/*------------------------------------------------------------------------*/

// Non-IPASIR conformant 'C' functions.


/// @brief dds a literal to the constraint clause. Same functionality as 'add'
/// but the clause only exists for the next call to solve (same lifetime as
/// assumptions). Only one constraint may exists at a time. A new
/// constraint replaces the old. The main application of this functionality
/// is the model checking algorithm IC3. See our FMCAD'21 paper
/// [FroleyksBiere-FMCAD'19] for more details.
/// @param s Pointer to CaDiCaLSolver instance
/// @param lit Literal to constrain
void cadical_constrain (CaDiCaLSolver *, int lit);
/// @brief Determine whether the constraint was used to proof the
/// unsatisfiability.
/// @note Note that the formula might still be unsatisfiable
/// without the constraint.
/// @param  
/// @return bool value 
int cadical_constraint_failed (CaDiCaLSolver *);
/// @brief Set option.
/// @param s Pointer to CaDiCaLSolver instance
/// @param name Name of option
/// @param val Value of option
/// @return boolean value
int cadical_set_option (CaDiCaLSolver *, const char *name, int val);
/// @brief Specify search limits. 
/// @param s Pointer to CaDiCaLSolver instance
/// @param name  can be "conflicts", "decisions", "preprocessing", or "localsearch"
/// @param limit Value of limit
/// @return boolean value
int cadical_limit (CaDiCaLSolver *, const char *name, int limit);
/// @brief Get the current value of the option 
/// @param  
/// @param name 
/// @return 
int cadical_get_option (CaDiCaLSolver *, const char *name);
/// @brief print statistics 
/// @param  
/// @return 
void  cadical_print_statistics (CaDiCaLSolver *);
/// @brief The number of currently active variables and clauses can be queried by
/// these functions. Variables become active if a clause is added with it.
/// They become inactive if they are eliminated or fixed at the root level
// Clauses become inactive if they are satisfied, subsumed, eliminated.
/// Redundant clauses are reduced regularly and thus the 'redundant'
// function is less useful.
/// @param  
/// @return 
int64_t cadical_active (CaDiCaLSolver *);

/// @brief The number of currently irredundant clauses can be queried by this function.
/// @param  
/// @return 
int64_t cadical_irredundant (CaDiCaLSolver *);
/// @brief Root level assigned variables can be queried with this function.
/// @param s Pointer to CaDiCaLSolver instance
/// @param lit Literal to get fixed
/// @return  '1' if the literal is implied by the formula, '-1' if its
// negation is implied, or '0' if this is unclear at this point.
int cadical_fixed (CaDiCaLSolver *, int lit);
// int cadical_trace_proof (CaDiCaLSolver *, FILE *, const char *);
// void cadical_close_proof (CaDiCaLSolver *);
void cadical_conclude (CaDiCaLSolver *);
/// @brief Force termination of 'solve' asynchronously.
/// @param  
void cadical_terminate (CaDiCaLSolver *);
/// @brief 
/// @param  
/// @param lit 
void cadical_freeze (CaDiCaLSolver *, int lit);
/// @brief See our SAT'19 paper [FazekasBiereScholl-SAT'19] for more details.
/// @param  
/// @param lit 
/// @return 
int cadical_frozen (CaDiCaLSolver *, int lit);
void cadical_melt (CaDiCaLSolver *, int lit);
/// @briefThis function executes the given number of preprocessing rounds. It is
/// similar to 'solve' with 'limits ("preprocessing", rounds)' except that
/// no CDCL nor local search, nor lucky phases are executed.
/// @param  
/// @return  10=SATISFIABLE, 20=UNSATISFIABLE, 30=UNKNOWN,.

int cadical_simplify (CaDiCaLSolver *);




/// @brief Allocate clauses in arena
/// @param s Pointer to CaDiCaLSolver instance
/// @param arena Boolean value
/// @return boolean value
int cadical_set_opt_arena(CaDiCaLSolver *s, int arena);

/// @brief Keep clauses compact
/// @param s Pointer to CaDiCaLSolver instance
/// @param arenacompact Boolean value
/// @return boolean value
int cadical_set_opt_arenacompact(CaDiCaLSolver *s, int arenacompact);

/// @brief Sort clauses in arena
/// @param s Pointer to CaDiCaLSolver instance
/// @param arenasort Boolean value
/// @return boolean value
int cadical_set_opt_arenasort(CaDiCaLSolver *s, int arenasort);

/// @brief Set arena type (1=clause, 2=var, 3=queue)
/// @param s Pointer to CaDiCaLSolver instance
/// @param arenatype Integer value (1 to 3)
/// @return boolean value
int cadical_set_opt_arenatype(CaDiCaLSolver *s, int arenatype);

/// @brief Use binary proof format
/// @param s Pointer to CaDiCaLSolver instance
/// @param binary Boolean value
/// @return boolean value
int cadical_set_opt_binary(CaDiCaLSolver *s, int binary);

/// @brief Enable blocked clause elimination
/// @param s Pointer to CaDiCaLSolver instance
/// @param block Boolean value
/// @return boolean value
int cadical_set_opt_block(CaDiCaLSolver *s, int block);

/// @brief Set maximum clause size for blocked clause elimination
/// @param s Pointer to CaDiCaLSolver instance
/// @param blockmaxclslim Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_blockmaxclslim(CaDiCaLSolver *s, int blockmaxclslim);

/// @brief Set minimum clause size for blocked clause elimination
/// @param s Pointer to CaDiCaLSolver instance
/// @param blockminclslim Integer value (2 to 2e9)
/// @return boolean value
int cadical_set_opt_blockminclslim(CaDiCaLSolver *s, int blockminclslim);

/// @brief Set occurrence limit for blocked clause elimination
/// @param s Pointer to CaDiCaLSolver instance
/// @param blockocclim Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_blockocclim(CaDiCaLSolver *s, int blockocclim);

/// @brief Bump variables
/// @param s Pointer to CaDiCaLSolver instance
/// @param bump Boolean value
/// @return boolean value
int cadical_set_opt_bump(CaDiCaLSolver *s, int bump);

/// @brief Bump reason literals too
/// @param s Pointer to CaDiCaLSolver instance
/// @param bumpreason Boolean value
/// @return boolean value
int cadical_set_opt_bumpreason(CaDiCaLSolver *s, int bumpreason);

/// @brief Set bump reason depth
/// @param s Pointer to CaDiCaLSolver instance
/// @param bumpreasondepth Integer value (1 to 3)
/// @return boolean value
int cadical_set_opt_bumpreasondepth(CaDiCaLSolver *s, int bumpreasondepth);

/// @brief Enable internal checking
/// @param s Pointer to CaDiCaLSolver instance
/// @param check Boolean value
/// @return boolean value
int cadical_set_opt_check(CaDiCaLSolver *s, int check);

/// @brief Check assumptions satisfied
/// @param s Pointer to CaDiCaLSolver instance
/// @param checkassumptions Boolean value
/// @return boolean value
int cadical_set_opt_checkassumptions(CaDiCaLSolver *s, int checkassumptions);

/// @brief Check constraint satisfied
/// @param s Pointer to CaDiCaLSolver instance
/// @param checkconstraint Boolean value
/// @return boolean value
int cadical_set_opt_checkconstraint(CaDiCaLSolver *s, int checkconstraint);

/// @brief Check failed literals form core
/// @param s Pointer to CaDiCaLSolver instance
/// @param checkfailed Boolean value
/// @return boolean value
int cadical_set_opt_checkfailed(CaDiCaLSolver *s, int checkfailed);

/// @brief Check all frozen semantics
/// @param s Pointer to CaDiCaLSolver instance
/// @param checkfrozen Boolean value
/// @return boolean value
int cadical_set_opt_checkfrozen(CaDiCaLSolver *s, int checkfrozen);

/// @brief Set proof checking mode (1=drat, 2=lrat, 3=both)
/// @param s Pointer to CaDiCaLSolver instance
/// @param checkproof Integer value (0 to 3)
/// @return boolean value
int cadical_set_opt_checkproof(CaDiCaLSolver *s, int checkproof);

/// @brief Check witness internally
/// @param s Pointer to CaDiCaLSolver instance
/// @param checkwitness Boolean value
/// @return boolean value
int cadical_set_opt_checkwitness(CaDiCaLSolver *s, int checkwitness);

/// @brief Set chronological backtracking mode
/// @param s Pointer to CaDiCaLSolver instance
/// @param chrono Integer value (0 to 2)
/// @return boolean value
int cadical_set_opt_chrono(CaDiCaLSolver *s, int chrono);

/// @brief Force always chronological backtracking
/// @param s Pointer to CaDiCaLSolver instance
/// @param chronoalways Boolean value
/// @return boolean value
int cadical_set_opt_chronoalways(CaDiCaLSolver *s, int chronoalways);

/// @brief Set chronological level limit
/// @param s Pointer to CaDiCaLSolver instance
/// @param chronolevelim Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_chronolevelim(CaDiCaLSolver *s, int chronolevelim);

/// @brief Reuse trail chronologically
/// @param s Pointer to CaDiCaLSolver instance
/// @param chronoreusetrail Boolean value
/// @return boolean value
int cadical_set_opt_chronoreusetrail(CaDiCaLSolver *s, int chronoreusetrail);

/// @brief Compact internal variables
/// @param s Pointer to CaDiCaLSolver instance
/// @param compact Boolean value
/// @return boolean value
int cadical_set_opt_compact(CaDiCaLSolver *s, int compact);

/// @brief Set compacting interval
/// @param s Pointer to CaDiCaLSolver instance
/// @param compactint Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_compactint(CaDiCaLSolver *s, int compactint);

/// @brief Set inactive limit per mille
/// @param s Pointer to CaDiCaLSolver instance
/// @param compactlim Integer value (0 to 1e3)
/// @return boolean value
int cadical_set_opt_compactlim(CaDiCaLSolver *s, int compactlim);

/// @brief Set minimum inactive limit
/// @param s Pointer to CaDiCaLSolver instance
/// @param compactmin Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_compactmin(CaDiCaLSolver *s, int compactmin);

/// @brief Enable globally blocked clause elimination
/// @param s Pointer to CaDiCaLSolver instance
/// @param condition Boolean value
/// @return boolean value
int cadical_set_opt_condition(CaDiCaLSolver *s, int condition);

/// @brief Set initial conflict interval for condition
/// @param s Pointer to CaDiCaLSolver instance
/// @param conditionint Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_conditionint(CaDiCaLSolver *s, int conditionint);

/// @brief Set maximum condition efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param conditionmaxeff Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_conditionmaxeff(CaDiCaLSolver *s, int conditionmaxeff);

/// @brief Set maximum clause variable ratio
/// @param s Pointer to CaDiCaLSolver instance
/// @param conditionmaxrat Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_conditionmaxrat(CaDiCaLSolver *s, int conditionmaxrat);

/// @brief Set minimum condition efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param conditionmineff Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_conditionmineff(CaDiCaLSolver *s, int conditionmineff);

/// @brief Set relative efficiency per mille for condition
/// @param s Pointer to CaDiCaLSolver instance
/// @param conditionreleff Integer value (1 to 1e5)
/// @return boolean value
int cadical_set_opt_conditionreleff(CaDiCaLSolver *s, int conditionreleff);

/// @brief Enable covered clause elimination
/// @param s Pointer to CaDiCaLSolver instance
/// @param cover Boolean value
/// @return boolean value
int cadical_set_opt_cover(CaDiCaLSolver *s, int cover);

/// @brief Set maximum clause size for cover
/// @param s Pointer to CaDiCaLSolver instance
/// @param covermaxclslim Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_covermaxclslim(CaDiCaLSolver *s, int covermaxclslim);

/// @brief Set maximum cover efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param covermaxeff Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_covermaxeff(CaDiCaLSolver *s, int covermaxeff);

/// @brief Set minimum clause size for cover
/// @param s Pointer to CaDiCaLSolver instance
/// @param coverminclslim Integer value (2 to 2e9)
/// @return boolean value
int cadical_set_opt_coverminclslim(CaDiCaLSolver *s, int coverminclslim);

/// @brief Set minimum cover efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param covermineff Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_covermineff(CaDiCaLSolver *s, int covermineff);

/// @brief Set relative efficiency per mille for cover
/// @param s Pointer to CaDiCaLSolver instance
/// @param coverreleff Integer value (1 to 1e5)
/// @return boolean value
int cadical_set_opt_coverreleff(CaDiCaLSolver *s, int coverreleff);

/// @brief Decompose BIG in SCCs and ELS
/// @param s Pointer to CaDiCaLSolver instance
/// @param decompose Boolean value
/// @return boolean value
int cadical_set_opt_decompose(CaDiCaLSolver *s, int decompose);

/// @brief Set number of decompose rounds
/// @param s Pointer to CaDiCaLSolver instance
/// @param decomposerounds Integer value (1 to 16)
/// @return boolean value
int cadical_set_opt_decomposerounds(CaDiCaLSolver *s, int decomposerounds);

/// @brief Remove duplicated binaries
/// @param s Pointer to CaDiCaLSolver instance
/// @param deduplicate Boolean value
/// @return boolean value
int cadical_set_opt_deduplicate(CaDiCaLSolver *s, int deduplicate);

/// @brief Subsume recently learned clauses
/// @param s Pointer to CaDiCaLSolver instance
/// @param eagersubsume Boolean value
/// @return boolean value
int cadical_set_opt_eagersubsume(CaDiCaLSolver *s, int eagersubsume);

/// @brief Set limit on subsumed candidates
/// @param s Pointer to CaDiCaLSolver instance
/// @param eagersubsumelim Integer value (1 to 1e3)
/// @return boolean value
int cadical_set_opt_eagersubsumelim(CaDiCaLSolver *s, int eagersubsumelim);

/// @brief Enable bounded variable elimination
/// @param s Pointer to CaDiCaLSolver instance
/// @param elim Boolean value
/// @return boolean value
int cadical_set_opt_elim(CaDiCaLSolver *s, int elim);

/// @brief Find AND gates
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimands Boolean value
/// @return boolean value
int cadical_set_opt_elimands(CaDiCaLSolver *s, int elimands);

/// @brief Set maximum elimination efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimaxeff Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_elimaxeff(CaDiCaLSolver *s, int elimaxeff);

/// @brief Enable eager backward subsumption
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimbackward Boolean value
/// @return boolean value
int cadical_set_opt_elimbackward(CaDiCaLSolver *s, int elimbackward);

/// @brief Set maximum elimination bound
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimboundmax Integer value (-1 to 2e6)
/// @return boolean value
int cadical_set_opt_elimboundmax(CaDiCaLSolver *s, int elimboundmax);

/// @brief Set minimum elimination bound
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimboundmin Integer value (-1 to 2e6)
/// @return boolean value
int cadical_set_opt_elimboundmin(CaDiCaLSolver *s, int elimboundmin);

/// @brief Set resolvent size limit
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimclslim Integer value (2 to 2e9)
/// @return boolean value
int cadical_set_opt_elimclslim(CaDiCaLSolver *s, int elimclslim);

/// @brief Find equivalence gates
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimequivs Boolean value
/// @return boolean value
int cadical_set_opt_elimequivs(CaDiCaLSolver *s, int elimequivs);

/// @brief Set minimum elimination efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimineff Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_elimineff(CaDiCaLSolver *s, int elimineff);

/// @brief Set elimination interval
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimint Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_elimint(CaDiCaLSolver *s, int elimint);

/// @brief Find if-then-else gates
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimites Boolean value
/// @return boolean value
int cadical_set_opt_elimites(CaDiCaLSolver *s, int elimites);

/// @brief Limit resolutions
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimlimited Boolean value
/// @return boolean value
int cadical_set_opt_elimlimited(CaDiCaLSolver *s, int elimlimited);

/// @brief Set occurrence limit for elimination
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimocclim Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_elimocclim(CaDiCaLSolver *s, int elimocclim);

/// @brief Set elimination score product weight
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimprod Integer value (0 to 1e4)
/// @return boolean value
int cadical_set_opt_elimprod(CaDiCaLSolver *s, int elimprod);

/// @brief Set relative efficiency per mille for elimination
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimreleff Integer value (1 to 1e5)
/// @return boolean value
int cadical_set_opt_elimreleff(CaDiCaLSolver *s, int elimreleff);

/// @brief Set usual number of elimination rounds
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimrounds Integer value (1 to 512)
/// @return boolean value
int cadical_set_opt_elimrounds(CaDiCaLSolver *s, int elimrounds);

/// @brief Enable elimination by substitution
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimsubst Boolean value
/// @return boolean value
int cadical_set_opt_elimsubst(CaDiCaLSolver *s, int elimsubst);

/// @brief Set elimination score sum weight
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimsum Integer value (0 to 1e4)
/// @return boolean value
int cadical_set_opt_elimsum(CaDiCaLSolver *s, int elimsum);

/// @brief Set maximum XOR size
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimxorlim Integer value (2 to 27)
/// @return boolean value
int cadical_set_opt_elimxorlim(CaDiCaLSolver *s, int elimxorlim);

/// @brief Find XOR gates
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimxors Boolean value
/// @return boolean value
int cadical_set_opt_elimxors(CaDiCaLSolver *s, int elimxors);

/// @brief Set window fast glue
/// @param s Pointer to CaDiCaLSolver instance
/// @param emagluefast Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_emagluefast(CaDiCaLSolver *s, int emagluefast);

/// @brief Set window slow glue
/// @param s Pointer to CaDiCaLSolver instance
/// @param emaglueslow Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_emaglueslow(CaDiCaLSolver *s, int emaglueslow);

/// @brief Set window back-jump level
/// @param s Pointer to CaDiCaLSolver instance
/// @param emajump Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_emajump(CaDiCaLSolver *s, int emajump);

/// @brief Set window back-track level
/// @param s Pointer to CaDiCaLSolver instance
/// @param emalevel Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_emalevel(CaDiCaLSolver *s, int emalevel);

/// @brief Set window learned clause size
/// @param s Pointer to CaDiCaLSolver instance
/// @param emasize Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_emasize(CaDiCaLSolver *s, int emasize);

/// @brief Set window fast trail
/// @param s Pointer to CaDiCaLSolver instance
/// @param ematrailfast Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_ematrailfast(CaDiCaLSolver *s, int ematrailfast);

/// @brief Set window slow trail
/// @param s Pointer to CaDiCaLSolver instance
/// @param ematrailslow Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_ematrailslow(CaDiCaLSolver *s, int ematrailslow);

/// @brief Eagerly ask for all reasons (0: only when needed)
/// @param s Pointer to CaDiCaLSolver instance
/// @param exteagerreasons Boolean value
/// @return boolean value
int cadical_set_opt_exteagerreasons(CaDiCaLSolver *s, int exteagerreasons);

/// @brief Recalculate all levels after eagerly asking for reasons (0: trust the external tool)
/// @param s Pointer to CaDiCaLSolver instance
/// @param exteagerrecalc Boolean value
/// @return boolean value
int cadical_set_opt_exteagerrecalc(CaDiCaLSolver *s, int exteagerrecalc);

/// @brief Enable external LRAT
/// @param s Pointer to CaDiCaLSolver instance
/// @param externallrat Boolean value
/// @return boolean value
int cadical_set_opt_externallrat(CaDiCaLSolver *s, int externallrat);

/// @brief Flush redundant clauses
/// @param s Pointer to CaDiCaLSolver instance
/// @param flush Boolean value
/// @return boolean value
int cadical_set_opt_flush(CaDiCaLSolver *s, int flush);

/// @brief Set interval increase for flushing
/// @param s Pointer to CaDiCaLSolver instance
/// @param flushfactor Integer value (1 to 1e3)
/// @return boolean value
int cadical_set_opt_flushfactor(CaDiCaLSolver *s, int flushfactor);

/// @brief Set initial limit for flushing
/// @param s Pointer to CaDiCaLSolver instance
/// @param flushint Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_flushint(CaDiCaLSolver *s, int flushint);

/// @brief Always use initial phase
/// @param s Pointer to CaDiCaLSolver instance
/// @param forcephase Boolean value
/// @return boolean value
int cadical_set_opt_forcephase(CaDiCaLSolver *s, int forcephase);

/// @brief Set FRAT proof format (1=frat(lrat), 2=frat(drat))
/// @param s Pointer to CaDiCaLSolver instance
/// @param frat Integer value (0 to 2)
/// @return boolean value
int cadical_set_opt_frat(CaDiCaLSolver *s, int frat);

/// @brief Use incremental proof format
/// @param s Pointer to CaDiCaLSolver instance
/// @param idrup Boolean value
/// @return boolean value
int cadical_set_opt_idrup(CaDiCaLSolver *s, int idrup);

/// @brief Enable ILB (incremental lazy backtrack)
/// @param s Pointer to CaDiCaLSolver instance
/// @param ilb Boolean value
/// @return boolean value
int cadical_set_opt_ilb(CaDiCaLSolver *s, int ilb);

/// @brief Enable trail reuse for assumptions (ILB-like)
/// @param s Pointer to CaDiCaLSolver instance
/// @param ilbassumptions Boolean value
/// @return boolean value
int cadical_set_opt_ilbassumptions(CaDiCaLSolver *s, int ilbassumptions);

/// @brief Enable inprocessing
/// @param s Pointer to CaDiCaLSolver instance
/// @param inprocessing Boolean value
/// @return boolean value
int cadical_set_opt_inprocessing(CaDiCaLSolver *s, int inprocessing);

/// @brief Enable variable instantiation
/// @param s Pointer to CaDiCaLSolver instance
/// @param instantiate Boolean value
/// @return boolean value
int cadical_set_opt_instantiate(CaDiCaLSolver *s, int instantiate);

/// @brief Set minimum clause size for instantiation
/// @param s Pointer to CaDiCaLSolver instance
/// @param instantiateclslim Integer value (2 to 2e9)
/// @return boolean value
int cadical_set_opt_instantiateclslim(CaDiCaLSolver *s, int instantiateclslim);

/// @brief Set maximum occurrence limit for instantiation
/// @param s Pointer to CaDiCaLSolver instance
/// @param instantiateocclim Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_instantiateocclim(CaDiCaLSolver *s, int instantiateocclim);

/// @brief Instantiate each clause once
/// @param s Pointer to CaDiCaLSolver instance
/// @param instantiateonce Boolean value
/// @return boolean value
int cadical_set_opt_instantiateonce(CaDiCaLSolver *s, int instantiateonce);

/// @brief Use linear incremental proof format
/// @param s Pointer to CaDiCaLSolver instance
/// @param lidrup Boolean value
/// @return boolean value
int cadical_set_opt_lidrup(CaDiCaLSolver *s, int lidrup);

/// @brief Enable logging
/// @param s Pointer to CaDiCaLSolver instance
/// @param log Boolean value
/// @return boolean value
int cadical_set_opt_log(CaDiCaLSolver *s, int log);

/// @brief Sort logged clauses
/// @param s Pointer to CaDiCaLSolver instance
/// @param logsort Boolean value
/// @return boolean value
int cadical_set_opt_logsort(CaDiCaLSolver *s, int logsort);

/// @brief Use LRAT proof format
/// @param s Pointer to CaDiCaLSolver instance
/// @param lrat Boolean value
/// @return boolean value
int cadical_set_opt_lrat(CaDiCaLSolver *s, int lrat);

/// @brief Search for lucky phases
/// @param s Pointer to CaDiCaLSolver instance
/// @param lucky Boolean value
/// @return boolean value
int cadical_set_opt_lucky(CaDiCaLSolver *s, int lucky);

/// @brief Minimize learned clauses
/// @param s Pointer to CaDiCaLSolver instance
/// @param minimize Boolean value
/// @return boolean value
int cadical_set_opt_minimize(CaDiCaLSolver *s, int minimize);

/// @brief Set minimization depth
/// @param s Pointer to CaDiCaLSolver instance
/// @param minimizedepth Integer value (0 to 1e3)
/// @return boolean value
int cadical_set_opt_minimizedepth(CaDiCaLSolver *s, int minimizedepth);

/// @brief Enable on-the-fly self subsumption
/// @param s Pointer to CaDiCaLSolver instance
/// @param otfs Boolean value
/// @return boolean value
int cadical_set_opt_otfs(CaDiCaLSolver *s, int otfs);

/// @brief Set initial phase
/// @param s Pointer to CaDiCaLSolver instance
/// @param phase Boolean value
/// @return boolean value
int cadical_set_opt_phase(CaDiCaLSolver *s, int phase);

/// @brief Enable failed literal probing
/// @param s Pointer to CaDiCaLSolver instance
/// @param probe Boolean value
/// @return boolean value
int cadical_set_opt_probe(CaDiCaLSolver *s, int probe);

/// @brief Learn hyper binary clauses
/// @param s Pointer to CaDiCaLSolver instance
/// @param probehbr Boolean value
/// @return boolean value
int cadical_set_opt_probehbr(CaDiCaLSolver *s, int probehbr);

/// @brief Set probing interval
/// @param s Pointer to CaDiCaLSolver instance
/// @param probeint Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_probeint(CaDiCaLSolver *s, int probeint);

/// @brief Set maximum probing efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param probemaxeff Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_probemaxeff(CaDiCaLSolver *s, int probemaxeff);

/// @brief Set minimum probing efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param probemineff Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_probemineff(CaDiCaLSolver *s, int probemineff);

/// @brief Set relative efficiency per mille for probing
/// @param s Pointer to CaDiCaLSolver instance
/// @param probereleff Integer value (1 to 1e5)
/// @return boolean value
int cadical_set_opt_probereleff(CaDiCaLSolver *s, int probereleff);

/// @brief Set probing rounds
/// @param s Pointer to CaDiCaLSolver instance
/// @param proberounds Integer value (1 to 16)
/// @return boolean value
int cadical_set_opt_proberounds(CaDiCaLSolver *s, int proberounds);

/// @brief Set profiling level
/// @param s Pointer to CaDiCaLSolver instance
/// @param profile Integer value (0 to 4)
/// @return boolean value
int cadical_set_opt_profile(CaDiCaLSolver *s, int profile);

/// @brief Disable all messages
/// @param s Pointer to CaDiCaLSolver instance
/// @param quiet Boolean value
/// @return boolean value
int cadical_set_opt_quiet(CaDiCaLSolver *s, int quiet);

/// @brief Set radix sort limit
/// @param s Pointer to CaDiCaLSolver instance
/// @param radixsortlim Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_radixsortlim(CaDiCaLSolver *s, int radixsortlim);

/// @brief Use real instead of process time
/// @param s Pointer to CaDiCaLSolver instance
/// @param realtime Boolean value
/// @return boolean value
int cadical_set_opt_realtime(CaDiCaLSolver *s, int realtime);

/// @brief Reduce useless clauses
/// @param s Pointer to CaDiCaLSolver instance
/// @param reduce Boolean value
/// @return boolean value
int cadical_set_opt_reduce(CaDiCaLSolver *s, int reduce);

/// @brief Set reduce interval
/// @param s Pointer to CaDiCaLSolver instance
/// @param reduceint Integer value (10 to 1e6)
/// @return boolean value
int cadical_set_opt_reduceint(CaDiCaLSolver *s, int reduceint);

/// @brief Set reduce fraction in percent
/// @param s Pointer to CaDiCaLSolver instance
/// @param reducetarget Integer value (10 to 1e2)
/// @return boolean value
int cadical_set_opt_reducetarget(CaDiCaLSolver *s, int reducetarget);

/// @brief Set glue of kept learned clauses
/// @param s Pointer to CaDiCaLSolver instance
/// @param reducetier1glue Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_reducetier1glue(CaDiCaLSolver *s, int reducetier1glue);

/// @brief Set glue of tier two clauses
/// @param s Pointer to CaDiCaLSolver instance
/// @param reducetier2glue Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_reducetier2glue(CaDiCaLSolver *s, int reducetier2glue);

/// @brief Set reluctant doubling period
/// @param s Pointer to CaDiCaLSolver instance
/// @param reluctant Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_reluctant(CaDiCaLSolver *s, int reluctant);

/// @brief Set maximum reluctant doubling period
/// @param s Pointer to CaDiCaLSolver instance
/// @param reluctantmax Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_reluctantmax(CaDiCaLSolver *s, int reluctantmax);

/// @brief Enable resetting phase
/// @param s Pointer to CaDiCaLSolver instance
/// @param rephase Boolean value
/// @return boolean value
int cadical_set_opt_rephase(CaDiCaLSolver *s, int rephase);

/// @brief Set rephase interval
/// @param s Pointer to CaDiCaLSolver instance
/// @param rephaseint Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_rephaseint(CaDiCaLSolver *s, int rephaseint);

/// @brief Enable reporting
/// @param s Pointer to CaDiCaLSolver instance
/// @param report Boolean value
/// @return boolean value
int cadical_set_opt_report(CaDiCaLSolver *s, int report);

/// @brief Report even if not successful
/// @param s Pointer to CaDiCaLSolver instance
/// @param reportall Boolean value
/// @return boolean value
int cadical_set_opt_reportall(CaDiCaLSolver *s, int reportall);

/// @brief Use solving not process time for reporting
/// @param s Pointer to CaDiCaLSolver instance
/// @param reportsolve Boolean value
/// @return boolean value
int cadical_set_opt_reportsolve(CaDiCaLSolver *s, int reportsolve);

/// @brief Enable restarts
/// @param s Pointer to CaDiCaLSolver instance
/// @param restart Boolean value
/// @return boolean value
int cadical_set_opt_restart(CaDiCaLSolver *s, int restart);

/// @brief Set restart interval
/// @param s Pointer to CaDiCaLSolver instance
/// @param restartint Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_restartint(CaDiCaLSolver *s, int restartint);

/// @brief Set slow fast margin in percent
/// @param s Pointer to CaDiCaLSolver instance
/// @param restartmargin Integer value (0 to 1e2)
/// @return boolean value
int cadical_set_opt_restartmargin(CaDiCaLSolver *s, int restartmargin);

/// @brief Enable trail reuse
/// @param s Pointer to CaDiCaLSolver instance
/// @param restartreusetrail Boolean value
/// @return boolean value
int cadical_set_opt_restartreusetrail(CaDiCaLSolver *s, int restartreusetrail);

/// @brief Restore all clauses (2=really)
/// @param s Pointer to CaDiCaLSolver instance
/// @param restoreall Integer value (0 to 2)
/// @return boolean value
int cadical_set_opt_restoreall(CaDiCaLSolver *s, int restoreall);

/// @brief Remove satisfied clauses
/// @param s Pointer to CaDiCaLSolver * instance
/// @param restoreflush Boolean value
/// @return boolean value
int cadical_set_opt_restoreflush(CaDiCaLSolver *s, int restoreflush);

/// @brief Reverse variable ordering
/// @param s Pointer to CaDiCaLSolver instance
/// @param reverse Boolean value
/// @return boolean value
int cadical_set_opt_reverse(CaDiCaLSolver *s, int reverse);

/// @brief Use EVSIDS scores
/// @param s Pointer to CaDiCaLSolver instance
/// @param score Boolean value
/// @return boolean value
int cadical_set_opt_score(CaDiCaLSolver *s, int score);

/// @brief Set score factor per mille
/// @param s Pointer to CaDiCaLSolver instance
/// @param scorefactor Integer value (500 to 1e3)
/// @return boolean value
int cadical_set_opt_scorefactor(CaDiCaLSolver *s, int scorefactor);

/// @brief Set random seed
/// @param s Pointer to CaDiCaLSolver instance
/// @param seed Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_seed(CaDiCaLSolver *s, int seed);

/// @brief Shrink conflict clause (1=only with binary, 2=minimize when pulling, 3=full)
/// @param s Pointer to CaDiCaLSolver instance
/// @param shrink Integer value (0 to 3)
/// @return boolean value
int cadical_set_opt_shrink(CaDiCaLSolver *s, int shrink);

/// @brief Use a reap for shrinking
/// @param s Pointer to CaDiCaLSolver instance
/// @param shrinkreap Boolean value
/// @return boolean value
int cadical_set_opt_shrinkreap(CaDiCaLSolver *s, int shrinkreap);

/// @brief Shuffle variables
/// @param s Pointer to CaDiCaLSolver instance
/// @param shuffle Boolean value
/// @return boolean value
int cadical_set_opt_shuffle(CaDiCaLSolver *s, int shuffle);

/// @brief Shuffle variable queue
/// @param s Pointer to CaDiCaLSolver instance
/// @param shufflequeue Boolean value
/// @return boolean value
int cadical_set_opt_shufflequeue(CaDiCaLSolver *s, int shufflequeue);

/// @brief Use random instead of reverse shuffling
/// @param s Pointer to CaDiCaLSolver instance
/// @param shufflerandom Boolean value
/// @return boolean value
int cadical_set_opt_shufflerandom(CaDiCaLSolver *s, int shufflerandom);

/// @brief Shuffle variable scores
/// @param s Pointer to CaDiCaLSolver instance
/// @param shufflescores Boolean value
/// @return boolean value
int cadical_set_opt_shufflescores(CaDiCaLSolver *s, int shufflescores);

/// @brief Enable stabilizing phases
/// @param s Pointer to CaDiCaLSolver instance
/// @param stabilize Boolean value
/// @return boolean value
int cadical_set_opt_stabilize(CaDiCaLSolver *s, int stabilize);

/// @brief Set phase increase in percent
/// @param s Pointer to CaDiCaLSolver instance
/// @param stabilizefactor Integer value (101 to 2e9)
/// @return boolean value
int cadical_set_opt_stabilizefactor(CaDiCaLSolver *s, int stabilizefactor);

/// @brief Set stabilizing interval
/// @param s Pointer to CaDiCaLSolver instance
/// @param stabilizeint Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_stabilizeint(CaDiCaLSolver *s, int stabilizeint);

/// @brief Set maximum stabilizing phase
/// @param s Pointer to CaDiCaLSolver instance
/// @param stabilizemaxint Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_stabilizemaxint(CaDiCaLSolver *s, int stabilizemaxint);

/// @brief Use only stabilizing phases
/// @param s Pointer to CaDiCaLSolver instance
/// @param stabilizeonly Boolean value
/// @return boolean value
int cadical_set_opt_stabilizeonly(CaDiCaLSolver *s, int stabilizeonly);

/// @brief Print all statistics at the end of the run
/// @param s Pointer to CaDiCaLSolver instance
/// @param stats Boolean value
/// @return boolean value
int cadical_set_opt_stats(CaDiCaLSolver *s, int stats);

/// @brief Enable clause subsumption
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsume Boolean value
/// @return boolean value
int cadical_set_opt_subsume(CaDiCaLSolver *s, int subsume);

/// @brief Set watch list length limit for subsumption
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsumebinlim Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_subsumebinlim(CaDiCaLSolver *s, int subsumebinlim);

/// @brief Set clause length limit for subsumption
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsumeclslim Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_subsumeclslim(CaDiCaLSolver *s, int subsumeclslim);

/// @brief Set subsume interval
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsumeint Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_subsumeint(CaDiCaLSolver *s, int subsumeint);

/// @brief Limit subsumption checks
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsumelimited Boolean value
/// @return boolean value
int cadical_set_opt_subsumelimited(CaDiCaLSolver *s, int subsumelimited);

/// @brief Set maximum subsuming efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsumemaxeff Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_subsumemaxeff(CaDiCaLSolver *s, int subsumemaxeff);

/// @brief Set minimum subsuming efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsumemineff Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_subsumemineff(CaDiCaLSolver *s, int subsumemineff);

/// @brief Set watch list length limit for subsumption
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsumeocclim Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_subsumeocclim(CaDiCaLSolver *s, int subsumeocclim);

/// @brief Set relative efficiency per mille for subsumption
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsumereleff Integer value erős (1 to 1e5)
/// @return boolean value
int cadical_set_opt_subsumereleff(CaDiCaLSolver *s, int subsumereleff);

/// @brief Strengthen during subsume
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsumestr Boolean value
/// @return boolean value
int cadical_set_opt_subsumestr(CaDiCaLSolver *s, int subsumestr);

/// @brief Set target phases (1=stable only)
/// @param s Pointer to CaDiCaLSolver instance
/// @param target Integer value (0 to 2)
/// @return boolean value
int cadical_set_opt_target(CaDiCaLSolver *s, int target);

/// @brief Set termination check interval
/// @param s Pointer to CaDiCaLSolver instance
/// @param terminateint Integer value (0 to 1e4)
/// @return boolean value
int cadical_set_opt_terminateint(CaDiCaLSolver *s, int terminateint);

/// @brief Enable hyper ternary resolution
/// @param s Pointer to CaDiCaLSolver instance
/// @param ternary Boolean value
/// @return boolean value
int cadical_set_opt_ternary(CaDiCaLSolver *s, int ternary);

/// @brief Set max clauses added in percent for ternary
/// @param s Pointer to CaDiCaLSolver instance
/// @param ternarymaxadd Integer value (0 to 1e4)
/// @return boolean value
int cadical_set_opt_ternarymaxadd(CaDiCaLSolver *s, int ternarymaxadd);

/// @brief Set ternary maximum efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param ternarymaxeff Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_ternarymaxeff(CaDiCaLSolver *s, int ternarymaxeff);

/// @brief Set minimum ternary efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param ternarymineff Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_ternarymineff(CaDiCaLSolver *s, int ternarymineff);

/// @brief Set ternary occurrence limit
/// @param s Pointer to CaDiCaLSolver instance
/// @param ternaryocclim Integer value (1 to 2e9)
/// @return boolean value
int cadical_set_opt_ternaryocclim(CaDiCaLSolver *s, int ternaryocclim);

/// @brief Set relative efficiency per mille for ternary
/// @param s Pointer to CaDiCaLSolver instance
/// @param ternaryreleff Integer value (1 to 1e5)
/// @return boolean value
int cadical_set_opt_ternaryreleff(CaDiCaLSolver *s, int ternaryreleff);

/// @brief Set maximum ternary rounds
/// @param s Pointer to CaDiCaLSolver instance
/// @param ternaryrounds Integer value (1 to 16)
/// @return boolean value
int cadical_set_opt_ternaryrounds(CaDiCaLSolver *s, int ternaryrounds);

/// @brief Enable transitive reduction of BIG
/// @param s Pointer to CaDiCaLSolver instance
/// @param transred Boolean value
/// @return boolean value
int cadical_set_opt_transred(CaDiCaLSolver *s, int transred);

/// @brief Set maximum efficiency for transitive reduction
/// @param s Pointer to CaDiCaLSolver instance
/// @param transredmaxeff Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_transredmaxeff(CaDiCaLSolver *s, int transredmaxeff);

/// @brief Set minimum efficiency for transitive reduction
/// @param s Pointer to CaDiCaLSolver instance
/// @param transredmineff Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_transredmineff(CaDiCaLSolver *s, int transredmineff);

/// @brief Set relative efficiency per mille for transitive reduction
/// @param s Pointer to CaDiCaLSolver instance
/// @param transredreleff Integer value (1 to 1e5)
/// @return boolean value
int cadical_set_opt_transredreleff(CaDiCaLSolver *s, int transredreleff);

/// @brief Set verbose message level
/// @param s Pointer to CaDiCaLSolver instance
/// @param verbose Integer value (0 to 3)
/// @return boolean value
int cadical_set_opt_verbose(CaDiCaLSolver *s, int verbose);

/// @brief Set VeriPB mode (odd=checkdeletions, > 2=drat)
/// @param s Pointer to CaDiCaLSolver instance
/// @param veripb Integer value (0 to 4)
/// @return boolean value
int cadical_set_opt_veripb(CaDiCaLSolver *s, int veripb);

/// @brief Enable vivification
/// @param s Pointer to CaDiCaLSolver instance
/// @param vivify Boolean value
/// @return boolean value
int cadical_set_opt_vivify(CaDiCaLSolver *s, int vivify);

/// @brief Instantiate last literal when vivifying
/// @param s Pointer to CaDiCaLSolver instance
/// @param vivifyinst Boolean value
/// @return boolean value
int cadical_set_opt_vivifyinst(CaDiCaLSolver *s, int vivifyinst);

/// @brief Set maximum efficiency for vivification
/// @param s Pointer to CaDiCaLSolver instance
/// @param vivifymaxeff Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_vivifymaxeff(CaDiCaLSolver *s, int vivifymaxeff);

/// @brief Set minimum efficiency for vivification
/// @param s Pointer to CaDiCaLSolver instance
/// @param vivifymineff Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_vivifymineff(CaDiCaLSolver *s, int vivifymineff);

/// @brief Set vivify once mode (1=red, 2=red+irr)
/// @param s Pointer to CaDiCaLSolver instance
/// @param vivifyonce Integer value (0 to 2)
/// @return boolean value
int cadical_set_opt_vivifyonce(CaDiCaLSolver *s, int vivifyonce);

/// @brief Set redundant efficiency per mille for vivification
/// @param s Pointer to CaDiCaLSolver instance
/// @param vivifyredeff Integer value (0 to 1e3)
/// @return boolean value
int cadical_set_opt_vivifyredeff(CaDiCaLSolver *s, int vivifyredeff);

/// @brief Set relative efficiency per mille for vivification
/// @param s Pointer to CaDiCaLSolver instance
/// @param vivifyreleff Integer value (1 to 1e5)
/// @return boolean value
int cadical_set_opt_vivifyreleff(CaDiCaLSolver *s, int vivifyreleff);

/// @brief Enable random walks
/// @param s Pointer to CaDiCaLSolver instance
/// @param walk Boolean value
/// @return boolean value
int cadical_set_opt_walk(CaDiCaLSolver *s, int walk);

/// @brief Set maximum efficiency for random walks
/// @param s Pointer to CaDiCaLSolver instance
/// @param walkmaxeff Integer value (0 to 2e9)
/// @return boolean value
int cadical_set_opt_walkmaxeff(CaDiCaLSolver *s, int walkmaxeff);

/// @brief Set minimum efficiency for random walks
/// @param s Pointer to CaDiCaLSolver instance
/// @param walkmineff Integer value (0 to 1e7)
/// @return boolean value
int cadical_set_opt_walkmineff(CaDiCaLSolver *s, int walkmineff);

/// @brief Walk in non-stabilizing phase
/// @param s Pointer to CaDiCaLSolver instance
/// @param walknonstable Boolean value
/// @return boolean value
int cadical_set_opt_walknonstable(CaDiCaLSolver *s, int walknonstable);

/// @brief Walk redundant clauses too
/// @param s Pointer to CaDiCaLSolver instance
/// @param walkredundant Boolean value
/// @return boolean value
int cadical_set_opt_walkredundant(CaDiCaLSolver *s, int walkredundant);

/// @brief Set relative efficiency per mille for random walks
/// @param s Pointer to CaDiCaLSolver instance
/// @param walkreleff Integer value (1 to 1e5)
/// @return boolean value
int cadical_set_opt_walkreleff(CaDiCaLSolver *s, int walkreleff);

#ifdef __cplusplus
}
#endif

#endif
