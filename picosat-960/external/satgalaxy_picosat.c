
#include "satgalaxy_picosat.h"
#include "picosat.h"
#include <stdarg.h>


const char *picosat_version (void){
  return "PICOSAT_VERSION";
}
PicoSATSolver *Picosat_init(void) {
  return (PicoSATSolver *)picosat_init();
}

PicoSATSolver *Picosat_minit(void *state,
                                       Picosat_malloc m,
                                       Picosat_realloc r,
                                       Picosat_free f) {
  return (PicoSATSolver *)picosat_minit(state, m, r, f);
}

void Picosat_reset(PicoSATSolver *solver) {
  picosat_reset((PicoSAT *)solver);
}
void Picosat_set_output(PicoSATSolver *solver, FILE *file) {
  picosat_set_output((PicoSAT *)solver, file);
}

void Picosat_measure_all_calls(PicoSATSolver *solver) {
  picosat_measure_all_calls((PicoSAT *)solver);
}

void Picosat_set_prefix(PicoSATSolver *solver, const char *prefix) {
  picosat_set_prefix((PicoSAT *)solver, prefix);
}

void Picosat_set_verbosity(PicoSATSolver *solver, int new_verbosity_level) {
  picosat_set_verbosity((PicoSAT *)solver, new_verbosity_level);
}

void Picosat_set_plain(PicoSATSolver *solver, int new_plain_value) {
  picosat_set_plain((PicoSAT *)solver, new_plain_value);
}

void Picosat_set_global_default_phase(PicoSATSolver *solver, int phase) {
  picosat_set_global_default_phase((PicoSAT *)solver, phase);
}

void Picosat_set_default_phase_lit(PicoSATSolver *solver, int lit, int phase) {
  picosat_set_default_phase_lit((PicoSAT *)solver, lit, phase);
}

void Picosat_reset_phases(PicoSATSolver *solver) {
  picosat_reset_phases((PicoSAT *)solver);
}

void Picosat_reset_scores(PicoSATSolver *solver) {
  picosat_reset_scores((PicoSAT *)solver);
}

void Picosat_remove_learned(PicoSATSolver *solver, unsigned percentage) {
  picosat_remove_learned((PicoSAT *)solver, percentage);
}

void Picosat_set_more_important_lit(PicoSATSolver *solver, int lit) {
  picosat_set_more_important_lit((PicoSAT *)solver, lit);
}

void Picosat_set_less_important_lit(PicoSATSolver *solver, int lit) {
  picosat_set_less_important_lit((PicoSAT *)solver, lit);
}

void Picosat_message(PicoSATSolver *solver, int verbosity_level, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  picosat_message((PicoSAT *)solver, verbosity_level, fmt, args);
  va_end(args);
}

void Picosat_set_seed(PicoSATSolver *solver, unsigned random_number_generator_seed) {
  picosat_set_seed((PicoSAT *)solver, random_number_generator_seed);
}

int Picosat_enable_trace_generation(PicoSATSolver *solver) {
  return picosat_enable_trace_generation((PicoSAT *)solver);
}

void Picosat_set_incremental_rup_file(PicoSATSolver *solver, FILE *file, int m, int n) {
  picosat_set_incremental_rup_file((PicoSAT *)solver, file, m, n);
}

void Picosat_save_original_clauses(PicoSATSolver *solver) {
  picosat_save_original_clauses((PicoSAT *)solver);
}

int Picosat_inc_max_var(PicoSATSolver *solver) {
  return picosat_inc_max_var((PicoSAT *)solver);
}

int Picosat_push(PicoSATSolver *solver) {
  return picosat_push((PicoSAT *)solver);
}

int Picosat_failed_context(PicoSATSolver *solver, int lit) {
  return picosat_failed_context((PicoSAT *)solver, lit);
}

int Picosat_context(PicoSATSolver *solver) {
  return picosat_context((PicoSAT *)solver);
}

int Picosat_pop(PicoSATSolver *solver) {
  return picosat_pop((PicoSAT *)solver);
}

void Picosat_simplify(PicoSATSolver *solver) {
  picosat_simplify((PicoSAT *)solver);
}

void Picosat_adjust(PicoSATSolver *solver, int max_idx) {
  picosat_adjust((PicoSAT *)solver, max_idx);
}

int Picosat_variables(PicoSATSolver *solver) {
  return picosat_variables((PicoSAT *)solver);
}

int Picosat_added_original_clauses(PicoSATSolver *solver) {
  return picosat_added_original_clauses((PicoSAT *)solver);
}

size_t Picosat_max_bytes_allocated(PicoSATSolver *solver) {
  return picosat_max_bytes_allocated((PicoSAT *)solver);
}

double Picosat_time_stamp(void) {
  return picosat_time_stamp();
}

void Picosat_stats(PicoSATSolver *solver) {
  picosat_stats((PicoSAT *)solver);
}

