
#include "glucose_port.h"
#include "simp/SimpSolver.h"
#include "utils/Options.h"

Glucose::Lit make_lit(Glucose::SimpSolver *solver, int val)
{
    int value = abs(val) - 1;
    while (value >= solver->nVars())
    {
        solver->newVar();
    }
    return Glucose::mkLit(value, val < 0);
}
void *glucose_new_solver()
{
    return new Glucose::SimpSolver();
}
void glucose_destroy(void *s)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    delete solver;
}
int glucose_new_var(void *s)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return solver->newVar();
}

int glucose_add_clause(void *s, const int ps[], unsigned long length)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    Glucose::vec<Glucose::Lit> lits;
    for (unsigned long i = 0; i < length; i++)
    {
        lits.push(make_lit(solver, ps[i]));
    }
    return solver->addClause(lits);
}
int glucose_add_empty_clause(void *s)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return solver->addEmptyClause();
}

int glucose_solve_assumps(void *s, const int ps[], unsigned long length, int do_simp, int turn_off_simp)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    Glucose::vec<Glucose::Lit> lits;
    for (unsigned long i = 0; i < length; i++)
    {
        lits.push(make_lit(solver, ps[i]));
    }
    return solver->solve(lits, (int)do_simp, (int)turn_off_simp);
}
int glucose_solve_limited(void *s, const int ps[], unsigned long length, int do_simp, int turn_off_simp)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    Glucose::vec<Glucose::Lit> lits;
    for (unsigned long i = 0; i < length; i++)
    {
        lits.push(make_lit(solver, ps[i]));
    }
    return (Glucose::toInt(solver->solveLimited(lits, (int)do_simp, (int)turn_off_simp)) + 1) * 10;
}
int glucose_solve(void *s, int do_simp, int turn_off_simp)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return solver->solve((int)do_simp, (int)turn_off_simp);
}

int glucose_eliminate(void *s, int turn_off_elim)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return solver->eliminate(turn_off_elim);
}

int glucose_nassigns(void *s)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return solver->nAssigns();
}
int glucose_nclauses(void *s)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return solver->nClauses();
}
int glucose_nlearnts(void *s)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return solver->nLearnts();
}
int glucose_nvars(void *s)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return solver->nVars();
}
int glucose_nfree_vars(void *s)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return solver->nFreeVars();
}
int glucose_value(void *s, int val)
{
    int abs_val = abs(val);

    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    if (abs_val == 0 || abs_val > solver->nVars())
    {
        return 0;
    }
    return ((val < 0) ^ (solver->value(abs_val - 1) == l_True));
}
int glucose_model_value(void *s, int val)
{
    int abs_val = abs(val);

    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    if (abs_val == 0 || abs_val > solver->nVars())
    {
        return 0;
    }
    return (int)(((val < 0) ^ solver->model[abs_val - 1] == l_True));
}
int glucose_okay(void *s)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return (int)solver->okay();
}
void glucose_set_opt_K(double value)
{
    Glucose::set_opt_K(value);
}

void glucose_set_opt_R(double value)
{
    Glucose::set_opt_R(value);
}

void glucose_set_opt_size_lbd_queue(int value)
{
    Glucose::set_opt_size_lbd_queue(value);
}

void glucose_set_opt_size_trail_queue(int value)
{
    Glucose::set_opt_size_trail_queue(value);
}

void glucose_set_opt_first_reduce_db(int value)
{
    Glucose::set_opt_first_reduce_db(value);
}

void glucose_set_opt_inc_reduce_db(int value)
{
    Glucose::set_opt_inc_reduce_db(value);
}

void glucose_set_opt_spec_inc_reduce_db(int value)
{
    Glucose::set_opt_spec_inc_reduce_db(value);
}

void glucose_set_opt_lb_lbd_frozen_clause(int value)
{
    Glucose::set_opt_lb_lbd_frozen_clause(value);
}

void glucose_set_opt_chanseok_hack(bool value)
{
    Glucose::set_opt_chanseok_hack(value);
}

void glucose_set_opt_chanseok_limit(int value)
{
    Glucose::set_opt_chanseok_limit(value);
}

void glucose_set_opt_lb_size_minimzing_clause(int value)
{
    Glucose::set_opt_lb_size_minimzing_clause(value);
}

void glucose_set_opt_lb_lbd_minimzing_clause(int value)
{
    Glucose::set_opt_lb_lbd_minimzing_clause(value);
}

void glucose_set_opt_lcm(bool value)
{
    Glucose::set_opt_lcm(value);
}

void glucose_set_opt_lcm_update_lbd(bool value)
{
    Glucose::set_opt_lcm_update_lbd(value);
}

void glucose_set_opt_var_decay(double value)
{
    Glucose::set_opt_var_decay(value);
}

void glucose_set_opt_max_var_decay(double value)
{
    Glucose::set_opt_max_var_decay(value);
}

void glucose_set_opt_clause_decay(double value)
{
    Glucose::set_opt_clause_decay(value);
}

void glucose_set_opt_random_var_freq(double value)
{
    Glucose::set_opt_random_var_freq(value);
}

void glucose_set_opt_random_seed(double value)
{
    Glucose::set_opt_random_seed(value);
}

void glucose_set_opt_ccmin_mode(int value)
{
    Glucose::set_opt_ccmin_mode(value);
}

void glucose_set_opt_phase_saving(int value)
{
    Glucose::set_opt_phase_saving(value);
}

void glucose_set_opt_rnd_init_act(bool value)
{
    Glucose::set_opt_rnd_init_act(value);
}

void glucose_set_opt_garbage_frac(double value)
{
    Glucose::set_opt_garbage_frac(value);
}

void glucose_set_opt_glu_reduction(bool value)
{
    Glucose::set_opt_glu_reduction(value);
}

void glucose_set_opt_luby_restart(bool value)
{
    Glucose::set_opt_luby_restart(value);
}

void glucose_set_opt_restart_inc(double value)
{
    Glucose::set_opt_restart_inc(value);
}

void glucose_set_opt_luby_restart_factor(int value)
{
    Glucose::set_opt_luby_restart_factor(value);
}

void glucose_set_opt_randomize_phase_on_restarts(int value)
{
    Glucose::set_opt_randomize_phase_on_restarts(value);
}

void glucose_set_opt_fixed_randomize_phase_on_restarts(bool value)
{
    Glucose::set_opt_fixed_randomize_phase_on_restarts(value);
}

void glucose_set_opt_adapt(bool value)
{
    Glucose::set_opt_adapt(value);
}

void glucose_set_opt_forceunsat(bool value)
{
    Glucose::set_opt_forceunsat(value);
}

void glucose_set_opt_use_asymm(bool value)
{
    Glucose::set_opt_use_asymm(value);
}

void glucose_set_opt_use_rcheck(bool value)
{
    Glucose::set_opt_use_rcheck(value);
}

void glucose_set_opt_use_elim(bool value)
{
    Glucose::set_opt_use_elim(value);
}

void glucose_set_opt_grow(int value)
{
    Glucose::set_opt_grow(value);
}

void glucose_set_opt_clause_lim(int value)
{
    Glucose::set_opt_clause_lim(value);
}

void glucose_set_opt_subsumption_lim(int value)
{
    Glucose::set_opt_subsumption_lim(value);
}

void glucose_set_opt_simp_garbage_frac(double value)
{
    Glucose::set_opt_simp_garbage_frac(value);
}

void glucose_set_opt_verbosity(int value)
{
    Glucose::set_opt_verbosity(value);
}
