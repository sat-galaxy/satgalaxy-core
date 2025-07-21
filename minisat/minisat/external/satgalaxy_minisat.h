#ifndef SATGALAXY_MINISAT_H
#define SATGALAXY_MINISAT_H
#include <stdlib.h>
//=================================================================================================

#ifdef __cplusplus
extern "C"
{
#endif
typedef struct MiniSATSolver MiniSATSolver;

    /// @brief get error message by error code
    /// @param code error code
    /// @return message
    const char *minisat_error_msg(int code);

    /// @brief The variable activity decay factor
    /// @param value must be in (0, 1)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_var_decay(MiniSATSolver*, double);


    /// @brief The clause activity decay factor
    /// @param value must be in (MiniSATSolver*,0, 1)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_clause_decay(MiniSATSolver*,double decay);

    /// @brief The frequency with which the decision heuristic tries to choose a random variable
    /// @param value must be in [0,1]
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_random_var_freq(MiniSATSolver*,double freq);

    /// @brief Used by the random variable selection
    /// @param value must be positive
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_random_seed(MiniSATSolver*,double seed);

    /// @brief Controls conflict clause minimization
    /// @param value must be 0, 1, or 2 (MiniSATSolver*,0=none, 1=basic, 2=deep)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_ccmin_mode(MiniSATSolver*,int mode);

    /// @brief Controls the level of phase saving
    /// @param value must be 0, 1, or 2 (MiniSATSolver*,0=none, 1=limited, 2=full)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_phase_saving(MiniSATSolver*,int mode);

    /// @brief Randomize the initial activity
    /// @param value boolean value (MiniSATSolver*,0=false, others=true)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_rnd_init_act(MiniSATSolver*,int flag);

    /// @brief Use the Luby restart sequence
    /// @param value boolean value (MiniSATSolver*,0=false, others=true)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_luby_restart(MiniSATSolver*,int flag);

    /// @brief The base restart interval
    /// @param value must be a positive integer
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_restart_first(MiniSATSolver*,int restart_first);

    /// @brief Restart interval increase factor
    /// @param value must be at least 1.0
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_restart_inc(MiniSATSolver*,double restart_inc);

    /// @brief The fraction of wasted memory allowed before a garbage collection is triggered
    /// @param value must be positive
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_garbage_frac(MiniSATSolver*,double garbage_frac);

    /// @brief Minimum learnt clause limit
    /// @param value must be at least 0
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_min_learnts_lim(MiniSATSolver*,int min_learnts_lim);

    /// @brief Shrink clauses by asymmetric branching
    /// @param value boolean value (MiniSATSolver*,0=false, others=true)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_use_asymm(MiniSATSolver*,int opt_use_asymm);

    /// @brief Check if a clause is already implied (MiniSATSolver*,costly)
    /// @param value boolean value (MiniSATSolver*,0=false, others=true)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_use_rcheck(MiniSATSolver*,int opt_use_rcheck);

    /// @brief Perform variable elimination
    /// @param value boolean value (MiniSATSolver*,0=false, others=true)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_use_elim(MiniSATSolver*,int opt_use_elim);

    /// @brief Allow a variable elimination step to grow by a number of clauses
    /// @param value must be at least 0
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_grow(MiniSATSolver*,int opt_grow);

    /// @brief Variables are not eliminated if it produces a resolvent with a length above this limit
    /// @param value must be at least -1 (MiniSATSolver*,-1 means no limit)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_clause_lim(MiniSATSolver*,int opt_clause_lim);

    /// @brief Do not check if subsumption against a clause larger than this
    /// @param value must be at least -1 (MiniSATSolver*,-1 means no limit)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_subsumption_lim(MiniSATSolver*,int opt_subsumption_lim);

    /// @brief The fraction of wasted memory allowed before a garbage collection is triggered during simplification
    /// @param value must be positive
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_simp_garbage_frac(MiniSATSolver*,double opt_simp_garbage_frac);

    /// @brief Verbosity level
    /// @param value must be 0, 1, or 2 (MiniSATSolver*,0=silent, 1=some, 2=more)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_opt_verbosity(MiniSATSolver*,int verb);

    /// @brief The variable activity decay factor
    /// @param value must be in (0, 1)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_var_decay(double);

   /// @brief The clause activity decay factor
    /// @param value must be in (0, 1)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_clause_decay(double decay);

    /// @brief The frequency with which the decision heuristic tries to choose a random variable
    /// @param value must be in [0,1]
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_random_var_freq(double freq);

    /// @brief Used by the random variable selection
    /// @param value must be positive
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_random_seed(double seed);

    /// @brief Controls conflict clause minimization
    /// @param value must be 0, 1, or 2 (0=none, 1=basic, 2=deep)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_ccmin_mode(int mode);

    /// @brief Controls the level of phase saving
    /// @param value must be 0, 1, or 2 (0=none, 1=limited, 2=full)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_phase_saving(int mode);

    /// @brief Randomize the initial activity
    /// @param value boolean value (0=false, others=true)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_rnd_init_act(int flag);

    /// @brief Use the Luby restart sequence
    /// @param value boolean value (0=false, others=true)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_luby_restart(int flag);

    /// @brief The base restart interval
    /// @param value must be a positive integer
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_restart_first(int restart_first);

    /// @brief Restart interval increase factor
    /// @param value must be at least 1.0
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_restart_inc(double restart_inc);

    /// @brief The fraction of wasted memory allowed before a garbage collection is triggered
    /// @param value must be positive
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_garbage_frac(double garbage_frac);

    /// @brief Minimum learnt clause limit
    /// @param value must be at least 0
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_min_learnts_lim(int min_learnts_lim);

    /// @brief Shrink clauses by asymmetric branching
    /// @param value boolean value (0=false, others=true)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_use_asymm(int opt_use_asymm);

    /// @brief Check if a clause is already implied (costly)
    /// @param value boolean value (0=false, others=true)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_use_rcheck(int opt_use_rcheck);

    /// @brief Perform variable elimination
    /// @param value boolean value (0=false, others=true)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_use_elim(int opt_use_elim);

    /// @brief Allow a variable elimination step to grow by a number of clauses
    /// @param value must be at least 0
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_grow(int opt_grow);

    /// @brief Variables are not eliminated if it produces a resolvent with a length above this limit
    /// @param value must be at least -1 (-1 means no limit)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_clause_lim(int opt_clause_lim);

    /// @brief Do not check if subsumption against a clause larger than this
    /// @param value must be at least -1 (-1 means no limit)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_subsumption_lim(int opt_subsumption_lim);

    /// @brief The fraction of wasted memory allowed before a garbage collection is triggered during simplification
    /// @param value must be positive
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_simp_garbage_frac(double opt_simp_garbage_frac);

    /// @brief Verbosity level
    /// @param value must be 0, 1, or 2 (0=silent, 1=some, 2=more)
    /// @return error code, 0 for success, others for invalid parameter
    int minisat_set_global_opt_verbosity(int verb);

    MiniSATSolver *minisat_new_solver();
    /// @brief  Add a new variable to the solver.
    /// @param solver 
    /// @return variable id
    int minisat_new_var(MiniSATSolver* solver);
    void minisat_release_var(MiniSATSolver* solver, int l);
    /// @brief  Add a clause to the solver.
    /// @param solver 
    /// @param ps  array of literals
    /// @param length  length of the array
    /// @return boolean value
    int minisat_add_clause(MiniSATSolver* solver, const int ps[], size_t length);
    /// @brief  Add the empty clause to the solver.
    /// @param solver 
    /// @return boolean value
    int minisat_add_empty_clause(MiniSATSolver* solver);
    /// @brief  Get the value of a literal.
    /// @param solver 
    /// @param x  literal
    /// @return 0 if false, 1 if true, 2 if undefined
    int minisat_value(MiniSATSolver* solver, int x);
      /// @brief  Get the value of a literal in the model.
    /// @param solver 
    /// @param x  literal
    /// @return 0 if false, 1 if true, 2 if undefined
    int minisat_model_value(MiniSATSolver* solver, int x);

    /// @brief  Solve the problem with assumptions.
    /// @param solver 
    /// @param assumps  array of assumptions
    /// @param length  length of the array
    /// @param do_simp  boolean value, recommand true (1=true, 0=false)
    /// @param turn_off_simp  boolean value, recommand false (1=true, 0=false)
    /// @return 10 for sat, 20 for unsat, 30 for unkown
    int minisat_solve_assumps(MiniSATSolver* solver, const int assumps[],
                              size_t length, int do_simp,
                              int turn_off_simp);
     /// @brief  Solve the problem with limited.
    /// @param solver 
    /// @param assumps  array of assumptions
    /// @param length  length of the array
    /// @param do_simp  boolean value, recommand true (1=true, 0=false)
    /// @param turn_off_simp  boolean value, recommand false  (1=true, 0=false)
    /// @return 10 for sat, 20 for unsat, 30 for unkown
    int minisat_solve_limited(MiniSATSolver* solver, const int assumps[],
                              size_t length, int do_simp,
                              int turn_off_simp);
   /// @brief  Solve the problem.
    /// @param solver 
    /// @param do_simp  boolean value, recommand true (1=true, 0=false)
    /// @param turn_off_simp  boolean value, recommand false  (1=true, 0=false)
    /// @return 10 for sat, 20 for unsat, 30 for unkown
    int minisat_solve(MiniSATSolver* solver, int do_simp, int turn_off_simp);
    /// @brief   Perform variable elimination based simplification.
    /// @param solver 
    /// @param assumps  array of assumptions
    /// @param length  length of the array
    /// @param turn_off_elim  boolean value, recommand false  (1=true, 0=false)
    int minisat_eliminate(
        MiniSATSolver* solver,
        int turn_off_elim);
    /// The current number of assigned literals.
    int minisat_nassigns(MiniSATSolver* solver);
    /// The current number of original clauses.
    int minisat_nclauses(MiniSATSolver* solver);
    /// The current number of learnt clauses.
    int minisat_nlearnts(MiniSATSolver* solver);
    /// The current number of variables.
    int minisat_nvars(MiniSATSolver* solver);
    int minisat_nfree_vars(MiniSATSolver* solver);
    void minisat_destroy(MiniSATSolver* solver);
    /// @brief  Check if the solver is okay.
    /// @param solver 
    /// @return boolean value
    int minisat_okay(MiniSATSolver* solver);
#ifdef __cplusplus
}
#endif

#endif
