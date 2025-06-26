#ifndef Minisat_StdSimpSolver_h
#define Minisat_StdSimpSolver_h

//=================================================================================================

#ifdef __cplusplus
extern "C"
{
#endif
    void *minisat_new_solver();
    int minisat_newVar(void *solver);
    void minisat_releaseVar(void *solver, int l);
    int minisat_addClause(void *solver, const int ps[], unsigned long length);
    int minisat_addEmptyClause(void *solver); // Add the empty clause to the solver.
    int minisat_value(void *solver, int x);

    // Solving:
    //
    int minisat_solve_assumps(void *solver, const int assumps[], unsigned long length, int do_simp = true, int turn_off_simp = false);
    int minisat_solveLimited(void *solver, const int assumps[], unsigned long length, int do_simp = true, int turn_off_simp = false);
    int minisat_solve(void *solver, int do_simp = true, int turn_off_simp = false);
    int minisat_eliminate(void *solver, int turn_off_elim = false); // Perform variable elimination based simplification.
    int minisat_nAssigns(void *solver);                             // The current number of assigned literals.
    int minisat_nClauses(void *solver);                             // The current number of original clauses.
    int minisat_nLearnts(void *solver);                             // The current number of learnt clauses.
    int minisat_nVars(void *solver);                                // The current number of variables.
    int minisat_nFreeVars(void *solver);
    void minisat_destroy(void *solver);
#ifdef __cplusplus
}
#endif

#endif
