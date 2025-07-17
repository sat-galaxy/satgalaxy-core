
#include "satgalaxy_picosat.h"
#include "picosat.h"
#include <stdarg.h>


struct PicoSATSolver
{
  /* data */
  PicoSAT *solver;
  int error;
};


const char *picosat_version (void){
  return "PICOSAT_VERSION";
}
PicoSATSolver *Picosat_init(void) {
  PicoSATSolver *solver = malloc(sizeof(PicoSATSolver));
  solver->solver = (PicoSAT *)picosat_init();
  solver->error = 0;
  return solver;
}

PicoSATSolver *Picosat_minit(void *state,
                                       Picosat_malloc m,
                                       Picosat_realloc r,
                                       Picosat_free f) {
  return (PicoSATSolver *)picosat_minit(state, m, r, f);
}

void Picosat_reset(PicoSATSolver *solver) {
  picosat_reset(solver->solver);
}
void Picosat_set_output(PicoSATSolver *solver, FILE *file) {
  picosat_set_output(solver->solver, file);
}

void Picosat_measure_all_calls(PicoSATSolver *solver) {
  picosat_measure_all_calls(solver->solver);
}

void Picosat_set_prefix(PicoSATSolver *solver, const char *prefix) {
  picosat_set_prefix(solver->solver, prefix);
}

void Picosat_set_verbosity(PicoSATSolver *solver, int new_verbosity_level) {
  picosat_set_verbosity(solver->solver, new_verbosity_level);
}

void Picosat_set_plain(PicoSATSolver *solver, int new_plain_value) {
  picosat_set_plain(solver->solver, new_plain_value);
}

void Picosat_set_global_default_phase(PicoSATSolver *solver, int phase) {
  picosat_set_global_default_phase(solver->solver, phase);
}

void Picosat_set_default_phase_lit(PicoSATSolver *solver, int lit, int phase) {
  picosat_set_default_phase_lit(solver->solver, lit, phase);
}

void Picosat_reset_phases(PicoSATSolver *solver) {
  picosat_reset_phases(solver->solver);
}

void Picosat_reset_scores(PicoSATSolver *solver) {
  picosat_reset_scores(solver->solver);
}

void Picosat_remove_learned(PicoSATSolver *solver, unsigned percentage) {
  picosat_remove_learned(solver->solver, percentage);
}

void Picosat_set_more_important_lit(PicoSATSolver *solver, int lit) {
  picosat_set_more_important_lit(solver->solver, lit);
}

void Picosat_set_less_important_lit(PicoSATSolver *solver, int lit) {
  picosat_set_less_important_lit(solver->solver, lit);
}

void Picosat_message(PicoSATSolver *solver, int verbosity_level, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  picosat_message(solver->solver, verbosity_level, fmt, args);
  va_end(args);
}

void Picosat_set_seed(PicoSATSolver *solver, unsigned random_number_generator_seed) {
  picosat_set_seed(solver->solver, random_number_generator_seed);
}

int Picosat_enable_trace_generation(PicoSATSolver *solver) {
  return picosat_enable_trace_generation(solver->solver);
}

void Picosat_set_incremental_rup_file(PicoSATSolver *solver, FILE *file, int m, int n) {
  picosat_set_incremental_rup_file(solver->solver, file, m, n);
}

void Picosat_save_original_clauses(PicoSATSolver *solver) {
  picosat_save_original_clauses(solver->solver);
}

int Picosat_inc_max_var(PicoSATSolver *solver) {
  return picosat_inc_max_var(solver->solver);
}

int Picosat_push(PicoSATSolver *solver) {
  return picosat_push(solver->solver);
}

int Picosat_failed_context(PicoSATSolver *solver, int lit) {
  return picosat_failed_context(solver->solver, lit);
}

int Picosat_context(PicoSATSolver *solver) {
  return picosat_context(solver->solver);
}

int Picosat_pop(PicoSATSolver *solver) {
  return picosat_pop(solver->solver);
}

void Picosat_simplify(PicoSATSolver *solver) {
  picosat_simplify(solver->solver);
}

void Picosat_adjust(PicoSATSolver *solver, int max_idx) {
  picosat_adjust(solver->solver, max_idx);
}

int Picosat_variables(PicoSATSolver *solver) {
  return picosat_variables(solver->solver);
}

int Picosat_added_original_clauses(PicoSATSolver *solver) {
  return picosat_added_original_clauses(solver->solver);
}

size_t Picosat_max_bytes_allocated(PicoSATSolver *solver) {
  return picosat_max_bytes_allocated(solver->solver);
}

double Picosat_time_stamp(void) {
  return picosat_time_stamp();
}

