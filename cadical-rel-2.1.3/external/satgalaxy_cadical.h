#ifndef SATGALAXY_CADICAL_H
#define SATGALAXY_CADICAL_H
#include <stdint.h>
//=================================================================================================

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CaDiCaLSolver CaDiCaLSolver;
CaDiCaLSolver *cadical_new_solver ();
int cadical_add_clause (const CaDiCaLSolver *solver, const int ps[],
                         unsigned long length);
int cadical_add_empty_clause (const CaDiCaLSolver *solver);
// This function can be used to check if the formula is already
// inconsistent (contains the empty clause or was proven to be
// root-level unsatisfiable).
int cadical_add (const CaDiCaLSolver *, int lit);
int cadical_assume (const CaDiCaLSolver *, int lit);
int cadical_solve (const CaDiCaLSolver *);
int cadical_val (const CaDiCaLSolver *, int lit);
int cadical_failed (const CaDiCaLSolver *, int lit);

int cadical_set_terminate (const CaDiCaLSolver *, void *state,
                             int (*terminate) (void *state));

int cadical_set_learn (const CaDiCaLSolver *, void *state, int max_length,
                         void (*learn) (void *state, int *clause));

/*------------------------------------------------------------------------*/

// Non-IPASIR conformant 'C' functions.

int cadical_constrain (const CaDiCaLSolver *, int lit);
int cadical_constraint_failed (const CaDiCaLSolver *);
int cadical_set_option (const CaDiCaLSolver *, const char *name, int val);
int cadical_limit (const CaDiCaLSolver *, const char *name, int limit);
int cadical_get_option (const CaDiCaLSolver *, const char *name);
int cadical_print_statistics (const CaDiCaLSolver *);
int64_t cadical_active (const CaDiCaLSolver *);
int64_t cadical_irredundant (const CaDiCaLSolver *);
int cadical_fixed (const CaDiCaLSolver *, int lit);
// int cadical_trace_proof (const CaDiCaLSolver *, FILE *, const char *);
// void cadical_close_proof (const CaDiCaLSolver *);
void cadical_conclude (const CaDiCaLSolver *);
void cadical_terminate (const CaDiCaLSolver *);
void cadical_freeze (const CaDiCaLSolver *, int lit);
int cadical_frozen (const CaDiCaLSolver *, int lit);
void cadical_melt (const CaDiCaLSolver *, int lit);
int cadical_simplify (const CaDiCaLSolver *);




/// @brief Allocate clauses in arena
/// @param s Pointer to CaDiCaLSolver instance
/// @param arena Boolean value
/// @return Error code
int cadical_set_opt_arena(const CaDiCaLSolver *s, int arena);

/// @brief Keep clauses compact
/// @param s Pointer to CaDiCaLSolver instance
/// @param arenacompact Boolean value
/// @return Error code
int cadical_set_opt_arenacompact(const CaDiCaLSolver *s, int arenacompact);

/// @brief Sort clauses in arena
/// @param s Pointer to CaDiCaLSolver instance
/// @param arenasort Boolean value
/// @return Error code
int cadical_set_opt_arenasort(const CaDiCaLSolver *s, int arenasort);

/// @brief Set arena type (1=clause, 2=var, 3=queue)
/// @param s Pointer to CaDiCaLSolver instance
/// @param arenatype Integer value (1 to 3)
/// @return Error code
int cadical_set_opt_arenatype(const CaDiCaLSolver *s, int arenatype);

/// @brief Use binary proof format
/// @param s Pointer to CaDiCaLSolver instance
/// @param binary Boolean value
/// @return Error code
int cadical_set_opt_binary(const CaDiCaLSolver *s, int binary);

/// @brief Enable blocked clause elimination
/// @param s Pointer to CaDiCaLSolver instance
/// @param block Boolean value
/// @return Error code
int cadical_set_opt_block(const CaDiCaLSolver *s, int block);

/// @brief Set maximum clause size for blocked clause elimination
/// @param s Pointer to CaDiCaLSolver instance
/// @param blockmaxclslim Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_blockmaxclslim(const CaDiCaLSolver *s, int blockmaxclslim);

/// @brief Set minimum clause size for blocked clause elimination
/// @param s Pointer to CaDiCaLSolver instance
/// @param blockminclslim Integer value (2 to 2e9)
/// @return Error code
int cadical_set_opt_blockminclslim(const CaDiCaLSolver *s, int blockminclslim);

/// @brief Set occurrence limit for blocked clause elimination
/// @param s Pointer to CaDiCaLSolver instance
/// @param blockocclim Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_blockocclim(const CaDiCaLSolver *s, int blockocclim);

/// @brief Bump variables
/// @param s Pointer to CaDiCaLSolver instance
/// @param bump Boolean value
/// @return Error code
int cadical_set_opt_bump(const CaDiCaLSolver *s, int bump);

/// @brief Bump reason literals too
/// @param s Pointer to CaDiCaLSolver instance
/// @param bumpreason Boolean value
/// @return Error code
int cadical_set_opt_bumpreason(const CaDiCaLSolver *s, int bumpreason);

/// @brief Set bump reason depth
/// @param s Pointer to CaDiCaLSolver instance
/// @param bumpreasondepth Integer value (1 to 3)
/// @return Error code
int cadical_set_opt_bumpreasondepth(const CaDiCaLSolver *s, int bumpreasondepth);

