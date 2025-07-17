
#include "satgalaxy_minisat.h"
#include "minisat/simp/SimpSolver.h"
#include "minisat/utils/Options.h"

struct MiniSATSolver
{
  int last_error;
  Minisat::SimpSolver *solver;
};
Minisat::Lit make_lit(Minisat::SimpSolver *solver, int val)
{
    int value = abs(val) - 1;
    while (value >= solver->nVars())
    {
        solver->newVar();
    }
    return Minisat::mkLit(value, val < 0);
}
MiniSATSolver *minisat_new_solver()
{
    MiniSATSolver *solver = new MiniSATSolver();
    solver->solver = new Minisat::SimpSolver();
    return solver;
}
void minisat_destroy(MiniSATSolver* s)
{
    Minisat::SimpSolver *solver = s->solver;
    delete solver;
}
int minisat_new_var(MiniSATSolver* s)
{
    Minisat::SimpSolver *solver =  s->solver;
    return solver->newVar();
}
void minisat_release_var(MiniSATSolver* s, int l)
{
    Minisat::SimpSolver *solver =  s->solver;
    solver->releaseVar(make_lit(solver, l));
}

int minisat_add_clause(MiniSATSolver* s, const int ps[], unsigned long length)
{
    Minisat::SimpSolver *solver =  s->solver;
    Minisat::vec<Minisat::Lit> lits;
    for (unsigned long i = 0; i < length; i++)
    {
        lits.push(make_lit(solver, ps[i]));
    }
    return solver->addClause(lits);
}
int minisat_add_empty_clause(MiniSATSolver* s)
{
    Minisat::SimpSolver *solver =  s->solver;
    return solver->addEmptyClause();
}

int minisat_solve_assumps(MiniSATSolver* s, const int ps[], unsigned long length, int do_simp, int turn_off_simp)
{
    Minisat::SimpSolver *solver =  s->solver;
    Minisat::vec<Minisat::Lit> lits;
    for (unsigned long i = 0; i < length; i++)
    {
        lits.push(make_lit(solver, ps[i]));
    }
    return solver->solve(lits, (int)do_simp, (int)turn_off_simp);
}
int minisat_solve_limited(MiniSATSolver* s, const int ps[], unsigned long length, int do_simp, int turn_off_simp)
{
    Minisat::SimpSolver *solver =  s->solver;
    Minisat::vec<Minisat::Lit> lits;
    for (unsigned long i = 0; i < length; i++)
    {
        lits.push(make_lit(solver, ps[i]));
    }
    return (Minisat::toInt(solver->solveLimited(lits, (int)do_simp, (int)turn_off_simp)) + 1) * 10;
}
int minisat_solve(MiniSATSolver* s, int do_simp, int turn_off_simp)
{
    Minisat::SimpSolver *solver =  s->solver;
    return solver->solve((int)do_simp, (int)turn_off_simp);
}

int minisat_eliminate(MiniSATSolver* s, int turn_off_elim)
{
    Minisat::SimpSolver *solver =  s->solver;
    return solver->eliminate(turn_off_elim);
}

int minisat_nassigns(MiniSATSolver* s)
{
    Minisat::SimpSolver *solver =  s->solver;
    return solver->nAssigns();
}
int minisat_nclauses(MiniSATSolver* s)
{
    Minisat::SimpSolver *solver =  s->solver;
    return solver->nClauses();
}
int minisat_nlearnts(MiniSATSolver* s)
{
    Minisat::SimpSolver *solver =  s->solver;
    return solver->nLearnts();
}
int minisat_nvars(MiniSATSolver* s)
{
    Minisat::SimpSolver *solver =  s->solver;
    return solver->nVars();
}
int minisat_nfree_vars(MiniSATSolver* s)
{
    Minisat::SimpSolver *solver =  s->solver;
    return solver->nFreeVars();
}
int minisat_value(MiniSATSolver* s, int val)
{
    int abs_val = abs(val);

    Minisat::SimpSolver *solver =  s->solver;
    if (abs_val == 0 || abs_val > solver->nVars())
    {
        return 0;
    }
    return ((val < 0) ^ (solver->value(abs_val - 1) == Minisat::l_True));
}
int minisat_model_value(MiniSATSolver* s, int val)
{
    int abs_val = abs(val);

    Minisat::SimpSolver *solver =  s->solver;
    if (abs_val == 0 || abs_val > solver->nVars())
    {
        return 0;
    }
    return (int)(((val < 0) ^ solver->model[abs_val - 1] == Minisat::l_True));
}
int minisat_okay(MiniSATSolver* s)
{
    Minisat::SimpSolver *solver =  s->solver;
    return (int)solver->okay();
}

int minisat_set_opt_var_decay(double decay)
{
    if (decay <= 0 || decay >= 1)
    {
        return 100;
    }
    Minisat::set_opt_var_decay(decay);
    return 0;
}

