
#ifndef Glucose_Options_h
#define Glucose_Options_h

namespace Glucose
{

    extern double opt_K;
    extern double opt_R;
    extern int opt_size_lbd_queue;
    extern int opt_size_trail_queue;

    extern int opt_first_reduce_db;
    extern int opt_inc_reduce_db;
    extern int opt_spec_inc_reduce_db;
    extern int opt_lb_lbd_frozen_clause;
    extern bool opt_chanseok_hack;
    extern int opt_chanseok_limit;

    extern int opt_lb_size_minimzing_clause;
    extern int opt_lb_lbd_minimzing_clause;
    extern bool opt_lcm;
    extern bool opt_lcm_update_lbd;

    extern double opt_var_decay;
    extern double opt_max_var_decay;
    extern double opt_clause_decay;
    extern double opt_random_var_freq;
    extern double opt_random_seed;
    extern int opt_ccmin_mode;
    extern int opt_phase_saving;
    extern bool opt_rnd_init_act;
    extern double opt_garbage_frac;
    extern bool opt_glu_reduction;
    extern bool opt_luby_restart;
    extern double opt_restart_inc;
    extern int opt_luby_restart_factor;

    extern int opt_randomize_phase_on_restarts;
    extern bool opt_fixed_randomize_phase_on_restarts;

    extern bool opt_adapt;

    extern bool opt_forceunsat;

    extern bool opt_use_asymm;
    extern bool opt_use_rcheck;
    extern bool opt_use_elim;
    extern int opt_grow;
    extern int opt_clause_lim;
    extern int opt_subsumption_lim;
    extern double opt_simp_garbage_frac;
    extern int opt_verbosity;

    void set_opt_K(double value);
    void set_opt_R(double value);
    void set_opt_size_lbd_queue(int value);
    void set_opt_size_trail_queue(int value);
    void set_opt_first_reduce_db(int value);
    void set_opt_inc_reduce_db(int value);
    void set_opt_spec_inc_reduce_db(int value);
    void set_opt_lb_lbd_frozen_clause(int value);
    void set_opt_chanseok_hack(bool value);
    void set_opt_chanseok_limit(int value);
    void set_opt_lb_size_minimzing_clause(int value);
    void set_opt_lb_lbd_minimzing_clause(int value);
    void set_opt_lcm(bool value);
    void set_opt_lcm_update_lbd(bool value);
    void set_opt_var_decay(double value);
    void set_opt_max_var_decay(double value);
    void set_opt_clause_decay(double value);
    void set_opt_random_var_freq(double value);
    void set_opt_random_seed(double value);
    void set_opt_ccmin_mode(int value);
    void set_opt_phase_saving(int value);
    void set_opt_rnd_init_act(bool value);
    void set_opt_garbage_frac(double value);
    void set_opt_glu_reduction(bool value);
    void set_opt_luby_restart(bool value);
    void set_opt_restart_inc(double value);
    void set_opt_luby_restart_factor(int value);
    void set_opt_randomize_phase_on_restarts(int value);
    void set_opt_fixed_randomize_phase_on_restarts(bool value);
    void set_opt_adapt(bool value);
    void set_opt_forceunsat(bool value);
    void set_opt_use_asymm(bool value);
    void set_opt_use_rcheck(bool value);
    void set_opt_use_elim(bool value);
    void set_opt_grow(int value);
    void set_opt_clause_lim(int value);
    void set_opt_subsumption_lim(int value);
    void set_opt_simp_garbage_frac(double value);
    void set_opt_verbosity(int value);

} // namespace Glucose

#endif