/// @brief Enable internal checking
/// @param s Pointer to CaDiCaLSolver instance
/// @param check Boolean value
/// @return Error code
int cadical_set_opt_check(const CaDiCaLSolver *s, int check);

/// @brief Check assumptions satisfied
/// @param s Pointer to CaDiCaLSolver instance
/// @param checkassumptions Boolean value
/// @return Error code
int cadical_set_opt_checkassumptions(const CaDiCaLSolver *s, int checkassumptions);

/// @brief Check constraint satisfied
/// @param s Pointer to CaDiCaLSolver instance
/// @param checkconstraint Boolean value
/// @return Error code
int cadical_set_opt_checkconstraint(const CaDiCaLSolver *s, int checkconstraint);

/// @brief Check failed literals form core
/// @param s Pointer to CaDiCaLSolver instance
/// @param checkfailed Boolean value
/// @return Error code
int cadical_set_opt_checkfailed(const CaDiCaLSolver *s, int checkfailed);

/// @brief Check all frozen semantics
/// @param s Pointer to CaDiCaLSolver instance
/// @param checkfrozen Boolean value
/// @return Error code
int cadical_set_opt_checkfrozen(const CaDiCaLSolver *s, int checkfrozen);

/// @brief Set proof checking mode (1=drat, 2=lrat, 3=both)
/// @param s Pointer to CaDiCaLSolver instance
/// @param checkproof Integer value (0 to 3)
/// @return Error code
int cadical_set_opt_checkproof(const CaDiCaLSolver *s, int checkproof);

/// @brief Check witness internally
/// @param s Pointer to CaDiCaLSolver instance
/// @param checkwitness Boolean value
/// @return Error code
int cadical_set_opt_checkwitness(const CaDiCaLSolver *s, int checkwitness);

/// @brief Set chronological backtracking mode
/// @param s Pointer to CaDiCaLSolver instance
/// @param chrono Integer value (0 to 2)
/// @return Error code
int cadical_set_opt_chrono(const CaDiCaLSolver *s, int chrono);

/// @brief Force always chronological backtracking
/// @param s Pointer to CaDiCaLSolver instance
/// @param chronoalways Boolean value
/// @return Error code
int cadical_set_opt_chronoalways(const CaDiCaLSolver *s, int chronoalways);

/// @brief Set chronological level limit
/// @param s Pointer to CaDiCaLSolver instance
/// @param chronolevelim Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_chronolevelim(const CaDiCaLSolver *s, int chronolevelim);

/// @brief Reuse trail chronologically
/// @param s Pointer to CaDiCaLSolver instance
/// @param chronoreusetrail Boolean value
/// @return Error code
int cadical_set_opt_chronoreusetrail(const CaDiCaLSolver *s, int chronoreusetrail);

/// @brief Compact internal variables
/// @param s Pointer to CaDiCaLSolver instance
/// @param compact Boolean value
/// @return Error code
int cadical_set_opt_compact(const CaDiCaLSolver *s, int compact);

/// @brief Set compacting interval
/// @param s Pointer to CaDiCaLSolver instance
/// @param compactint Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_compactint(const CaDiCaLSolver *s, int compactint);

/// @brief Set inactive limit per mille
/// @param s Pointer to CaDiCaLSolver instance
/// @param compactlim Integer value (0 to 1e3)
/// @return Error code
int cadical_set_opt_compactlim(const CaDiCaLSolver *s, int compactlim);

/// @brief Set minimum inactive limit
/// @param s Pointer to CaDiCaLSolver instance
/// @param compactmin Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_compactmin(const CaDiCaLSolver *s, int compactmin);

/// @brief Enable globally blocked clause elimination
/// @param s Pointer to CaDiCaLSolver instance
/// @param condition Boolean value
/// @return Error code
int cadical_set_opt_condition(const CaDiCaLSolver *s, int condition);

/// @brief Set initial conflict interval for condition
/// @param s Pointer to CaDiCaLSolver instance
/// @param conditionint Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_conditionint(const CaDiCaLSolver *s, int conditionint);

/// @brief Set maximum condition efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param conditionmaxeff Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_conditionmaxeff(const CaDiCaLSolver *s, int conditionmaxeff);

/// @brief Set maximum clause variable ratio
/// @param s Pointer to CaDiCaLSolver instance
/// @param conditionmaxrat Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_conditionmaxrat(const CaDiCaLSolver *s, int conditionmaxrat);

/// @brief Set minimum condition efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param conditionmineff Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_conditionmineff(const CaDiCaLSolver *s, int conditionmineff);

/// @brief Set relative efficiency per mille for condition
/// @param s Pointer to CaDiCaLSolver instance
/// @param conditionreleff Integer value (1 to 1e5)
/// @return Error code
int cadical_set_opt_conditionreleff(const CaDiCaLSolver *s, int conditionreleff);

/// @brief Enable covered clause elimination
/// @param s Pointer to CaDiCaLSolver instance
/// @param cover Boolean value
/// @return Error code
int cadical_set_opt_cover(const CaDiCaLSolver *s, int cover);

/// @brief Set maximum clause size for cover
/// @param s Pointer to CaDiCaLSolver instance
/// @param covermaxclslim Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_covermaxclslim(const CaDiCaLSolver *s, int covermaxclslim);

/// @brief Set maximum cover efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param covermaxeff Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_covermaxeff(const CaDiCaLSolver *s, int covermaxeff);

