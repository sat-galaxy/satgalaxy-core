#ifndef SATGALAXY_GLUCOSE_H
#define SATGALAXY_GLUCOSE_H


//=================================================================================================

#ifdef __cplusplus
extern "C"
{
#endif
    // The variable activity decay factor
    void glucose_set_opt_K(double value);
    void glucose_set_opt_R(double value);
    void glucose_set_opt_size_lbd_queue(int value);
    void glucose_set_opt_size_trail_queue(int value);
    void glucose_set_opt_first_reduce_db(int value);
    void glucose_set_opt_inc_reduce_db(int value);
    void glucose_set_opt_spec_inc_reduce_db(int value);
    void glucose_set_opt_lb_lbd_frozen_clause(int value);
    void glucose_set_opt_chanseok_hack(int value);
    void glucose_set_opt_chanseok_limit(int value);
    void glucose_set_opt_lb_size_minimzing_clause(int value);
    void glucose_set_opt_lb_lbd_minimzing_clause(int value);
    void glucose_set_opt_lcm(int value);
    void glucose_set_opt_lcm_update_lbd(int value);
    void glucose_set_opt_var_decay(double value);
    void glucose_set_opt_max_var_decay(double value);
    void glucose_set_opt_clause_decay(double value);
    void glucose_set_opt_random_var_freq(double value);
    void glucose_set_opt_random_seed(double value);
    void glucose_set_opt_ccmin_mode(int value);
    void glucose_set_opt_phase_saving(int value);
    void glucose_set_opt_rnd_init_act(int value);
    void glucose_set_opt_garbage_frac(double value);
    void glucose_set_opt_glu_reduction(int value);
    void glucose_set_opt_luby_restart(int value);
    void glucose_set_opt_restart_inc(double value);
    void glucose_set_opt_luby_restart_factor(int value);
    void glucose_set_opt_randomize_phase_on_restarts(int value);
    void glucose_set_opt_fixed_randomize_phase_on_restarts(int value);
    void glucose_set_opt_adapt(int value);
    void glucose_set_opt_forceunsat(int value);
    void glucose_set_opt_use_asymm(int value);
    void glucose_set_opt_use_rcheck(int value);
    void glucose_set_opt_use_elim(int value);
    void glucose_set_opt_grow(int value);
    void glucose_set_opt_clause_lim(int value);
    void glucose_set_opt_subsumption_lim(int value);
    void glucose_set_opt_simp_garbage_frac(double value);
    void glucose_set_opt_verbosity(int value);



    void *glucose_new_solver();
    int glucose_new_var(const void *solver);
    int glucose_add_clause(const void *solver, const int ps[], unsigned long length);
    int glucose_add_empty_clause(const void *solver); // Add the empty clause to the solver.
    // start with 1
    int glucose_value(const void *solver, int x);
    int glucose_model_value(const void *solver, int x);

    // Solving:
    // return as int, do_simp and turn_off_simp as int
    int glucose_solve_assumps(const void *solver, const int assumps[],
                              unsigned long length, int do_simp,
                              int turn_off_simp);
    //  10 for sat, 20 for unsat, 30 for unkown
    int glucose_solve_limited(const void *solver, const int assumps[],
                              unsigned long length, int do_simp,
                              int turn_off_simp);
    // return as int
    int glucose_solve(const void *solver, int do_simp, int turn_off_simp);
    int glucose_eliminate(
        const void *solver,
        int turn_off_elim);             // Perform variable elimination based simplification.
    int glucose_nassigns(const void *solver); // The current number of assigned literals.
    int glucose_nclauses(const void *solver); // The current number of original clauses.
    int glucose_nlearnts(const void *solver); // The current number of learnt clauses.
    int glucose_nvars(const void *solver);    // The current number of variables.
    int glucose_nfree_vars(const void *solver);
    void glucose_destroy(const void *solver);
    // return int
    int glucose_okay(const void *solver);
#ifdef __cplusplus
}
#endif

#endif