unsigned long long Picosat_propagations(PicoSATSolver *solver) {
  return picosat_propagations((PicoSAT *)solver);
}

unsigned long long Picosat_decisions(PicoSATSolver *solver) {
  return picosat_decisions((PicoSAT *)solver);
}

unsigned long long Picosat_visits(PicoSATSolver *solver) {
  return picosat_visits((PicoSAT *)solver);
}

double Picosat_seconds(PicoSATSolver *solver) {
  return picosat_seconds((PicoSAT *)solver);
}

int Picosat_add(PicoSATSolver *solver, int lit) {
  return picosat_add((PicoSAT *)solver, lit);
}

int Picosat_add_arg(PicoSATSolver *solver, ...) {
  va_list args;
  int res = picosat_add_arg((PicoSAT *)solver, args);
  return res;
}

int Picosat_add_lits(PicoSATSolver *solver, int *lits) {
  return picosat_add_lits((PicoSAT *)solver, lits);
}

void Picosat_print(PicoSATSolver *solver, FILE *file) {
  picosat_print((PicoSAT *)solver, file);
}

void Picosat_assume(PicoSATSolver *solver, int lit) {
  picosat_assume((PicoSAT *)solver, lit);
}

void Picosat_add_ado_lit(PicoSATSolver *solver, int lit) {
  picosat_add_ado_lit((PicoSAT *)solver, lit);
}

int Picosat_sat(PicoSATSolver *solver, int decision_limit) {
  return picosat_sat((PicoSAT *)solver, decision_limit);
}

void Picosat_set_propagation_limit(PicoSATSolver *solver, unsigned long long limit) {
  picosat_set_propagation_limit((PicoSAT *)solver, limit);
}

int Picosat_res(PicoSATSolver *solver) {
  return picosat_res((PicoSAT *)solver);
}

int Picosat_deref(PicoSATSolver *solver, int lit) {
  return picosat_deref((PicoSAT *)solver, lit);
}

int Picosat_deref_toplevel(PicoSATSolver *solver, int lit) {
  return picosat_deref_toplevel((PicoSAT *)solver, lit);
}

int Picosat_deref_partial(PicoSATSolver *solver, int lit) {
  return picosat_deref_partial((PicoSAT *)solver, lit);
}

int Picosat_inconsistent(PicoSATSolver *solver) {
  return picosat_inconsistent((PicoSAT *)solver);
}

int Picosat_failed_assumption(PicoSATSolver *solver, int lit) {
  return picosat_failed_assumption((PicoSAT *)solver, lit);
}

const int *Picosat_failed_assumptions(PicoSATSolver *solver) {
  return picosat_failed_assumptions((PicoSAT *)solver);
}

const int *Picosat_mus_assumptions(PicoSATSolver *solver, void *state,
                                             void (*callback)(void *, const int *), int fix) {
  return picosat_mus_assumptions((PicoSAT *)solver, state, callback, fix);
}

const int *Picosat_maximal_satisfiable_subset_of_assumptions(PicoSATSolver *solver) {
  return picosat_maximal_satisfiable_subset_of_assumptions((PicoSAT *)solver);
}

const int *Picosat_next_maximal_satisfiable_subset_of_assumptions(PicoSATSolver *solver) {
  return picosat_next_maximal_satisfiable_subset_of_assumptions((PicoSAT *)solver);
}

const int *Picosat_next_minimal_correcting_subset_of_assumptions(PicoSATSolver *solver) {
  return picosat_next_minimal_correcting_subset_of_assumptions((PicoSAT *)solver);
}

const int *Picosat_humus(PicoSATSolver *solver,
                                   void (*callback)(void *, int nmcs, int nhumus),
                                   void *state) {
  return picosat_humus((PicoSAT *)solver, callback, state);
}

int Picosat_changed(PicoSATSolver *solver) {
  return picosat_changed((PicoSAT *)solver);
}

int Picosat_coreclause(PicoSATSolver *solver, int i) {
  return picosat_coreclause((PicoSAT *)solver, i);
}

int Picosat_corelit(PicoSATSolver *solver, int lit) {
  return picosat_corelit((PicoSAT *)solver, lit);
}

void Picosat_write_clausal_core(PicoSATSolver *solver, FILE *core_file) {
  picosat_write_clausal_core((PicoSAT *)solver, core_file);
}

void Picosat_write_compact_trace(PicoSATSolver *solver, FILE *trace_file) {
  picosat_write_compact_trace((PicoSAT *)solver, trace_file);
}

void Picosat_write_extended_trace(PicoSATSolver *solver, FILE *trace_file) {
  picosat_write_extended_trace((PicoSAT *)solver, trace_file);
}

void Picosat_write_rup_trace(PicoSATSolver *solver, FILE *trace_file) {
  picosat_write_rup_trace((PicoSAT *)solver, trace_file);
}

int Picosat_usedlit(PicoSATSolver *solver, int lit) {
  return picosat_usedlit((PicoSAT *)solver, lit);
}