/// @brief Set minimum clause size for cover
/// @param s Pointer to CaDiCaLSolver instance
/// @param coverminclslim Integer value (2 to 2e9)
/// @return Error code
int cadical_set_opt_coverminclslim(const CaDiCaLSolver *s, int coverminclslim);

/// @brief Set minimum cover efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param covermineff Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_covermineff(const CaDiCaLSolver *s, int covermineff);

/// @brief Set relative efficiency per mille for cover
/// @param s Pointer to CaDiCaLSolver instance
/// @param coverreleff Integer value (1 to 1e5)
/// @return Error code
int cadical_set_opt_coverreleff(const CaDiCaLSolver *s, int coverreleff);

/// @brief Decompose BIG in SCCs and ELS
/// @param s Pointer to CaDiCaLSolver instance
/// @param decompose Boolean value
/// @return Error code
int cadical_set_opt_decompose(const CaDiCaLSolver *s, int decompose);

/// @brief Set number of decompose rounds
/// @param s Pointer to CaDiCaLSolver instance
/// @param decomposerounds Integer value (1 to 16)
/// @return Error code
int cadical_set_opt_decomposerounds(const CaDiCaLSolver *s, int decomposerounds);

/// @brief Remove duplicated binaries
/// @param s Pointer to CaDiCaLSolver instance
/// @param deduplicate Boolean value
/// @return Error code
int cadical_set_opt_deduplicate(const CaDiCaLSolver *s, int deduplicate);

/// @brief Subsume recently learned clauses
/// @param s Pointer to CaDiCaLSolver instance
/// @param eagersubsume Boolean value
/// @return Error code
int cadical_set_opt_eagersubsume(const CaDiCaLSolver *s, int eagersubsume);

/// @brief Set limit on subsumed candidates
/// @param s Pointer to CaDiCaLSolver instance
/// @param eagersubsumelim Integer value (1 to 1e3)
/// @return Error code
int cadical_set_opt_eagersubsumelim(const CaDiCaLSolver *s, int eagersubsumelim);

/// @brief Enable bounded variable elimination
/// @param s Pointer to CaDiCaLSolver instance
/// @param elim Boolean value
/// @return Error code
int cadical_set_opt_elim(const CaDiCaLSolver *s, int elim);

/// @brief Find AND gates
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimands Boolean value
/// @return Error code
int cadical_set_opt_elimands(const CaDiCaLSolver *s, int elimands);

/// @brief Set maximum elimination efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimaxeff Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_elimaxeff(const CaDiCaLSolver *s, int elimaxeff);

/// @brief Enable eager backward subsumption
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimbackward Boolean value
/// @return Error code
int cadical_set_opt_elimbackward(const CaDiCaLSolver *s, int elimbackward);

/// @brief Set maximum elimination bound
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimboundmax Integer value (-1 to 2e6)
/// @return Error code
int cadical_set_opt_elimboundmax(const CaDiCaLSolver *s, int elimboundmax);

/// @brief Set minimum elimination bound
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimboundmin Integer value (-1 to 2e6)
/// @return Error code
int cadical_set_opt_elimboundmin(const CaDiCaLSolver *s, int elimboundmin);

/// @brief Set resolvent size limit
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimclslim Integer value (2 to 2e9)
/// @return Error code
int cadical_set_opt_elimclslim(const CaDiCaLSolver *s, int elimclslim);

/// @brief Find equivalence gates
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimequivs Boolean value
/// @return Error code
int cadical_set_opt_elimequivs(const CaDiCaLSolver *s, int elimequivs);

/// @brief Set minimum elimination efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimineff Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_elimineff(const CaDiCaLSolver *s, int elimineff);

/// @brief Set elimination interval
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimint Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_elimint(const CaDiCaLSolver *s, int elimint);

/// @brief Find if-then-else gates
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimites Boolean value
/// @return Error code
int cadical_set_opt_elimites(const CaDiCaLSolver *s, int elimites);

/// @brief Limit resolutions
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimlimited Boolean value
/// @return Error code
int cadical_set_opt_elimlimited(const CaDiCaLSolver *s, int elimlimited);

/// @brief Set occurrence limit for elimination
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimocclim Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_elimocclim(const CaDiCaLSolver *s, int elimocclim);

/// @brief Set elimination score product weight
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimprod Integer value (0 to 1e4)
/// @return Error code
int cadical_set_opt_elimprod(const CaDiCaLSolver *s, int elimprod);

/// @brief Set relative efficiency per mille for elimination
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimreleff Integer value (1 to 1e5)
/// @return Error code
int cadical_set_opt_elimreleff(const CaDiCaLSolver *s, int elimreleff);

/// @brief Set usual number of elimination rounds
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimrounds Integer value (1 to 512)
/// @return Error code
int cadical_set_opt_elimrounds(const CaDiCaLSolver *s, int elimrounds);

/// @brief Enable elimination by substitution
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimsubst Boolean value
/// @return Error code
int cadical_set_opt_elimsubst(const CaDiCaLSolver *s, int elimsubst);

/// @brief Set elimination score sum weight
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimsum Integer value (0 to 1e4)
/// @return Error code
int cadical_set_opt_elimsum(const CaDiCaLSolver *s, int elimsum);

/// @brief Set maximum XOR size
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimxorlim Integer value (2 to 27)
/// @return Error code
int cadical_set_opt_elimxorlim(const CaDiCaLSolver *s, int elimxorlim);

