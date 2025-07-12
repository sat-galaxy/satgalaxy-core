#ifndef SATGALAXY_PICOSAT_H
#define SATGALAXY_PICOSAT_H
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
//=================================================================================================

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct PicoSATSolver PicoSATSolver;

    const char *picosat_version(void);
    const char *picosat_config(void);
    const char *picosat_copyright(void);

    typedef void *(*Picosat_malloc)(void *, size_t);
    typedef void *(*Picosat_realloc)(void *, void *, size_t, size_t);
    typedef void (*Picosat_free)(void *, void *, size_t);

    /// @brief Initializes a new PicoSAT solver instance (constructor).
    /// @return Pointer to the initialized PicoSATSolver.
    PicoSATSolver *Picosat_init(void);

    /// @brief Initializes a PicoSAT solver with custom memory management functions.
    /// @param state User-defined state for memory management.
    /// @param m Malloc function for memory allocation.
    /// @param r Realloc function for memory reallocation.
    /// @param f Free function for memory deallocation.
    /// @return Pointer to the initialized PicoSATSolver.
    PicoSATSolver *Picosat_minit(void *state, Picosat_malloc m, Picosat_realloc r, Picosat_free f);

    /// @brief Destroys a PicoSAT solver instance (destructor).
    /// @param solver Pointer to the PicoSATSolver to reset.
    void Picosat_reset(PicoSATSolver *solver);

    /// @brief Configures initial solver settings. These functions must be called immediately after Picosat_init and before adding literals.
    /// @note Do not call these after adding literals.

    /// @param solver Pointer to the PicoSATSolver.
    /// @param file Output file for solver messages (default: stdout).
    void Picosat_set_output(PicoSATSolver *solver, FILE *file);

    /// @brief Measure all time spent in all calls in the solver.  By default only the time spent in 'Picosat_sat' is measured.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note Enabling this may significantly increase time for adding large CNFs due to getrusage calls.
    void Picosat_measure_all_calls(PicoSATSolver *solver);

    /// @param solver Pointer to the PicoSATSolver.
    /// @param prefix String prefix for verbose messages and statistics (default: "c ").
    void Picosat_set_prefix(PicoSATSolver *solver, const char *prefix);

    /// @param solver Pointer to the PicoSATSolver.
    /// @param new_verbosity_level Verbosity level (1+ for detailed progress reports).
    /// @note Reports are printed to the output file set by Picosat_set_output, prefixed by Picosat_set_prefix.
    void Picosat_set_verbosity(PicoSATSolver *solver, int new_verbosity_level);

    /// @param solver Pointer to the PicoSATSolver.
    /// @param new_plain_value Non-zero to disable preprocessing (plain solving), zero to enable.
    /// @note Currently affects only failed literal probing.
    void Picosat_set_plain(PicoSATSolver *solver, int new_plain_value);

    /// @brief Sets the default initial phase for decision variables.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param phase Phase value: 0 (false), 1 (true), 2 (Jeroslow-Wang, default), 3 (random).
    /// @note After first assignment, variables reuse their previous value for decisions.
    /// @return None.
    void Picosat_set_global_default_phase(PicoSATSolver *solver, int phase);

    /// @brief Sets the initial phase for a specific variable when chosen as a decision variable.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to set the phase for.
    /// @param phase Phase value: negative (false), positive (true), 0 (use global default phase).
    /// @note Forced assignments override this phase for decision variables.
    /// @return None.
    void Picosat_set_default_phase_lit(PicoSATSolver *solver, int lit, int phase);

    /// @brief Resets all variable phases to their default state.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return None.
    void Picosat_reset_phases(PicoSATSolver *solver);

    /// @brief Erases variable scores, keeping learned clauses and literal pointers.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note Incremental mode may differ from a fresh CNF due to retained clauses.
    /// @return None.
    void Picosat_reset_scores(PicoSATSolver *solver);

    /// @brief Resets assignment in SAT state and removes a percentage of less active learned clauses.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param percentage Percentage of large learned clauses to remove (100% removes all).
    /// @return None.
    void Picosat_remove_learned(PicoSATSolver *solver, unsigned percentage);

    /// @brief Sets priority for decision variables.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to mark as more important.
    /// @note Default is all variables marked as indifferent.
    void Picosat_set_more_important_lit(PicoSATSolver *solver, int lit);
    /// @brief Sets priority for decision variables.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to mark as less important.
    /// @note Default is all variables marked as indifferent.
    void Picosat_set_less_important_lit(PicoSATSolver *solver, int lit);

    /// @brief Prints a message to the solver's internal output file.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param verbosity_level Verbosity level required for the message to be printed.
    /// @param fmt Format string for the message.
    /// @param ... Additional arguments for the format string.
    /// @return None.
    void Picosat_message(PicoSATSolver *solver, int verbosity_level, const char *fmt, ...);

    /// @brief Sets the seed for the random number generator used in random decisions.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param random_number_generator_seed Seed value for the random number generator.
    /// @note Useful for benchmarking different parameter sets, less effective for industrial examples.
    /// @return None.
    void Picosat_set_seed(PicoSATSolver *solver, unsigned random_number_generator_seed);

    /// @brief Enables proof trace generation for extracting cores or traces.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note Must be called immediately after Picosat_init. Not needed for Picosat_set_incremental_rup_file.
    /// @note Trace generation may not be included if compiled with full optimization (e.g., './configure -O').
    /// @return Non-zero if trace generation is supported, zero otherwise.
    int Picosat_enable_trace_generation(PicoSATSolver *solver);

    /// @brief Sets a file for incremental RUP proof trace dumping.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param file Output file for the RUP trace.
    /// @param m Maximum number of variables.
    /// @param n Number of original clauses.
    /// @note Reduces memory usage but dumped clauses may not be in the clausal core.
    /// @return None.
    void Picosat_set_incremental_rup_file(PicoSATSolver *solver, FILE *file, int m, int n);

    /// @brief Saves original clauses for use with Picosat_deref_partial.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return None.
    void Picosat_save_original_clauses(PicoSATSolver *solver);

    /// @brief Allocates and returns the next unused variable index.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note The variable is treated as used in future calls to Picosat_sat, Picosat_deref, and Picosat_changed.
    /// @return The next available variable index.
    int Picosat_inc_max_var(PicoSATSolver *solver);

    /// @brief Push and pop semantics for PicoSAT.   'picosat_push' opens up a new
    /// context.  All clauses added in this context are attached to it and
    /// discarded when the context is closed with 'picosat_pop'.  It is also
    /// possible to nest contexts.
    ///
    /// The current implementation uses a new internal variable for each context.
    /// However, the indices for these internal variables are shared with
    /// ordinary external variables.  This means that after any call to
    /// 'picosat_push', new variable indices should be obtained with
    /// 'picosat_inc_max_var' and not just by incrementing the largest variable
    /// index used so far.
    ///
    /// @param solver Pointer to the PicoSATSolver..
    /// @return The return value is the index of the literal that assumes this context.
    /// This literal can only be used for 'picosat_failed_context' otherwise
    /// it will lead to an API usage error.
    int Picosat_push(PicoSATSolver *solver);
    /// @brief This is as 'picosat_failed_assumption', but only for internal variables
    /// generated by 'picosat_push'.
    /// @param solver
    /// @param lit
    /// @return boolean value
    int Picosat_failed_context(PicoSATSolver *solver, int lit);

    /// @brief
    /// @param solver
    /// @return the literal that assumes the current context or zero if the outer context has been reached.
    int Picosat_context(PicoSATSolver *solver);
    /// @brief Closes the current context and recycles the literal generated for assuming this context.
    /// @return return value is the literal for the new outer context or zero if the outer most context has been reached.
    int Picosat_pop(PicoSATSolver *solver);

    /// @brief Forces immediate removal of satisfied clauses and those in closed contexts.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note Called internally after sufficient units are learned or contexts closed (MAXCILS limit).
    /// @note Retains learned clauses involving outer contexts.
    /// @return None.
    void Picosat_simplify(PicoSATSolver *solver);

    /// @brief Optimizes variable table size to reduce resizing.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param max_idx Estimated maximum variable index.
    /// @note Has the same effect as Picosat_inc_max_var but optimizes allocation.
    /// @return None.
    void Picosat_adjust(PicoSATSolver *solver, int max_idx);

    /// @brief Retrieves solver statistics.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return  Number of variables (p cnf <m> n).
    int Picosat_variables(PicoSATSolver *solver);
    /// @brief Retrieves solver statistics.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return  Number of original clauses (p cnf m <n>).
    int Picosat_added_original_clauses(PicoSATSolver *solver);
    /// @brief Retrieves solver statistics.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return  Maximum memory allocated.
    size_t Picosat_max_bytes_allocated(PicoSATSolver *solver);
    /// @brief Retrieves solver statistics.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return Current process time.
    double Picosat_time_stamp(void);
    /// @brief Retrieves solver statistics.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return  None (prints to output file).
    void Picosat_stats(PicoSATSolver *solver);
    /// @brief Retrieves solver statistics.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param file Output file for Picosat_stats (others return directly).
    /// @return  Number of propagations.
    unsigned long long Picosat_propagations(PicoSATSolver *solver);
    /// @brief Retrieves solver statistics.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return  Number of decisions.
    unsigned long long Picosat_decisions(PicoSATSolver *solver);
    /// @brief Retrieves solver statistics.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return Number of visits.
    unsigned long long Picosat_visits(PicoSATSolver *solver);
    /// @brief Retrieves solver statistics.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return Time spent in library calls or Picosat_sat (if Picosat_measure_all_calls enabled).
    double Picosat_seconds(PicoSATSolver *solver);

    /// @brief Adds literals or clauses to the solver incrementally.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to add (Picosat_add).
    /// @note Adding a literal resets the previous assignment.
    /// @return The original clause index (starting at 0) for the added literal or clause.
    int Picosat_add(PicoSATSolver *solver, int lit);
    /// @brief Adds literals or clauses to the solver incrementally.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param ... Variable argument list of literals terminated by zero (Picosat_add_arg).
    /// @note Adding a literal resets the previous assignment.
    /// @return The original clause index (starting at 0) for the added literal or clause.
    int Picosat_add_arg(PicoSATSolver *solver, ...);
    /// @brief Adds literals or clauses to the solver incrementally.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lits Array of literals terminated by zero (Picosat_add_lits).
    /// @note Adding a literal resets the previous assignment.
    /// @return The original clause index (starting at 0) for the added literal or clause.
    int Picosat_add_lits(PicoSATSolver *solver, int *lits);

    /// @brief Prints the CNF to a file in DIMACS format.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param file Output file for the CNF.
    /// @return None.
    void Picosat_print(PicoSATSolver *solver, FILE *file);

    /// @brief Adds an assumption for the next Picosat_sat call.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to assume (interpreted as a unit clause).
    /// @note Assumptions are valid only for the next Picosat_sat call and are cleared afterward unless reassumed.
    /// @note Assumptions remain valid post-Picosat_sat for Picosat_failed_assumption until Picosat_add, Picosat_assume, or another Picosat_sat is called.
    /// @return None.
    void Picosat_assume(PicoSATSolver *solver, int lit);

    /// @brief Adds a literal to the global all-different constraint (ADC).
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to add to the ADC.
    /// @note Only one global ADC is supported; all bit-vectors must have identical bit-width.
    /// @note TODO: Handle top-level assigned literals.
    /// @return None.
    void Picosat_add_ado_lit(PicoSATSolver *solver, int lit);

    /// @brief Runs the main SAT solving routine.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param decision_limit Maximum number of decisions (negative for no limit).
    /// @return PICOSAT_SATISFIABLE, PICOSAT_UNSATISFIABLE, or PICOSAT_UNKNOWN.
    int Picosat_sat(PicoSATSolver *solver, int decision_limit);

    /// @brief Sets a propagation limit for Picosat_sat.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param limit Maximum number of propagations.
    /// @note Must be called after Picosat_init and before Picosat_sat.
    /// @return None.
    void Picosat_set_propagation_limit(PicoSATSolver *solver, unsigned long long limit);

    /// @brief Returns the result of the last Picosat_sat call.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return Last Picosat_sat result or 0 if not called.
    int Picosat_res(PicoSATSolver *solver);

    /// @brief Dereferences a literal to get its assignment after Picosat_sat returns PICOSAT_SATISFIABLE.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to dereference.
    /// @return 1 (true), -1 (false), or 0 (unknown).
    int Picosat_deref(PicoSATSolver *solver, int lit);

    /// @brief Checks if a literal is forced at the top level.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to check.
    /// @note Does not require Picosat_sat and does not reset incremental usage.
    /// @return 1 (true), -1 (false), or 0 (unknown).
    int Picosat_deref_toplevel(PicoSATSolver *solver, int lit);

    /// @brief Retrieves a partial satisfying assignment for original clauses after Picosat_sat returns PICOSAT_SATISFIABLE.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to dereference.
    /// @note Requires Picosat_save_original_clauses to be called after initialization.
    /// @return 1 (true), -1 (false), or 0 (unknown).
    int Picosat_deref_partial(PicoSATSolver *solver, int lit);

    /// @brief Checks if the CNF is unsatisfiable due to an empty clause.
    /// @param solver Pointer to the PicoSATSolver.
    /// @return Non-zero if unsatisfiable due to an empty clause, zero otherwise.
    int Picosat_inconsistent(PicoSATSolver *solver);

    /// @brief Checks if a literal is a failed assumption in the last Picosat_sat call.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param lit Literal to check.
    /// @note Only valid while current assumptions are active (see Picosat_assume).
    /// @return Non-zero if the literal is a failed assumption, zero otherwise.
    int Picosat_failed_assumption(PicoSATSolver *solver, int lit);

    /// @brief Returns a zero-terminated list of failed assumptions from the last Picosat_sat call.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note Valid until the next Picosat_sat or Picosat_failed_assumptions call.
    /// @note Only meaningful if Picosat_sat returned PICOSAT_UNSATISFIABLE.
    /// @return Pointer to a zero-terminated array of failed assumptions.
    const int *Picosat_failed_assumptions(PicoSATSolver *solver);

    /// @brief Computes a minimized list of failed assumptions from the last Picosat_sat call.
    /// @param solver Pointer to the PicoSATSolver.
    /// @param state User-defined state for the callback.
    /// @param callback Function called for each simplified assumption set (receives state and reduced assumptions).
    /// @param fix Non-zero to permanently assign assumptions (true for necessary, false for redundant).
    /// @note Only meaningful if Picosat_sat returned PICOSAT_UNSATISFIABLE.
    /// @note Valid until the next Picosat_sat, Picosat_mus_assumptions, or this function call.
    /// @return Pointer to a zero-terminated minimized array of failed assumptions.
    const int *Picosat_mus_assumptions(PicoSATSolver *solver, void *state, void (*callback)(void *, const int *), int fix);

    /// @brief Computes a maximal satisfiable subset of assumptions.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note Requires assumptions set and Picosat_sat called with Picosat_inconsistent checked.
    /// @note Reassumes all assumptions before returning.
    /// @note Setting assumption phases to true may improve performance.
    /// @return Pointer to a zero-terminated array of consistent assumptions.
    const int *Picosat_maximal_satisfiable_subset_of_assumptions(PicoSATSolver *solver);

    /// @brief Iterates over maximal satisfiable subsets of assumptions.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note Requires assumptions set via Picosat_assume; calls Picosat_sat internally unless inconsistent.
    /// @note Adds a blocking clause to rule out the returned subset, altering the CNF.
    /// @note Setting assumption phases to true may improve performance.
    /// @return Pointer to a zero-terminated array of consistent assumptions or NULL if none remain.
    const int *Picosat_next_maximal_satisfiable_subset_of_assumptions(PicoSATSolver *solver);

    /// @brief Iterates over minimal correcting assumption sets.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note Each assumed literal appears once in the result, even if assumed multiple times.
    /// @note Setting assumption phases to true may improve performance.
    /// @return Pointer to a zero-terminated array of minimal correcting assumptions.
    const int *Picosat_next_minimal_correcting_subset_of_assumptions(PicoSATSolver *solver);

    /// @brief Computes the union of all minimal correcting assumption sets (HUMUS).
    /// @param solver Pointer to the PicoSATSolver.
    /// @param callback Function called after each minimal correcting set (receives state, nmcs, nhumus).
    /// @param state User-defined state for the callback.
    /// @note Renders the CNF inconsistent after one call; requires solver reset.
    /// @note Uses Picosat_next_minimal_correcting_subset_of_assumptions internally.
    /// @return Pointer to a zero-terminated array of assumptions in the HUMUS.
    const int *Picosat_humus(PicoSATSolver *solver, void (*callback)(void *state, int nmcs, int nhumus), void *state);

    /// @brief Checks if the assignment of old variables changed between Picosat_sat calls returning SATISFIABLE.
    /// @param solver Pointer to the PicoSATSolver.
    /// @note Valid until Picosat_add, Picosat_assume, or Picosat_sat is called.
    /// @note May return non-zero even if no change occurred due to internal flip tracking (TODO: exact tracking not implemented).
    /// @return 0 if old variable assignments are unchanged, non-zero if they might have changed.
    int Picosat_changed(PicoSATSolver *solver);

    /// @brief Determines if the i'th original clause is in the clausal core.
    /// @param solver Pointer to the PicoSAT solver.
    /// @param i Clause index from picosat_add (0 <= i < picosat_added_original_clauses).
    /// @note Requires trace generation enabled via picosat_enable_trace_generation after picosat_init.
    /// @note Incremental mode with assumptions tested only for picosat_corelit; may not work reliably here.
    /// @return Non-zero if the clause is in the core, zero otherwise.
    int Picosat_coreclause(PicoSATSolver *solver, int i);

    /// @brief Checks if a literal is in the variable core (resolved in deriving the empty clause).
    /// @param solver Pointer to the PicoSAT solver.
    /// @param lit Literal to check.
    /// @note Requires trace generation enabled via picosat_enable_trace_generation after picosat_init.
    /// @note Tested in incremental mode with assumptions; other core functions may not work reliably.
    /// @return Non-zero if the literal is in the variable core, zero otherwise.
    int Picosat_corelit(PicoSATSolver *solver, int lit);

    /// @brief Writes clauses used in deriving the empty clause to a file in DIMACS format.
    /// @param solver Pointer to the PicoSAT solver.
    /// @param core_file Output file for the clausal core.
    /// @note Requires trace generation enabled via picosat_enable_trace_generation after picosat_init.
    /// @note Incremental mode with assumptions tested only for picosat_corelit; may not work reliably here.
    /// @return None.
    void Picosat_write_clausal_core(PicoSATSolver *solver, FILE *core_file);

    /// @brief Writes a compact proof trace in TraceCheck format to a file.
    /// @param solver Pointer to the PicoSAT solver.
    /// @param trace_file Output file for the proof trace.
    /// @note Requires trace generation enabled via picosat_enable_trace_generation after picosat_init.
    /// @note Incremental mode with assumptions tested only for picosat_corelit; may not work reliably here.
    /// @return None.
    void Picosat_write_compact_trace(PicoSATSolver *solver, FILE *trace_file);

    /// @brief Writes an extended proof trace in TraceCheck format to a file.
    /// @param solver Pointer to the PicoSAT solver.
    /// @param trace_file Output file for the proof trace.
    /// @note Requires trace generation enabled via picosat_enable_trace_generation after picosat_init.
    /// @note Incremental mode with assumptions tested only for picosat_corelit; may not work reliably here.
    /// @return None.
    void Picosat_write_extended_trace(PicoSATSolver *solver, FILE *trace_file);

    /// @brief Writes a RUP trace of learned core clauses to a file.
    /// @param solver Pointer to the PicoSAT solver.
    /// @param trace_file Output file for the RUP trace.
    /// @note Requires trace generation enabled via picosat_enable_trace_generation after picosat_init.
    /// @note Unlike picosat_set_incremental_rup_file, only includes learned core clauses.
    /// @note Incremental mode with assumptions tested only for picosat_corelit; may not work reliably here.
    /// @return None.
    void Picosat_write_rup_trace(PicoSATSolver *solver, FILE *trace_file);

    /// @brief Checks if a literal was used in resolution to derive a learned clause.
    /// @param solver Pointer to the PicoSAT solver.
    /// @param lit Literal to check.
    /// @note Core literals are a subset of used literals; does not require keeping proof traces.
    /// @return Non-zero if the literal was used, zero otherwise.
    int Picosat_usedlit(PicoSATSolver *solver, int lit);
#ifdef __cplusplus
}
#endif

#endif