int minisat_set_opt_clause_decay(double decay)
{
    if (decay <= 0 || decay >= 1)
    {
        return 101;
    }
    Minisat::set_opt_clause_decay(decay);
    return 0;
}
int minisat_set_opt_random_var_freq(double freq)
{
    if (freq < 0 || freq > 1)
    {
        return 102;
    }
    Minisat::set_opt_random_var_freq(freq);
    return 0;
}
int minisat_set_opt_random_seed(double seed)
{
    if (seed >= 0)
    {
        return 103;
    }
    Minisat::set_opt_random_seed(seed);
    return 0;
}
int minisat_set_opt_ccmin_mode(int mode)
{
    if (mode != 0 && mode != 1 && mode != 2)
    {
        return 104;
    }
    Minisat::set_opt_ccmin_mode(mode);
    return 0;
}
int minisat_set_opt_phase_saving(int mode)
{
    if (mode < 0 || mode > 2)
    {
        return 105;
    }
    Minisat::set_opt_phase_saving(mode);
    return 0;
}
int minisat_set_opt_rnd_init_act(int flag)
{
    Minisat::set_opt_rnd_init_act(flag);
    return 0;
}
int minisat_set_opt_luby_restart(int flag)
{
    Minisat::set_opt_luby_restart(flag);
    return 0;
}
int minisat_set_opt_restart_first(int restart_first)
{
    Minisat::set_opt_restart_first(restart_first);
    return 108;
}
int minisat_set_opt_restart_inc(double restart_inc)
{
    if (restart_inc < 1.0)
    {
        return 109;
    }
    Minisat::set_opt_restart_inc(restart_inc);
    return 0;
}
int minisat_set_opt_garbage_frac(double garbage_frac)
{
    if (garbage_frac <= 0)
    {
        return 110;
    }

    Minisat::set_opt_garbage_frac(garbage_frac);
    return 0;
}
int minisat_set_opt_min_learnts_lim(int min_learnts_lim)
{
    if (min_learnts_lim < 0)
    {
        return 111;
    }
    Minisat::set_opt_min_learnts_lim(min_learnts_lim);
    return 0;
}
int minisat_set_opt_use_asymm(int opt_use_asymm)
{
    Minisat::set_opt_use_asymm(opt_use_asymm);
    return 0;
}
int minisat_set_opt_use_rcheck(int opt_use_rcheck)
{
    Minisat::set_opt_use_rcheck(opt_use_rcheck);
    return 0;
}
int minisat_set_opt_use_elim(int opt_use_elim)
{
    Minisat::set_opt_use_elim(opt_use_elim);
    return 0;
}
int minisat_set_opt_grow(int opt_grow)
{
    if (opt_grow < 0)
    {
        return 112;
    }

    Minisat::set_opt_grow(opt_grow);
    return 0;
}

int minisat_set_opt_clause_lim(int opt_clause_lim)
{
    if (opt_clause_lim < -1)
    {
        return 113;
    }

    Minisat::set_opt_clause_lim(opt_clause_lim);
    return 0;
}
int minisat_set_opt_subsumption_lim(int opt_subsumption_lim)
{
    if (opt_subsumption_lim < -1)
    {
        return 114;
    }
    Minisat::set_opt_subsumption_lim(opt_subsumption_lim);
    return 0;
}

int minisat_set_opt_simp_garbage_frac(double opt_simp_garbage_frac)
{
    if (opt_simp_garbage_frac <= 0)
    {
        return 115;
    }
    Minisat::set_opt_simp_garbage_frac(opt_simp_garbage_frac);
    return 0;
}

int minisat_set_opt_verbosity(int verb)
{
    if (verb < 0 || verb > 3)
    {
        return 116;
    }

    Minisat::set_opt_verbosity(verb);
    return 0;
}

const char *minisat_error_msg(int code)
{
    switch (code)
    {
    case 100: return "var_decay must be in (0,1)";
    case 101: return "clause_decay must be in (0,1)";
    case 102: return "random_var_freq must be in [0,1]";
    case 103: return "random_seed must be non-negative";
    case 104: return "ccmin_mode must be 0/1/2";
    case 105: return "phase_saving must be 0-2";
    case 106: return "rnd_init_act must be 0/1";
    case 107: return "luby_restart must be 0/1";
    case 108: return "invalid restart_first value";
    case 109: return "restart_inc must >=1.0";
    case 110: return "garbage_frac must >0";
    case 111: return "min_learnts_lim must >=0";
    case 112: return "grow value must >=0";
    case 113: return "clause_lim must >=-1";
    case 114: return "subsumption_lim must >=-1";
    case 115: return "simp_garbage_frac must >0";
    case 116: return "verbosity must be 0-3";
    default:  return "unknown error";
    }
}