/// @brief Find XOR gates
/// @param s Pointer to CaDiCaLSolver instance
/// @param elimxors Boolean value
/// @return Error code
int cadical_set_opt_elimxors(const CaDiCaLSolver *s, int elimxors);

/// @brief Set window fast glue
/// @param s Pointer to CaDiCaLSolver instance
/// @param emagluefast Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_emagluefast(const CaDiCaLSolver *s, int emagluefast);

/// @brief Set window slow glue
/// @param s Pointer to CaDiCaLSolver instance
/// @param emaglueslow Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_emaglueslow(const CaDiCaLSolver *s, int emaglueslow);

/// @brief Set window back-jump level
/// @param s Pointer to CaDiCaLSolver instance
/// @param emajump Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_emajump(const CaDiCaLSolver *s, int emajump);

/// @brief Set window back-track level
/// @param s Pointer to CaDiCaLSolver instance
/// @param emalevel Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_emalevel(const CaDiCaLSolver *s, int emalevel);

/// @brief Set window learned clause size
/// @param s Pointer to CaDiCaLSolver instance
/// @param emasize Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_emasize(const CaDiCaLSolver *s, int emasize);

/// @brief Set window fast trail
/// @param s Pointer to CaDiCaLSolver instance
/// @param ematrailfast Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_ematrailfast(const CaDiCaLSolver *s, int ematrailfast);

/// @brief Set window slow trail
/// @param s Pointer to CaDiCaLSolver instance
/// @param ematrailslow Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_ematrailslow(const CaDiCaLSolver *s, int ematrailslow);

/// @brief Eagerly ask for all reasons (0: only when needed)
/// @param s Pointer to CaDiCaLSolver instance
/// @param exteagerreasons Boolean value
/// @return Error code
int cadical_set_opt_exteagerreasons(const CaDiCaLSolver *s, int exteagerreasons);

/// @brief Recalculate all levels after eagerly asking for reasons (0: trust the external tool)
/// @param s Pointer to CaDiCaLSolver instance
/// @param exteagerrecalc Boolean value
/// @return Error code
int cadical_set_opt_exteagerrecalc(const CaDiCaLSolver *s, int exteagerrecalc);

/// @brief Enable external LRAT
/// @param s Pointer to CaDiCaLSolver instance
/// @param externallrat Boolean value
/// @return Error code
int cadical_set_opt_externallrat(const CaDiCaLSolver *s, int externallrat);

/// @brief Flush redundant clauses
/// @param s Pointer to CaDiCaLSolver instance
/// @param flush Boolean value
/// @return Error code
int cadical_set_opt_flush(const CaDiCaLSolver *s, int flush);

/// @brief Set interval increase for flushing
/// @param s Pointer to CaDiCaLSolver instance
/// @param flushfactor Integer value (1 to 1e3)
/// @return Error code
int cadical_set_opt_flushfactor(const CaDiCaLSolver *s, int flushfactor);

/// @brief Set initial limit for flushing
/// @param s Pointer to CaDiCaLSolver instance
/// @param flushint Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_flushint(const CaDiCaLSolver *s, int flushint);

/// @brief Always use initial phase
/// @param s Pointer to CaDiCaLSolver instance
/// @param forcephase Boolean value
/// @return Error code
int cadical_set_opt_forcephase(const CaDiCaLSolver *s, int forcephase);

/// @brief Set FRAT proof format (1=frat(lrat), 2=frat(drat))
/// @param s Pointer to CaDiCaLSolver instance
/// @param frat Integer value (0 to 2)
/// @return Error code
int cadical_set_opt_frat(const CaDiCaLSolver *s, int frat);

/// @brief Use incremental proof format
/// @param s Pointer to CaDiCaLSolver instance
/// @param idrup Boolean value
/// @return Error code
int cadical_set_opt_idrup(const CaDiCaLSolver *s, int idrup);

/// @brief Enable ILB (incremental lazy backtrack)
/// @param s Pointer to CaDiCaLSolver instance
/// @param ilb Boolean value
/// @return Error code
int cadical_set_opt_ilb(const CaDiCaLSolver *s, int ilb);

/// @brief Enable trail reuse for assumptions (ILB-like)
/// @param s Pointer to CaDiCaLSolver instance
/// @param ilbassumptions Boolean value
/// @return Error code
int cadical_set_opt_ilbassumptions(const CaDiCaLSolver *s, int ilbassumptions);

/// @brief Enable inprocessing
/// @param s Pointer to CaDiCaLSolver instance
/// @param inprocessing Boolean value
/// @return Error code
int cadical_set_opt_inprocessing(const CaDiCaLSolver *s, int inprocessing);

/// @brief Enable variable instantiation
/// @param s Pointer to CaDiCaLSolver instance
/// @param instantiate Boolean value
/// @return Error code
int cadical_set_opt_instantiate(const CaDiCaLSolver *s, int instantiate);

/// @brief Set minimum clause size for instantiation
/// @param s Pointer to CaDiCaLSolver instance
/// @param instantiateclslim Integer value (2 to 2e9)
/// @return Error code
int cadical_set_opt_instantiateclslim(const CaDiCaLSolver *s, int instantiateclslim);

/// @brief Set maximum occurrence limit for instantiation
/// @param s Pointer to CaDiCaLSolver instance
/// @param instantiateocclim Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_instantiateocclim(const CaDiCaLSolver *s, int instantiateocclim);

