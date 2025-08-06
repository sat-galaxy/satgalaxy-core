#ifndef SATGALAXY_picosat_s_H
#define SATGALAXY_picosat_s_H
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
//=================================================================================================

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct PicoSATSolver PicoSATSolver;

    const char *picosat_s_version(void);
    const char *picosat_s_config(void);
    const char *picosat_s_copyright(void);

    typedef void *(*picosat_s_malloc)(void *, size_t);
    typedef void *(*picosat_s_realloc)(void *, void *, size_t, size_t);
    typedef void (*picosat_s_free)(void *, void *, size_t);

    /// @brief Initializes a new PicoSAT solver instance (constructor).
    /// @return Pointer to the initialized PicoSATSolver.
    PicoSATSolver *picosat_s_init(void);

    /// @brief Initializes a PicoSAT solver with custom memory management functions.
    /// @param state User-defined state for memory management.
    /// @param m Malloc function for memory allocation.
    /// @param r Realloc function for memory reallocation.
    /// @param f Free function for memory deallocation.
    /// @return Pointer to the initialized PicoSATSolver.
    PicoSATSolver *picosat_s_minit(void *state, picosat_s_malloc m, picosat_s_realloc r, picosat_s_free f);

    /// @brief Destroys a PicoSAT solver instance (destructor).
    /// @param solver Pointer to the PicoSATSolver to reset.
    void picosat_s_reset(PicoSATSolver *solver);

    /// @brief Enters the PicoSAT solver context.
    /// @param solver Pointer to the PicoSATSolver.
    void picosat_s_enter (PicoSATSolver *solver);
    
    /// @brief Exits the PicoSAT solver context.
    /// @param solver Pointer to the PicoSATSolver.
    void picosat_s_leave (PicoSATSolver *solver);
    /// @brief Configures initial solver settings. These functions must be called immediately after picosat_s_init and before adding literals.
    /// @note Do not call these after adding literals.


    /// @brief Measure all time spent in all calls in the solver.  By default only the time spent in 'picosat_s_sat' is measured.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note Enabling this may significantly increase time for adding large CNFs due to getrusage calls.
    void picosat_s_measure_all_calls(PicoSATSolver *solver);

    /// @param solver Pointer to the PicoSATSolver.
    /// @param prefix String prefix for verbose messages and statistics (default: "c ").
    void picosat_s_set_prefix(PicoSATSolver *solver, const char *prefix);

    /// @param solver Pointer to the PicoSATSolver.
    /// @param new_verbosity_level Verbosity level (1+ for detailed progress reports).
    /// @note Reports are printed to the output file set by picosat_s_set_output, prefixed by picosat_s_set_prefix.
    void picosat_s_set_verbosity(PicoSATSolver *solver, int new_verbosity_level);

    /// @param solver Pointer to the PicoSATSolver.
    /// @param new_plain_value Non-zero to disable preprocessing (plain solving), zero to enable.
    /// @note Currently affects only failed literal probing.
    void picosat_s_set_plain(PicoSATSolver *solver, int new_plain_value);

    /// @brief Sets the default initial phase for decision variables.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param phase Phase value: 0 (false), 1 (true), 2 (Jeroslow-Wang, default), 3 (random).
    /// @note After first assignment, variables reuse their previous value for decisions.
    /// @return None.
    void picosat_s_set_global_default_phase(PicoSATSolver *solver, int phase);

    /// @brief Sets the initial phase for a specific variable when chosen as a decision variable.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to set the phase for.
    /// @param phase Phase value: negative (false), positive (true), 0 (use global default phase).
    /// @note Forced assignments override this phase for decision variables.
    /// @return None.
    void picosat_s_set_default_phase_lit(PicoSATSolver *solver, int lit, int phase);

    /// @brief Resets all variable phases to their default state.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return None.
    void picosat_s_reset_phases(PicoSATSolver *solver);

    /// @brief Erases variable scores, keeping learned clauses and literal pointers.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note Incremental mode may differ from a fresh CNF due to retained clauses.
    /// @return None.
    void picosat_s_reset_scores(PicoSATSolver *solver);

    /// @brief Resets assignment in SAT state and removes a percentage of less active learned clauses.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param percentage Percentage of large learned clauses to remove (100% removes all).
    /// @return None.
    void picosat_s_remove_learned(PicoSATSolver *solver, unsigned percentage);

    /// @brief Sets priority for decision variables.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to mark as more important.
    /// @note Default is all variables marked as indifferent.
    void picosat_s_set_more_important_lit(PicoSATSolver *solver, int lit);
    /// @brief Sets priority for decision variables.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to mark as less important.
    /// @note Default is all variables marked as indifferent.
    void picosat_s_set_less_important_lit(PicoSATSolver *solver, int lit);

    /// @brief Prints a message to the solver's internal output file.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param verbosity_level Verbosity level required for the message to be printed.
    /// @param fmt Format string for the message.
    /// @param ... Additional arguments for the format string.
    /// @return None.
    void picosat_s_message(PicoSATSolver *solver, int verbosity_level, const char *fmt, ...);

    /// @brief Sets the seed for the random number generator used in random decisions.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param random_number_generator_seed Seed value for the random number generator.
    /// @note Useful for benchmarking different parameter sets, less effective for industrial examples.
    /// @return None.
    void picosat_s_set_seed(PicoSATSolver *solver, unsigned random_number_generator_seed);

    /// @brief Enables proof trace generation for extracting cores or traces.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note Must be called immediately after picosat_s_init. Not needed for picosat_s_set_incremental_rup_file.
    /// @note Trace generation may not be included if compiled with full optimization (e.g., './configure -O').
    /// @return Non-zero if trace generation is supported, zero otherwise.
    int picosat_s_enable_trace_generation(PicoSATSolver *solver);

 

    /// @brief Saves original clauses for use with picosat_s_deref_partial.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return None.
    void picosat_s_save_original_clauses(PicoSATSolver *solver);

    /// @brief Allocates and returns the next unused variable index.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note The variable is treated as used in future calls to picosat_s_sat, picosat_s_deref, and picosat_s_changed.
    /// @return The next available variable index.
    int picosat_s_inc_max_var(PicoSATSolver *solver);

    /// @brief Push and pop semantics for PicoSAT.   'picosat_s_push' opens up a new
    /// context.  All clauses added in this context are attached to it and
    /// discarded when the context is closed with 'picosat_s_pop'.  It is also
    /// possible to nest contexts.
    ///
    /// The current implementation uses a new internal variable for each context.
    /// However, the indices for these internal variables are shared with
    /// ordinary external variables.  This means that after any call to
    /// 'picosat_s_push', new variable indices should be obtained with
    /// 'picosat_s_inc_max_var' and not just by incrementing the largest variable
    /// index used so far.
    ///
    /// @param solver Pointer to the PicoSATSolver..
    /// @return The return value is the index of the literal that assumes this context.
    /// This literal can only be used for 'picosat_s_failed_context' otherwise
    /// it will lead to an API usage error.
    int picosat_s_push(PicoSATSolver *solver);
    /// @brief This is as 'picosat_s_failed_assumption', but only for internal variables
    /// generated by 'picosat_s_push'.
    /// @param solver
    /// @param lit
    /// @return boolean value
    int picosat_s_failed_context(PicoSATSolver *solver, int lit);

    /// @brief
    /// @param solver
    /// @return the literal that assumes the current context or zero if the outer context has been reached.
    int picosat_s_context(PicoSATSolver *solver);
    /// @brief Closes the current context and recycles the literal generated for assuming this context.
    /// @return return value is the literal for the new outer context or zero if the outer most context has been reached.
    int picosat_s_pop(PicoSATSolver *solver);

    /// @brief Forces immediate removal of satisfied clauses and those in closed contexts.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note Called internally after sufficient units are learned or contexts closed (MAXCILS limit).
    /// @note Retains learned clauses involving outer contexts.
    /// @return None.
    void picosat_s_simplify(PicoSATSolver *solver);

    /// @brief Optimizes variable table size to reduce resizing.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param max_idx Estimated maximum variable index.
    /// @note Has the same effect as picosat_s_inc_max_var but optimizes allocation.
    /// @return None.
    void picosat_s_adjust(PicoSATSolver *solver, int max_idx);

    /// @brief Retrieves solver statistics.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return  Number of variables (p cnf <m> n).
    int picosat_s_variables(PicoSATSolver *solver);
    /// @brief Retrieves solver statistics.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return  Number of original clauses (p cnf m <n>).
    int picosat_s_added_original_clauses(PicoSATSolver *solver);
    /// @brief Retrieves solver statistics.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return  Maximum memory allocated.
    size_t picosat_s_max_bytes_allocated(PicoSATSolver *solver);
    /// @brief Retrieves solver statistics.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return Current process time.
    double picosat_s_time_stamp(void);
    /// @brief Retrieves solver statistics.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return  None (prints to output file).
    void picosat_s_stats(PicoSATSolver *solver);
    /// @brief Retrieves solver statistics.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param file Output file for picosat_s_stats (others return directly).
    /// @return  Number of propagations.
    unsigned long long picosat_s_propagations(PicoSATSolver *solver);
    /// @brief Retrieves solver statistics.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return  Number of decisions.
    unsigned long long picosat_s_decisions(PicoSATSolver *solver);
    /// @brief Retrieves solver statistics.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return Number of visits.
    unsigned long long picosat_s_visits(PicoSATSolver *solver);
    /// @brief Retrieves solver statistics.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return Time spent in library calls or picosat_s_sat (if picosat_s_measure_all_calls enabled).
    double picosat_s_seconds(PicoSATSolver *solver);

    /// @brief Adds literals or clauses to the solver incrementally.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to add (picosat_s_add).
    /// @note Adding a literal resets the previous assignment.
    /// @return The original clause index (starting at 0) for the added literal or clause.
    int picosat_s_add(PicoSATSolver *solver, int lit);
    /// @brief Adds literals or clauses to the solver incrementally.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param ... Variable argument list of literals terminated by zero (picosat_s_add_arg).
    /// @note Adding a literal resets the previous assignment.
    /// @return The original clause index (starting at 0) for the added literal or clause.
    int picosat_s_add_arg(PicoSATSolver *solver, ...);
    /// @brief Adds literals or clauses to the solver incrementally.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lits Array of literals terminated by zero (picosat_s_add_lits).
    /// @note Adding a literal resets the previous assignment.
    /// @return The original clause index (starting at 0) for the added literal or clause.
    int picosat_s_add_lits(PicoSATSolver *solver, const int lits[], size_t len);



    /// @brief Adds an assumption for the next picosat_s_sat call.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to assume (interpreted as a unit clause).
    /// @note Assumptions are valid only for the next picosat_s_sat call and are cleared afterward unless reassumed.
    /// @note Assumptions remain valid post-picosat_s_sat for picosat_s_failed_assumption until picosat_s_add, picosat_s_assume, or another picosat_s_sat is called.
    /// @return None.
    void picosat_s_assume(PicoSATSolver *solver, int lit);

    /// @brief Adds a literal to the global all-different constraint (ADC).
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to add to the ADC.
    /// @note Only one global ADC is supported; all bit-vectors must have identical bit-width.
    /// @note TODO: Handle top-level assigned literals.
    /// @return None.
    void picosat_s_add_ado_lit(PicoSATSolver *solver, int lit);

    /// @brief Runs the main SAT solving routine.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param decision_limit Maximum number of decisions (negative for no limit).
    /// @return picosat_s_SATISFIABLE, picosat_s_UNSATISFIABLE, or picosat_s_UNKNOWN.
    int picosat_s_sat(PicoSATSolver *solver, int decision_limit);

    /// @brief Sets a propagation limit for picosat_s_sat.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param limit Maximum number of propagations.
    /// @note Must be called after picosat_s_init and before picosat_s_sat.
    /// @return None.
    void picosat_s_set_propagation_limit(PicoSATSolver *solver, unsigned long long limit);

    /// @brief Returns the result of the last picosat_s_sat call.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return Last picosat_s_sat result or 0 if not called.
    int picosat_s_res(PicoSATSolver *solver);

    /// @brief Dereferences a literal to get its assignment after picosat_s_sat returns picosat_s_SATISFIABLE.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to dereference.
    /// @return 1 (true), -1 (false), or 0 (unknown).
    int picosat_s_deref(PicoSATSolver *solver, int lit);

    /// @brief Checks if a literal is forced at the top level.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to check.
    /// @note Does not require picosat_s_sat and does not reset incremental usage.
    /// @return 1 (true), -1 (false), or 0 (unknown).
    int picosat_s_deref_toplevel(PicoSATSolver *solver, int lit);

    /// @brief Retrieves a partial satisfying assignment for original clauses after picosat_s_sat returns picosat_s_SATISFIABLE.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to dereference.
    /// @note Requires picosat_s_save_original_clauses to be called after initialization.
    /// @return 1 (true), -1 (false), or 0 (unknown).
    int picosat_s_deref_partial(PicoSATSolver *solver, int lit);

    /// @brief Checks if the CNF is unsatisfiable due to an empty clause.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return Non-zero if unsatisfiable due to an empty clause, zero otherwise.
    int picosat_s_inconsistent(PicoSATSolver *solver);

    /// @brief Checks if a literal is a failed assumption in the last picosat_s_sat call.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to check.
    /// @note Only valid while current assumptions are active (see picosat_s_assume).
    /// @return Non-zero if the literal is a failed assumption, zero otherwise.
    int picosat_s_failed_assumption(PicoSATSolver *solver, int lit);

    /// @brief Returns a zero-terminated list of failed assumptions from the last picosat_s_sat call.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note Valid until the next picosat_s_sat or picosat_s_failed_assumptions call.
    /// @note Only meaningful if picosat_s_sat returned picosat_s_UNSATISFIABLE.
    /// @return Pointer to a zero-terminated array of failed assumptions.
    const int *picosat_s_failed_assumptions(PicoSATSolver *solver);

    /// @brief Computes a minimized list of failed assumptions from the last picosat_s_sat call.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param state User-defined state for the callback.
    /// @param callback Function called for each simplified assumption set (receives state and reduced assumptions).
    /// @param fix Non-zero to permanently assign assumptions (true for necessary, false for redundant).
    /// @note Only meaningful if picosat_s_sat returned picosat_s_UNSATISFIABLE.
    /// @note Valid until the next picosat_s_sat, picosat_s_mus_assumptions, or this function call.
    /// @return Pointer to a zero-terminated minimized array of failed assumptions.
    const int *picosat_s_mus_assumptions(PicoSATSolver *solver, void *state, void (*callback)(void *, const int *), int fix);

    /// @brief Computes a maximal satisfiable subset of assumptions.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note Requires assumptions set and picosat_s_sat called with picosat_s_inconsistent checked.
    /// @note Reassumes all assumptions before returning.
    /// @note Setting assumption phases to true may improve performance.
    /// @return Pointer to a zero-terminated array of consistent assumptions.
    const int *picosat_s_maximal_satisfiable_subset_of_assumptions(PicoSATSolver *solver);

    /// @brief Iterates over maximal satisfiable subsets of assumptions.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note Requires assumptions set via picosat_s_assume; calls picosat_s_sat internally unless inconsistent.
    /// @note Adds a blocking clause to rule out the returned subset, altering the CNF.
    /// @note Setting assumption phases to true may improve performance.
    /// @return Pointer to a zero-terminated array of consistent assumptions or NULL if none remain.
    const int *picosat_s_next_maximal_satisfiable_subset_of_assumptions(PicoSATSolver *solver);

    /// @brief Iterates over minimal correcting assumption sets.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note Each assumed literal appears once in the result, even if assumed multiple times.
    /// @note Setting assumption phases to true may improve performance.
    /// @return Pointer to a zero-terminated array of minimal correcting assumptions.
    const int *picosat_s_next_minimal_correcting_subset_of_assumptions(PicoSATSolver *solver);

    /// @brief Computes the union of all minimal correcting assumption sets (HUMUS).
    /// @param solver Pointer to the PicoSATSolver.
    /// @param callback Function called after each minimal correcting set (receives state, nmcs, nhumus).
    /// @param state User-defined state for the callback.
    /// @note Renders the CNF inconsistent after one call; requires solver reset.
    /// @note Uses picosat_s_next_minimal_correcting_subset_of_assumptions internally.
    /// @return Pointer to a zero-terminated array of assumptions in the HUMUS.
    const int *picosat_s_humus(PicoSATSolver *solver, void (*callback)(void *state, int nmcs, int nhumus), void *state);

    /// @brief Checks if the assignment of old variables changed between picosat_s_sat calls returning SATISFIABLE.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note Valid until picosat_s_add, picosat_s_assume, or picosat_s_sat is called.
    /// @note May return non-zero even if no change occurred due to internal flip tracking (TODO: exact tracking not implemented).
    /// @return 0 if old variable assignments are unchanged, non-zero if they might have changed.
    int picosat_s_changed(PicoSATSolver *solver);

    /// @brief Determines if the i'th original clause is in the clausal core.
    /// @param solver Pointer to the PicoSAT solver.
    /// @param i Clause index from picosat_s_add (0 <= i < picosat_s_added_original_clauses).
    /// @note Requires trace generation enabled via picosat_s_enable_trace_generation after picosat_s_init.
    /// @note Incremental mode with assumptions tested only for picosat_s_corelit; may not work reliably here.
    /// @return Non-zero if the clause is in the core, zero otherwise.
    int picosat_s_coreclause(PicoSATSolver *solver, int i);

    /// @brief Checks if a literal is in the variable core (resolved in deriving the empty clause).
    /// @param solver Pointer to the PicoSAT solver.
    /// @param lit Literal to check.
    /// @note Requires trace generation enabled via picosat_s_enable_trace_generation after picosat_s_init.
    /// @note Tested in incremental mode with assumptions; other core functions may not work reliably.
    /// @return Non-zero if the literal is in the variable core, zero otherwise.
    int picosat_s_corelit(PicoSATSolver *solver, int lit);



    /// @brief Checks if a literal was used in resolution to derive a learned clause.
    /// @param solver Pointer to the PicoSAT solver.
    /// @param lit Literal to check.
    /// @note Core literals are a subset of used literals; does not require keeping proof traces.
    /// @return Non-zero if the literal was used, zero otherwise.
    int picosat_s_usedlit(PicoSATSolver *solver, int lit);
    int picosat_s_error(PicoSATSolver *solver);
    const char * picosat_s_errmsg(int code);

#ifdef __cplusplus
}
#endif

#endif
