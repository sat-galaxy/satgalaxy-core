
#ifndef Minisat_Options_h
#define Minisat_Options_h

namespace Minisat
{

    extern double opt_var_decay;
    extern double opt_clause_decay;
    extern double opt_random_var_freq;
    extern double opt_random_seed;
    extern int opt_ccmin_mode;
    extern int opt_phase_saving;
    extern bool opt_rnd_init_act;
    extern bool opt_luby_restart;
    extern int opt_restart_first;
    extern double opt_restart_inc;
    extern double opt_garbage_frac;
    extern int opt_min_learnts_lim;
    extern bool opt_use_asymm;
    extern bool opt_use_rcheck;
    extern bool opt_use_elim;
    extern int opt_grow;
    extern int opt_clause_lim;
    extern int opt_subsumption_lim;
    extern double opt_simp_garbage_frac;

    void set_opt_var_decay(double decay);
    void set_opt_clause_decay(double decay);
    void set_opt_random_var_freq(double freq);
    void set_opt_random_seed(double seed);
    void set_opt_ccmin_mode(int mode);
    void set_opt_phase_saving(int mode);
    void set_opt_rnd_init_act(bool flag);
    void set_opt_luby_restart(bool flag);
    void set_opt_restart_first(int restart_first);
    void set_opt_restart_inc(double restart_inc);
    void set_opt_garbage_frac(double garbage_frac);
    void set_opt_min_learnts_lim(int min_learnts_lim);
    void set_opt_use_asymm(bool opt_use_asymm);
    void set_opt_use_rcheck(bool opt_use_rcheck);
    void set_opt_use_elim(bool opt_use_elim);
    void set_opt_grow(int opt_grow);
    void set_opt_clause_lim(int opt_clause_lim);
    // okok
    void set_opt_subsumption_lim(int opt_subsumption_lim);
    void set_opt_simp_garbage_frac(double opt_simp_garbage_frac);

}

#endif