/// @brief Instantiate each clause once
/// @param s Pointer to CaDiCaLSolver instance
/// @param instantiateonce Boolean value
/// @return Error code
int cadical_set_opt_instantiateonce(const CaDiCaLSolver *s, int instantiateonce);

/// @brief Use linear incremental proof format
/// @param s Pointer to CaDiCaLSolver instance
/// @param lidrup Boolean value
/// @return Error code
int cadical_set_opt_lidrup(const CaDiCaLSolver *s, int lidrup);

/// @brief Enable logging
/// @param s Pointer to CaDiCaLSolver instance
/// @param log Boolean value
/// @return Error code
int cadical_set_opt_log(const CaDiCaLSolver *s, int log);

/// @brief Sort logged clauses
/// @param s Pointer to CaDiCaLSolver instance
/// @param logsort Boolean value
/// @return Error code
int cadical_set_opt_logsort(const CaDiCaLSolver *s, int logsort);

/// @brief Use LRAT proof format
/// @param s Pointer to CaDiCaLSolver instance
/// @param lrat Boolean value
/// @return Error code
int cadical_set_opt_lrat(const CaDiCaLSolver *s, int lrat);

/// @brief Search for lucky phases
/// @param s Pointer to CaDiCaLSolver instance
/// @param lucky Boolean value
/// @return Error code
int cadical_set_opt_lucky(const CaDiCaLSolver *s, int lucky);

/// @brief Minimize learned clauses
/// @param s Pointer to CaDiCaLSolver instance
/// @param minimize Boolean value
/// @return Error code
int cadical_set_opt_minimize(const CaDiCaLSolver *s, int minimize);

/// @brief Set minimization depth
/// @param s Pointer to CaDiCaLSolver instance
/// @param minimizedepth Integer value (0 to 1e3)
/// @return Error code
int cadical_set_opt_minimizedepth(const CaDiCaLSolver *s, int minimizedepth);

/// @brief Enable on-the-fly self subsumption
/// @param s Pointer to CaDiCaLSolver instance
/// @param otfs Boolean value
/// @return Error code
int cadical_set_opt_otfs(const CaDiCaLSolver *s, int otfs);

/// @brief Set initial phase
/// @param s Pointer to CaDiCaLSolver instance
/// @param phase Boolean value
/// @return Error code
int cadical_set_opt_phase(const CaDiCaLSolver *s, int phase);

/// @brief Enable failed literal probing
/// @param s Pointer to CaDiCaLSolver instance
/// @param probe Boolean value
/// @return Error code
int cadical_set_opt_probe(const CaDiCaLSolver *s, int probe);

/// @brief Learn hyper binary clauses
/// @param s Pointer to CaDiCaLSolver instance
/// @param probehbr Boolean value
/// @return Error code
int cadical_set_opt_probehbr(const CaDiCaLSolver *s, int probehbr);

/// @brief Set probing interval
/// @param s Pointer to CaDiCaLSolver instance
/// @param probeint Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_probeint(const CaDiCaLSolver *s, int probeint);

/// @brief Set maximum probing efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param probemaxeff Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_probemaxeff(const CaDiCaLSolver *s, int probemaxeff);

/// @brief Set minimum probing efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param probemineff Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_probemineff(const CaDiCaLSolver *s, int probemineff);

/// @brief Set relative efficiency per mille for probing
/// @param s Pointer to CaDiCaLSolver instance
/// @param probereleff Integer value (1 to 1e5)
/// @return Error code
int cadical_set_opt_probereleff(const CaDiCaLSolver *s, int probereleff);

/// @brief Set probing rounds
/// @param s Pointer to CaDiCaLSolver instance
/// @param proberounds Integer value (1 to 16)
/// @return Error code
int cadical_set_opt_proberounds(const CaDiCaLSolver *s, int proberounds);

/// @brief Set profiling level
/// @param s Pointer to CaDiCaLSolver instance
/// @param profile Integer value (0 to 4)
/// @return Error code
int cadical_set_opt_profile(const CaDiCaLSolver *s, int profile);

/// @brief Disable all messages
/// @param s Pointer to CaDiCaLSolver instance
/// @param quiet Boolean value
/// @return Error code
int cadical_set_opt_quiet(const CaDiCaLSolver *s, int quiet);

/// @brief Set radix sort limit
/// @param s Pointer to CaDiCaLSolver instance
/// @param radixsortlim Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_radixsortlim(const CaDiCaLSolver *s, int radixsortlim);

/// @brief Use real instead of process time
/// @param s Pointer to CaDiCaLSolver instance
/// @param realtime Boolean value
/// @return Error code
int cadical_set_opt_realtime(const CaDiCaLSolver *s, int realtime);

/// @brief Reduce useless clauses
/// @param s Pointer to CaDiCaLSolver instance
/// @param reduce Boolean value
/// @return Error code
int cadical_set_opt_reduce(const CaDiCaLSolver *s, int reduce);

/// @brief Set reduce interval
/// @param s Pointer to CaDiCaLSolver instance
/// @param reduceint Integer value (10 to 1e6)
/// @return Error code
int cadical_set_opt_reduceint(const CaDiCaLSolver *s, int reduceint);

/// @brief Set reduce fraction in percent
/// @param s Pointer to CaDiCaLSolver instance
/// @param reducetarget Integer value (10 to 1e2)
/// @return Error code
int cadical_set_opt_reducetarget(const CaDiCaLSolver *s, int reducetarget);

