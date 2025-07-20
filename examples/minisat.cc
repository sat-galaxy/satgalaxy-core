#include <stdio.h>
#include "satgalaxy/satgalaxy_minisat.h" // Assuming this is your Minisat C interface header

int main() {
    MiniSATSolver  * solver = minisat_new_solver();

    // Add some variables
    minisat_new_var(solver); // Variable 1
    minisat_new_var(solver); // Variable 2
    minisat_new_var(solver); // Variable 3

    // Add clause: (1 OR -2)
    int clause1[] = {1, -2}; // 0 indicates end of clause
    minisat_add_clause(solver, clause1,2);

    // Add clause: (2 OR 3)
    int clause2[] = {2, 3};
    minisat_add_clause(solver, clause2,2);
    printf("Solving...\n");
    printf("clause1: %d, %d\n",clause1[0],clause1[1]);
    printf("clause2: %d, %d\n",clause2[0],clause2[1]);

    // Solve
    if (minisat_solve(solver,1,0)) {
        printf("SATISFIABLE!\n");
        // Get model (assignment)
        printf("Model: var 1 = %d, var 2 = %d, var 3 = %d\n",
               minisat_model_value(solver, 1),
               minisat_model_value(solver, 2),
               minisat_model_value(solver, 3));
    } else {
        printf("UNSATISFIABLE!\n");
    }

    minisat_destroy(solver);
    return 0;
}