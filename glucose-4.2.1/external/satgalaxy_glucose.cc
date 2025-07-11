
#include "satgalaxy_glucose.h"
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
void glucose_destroy(const void *s)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    delete solver;
}
int glucose_new_var(const void *s)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return solver->newVar();
}

int glucose_add_clause(const void *s, const int ps[], unsigned long length)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    Glucose::vec<Glucose::Lit> lits;
    for (unsigned long i = 0; i < length; i++)
    {
        lits.push(make_lit(solver, ps[i]));
    }
    return solver->addClause(lits);
}
int glucose_add_empty_clause(const void *s)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return solver->addEmptyClause();
}

int glucose_solve_assumps(const void *s, const int ps[], unsigned long length, int do_simp, int turn_off_simp)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    Glucose::vec<Glucose::Lit> lits;
    for (unsigned long i = 0; i < length; i++)
    {
        lits.push(make_lit(solver, ps[i]));
    }
    return solver->solve(lits, (int)do_simp, (int)turn_off_simp);
}
int glucose_solve_limited(const void *s, const int ps[], unsigned long length, int do_simp, int turn_off_simp)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    Glucose::vec<Glucose::Lit> lits;
    for (unsigned long i = 0; i < length; i++)
    {
        lits.push(make_lit(solver, ps[i]));
    }
    return (Glucose::toInt(solver->solveLimited(lits, (bool)do_simp, (bool)turn_off_simp)) + 1) * 10;
}
int glucose_solve(const void *s, int do_simp, int turn_off_simp)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return solver->solve((int)do_simp, (int)turn_off_simp);
}

int glucose_eliminate(const void *s, int turn_off_elim)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return solver->eliminate(turn_off_elim);
}

int glucose_nassigns(const void *s)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return solver->nAssigns();
}
int glucose_nclauses(const void *s)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return solver->nClauses();
}
int glucose_nlearnts(const void *s)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return solver->nLearnts();
}
int glucose_nvars(const void *s)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return solver->nVars();
}
int glucose_nfree_vars(const void *s)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return solver->nFreeVars();
}
int glucose_value(const void *s, int val)
{
    int abs_val = abs(val);

    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    if (abs_val == 0 || abs_val > solver->nVars())
    {
        return 0;
    }
    return ((val < 0) ^ (solver->value(abs_val - 1) == l_True));
}
int glucose_model_value(const void *s, int val)
{
    int abs_val = abs(val);

    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    if (abs_val == 0 || abs_val > solver->nVars())
    {
        return 0;
    }
    return (int)(((val < 0) ^ solver->model[abs_val - 1] == l_True));
}
int glucose_okay(const void *s)
{
    Glucose::SimpSolver *solver = (Glucose::SimpSolver *)s;
    return (int)solver->okay();
}
const char *glucose_error_msg(int code)
{
    switch (code)
    {
    case 100:
        return "K must be in (0, 1)";
    case 101:
        return "R must be at least 10";
    case 102:
        return "size_lbd_queue must be at least 10";
    case 103:
        return "size_trail_queue must be at least 10";
    case 104:
        return "first_reduce_db must be a non-negative integer";
    case 105:
        return "inc_reduce_db must be a non-negative integer";
    case 106:
        return "spec_inc_reduce_db must be a non-negative integer";
    case 107:
        return "lb_lbd_frozen_clause must be a non-negative integer";
    case 108:
        return "chanseok_limit must be a positive integer greater than 1";
    case 109:
        return "lb_size_minimzing_clause must be at least 3";
    case 110:
        return "var_decay must in (0,1)";
    case 111:
        return "max_var_decay must be in (0,1)";
    case 112:
        return "clause_decay must be in (0,1)";
    case 113:
        return "random_var_freq  must be in [0, 1]";
    case 114:
        return "random_seed must be positive";
    case 115:
        return "ccmin_mode must be  0, 1, or 2";
    case 116:
        return "phase_saving  must be 0, 1, or 2";
    case 117:
        return "garbage_frac must >0";
    case 118:
        return "restart_inc must >=1.0";
    case 119:
        return "luby_restart_factor must >=1";
    case 120:
        return "randomize_phase must be 0-3";
    case 121:
        return "grow must >=0";
    case 122:
        return "clause_lim must >=-1";
    case 123:
        return "subsumption_lim must >=-1";
    case 124:
        return "simp_garbage_frac must >0";
    case 125:
        return "verbosity must be 0-2";
    default:
        return "Unknown error";
    }
}
int glucose_set_opt_K(double value)
{
    if (value > 0 && value < 1)
    {
        Glucose::set_opt_K(value);
        return 0;
    }
    else
    {
        return 100;
    }
}

int glucose_set_opt_R(double value)
{
    if (value > 0 && value < 5)
    {
        Glucose::set_opt_R(value);
        return 0;
    }
    else
    {
        return 101;
    }
}

int glucose_set_opt_size_lbd_queue(int value)
{
    if (value < 10)
    {
        return 102;
    }
    Glucose::set_opt_size_lbd_queue(value);
    return 0;
}

int glucose_set_opt_size_trail_queue(int value)
{
    if (value < 0)
    {
        return 103;
    }

    Glucose::set_opt_size_trail_queue(value);
    return 0;
}

int glucose_set_opt_first_reduce_db(int value)
{
    if (value < 0)
    {
        return 104;
    }

    Glucose::set_opt_first_reduce_db(value);
    return 0;
}

int glucose_set_opt_inc_reduce_db(int value)
{
    if (value < 0)
    {
        return 105;
    }
    Glucose::set_opt_inc_reduce_db(value);
    return 0;
}

