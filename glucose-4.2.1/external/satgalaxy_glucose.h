#ifndef SATGALAXY_GLUCOSE_H
#define SATGALAXY_GLUCOSE_H


//=================================================================================================

#ifdef __cplusplus
extern "C"
{
#endif
typedef  int boolean;

typedef struct GlucoseSolver GlucoseSolver;
    
    /// @brief get error message by error code 
    /// @param code error code
    /// @return message
    const char* glucose_error_msg(int code);

    int glucose_error(GlucoseSolver* solver);

    /// @brief The constant used to force restart
    /// @param value must be in (0, 1)
    /// @return error code
    int glucose_set_global_opt_K(double value);
    /// @brief The constant used to block restart
    /// @param value must be in (0, 5)
    /// @return error code
    int glucose_set_global_opt_R(double value);
    /// @brief The size of moving average for LBD (restarts)
    /// @param value must be at least 10
    /// @return error code
    int glucose_set_global_opt_size_lbd_queue(int value);
    /// @brief The size of moving average for trail (block restarts)
    /// @param value  must be at least 10
    /// @return error code
    int glucose_set_global_opt_size_trail_queue(int value);
    /// @brief The number of conflicts before the first reduce DB (or the size of learnts if chanseok is used)
    /// @param value  must be a non-negative integer
    /// @return error code
    int glucose_set_global_opt_first_reduce_db(int value);
    /// @brief Increment for reduce DB
    /// @param value  must be a non-negative integer
    /// @return error code
    int glucose_set_global_opt_inc_reduce_db(int value);
    /// @brief Special increment for reduce DB
    /// @param value must be a non-negative integer
    /// @return error code
    int glucose_set_global_opt_spec_inc_reduce_db(int value);
    /// @brief Protect clauses if their LBD decrease and is lower than (for one turn)
    /// @param value must be a non-negative integer
    /// @return error code
    int glucose_set_global_opt_lb_lbd_frozen_clause(int value);
    /// @brief Use Chanseok Oh strategy for LBD (keep all LBD<=co and remove half of firstreduceDB other learnt clauses)
    /// @param value boolean value (1=true, 0=false)
    /// @return error code
    int glucose_set_global_opt_chanseok_hack(boolean value);
    /// @brief Chanseok Oh: all learnt clauses with LBD<=co are permanent
    /// @param value must be a positive integer greater than 1
    /// @return error code
    int glucose_set_global_opt_chanseok_limit(int value);
    /// @brief The min size required to minimize clause
    /// @param value must be at least 3
    /// @return error code
    int glucose_set_global_opt_lb_size_minimzing_clause(int value);
    /// @brief The min LBD required to minimize clause
    /// @param value must be at least 3
    /// @return error code
    int glucose_set_global_opt_lb_lbd_minimzing_clause(int value);
    /// @brief Use inprocessing vivif (ijcai17 paper)
    /// @param value boolean value (1=true, 0=false)
    /// @return error code
    int glucose_set_global_opt_lcm(boolean value);
    /// @brief Updates LBD when doing LCM
    /// @param value boolean value (1=true, 0=false)
    /// @return error code
    int glucose_set_global_opt_lcm_update_lbd(boolean value);
    /// @brief The variable activity decay factor (starting point)
    /// @param value must be in (0, 1)
    /// @return error code
    int glucose_set_global_opt_var_decay(double value);
    /// @brief The maximum variable activity decay factor
    /// @param value must be in (0, 1)
    /// @return error code
    int glucose_set_global_opt_max_var_decay(double value);
    /// @brief The clause activity decay factor
    /// @param value must be in (0, 1)
    /// @return error code
    int glucose_set_global_opt_clause_decay(double value);
    /// @brief The frequency with which the decision heuristic tries to choose a random variable
    /// @param value  must be in [0, 1]
    /// @return error code
    int glucose_set_global_opt_random_var_freq(double value);
    /// @brief Used by the random variable selection
    /// @param value must be positive
    /// @return error code
    int glucose_set_global_opt_random_seed(double value);
    /// @brief  Controls conflict clause minimization (0=none, 1=basic, 2=deep)
    /// @param value must be 0, 1, or 2
    /// @return error code
    int glucose_set_global_opt_ccmin_mode(int value);
    /// @brief Controls phase saving (0=none, 1=basic, 2=deep)
    /// @param value must be 0, 1, or 2
    /// @return error code
    int glucose_set_global_opt_phase_saving(int value);
    /// @brief Randomize the initial activity
    /// @param value  boolean value (1=true, 0=false)
    /// @return error code
    int glucose_set_global_opt_rnd_init_act(boolean value);
    /// @brief The fraction of wasted memory allowed before a garbage collection is triggered
    /// @param value must be positive
    /// @return error code
    int glucose_set_global_opt_garbage_frac(double value);
    /// @brief glucose strategy to fire clause database reduction (must be false to fire Chanseok strategy)
    /// @param value  boolean value (1=true, 0=false)
    /// @return error code
    int glucose_set_global_opt_glu_reduction(boolean value);
    /// @brief  Use the Luby restart sequence
    /// @param value  boolean value (1=true, 0=false)
    /// @return error code
    int glucose_set_global_opt_luby_restart(boolean value);
    /// @brief Restart interval increase factor
    /// @param value must be at least 1.0
    /// @return error code
    int glucose_set_global_opt_restart_inc(double value);
    /// @brief Luby restart factor
    /// @param value must be a positive integer
    /// @return error code
    int glucose_set_global_opt_luby_restart_factor(int value);
    /// @brief The amount of randomization for the phase at each restart (0=none, 1=first branch, 2=first branch (no bad clauses), 3=first branch (only initial clauses))
    /// @param value must be 0, 1, 2, or 3
    /// @return error code
    int glucose_set_global_opt_randomize_phase_on_restarts(int value);
    /// @brief Fixes the first 7 levels at random phase
    /// @param value boolean value (1=true, 0=false)
    /// @return error code
    int glucose_set_global_opt_fixed_randomize_phase_on_restarts(int value);
    /// @brief Adapt dynamically stategies after 100000 conflicts
    /// @param value boolean value (1=true, 0=false)
    /// @return error code
    int glucose_set_global_opt_adapt(int value);
    /// @brief Force the phase for UNSAT
    /// @param value boolean value (1=true, 0=false)
    /// @return error code
    int glucose_set_global_opt_forceunsat(int value);
    /// @brief Shrink clauses by asymmetric branching
    /// @param value boolean value (1=true, 0=false)
    /// @return error code
    int glucose_set_global_opt_use_asymm(int value);
    /// @brief Check if a clause is already implied. (costly)
    /// @param value boolean value (1=true, 0=false)
    /// @return error code
    int glucose_set_global_opt_use_rcheck(int value);
    /// @brief Perform variable elimination.
    /// @param value boolean value (1=true, 0=false)
    /// @return error code
    int glucose_set_global_opt_use_elim(int value);
    /// @brief  Allow a variable elimination step to grow by a number of clauses.
    /// @param value 
    /// @return error code
    int glucose_set_global_opt_grow(int value);
    /// @brief Variables are not eliminated if it produces a resolvent with a length above this limit. -1 means no limit
    /// @param value must be -1 or a positive integer
    /// @return error code
    int glucose_set_global_opt_clause_lim(int value);
    /// @brief Do not check if subsumption against a clause larger than this. -1 means no limit.
    /// @param value must be -1 or a positive integer
    /// @return error code
    int glucose_set_global_opt_subsumption_lim(int value);
    /// @brief The fraction of wasted memory allowed before a garbage collection is triggered during simplification
    /// @param value  must be positive
    /// @return error code
    int glucose_set_global_opt_simp_garbage_frac(double value);
    /// @brief  Verbosity level (0=silent, 1=some, 2=more).
    /// @param value  must be 0, 1, or 2
    /// @return error code
    int glucose_set_global_opt_verbosity(int value);

        /// @brief The constant used to force restart
    /// @param value must be in (GlucoseSolver*,0, 1)
    /// @return error code
    int glucose_set_opt_K(GlucoseSolver*,double value);
    /// @brief The constant used to block restart
    /// @param value must be in (GlucoseSolver*,0, 5)
    /// @return error code
    int glucose_set_opt_R(GlucoseSolver*,double value);
    /// @brief The size of moving average for LBD (GlucoseSolver*,restarts)
    /// @param value must be at least 10
    /// @return error code
    int glucose_set_opt_size_lbd_queue(GlucoseSolver*,int value);
    /// @brief The size of moving average for trail (GlucoseSolver*,block restarts)
    /// @param value  must be at least 10
    /// @return error code
    int glucose_set_opt_size_trail_queue(GlucoseSolver*,int value);
    /// @brief The number of conflicts before the first reduce DB (GlucoseSolver*,or the size of learnts if chanseok is used)
    /// @param value  must be a non-negative integer
    /// @return error code
    int glucose_set_opt_first_reduce_db(GlucoseSolver*,int value);
    /// @brief Increment for reduce DB
    /// @param value  must be a non-negative integer
    /// @return error code
    int glucose_set_opt_inc_reduce_db(GlucoseSolver*,int value);

    /// @brief Protect clauses if their LBD decrease and is lower than (GlucoseSolver*,for one turn)
    /// @param value must be a non-negative integer
    /// @return error code
    int glucose_set_opt_lb_lbd_frozen_clause(GlucoseSolver*,int value);

    /// @brief Chanseok Oh: all learnt clauses with LBD<=co are permanent
    /// @param value must be a positive integer greater than 1
    /// @return error code
    int glucose_set_opt_chanseok_limit(GlucoseSolver*,int value);
    /// @brief The min size required to minimize clause
    /// @param value must be at least 3
    /// @return error code
    int glucose_set_opt_lb_size_minimzing_clause(GlucoseSolver*,int value);
    /// @brief The min LBD required to minimize clause
    /// @param value must be at least 3
    /// @return error code
    int glucose_set_opt_lb_lbd_minimzing_clause(GlucoseSolver*,int value);
    /// @brief Use inprocessing vivif (GlucoseSolver*,ijcai17 paper)
    /// @param value boolean value (GlucoseSolver*,1=true, 0=false)
    /// @return error code
    int glucose_set_opt_lcm(GlucoseSolver*,int value);
    /// @brief Updates LBD when doing LCM
    /// @param value boolean value (GlucoseSolver*,1=true, 0=false)
    /// @return error code
    int glucose_set_opt_lcm_update_lbd(GlucoseSolver*,int value);
    /// @brief The variable activity decay factor (GlucoseSolver*,starting point)
    /// @param value must be in (GlucoseSolver*,0, 1)
    /// @return error code
    int glucose_set_opt_var_decay(GlucoseSolver*,double value);
    /// @brief The maximum variable activity decay factor
    /// @param value must be in (GlucoseSolver*,0, 1)
    /// @return error code
    int glucose_set_opt_max_var_decay(GlucoseSolver*,double value);
    /// @brief The clause activity decay factor
    /// @param value must be in (GlucoseSolver*,0, 1)
    /// @return error code
    int glucose_set_opt_clause_decay(GlucoseSolver*,double value);
    /// @brief The frequency with which the decision heuristic tries to choose a random variable
    /// @param value  must be in [0, 1]
    /// @return error code
    int glucose_set_opt_random_var_freq(GlucoseSolver*,double value);
    /// @brief Used by the random variable selection
    /// @param value must be positive
    /// @return error code
    int glucose_set_opt_random_seed(GlucoseSolver*,double value);
    /// @brief  Controls conflict clause minimization (GlucoseSolver*,0=none, 1=basic, 2=deep)
    /// @param value must be 0, 1, or 2
    /// @return error code
    int glucose_set_opt_ccmin_mode(GlucoseSolver*,int value);
    /// @brief Controls phase saving (GlucoseSolver*,0=none, 1=basic, 2=deep)
    /// @param value must be 0, 1, or 2
    /// @return error code
    int glucose_set_opt_phase_saving(GlucoseSolver*,int value);
    /// @brief Randomize the initial activity
    /// @param value  boolean value (GlucoseSolver*,1=true, 0=false)
    /// @return error code
    int glucose_set_opt_rnd_init_act(GlucoseSolver*,boolean value);
    /// @brief The fraction of wasted memory allowed before a garbage collection is triggered
    /// @param value must be positive
    /// @return error code
    int glucose_set_opt_garbage_frac(GlucoseSolver*,double value);

    /// @brief Shrink clauses by asymmetric branching
    /// @param value boolean value (GlucoseSolver*,1=true, 0=false)
    /// @return error code
    int glucose_set_opt_use_asymm(GlucoseSolver*,boolean value);
    /// @brief Check if a clause is already implied. (GlucoseSolver*,costly)
    /// @param value boolean value (GlucoseSolver*,1=true, 0=false)
    /// @return error code
    int glucose_set_opt_use_rcheck(GlucoseSolver*,boolean value);
    /// @brief Perform variable elimination.
    /// @param value boolean value (GlucoseSolver*,1=true, 0=false)
    /// @return error code
    int glucose_set_opt_use_elim(GlucoseSolver*,boolean value);
    /// @brief  Allow a variable elimination step to grow by a number of clauses.
    /// @param value 
    /// @return error code
    int glucose_set_opt_grow(GlucoseSolver*,int value);
    /// @brief Variables are not eliminated if it produces a resolvent with a length above this limit. -1 means no limit
    /// @param value must be -1 or a positive integer
    /// @return error code
    int glucose_set_opt_clause_lim(GlucoseSolver*,int value);
    /// @brief Do not check if subsumption against a clause larger than this. -1 means no limit.
    /// @param value must be -1 or a positive integer
    /// @return error code
    int glucose_set_opt_subsumption_lim(GlucoseSolver*,int value);
    /// @brief The fraction of wasted memory allowed before a garbage collection is triggered during simplification
    /// @param value  must be positive
    /// @return error code
    int glucose_set_opt_simp_garbage_frac(GlucoseSolver*,double value);
    /// @brief  Verbosity level (GlucoseSolver*,0=silent, 1=some, 2=more).
    /// @param value  must be 0, 1, or 2
    /// @return error code
    int glucose_set_opt_verbosity(GlucoseSolver*,int value);


    GlucoseSolver *glucose_new_solver();
    /// @brief  Add a new variable to the solver.
    /// @param solver 
    /// @return variable id
    int glucose_new_var(GlucoseSolver *solver);
    /// @brief  Add a clause to the solver.
    /// @param solver 
    /// @param ps  array of literals
    /// @param length  length of the array
    /// @return boolean value
    boolean glucose_add_clause(GlucoseSolver *solver, const int ps[], unsigned long length);
    /// @brief  Add the empty clause to the solver.
    /// @param solver 
    /// @return boolean value
    boolean glucose_add_empty_clause(GlucoseSolver *solver); 
    /// @brief  Get the value of a literal.
    /// @param solver 
    /// @param x  literal
    /// @return 0 if false, 1 if true, 2 if undefined
    int glucose_value(GlucoseSolver *solver, int x);
    /// @brief  Get the value of a literal in the model.
    /// @param solver 
    /// @param x  literal
    /// @return 0 if false, 1 if true, 2 if undefined
    int glucose_model_value(GlucoseSolver *solver, int x);

    /// @brief  Solve the problem with assumptions.
    /// @param solver 
    /// @param assumps  array of assumptions
    /// @param length  length of the array
    /// @param do_simp  boolean value, recommand true (1=true, 0=false)
    /// @param turn_off_simp  boolean value, recommand false  (1=true, 0=false)
    /// @return 10 for sat, 20 for unsat, 30 for unkown
    int glucose_solve_assumps(GlucoseSolver *solver, const int assumps[],
                              size_t length, boolean do_simp,
                              boolean turn_off_simp);

    /// @brief  Solve the problem with limited.
    /// @param solver 
    /// @param assumps  array of assumptions
    /// @param length  length of the array
    /// @param do_simp  boolean value, recommand true (1=true, 0=false)
    /// @param turn_off_simp  boolean value, recommand false  (1=true, 0=false)
    /// @return 10 for sat, 20 for unsat, 30 for unkown
    int glucose_solve_limited(GlucoseSolver *solver, const int assumps[],
                              size_t length, boolean do_simp,
                              boolean turn_off_simp);
    /// @brief  Solve the problem.
    /// @param solver 
    /// @param do_simp  boolean value, recommand true (1=true, 0=false)
    /// @param turn_off_simp  boolean value, recommand false  (1=true, 0=false)
    /// @return boolean value, recommand true (1=true, 0=false)
    boolean glucose_solve(GlucoseSolver *solver, boolean do_simp, boolean turn_off_simp);
    /// @brief   Perform variable elimination based simplification.
    /// @param solver 
    /// @param assumps  array of assumptions
    /// @param length  length of the array
    /// @param turn_off_elim  boolean value, recommand false  (1=true, 0=false)
    int glucose_eliminate(
        GlucoseSolver *solver,
        int turn_off_elim);
    /// @brief The current number of assigned literals.
    /// @param solver 
    /// @return The current number of assigned literals.
    int glucose_nassigns(GlucoseSolver *solver);
    /// @brief The current number of original clauses.
    /// @param solver 
    /// @return 
    int glucose_nclauses(GlucoseSolver *solver); 
    /// @brief The current number of learnt clauses.
    /// @param solver 
    /// @return 
    int glucose_nlearnts(GlucoseSolver *solver); 
    /// @brief The current number of variables.
    /// @param solver 
    /// @return 
    int glucose_nvars(GlucoseSolver *solver);
    int glucose_nfree_vars(GlucoseSolver *solver);
    void glucose_destroy(GlucoseSolver *solver);
    /// @brief  Check if the solver is okay.
    /// @param solver 
    /// @return boolean value
    boolean glucose_okay(GlucoseSolver *solver);
#ifdef __cplusplus
}
#endif

#endif