/// @brief Set glue of kept learned clauses
/// @param s Pointer to CaDiCaLSolver instance
/// @param reducetier1glue Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_reducetier1glue(const CaDiCaLSolver *s, int reducetier1glue);

/// @brief Set glue of tier two clauses
/// @param s Pointer to CaDiCaLSolver instance
/// @param reducetier2glue Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_reducetier2glue(const CaDiCaLSolver *s, int reducetier2glue);

/// @brief Set reluctant doubling period
/// @param s Pointer to CaDiCaLSolver instance
/// @param reluctant Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_reluctant(const CaDiCaLSolver *s, int reluctant);

/// @brief Set maximum reluctant doubling period
/// @param s Pointer to CaDiCaLSolver instance
/// @param reluctantmax Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_reluctantmax(const CaDiCaLSolver *s, int reluctantmax);

/// @brief Enable resetting phase
/// @param s Pointer to CaDiCaLSolver instance
/// @param rephase Boolean value
/// @return Error code
int cadical_set_opt_rephase(const CaDiCaLSolver *s, int rephase);

/// @brief Set rephase interval
/// @param s Pointer to CaDiCaLSolver instance
/// @param rephaseint Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_rephaseint(const CaDiCaLSolver *s, int rephaseint);

/// @brief Enable reporting
/// @param s Pointer to CaDiCaLSolver instance
/// @param report Boolean value
/// @return Error code
int cadical_set_opt_report(const CaDiCaLSolver *s, int report);

/// @brief Report even if not successful
/// @param s Pointer to CaDiCaLSolver instance
/// @param reportall Boolean value
/// @return Error code
int cadical_set_opt_reportall(const CaDiCaLSolver *s, int reportall);

/// @brief Use solving not process time for reporting
/// @param s Pointer to CaDiCaLSolver instance
/// @param reportsolve Boolean value
/// @return Error code
int cadical_set_opt_reportsolve(const CaDiCaLSolver *s, int reportsolve);

/// @brief Enable restarts
/// @param s Pointer to CaDiCaLSolver instance
/// @param restart Boolean value
/// @return Error code
int cadical_set_opt_restart(const CaDiCaLSolver *s, int restart);

/// @brief Set restart interval
/// @param s Pointer to CaDiCaLSolver instance
/// @param restartint Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_restartint(const CaDiCaLSolver *s, int restartint);

/// @brief Set slow fast margin in percent
/// @param s Pointer to CaDiCaLSolver instance
/// @param restartmargin Integer value (0 to 1e2)
/// @return Error code
int cadical_set_opt_restartmargin(const CaDiCaLSolver *s, int restartmargin);

/// @brief Enable trail reuse
/// @param s Pointer to CaDiCaLSolver instance
/// @param restartreusetrail Boolean value
/// @return Error code
int cadical_set_opt_restartreusetrail(const CaDiCaLSolver *s, int restartreusetrail);

/// @brief Restore all clauses (2=really)
/// @param s Pointer to CaDiCaLSolver instance
/// @param restoreall Integer value (0 to 2)
/// @return Error code
int cadical_set_opt_restoreall(const CaDiCaLSolver *s, int restoreall);

/// @brief Remove satisfied clauses
/// @param s Pointer to CaDiCaLSolver * instance
/// @param restoreflush Boolean value
/// @return Error code
int cadical_set_opt_restoreflush(const CaDiCaLSolver *s, int restoreflush);

/// @brief Reverse variable ordering
/// @param s Pointer to CaDiCaLSolver instance
/// @param reverse Boolean value
/// @return Error code
int cadical_set_opt_reverse(const CaDiCaLSolver *s, int reverse);

/// @brief Use EVSIDS scores
/// @param s Pointer to CaDiCaLSolver instance
/// @param score Boolean value
/// @return Error code
int cadical_set_opt_score(const CaDiCaLSolver *s, int score);

/// @brief Set score factor per mille
/// @param s Pointer to CaDiCaLSolver instance
/// @param scorefactor Integer value (500 to 1e3)
/// @return Error code
int cadical_set_opt_scorefactor(const CaDiCaLSolver *s, int scorefactor);

/// @brief Set random seed
/// @param s Pointer to CaDiCaLSolver instance
/// @param seed Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_seed(const CaDiCaLSolver *s, int seed);

/// @brief Shrink conflict clause (1=only with binary, 2=minimize when pulling, 3=full)
/// @param s Pointer to CaDiCaLSolver instance
/// @param shrink Integer value (0 to 3)
/// @return Error code
int cadical_set_opt_shrink(const CaDiCaLSolver *s, int shrink);

/// @brief Use a reap for shrinking
/// @param s Pointer to CaDiCaLSolver instance
/// @param shrinkreap Boolean value
/// @return Error code
int cadical_set_opt_shrinkreap(const CaDiCaLSolver *s, int shrinkreap);

/// @brief Shuffle variables
/// @param s Pointer to CaDiCaLSolver instance
/// @param shuffle Boolean value
/// @return Error code
int cadical_set_opt_shuffle(const CaDiCaLSolver *s, int shuffle);

/// @brief Shuffle variable queue
/// @param s Pointer to CaDiCaLSolver instance
/// @param shufflequeue Boolean value
/// @return Error code
int cadical_set_opt_shufflequeue(const CaDiCaLSolver *s, int shufflequeue);

