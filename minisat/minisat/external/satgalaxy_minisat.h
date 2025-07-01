#ifndef SATGALAXY_MINISAT_H
#define SATGALAXY_MINISAT_H

//=================================================================================================

#ifdef __cplusplus
extern "C"
{
#endif
    // The variable activity decay factor
    void minisat_set_opt_var_decay(double decay);
    void minisat_set_opt_clause_decay(double decay);
    void minisat_set_opt_random_var_freq(double freq);
    void minisat_set_opt_random_seed(double seed);
    void minisat_set_opt_ccmin_mode(int mode);
    void minisat_set_opt_phase_saving(int mode);
    void minisat_set_opt_rnd_init_act(int flag);
    void minisat_set_opt_luby_restart(int flag);
    void minisat_set_opt_restart_first(int restart_first);
    void minisat_set_opt_restart_inc(double restart_inc);
    void minisat_set_opt_garbage_frac(double garbage_frac);
    void minisat_set_opt_min_learnts_lim(int min_learnts_lim);
    void minisat_set_opt_use_asymm(int opt_use_asymm);
    void minisat_set_opt_use_rcheck(int opt_use_rcheck);
    void minisat_set_opt_use_elim(int opt_use_elim);
    void minisat_set_opt_grow(int opt_grow);
    void minisat_set_opt_clause_lim(int opt_clause_lim);
    void minisat_set_opt_subsumption_lim(int opt_subsumption_lim);
    void minisat_set_opt_simp_garbage_frac(double opt_simp_garbage_frac);
    void minisat_set_opt_verbosity(int verb);



    void *minisat_new_solver();
    int minisat_new_var(const void *solver);
    void minisat_release_var(const void *solver, int l);
    int minisat_add_clause(const void *solver, const int ps[], unsigned long length);
    int minisat_add_empty_clause(const void *solver); // Add the empty clause to the solver.
    // start with 1
    int minisat_value(const void *solver, int x);
    int minisat_model_value(const void *solver, int x);

    // Solving:
    // return as bool, do_simp and turn_off_simp as bool
    int minisat_solve_assumps(const void *solver, const int assumps[],
                              unsigned long length, int do_simp,
                              int turn_off_simp);
    //  10 for sat, 20 for unsat, 30 for unkown 
    int minisat_solve_limited(const void *solver, const int assumps[],
                              unsigned long length, int do_simp,
                              int turn_off_simp );
    // return as bool
    int minisat_solve(const void *solver, int do_simp , int turn_off_simp);
    int minisat_eliminate(
        const void *solver,
        int turn_off_elim);                     // Perform variable elimination based simplification.
    int minisat_nassigns(const void *solver); // The current number of assigned literals.
    int minisat_nclauses(const void *solver); // The current number of original clauses.
    int minisat_nlearnts(const void *solver); // The current number of learnt clauses.
    int minisat_nvars(const void *solver);    // The current number of variables.
    int minisat_nfree_vars(const void *solver);
    void minisat_destroy(const void *solver);
    // return bool
    int minisat_okay(const void *solver);
#ifdef __cplusplus
}
#endif

#endif
