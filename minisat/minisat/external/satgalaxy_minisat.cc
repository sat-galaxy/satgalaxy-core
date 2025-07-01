
#include "satgalaxy_minisat.h"
#include "minisat/simp/SimpSolver.h"
#include "minisat/utils/Options.h"

Minisat::Lit make_lit(Minisat::SimpSolver *solver, int val)
{
    int value = abs(val) - 1;
    while (value >= solver->nVars())
    {
        solver->newVar();
    }
    return Minisat::mkLit(value, val < 0);
}
void *minisat_new_solver()
{
    return new Minisat::SimpSolver();
}
void minisat_destroy(const void *s)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    delete solver;
}
int minisat_new_var(const void *s)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return solver->newVar();
}
void minisat_release_var(const void *s, int l)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    solver->releaseVar(make_lit(solver, l));
}

int minisat_add_clause(const void *s, const int ps[], unsigned long length)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    Minisat::vec<Minisat::Lit> lits;
    for (unsigned long i = 0; i < length; i++)
    {
        lits.push(make_lit(solver, ps[i]));
    }
    return solver->addClause(lits);
}
int minisat_add_empty_clause(const void *s)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return solver->addEmptyClause();
}

int minisat_solve_assumps(const void *s, const int ps[], unsigned long length, int do_simp, int turn_off_simp)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    Minisat::vec<Minisat::Lit> lits;
    for (unsigned long i = 0; i < length; i++)
    {
        lits.push(make_lit(solver, ps[i]));
    }
    return solver->solve(lits, (int)do_simp, (int)turn_off_simp);
}
int minisat_solve_limited(const void *s, const int ps[], unsigned long length, int do_simp, int turn_off_simp)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    Minisat::vec<Minisat::Lit> lits;
    for (unsigned long i = 0; i < length; i++)
    {
        lits.push(make_lit(solver, ps[i]));
    }
    return (Minisat::toInt(solver->solveLimited(lits, (int)do_simp, (int)turn_off_simp))+1)*10;
 
    
    
}
int minisat_solve(const void *s, int do_simp, int turn_off_simp)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return solver->solve((int)do_simp, (int)turn_off_simp);
}

int minisat_eliminate(const void *s, int turn_off_elim)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return solver->eliminate(turn_off_elim);
}

int minisat_nassigns(const void *s)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return solver->nAssigns();
}
int minisat_nclauses(const void *s)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return solver->nClauses();
}
int minisat_nlearnts(const void *s)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return solver->nLearnts();
}
int minisat_nvars(const void *s)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return solver->nVars();
}
int minisat_nfree_vars(const void *s)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return solver->nFreeVars();
}
int minisat_value(const void *s, int val)
{
    int abs_val = abs(val);

    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    if (abs_val==0||abs_val > solver->nVars())
    {
        return 0;
    }
    return  ( (val<0) ^(solver->value(abs_val - 1) == Minisat::l_True));
}
int minisat_model_value(const void *s, int val)
{
    int abs_val = abs(val);

    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    if (abs_val==0||abs_val > solver->nVars())
    {
        return 0;
    }
    return (int)(((val<0) ^solver->model[abs_val - 1] == Minisat::l_True));
}
int minisat_okay(const void *s)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return (int)solver->okay();
}

void minisat_set_opt_var_decay(double decay)
{
    Minisat::set_opt_var_decay(decay);
}
void minisat_set_opt_clause_decay(double decay)
{
    Minisat::set_opt_clause_decay(decay);
}
void minisat_set_opt_random_var_freq(double freq)
{
    Minisat::set_opt_random_var_freq(freq);
}
void minisat_set_opt_random_seed(double seed)
{
    Minisat::set_opt_random_seed(seed);
}
void minisat_set_opt_ccmin_mode(int mode)
{
    Minisat::set_opt_ccmin_mode(mode);
}
void minisat_set_opt_phase_saving(int mode)
{
    Minisat::set_opt_phase_saving(mode);
}
void minisat_set_opt_rnd_init_act(int flag)
{
    Minisat::set_opt_rnd_init_act(flag);
}
void minisat_set_opt_luby_restart(int flag)
{
    Minisat::set_opt_luby_restart(flag);
}
void minisat_set_opt_restart_first(int restart_first)
{
    Minisat::set_opt_restart_first(restart_first);
}
void minisat_set_opt_restart_inc(double restart_inc)
{
    Minisat::set_opt_restart_inc(restart_inc);
}
void minisat_set_opt_garbage_frac(double garbage_frac)
{
    Minisat::set_opt_garbage_frac(garbage_frac);
}
void minisat_set_opt_min_learnts_lim(int min_learnts_lim)
{
    Minisat::set_opt_min_learnts_lim(min_learnts_lim);
}
void minisat_set_opt_use_asymm(int opt_use_asymm)
{
    Minisat::set_opt_use_asymm(opt_use_asymm);
}
void minisat_set_opt_use_rcheck(int opt_use_rcheck)
{
    Minisat::set_opt_use_rcheck(opt_use_rcheck);
}
void minisat_set_opt_use_elim(int opt_use_elim)
{
    Minisat::set_opt_use_elim(opt_use_elim);
}
void minisat_set_opt_grow(int opt_grow)
{
    Minisat::set_opt_grow(opt_grow);
}
void minisat_set_opt_clause_lim(int opt_clause_lim)
{
    Minisat::set_opt_clause_lim(opt_clause_lim);
}
void minisat_set_opt_subsumption_lim(int opt_subsumption_lim)
{
    Minisat::set_opt_subsumption_lim(opt_subsumption_lim);
}

void minisat_set_opt_simp_garbage_frac(double opt_simp_garbage_frac)
{
    Minisat::set_opt_simp_garbage_frac(opt_simp_garbage_frac);
}

void minisat_set_opt_verbosity(int verb){
    Minisat::set_opt_verbosity(verb);
}