/// @brief Use random instead of reverse shuffling
/// @param s Pointer to CaDiCaLSolver instance
/// @param shufflerandom Boolean value
/// @return Error code
int cadical_set_opt_shufflerandom(const CaDiCaLSolver *s, int shufflerandom);

/// @brief Shuffle variable scores
/// @param s Pointer to CaDiCaLSolver instance
/// @param shufflescores Boolean value
/// @return Error code
int cadical_set_opt_shufflescores(const CaDiCaLSolver *s, int shufflescores);

/// @brief Enable stabilizing phases
/// @param s Pointer to CaDiCaLSolver instance
/// @param stabilize Boolean value
/// @return Error code
int cadical_set_opt_stabilize(const CaDiCaLSolver *s, int stabilize);

/// @brief Set phase increase in percent
/// @param s Pointer to CaDiCaLSolver instance
/// @param stabilizefactor Integer value (101 to 2e9)
/// @return Error code
int cadical_set_opt_stabilizefactor(const CaDiCaLSolver *s, int stabilizefactor);

/// @brief Set stabilizing interval
/// @param s Pointer to CaDiCaLSolver instance
/// @param stabilizeint Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_stabilizeint(const CaDiCaLSolver *s, int stabilizeint);

/// @brief Set maximum stabilizing phase
/// @param s Pointer to CaDiCaLSolver instance
/// @param stabilizemaxint Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_stabilizemaxint(const CaDiCaLSolver *s, int stabilizemaxint);

/// @brief Use only stabilizing phases
/// @param s Pointer to CaDiCaLSolver instance
/// @param stabilizeonly Boolean value
/// @return Error code
int cadical_set_opt_stabilizeonly(const CaDiCaLSolver *s, int stabilizeonly);

/// @brief Print all statistics at the end of the run
/// @param s Pointer to CaDiCaLSolver instance
/// @param stats Boolean value
/// @return Error code
int cadical_set_opt_stats(const CaDiCaLSolver *s, int stats);

/// @brief Enable clause subsumption
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsume Boolean value
/// @return Error code
int cadical_set_opt_subsume(const CaDiCaLSolver *s, int subsume);

/// @brief Set watch list length limit for subsumption
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsumebinlim Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_subsumebinlim(const CaDiCaLSolver *s, int subsumebinlim);

/// @brief Set clause length limit for subsumption
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsumeclslim Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_subsumeclslim(const CaDiCaLSolver *s, int subsumeclslim);

/// @brief Set subsume interval
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsumeint Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_subsumeint(const CaDiCaLSolver *s, int subsumeint);

/// @brief Limit subsumption checks
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsumelimited Boolean value
/// @return Error code
int cadical_set_opt_subsumelimited(const CaDiCaLSolver *s, int subsumelimited);

/// @brief Set maximum subsuming efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsumemaxeff Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_subsumemaxeff(const CaDiCaLSolver *s, int subsumemaxeff);

/// @brief Set minimum subsuming efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsumemineff Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_subsumemineff(const CaDiCaLSolver *s, int subsumemineff);

/// @brief Set watch list length limit for subsumption
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsumeocclim Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_subsumeocclim(const CaDiCaLSolver *s, int subsumeocclim);

/// @brief Set relative efficiency per mille for subsumption
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsumereleff Integer value erős (1 to 1e5)
/// @return Error code
int cadical_set_opt_subsumereleff(const CaDiCaLSolver *s, int subsumereleff);

/// @brief Strengthen during subsume
/// @param s Pointer to CaDiCaLSolver instance
/// @param subsumestr Boolean value
/// @return Error code
int cadical_set_opt_subsumestr(const CaDiCaLSolver *s, int subsumestr);

/// @brief Set target phases (1=stable only)
/// @param s Pointer to CaDiCaLSolver instance
/// @param target Integer value (0 to 2)
/// @return Error code
int cadical_set_opt_target(const CaDiCaLSolver *s, int target);

/// @brief Set termination check interval
/// @param s Pointer to CaDiCaLSolver instance
/// @param terminateint Integer value (0 to 1e4)
/// @return Error code
int cadical_set_opt_terminateint(const CaDiCaLSolver *s, int terminateint);

/// @brief Enable hyper ternary resolution
/// @param s Pointer to CaDiCaLSolver instance
/// @param ternary Boolean value
/// @return Error code
int cadical_set_opt_ternary(const CaDiCaLSolver *s, int ternary);

/// @brief Set max clauses added in percent for ternary
/// @param s Pointer to CaDiCaLSolver instance
/// @param ternarymaxadd Integer value (0 to 1e4)
/// @return Error code
int cadical_set_opt_ternarymaxadd(const CaDiCaLSolver *s, int ternarymaxadd);

/// @brief Set ternary maximum efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param ternarymaxeff Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_ternarymaxeff(const CaDiCaLSolver *s, int ternarymaxeff);

/// @brief Set minimum ternary efficiency
/// @param s Pointer to CaDiCaLSolver instance
/// @param ternarymineff Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_ternarymineff(const CaDiCaLSolver *s, int ternarymineff);

/// @brief Set ternary occurrence limit
/// @param s Pointer to CaDiCaLSolver instance
/// @param ternaryocclim Integer value (1 to 2e9)
/// @return Error code
int cadical_set_opt_ternaryocclim(const CaDiCaLSolver *s, int ternaryocclim);

