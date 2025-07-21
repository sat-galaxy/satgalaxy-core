
#include "satgalaxy_minisat.h"
#include "minisat/simp/SimpSolver.h"
#include "minisat/utils/Options.h"

#define MINISAT_OPT(NAME,TY,COND,CODE) \
int minisat_global_set_opt_##NAME(TY value)\
{\
    if (COND)\
    {\
        return CODE;\
    }\
    Minisat::set_opt_##NAME(value);\
    return 0;\
}\
\
int minisat_set_opt_##NAME(MiniSATSolver *solver, TY value)\
{\
    if (COND)\
    {\
        return CODE;\
    }\
    solver->solver->NAME==value;\
    return 0;\
}\


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

int minisat_add_clause(MiniSATSolver* s, const int ps[], size_t length)
{
    Minisat::SimpSolver *solver =  s->solver;
    Minisat::vec<Minisat::Lit> lits;
    for (size_t i = 0; i < length; i++)
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

int minisat_solve_assumps(MiniSATSolver* s, const int ps[], size_t length, int do_simp, int turn_off_simp)
{
    Minisat::SimpSolver *solver =  s->solver;
    Minisat::vec<Minisat::Lit> lits;
    for (size_t i = 0; i < length; i++)
    {
        lits.push(make_lit(solver, ps[i]));
    }
    return solver->solve(lits, (int)do_simp, (int)turn_off_simp);
}
int minisat_solve_limited(MiniSATSolver* s, const int ps[], size_t length, int do_simp, int turn_off_simp)
{
    Minisat::SimpSolver *solver =  s->solver;
    Minisat::vec<Minisat::Lit> lits;
    for (size_t i = 0; i < length; i++)
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

MINISAT_OPT(var_decay, double, value <= 0 || value >= 1, 100)
MINISAT_OPT(clause_decay, double, value <= 0 || value >= 1, 101)
MINISAT_OPT(random_var_freq, double, value < 0 || value > 1, 102)
MINISAT_OPT(random_seed, double, value >= 0, 103)
MINISAT_OPT(ccmin_mode, int, value != 0 && value != 1 && value != 2, 104)
MINISAT_OPT(phase_saving, int, value < 0 || value > 2, 105)
MINISAT_OPT(rnd_init_act, int, false, 0)
MINISAT_OPT(luby_restart, int, false, 0)
MINISAT_OPT(restart_first, int, true, 108)
MINISAT_OPT(restart_inc, double, value < 1.0, 109)
MINISAT_OPT(garbage_frac, double, value <= 0, 110)
MINISAT_OPT(min_learnts_lim, int, value < 0, 111)
MINISAT_OPT(use_asymm, int, false, 0)
MINISAT_OPT(use_rcheck, int, false, 0)
MINISAT_OPT(use_elim, int, false, 0)
MINISAT_OPT(grow, int, value < 0, 112)
MINISAT_OPT(clause_lim, int, value < -1, 113)
MINISAT_OPT(subsumption_lim, int, value < -1, 114)
MINISAT_OPT(simp_garbage_frac, double, value <= 0, 115)
MINISAT_OPT(verbosity, int, value < 0 || value > 3, 116)
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