int glucose_set_opt_spec_inc_reduce_db(int value)
{
    if (value < 0)
    {
        return 106;
    }
    Glucose::set_opt_spec_inc_reduce_db(value);
    return 0;
}

int glucose_set_opt_lb_lbd_frozen_clause(int value)
{
    if (value < 0)
    {
        return 107;
    }

    Glucose::set_opt_lb_lbd_frozen_clause(value);
    return 0;
}

int glucose_set_opt_chanseok_hack(int value)
{
    Glucose::set_opt_chanseok_hack(value);
    return 0;
}

int glucose_set_opt_chanseok_limit(int value)
{
    if (value < 2)
    {
        return 108;
    }

    Glucose::set_opt_chanseok_limit(value);
    return 0;
}

int glucose_set_opt_lb_size_minimzing_clause(int value)
{
    if (value < 3)
    {
        return 109;
    }

    Glucose::set_opt_lb_size_minimzing_clause(value);
    return 0;
}

int glucose_set_opt_lb_lbd_minimzing_clause(int value)
{
    if (value < 3)
    {
        return 109;
    }
    Glucose::set_opt_lb_lbd_minimzing_clause(value);
    return 0;
}

int glucose_set_opt_lcm(int value)
{
    Glucose::set_opt_lcm(value);
    return 0;
}

int glucose_set_opt_lcm_update_lbd(int value)
{
    Glucose::set_opt_lcm_update_lbd(value);
    return 0;
}

int glucose_set_opt_var_decay(double value)
{
    if (value >= 1 || value <= 0)
    {
        return 110;
    }

    Glucose::set_opt_var_decay(value);
    return 0;
}

int glucose_set_opt_max_var_decay(double value)
{
    if (value >= 1 || value <= 0)
    {
        return 111;
    }
    Glucose::set_opt_max_var_decay(value);
    return 0;
}

int glucose_set_opt_clause_decay(double value)
{
    if (value >= 1 || value <= 0)
    {
        return 112;
    }
    Glucose::set_opt_clause_decay(value);
    return 0;
}

int glucose_set_opt_random_var_freq(double value)
{
    if (value > 1 || value < 0)
    {
        return 113;
    }
    Glucose::set_opt_random_var_freq(value);
    return 0;
}

int glucose_set_opt_random_seed(double value)
{
    if (value <= 0)
    {
        return 114;
    }

    Glucose::set_opt_random_seed(value);
    return 0;
}

int glucose_set_opt_ccmin_mode(int value)
{
    if (value < 0 || value > 2)
    {
        return 115;
    }

    Glucose::set_opt_ccmin_mode(value);
    return 0;
}

int glucose_set_opt_phase_saving(int value)
{
    if (value < 0 || value > 2)
    {
        return 116;
    }
    Glucose::set_opt_phase_saving(value);
    return 0;
}

int glucose_set_opt_rnd_init_act(int value)
{
    Glucose::set_opt_rnd_init_act(value);
    return 0;
}

int glucose_set_opt_garbage_frac(double value)
{
    if (value <= 0)
    {
        return 117;
    }
    Glucose::set_opt_garbage_frac(value);
    return 0;
}

int glucose_set_opt_glu_reduction(int value)
{
    Glucose::set_opt_glu_reduction(value);
    return 0;
}

int glucose_set_opt_luby_restart(int value)
{
    Glucose::set_opt_luby_restart(value);
    return 0;
}

int glucose_set_opt_restart_inc(double value)
{
    if (value < 1)
    {
        return 118;
    }

    Glucose::set_opt_restart_inc(value);
    return 0;
}

int glucose_set_opt_luby_restart_factor(int value)
{
    if (value < 1)
    {
        return 119;
    }

    Glucose::set_opt_luby_restart_factor(value);
    return 0;
}

int glucose_set_opt_randomize_phase_on_restarts(int value)
{
    if (value < 0 || value > 3)
    {
        return 120;
    }

    Glucose::set_opt_randomize_phase_on_restarts(value);
    return 0;
}

int glucose_set_opt_fixed_randomize_phase_on_restarts(int value)
{
    Glucose::set_opt_fixed_randomize_phase_on_restarts(value);
    return 0;
}

int glucose_set_opt_adapt(int value)
{
    Glucose::set_opt_adapt(value);
    return 0;
}

int glucose_set_opt_forceunsat(int value)
{
    Glucose::set_opt_forceunsat(value);
    return 0;
}

int glucose_set_opt_use_asymm(int value)
{
    Glucose::set_opt_use_asymm(value);
    return 0;
}

int glucose_set_opt_use_rcheck(int value)
{
    Glucose::set_opt_use_rcheck(value);
    return 0;
}

int glucose_set_opt_use_elim(int value)
{
    Glucose::set_opt_use_elim(value);
    return 0;
}

int glucose_set_opt_grow(int value)
{
    if (value < 0)
    {
        return 121;
    }

    Glucose::set_opt_grow(value);
    return 0;
}

int glucose_set_opt_clause_lim(int value)
{
    if (value < -1)
    {
        return 122;
    }

    Glucose::set_opt_clause_lim(value);
    return 0;
}

int glucose_set_opt_subsumption_lim(int value)
{
    if (value < -1)
    {
        return 123;
    }
    Glucose::set_opt_subsumption_lim(value);
    return 0;
}

int glucose_set_opt_simp_garbage_frac(double value)
{
    if (value <= 0)
    {
        return 124;
    }
    Glucose::set_opt_simp_garbage_frac(value);
    return 0;
}

int glucose_set_opt_verbosity(int value)
{
    if (value < 0 || value > 2)
    {
        return 125;
    }

    Glucose::set_opt_verbosity(value);
    return 0;
}
