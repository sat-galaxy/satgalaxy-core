
#include "minisat_port.h"
#include "minisat/simp/SimpSolver.h"
Minisat::Lit makeLit(Minisat::SimpSolver *solver, int val)
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
void minisat_destroy(void *s)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    delete solver;
}
int minisat_newVar(void *s)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return solver->newVar();
}
void minisat_releaseVar(void *s, int l)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    solver->releaseVar(makeLit(solver, l));
}

int minisat_addClause(void *s, const int ps[], unsigned long length)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    Minisat::vec<Minisat::Lit> lits;
    for (unsigned long i = 0; i < length; i++)
    {
        lits.push(makeLit(solver, ps[i]));
    }
    return solver->addClause(lits);
}
int minisat_addEmptyClause(void *s)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return solver->addEmptyClause();
}

int minisat_solve_assumps(void *s, const int ps[], unsigned long length, int do_simp, int turn_off_simp)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    Minisat::vec<Minisat::Lit> lits;
    for (unsigned long i = 0; i < length; i++)
    {
        lits.push(makeLit(solver, ps[i]));
    }
    return solver->solve(lits, (bool)do_simp, (bool)turn_off_simp);
}
int minisat_solveLimited(void *s, const int ps[], unsigned long length, int do_simp, int turn_off_simp)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    Minisat::vec<Minisat::Lit> lits;
    for (unsigned long i = 0; i < length; i++)
    {
        lits.push(makeLit(solver, ps[i]));
    }
    return Minisat::toInt(solver->solveLimited(lits, (bool)do_simp, (bool)turn_off_simp));
}
int minisat_solve(void *s, int do_simp, int turn_off_simp)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return solver->solve((bool)do_simp, (bool)turn_off_simp);
}

int minisat_eliminate(void *s, int turn_off_elim)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return solver->eliminate(turn_off_elim);
}

int minisat_nAssigns(void *s)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return solver->nAssigns();
}
int minisat_nClauses(void *s)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return solver->nClauses();
}
int minisat_nLearnts(void *s)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return solver->nLearnts();
}
int minisat_nVars(void *s)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return solver->nVars();
}
int minisat_nFreeVars(void *s)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    return solver->nFreeVars();
}
int minisat_value(void *s, int val)
{
    Minisat::SimpSolver *solver = (Minisat::SimpSolver *)s;
    Minisat::lbool b = solver->model[val];
    return (b == Minisat::l_True);
}