void Picosat_stats(PicoSATSolver *solver) {
  picosat_stats(solver->solver);
}

unsigned long long Picosat_propagations(PicoSATSolver *solver) {
  return picosat_propagations(solver->solver);
}

unsigned long long Picosat_decisions(PicoSATSolver *solver) {
  return picosat_decisions(solver->solver);
}

unsigned long long Picosat_visits(PicoSATSolver *solver) {
  return picosat_visits(solver->solver);
}

double Picosat_seconds(PicoSATSolver *solver) {
  return picosat_seconds(solver->solver);
}

int Picosat_add(PicoSATSolver *solver, int lit) {
  return picosat_add(solver->solver, lit);
}

int Picosat_add_arg(PicoSATSolver *solver, ...) {
  va_list args;
  int res = picosat_add_arg(solver->solver, args);
  return res;
}

int Picosat_add_lits(PicoSATSolver *solver, int *lits) {
  return picosat_add_lits(solver->solver, lits);
}

void Picosat_print(PicoSATSolver *solver, FILE *file) {
  picosat_print(solver->solver, file);
}

void Picosat_assume(PicoSATSolver *solver, int lit) {
  picosat_assume(solver->solver, lit);
}

void Picosat_add_ado_lit(PicoSATSolver *solver, int lit) {
  picosat_add_ado_lit(solver->solver, lit);
}

int Picosat_sat(PicoSATSolver *solver, int decision_limit) {
  return picosat_sat(solver->solver, decision_limit);
}

void Picosat_set_propagation_limit(PicoSATSolver *solver, unsigned long long limit) {
  picosat_set_propagation_limit(solver->solver, limit);
}

int Picosat_res(PicoSATSolver *solver) {
  return picosat_res(solver->solver);
}

int Picosat_deref(PicoSATSolver *solver, int lit) {
  return picosat_deref(solver->solver, lit);
}

int Picosat_deref_toplevel(PicoSATSolver *solver, int lit) {
  return picosat_deref_toplevel(solver->solver, lit);
}

int Picosat_deref_partial(PicoSATSolver *solver, int lit) {
  return picosat_deref_partial(solver->solver, lit);
}

int Picosat_inconsistent(PicoSATSolver *solver) {
  return picosat_inconsistent(solver->solver);
}

int Picosat_failed_assumption(PicoSATSolver *solver, int lit) {
  return picosat_failed_assumption(solver->solver, lit);
}

const int *Picosat_failed_assumptions(PicoSATSolver *solver) {
  return picosat_failed_assumptions(solver->solver);
}

const int *Picosat_mus_assumptions(PicoSATSolver *solver, void *state,
                                             void (*callback)(void *, const int *), int fix) {
  return picosat_mus_assumptions(solver->solver, state, callback, fix);
}

const int *Picosat_maximal_satisfiable_subset_of_assumptions(PicoSATSolver *solver) {
  return picosat_maximal_satisfiable_subset_of_assumptions(solver->solver);
}

const int *Picosat_next_maximal_satisfiable_subset_of_assumptions(PicoSATSolver *solver) {
  return picosat_next_maximal_satisfiable_subset_of_assumptions(solver->solver);
}

const int *Picosat_next_minimal_correcting_subset_of_assumptions(PicoSATSolver *solver) {
  return picosat_next_minimal_correcting_subset_of_assumptions(solver->solver);
}

const int *Picosat_humus(PicoSATSolver *solver,
                                   void (*callback)(void *, int nmcs, int nhumus),
                                   void *state) {
  return picosat_humus(solver->solver, callback, state);
}

int Picosat_changed(PicoSATSolver *solver) {
  return picosat_changed(solver->solver);
}

int Picosat_coreclause(PicoSATSolver *solver, int i) {
  return picosat_coreclause(solver->solver, i);
}

int Picosat_corelit(PicoSATSolver *solver, int lit) {
  return picosat_corelit(solver->solver, lit);
}

void Picosat_write_clausal_core(PicoSATSolver *solver, FILE *core_file) {
  picosat_write_clausal_core(solver->solver, core_file);
}

void Picosat_write_compact_trace(PicoSATSolver *solver, FILE *trace_file) {
  picosat_write_compact_trace(solver->solver, trace_file);
}

void Picosat_write_extended_trace(PicoSATSolver *solver, FILE *trace_file) {
  picosat_write_extended_trace(solver->solver, trace_file);
}

void Picosat_write_rup_trace(PicoSATSolver *solver, FILE *trace_file) {
  picosat_write_rup_trace(solver->solver, trace_file);
}

int Picosat_usedlit(PicoSATSolver *solver, int lit) {
  return picosat_usedlit(solver->solver, lit);
}