/// @brief Set relative efficiency per mille for ternary
/// @param s Pointer to CaDiCaLSolver instance
/// @param ternaryreleff Integer value (1 to 1e5)
/// @return Error code
int cadical_set_opt_ternaryreleff(const CaDiCaLSolver *s, int ternaryreleff);

/// @brief Set maximum ternary rounds
/// @param s Pointer to CaDiCaLSolver instance
/// @param ternaryrounds Integer value (1 to 16)
/// @return Error code
int cadical_set_opt_ternaryrounds(const CaDiCaLSolver *s, int ternaryrounds);

/// @brief Enable transitive reduction of BIG
/// @param s Pointer to CaDiCaLSolver instance
/// @param transred Boolean value
/// @return Error code
int cadical_set_opt_transred(const CaDiCaLSolver *s, int transred);

/// @brief Set maximum efficiency for transitive reduction
/// @param s Pointer to CaDiCaLSolver instance
/// @param transredmaxeff Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_transredmaxeff(const CaDiCaLSolver *s, int transredmaxeff);

/// @brief Set minimum efficiency for transitive reduction
/// @param s Pointer to CaDiCaLSolver instance
/// @param transredmineff Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_transredmineff(const CaDiCaLSolver *s, int transredmineff);

/// @brief Set relative efficiency per mille for transitive reduction
/// @param s Pointer to CaDiCaLSolver instance
/// @param transredreleff Integer value (1 to 1e5)
/// @return Error code
int cadical_set_opt_transredreleff(const CaDiCaLSolver *s, int transredreleff);

/// @brief Set verbose message level
/// @param s Pointer to CaDiCaLSolver instance
/// @param verbose Integer value (0 to 3)
/// @return Error code
int cadical_set_opt_verbose(const CaDiCaLSolver *s, int verbose);

/// @brief Set VeriPB mode (odd=checkdeletions, > 2=drat)
/// @param s Pointer to CaDiCaLSolver instance
/// @param veripb Integer value (0 to 4)
/// @return Error code
int cadical_set_opt_veripb(const CaDiCaLSolver *s, int veripb);

/// @brief Enable vivification
/// @param s Pointer to CaDiCaLSolver instance
/// @param vivify Boolean value
/// @return Error code
int cadical_set_opt_vivify(const CaDiCaLSolver *s, int vivify);

/// @brief Instantiate last literal when vivifying
/// @param s Pointer to CaDiCaLSolver instance
/// @param vivifyinst Boolean value
/// @return Error code
int cadical_set_opt_vivifyinst(const CaDiCaLSolver *s, int vivifyinst);

/// @brief Set maximum efficiency for vivification
/// @param s Pointer to CaDiCaLSolver instance
/// @param vivifymaxeff Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_vivifymaxeff(const CaDiCaLSolver *s, int vivifymaxeff);

/// @brief Set minimum efficiency for vivification
/// @param s Pointer to CaDiCaLSolver instance
/// @param vivifymineff Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_vivifymineff(const CaDiCaLSolver *s, int vivifymineff);

/// @brief Set vivify once mode (1=red, 2=red+irr)
/// @param s Pointer to CaDiCaLSolver instance
/// @param vivifyonce Integer value (0 to 2)
/// @return Error code
int cadical_set_opt_vivifyonce(const CaDiCaLSolver *s, int vivifyonce);

/// @brief Set redundant efficiency per mille for vivification
/// @param s Pointer to CaDiCaLSolver instance
/// @param vivifyredeff Integer value (0 to 1e3)
/// @return Error code
int cadical_set_opt_vivifyredeff(const CaDiCaLSolver *s, int vivifyredeff);

/// @brief Set relative efficiency per mille for vivification
/// @param s Pointer to CaDiCaLSolver instance
/// @param vivifyreleff Integer value (1 to 1e5)
/// @return Error code
int cadical_set_opt_vivifyreleff(const CaDiCaLSolver *s, int vivifyreleff);

/// @brief Enable random walks
/// @param s Pointer to CaDiCaLSolver instance
/// @param walk Boolean value
/// @return Error code
int cadical_set_opt_walk(const CaDiCaLSolver *s, int walk);

/// @brief Set maximum efficiency for random walks
/// @param s Pointer to CaDiCaLSolver instance
/// @param walkmaxeff Integer value (0 to 2e9)
/// @return Error code
int cadical_set_opt_walkmaxeff(const CaDiCaLSolver *s, int walkmaxeff);

/// @brief Set minimum efficiency for random walks
/// @param s Pointer to CaDiCaLSolver instance
/// @param walkmineff Integer value (0 to 1e7)
/// @return Error code
int cadical_set_opt_walkmineff(const CaDiCaLSolver *s, int walkmineff);

/// @brief Walk in non-stabilizing phase
/// @param s Pointer to CaDiCaLSolver instance
/// @param walknonstable Boolean value
/// @return Error code
int cadical_set_opt_walknonstable(const CaDiCaLSolver *s, int walknonstable);

/// @brief Walk redundant clauses too
/// @param s Pointer to CaDiCaLSolver instance
/// @param walkredundant Boolean value
/// @return Error code
int cadical_set_opt_walkredundant(const CaDiCaLSolver *s, int walkredundant);

/// @brief Set relative efficiency per mille for random walks
/// @param s Pointer to CaDiCaLSolver instance
/// @param walkreleff Integer value (1 to 1e5)
/// @return Error code
int cadical_set_opt_walkreleff(const CaDiCaLSolver *s, int walkreleff);

#ifdef __cplusplus
}
#endif

#endif
