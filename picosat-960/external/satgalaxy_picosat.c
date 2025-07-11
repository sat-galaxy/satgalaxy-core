
#include "satgalaxy_picosat.h"
#include "picosat.h"
#include <stdarg.h>


const char *picosat_version (void){
  return "PICOSAT_VERSION";
}
PicoSATSolver *satgalaxy_picosat_init(void) {
  return (PicoSATSolver *)picosat_init();
}

PicoSATSolver *satgalaxy_picosat_minit(void *state,
                                       satgalaxy_picosat_malloc m,
                                       satgalaxy_picosat_realloc r,
                                       satgalaxy_picosat_free f) {
  return (PicoSATSolver *)picosat_minit(state, m, r, f);
}

void satgalaxy_picosat_reset(PicoSATSolver *solver) {
  picosat_reset((PicoSAT *)solver);
}
void satgalaxy_picosat_set_output(PicoSATSolver *solver, FILE *file) {
  picosat_set_output((PicoSAT *)solver, file);
}

void satgalaxy_picosat_measure_all_calls(PicoSATSolver *solver) {
  picosat_measure_all_calls((PicoSAT *)solver);
}

void satgalaxy_picosat_set_prefix(PicoSATSolver *solver, const char *prefix) {
  picosat_set_prefix((PicoSAT *)solver, prefix);
}

void satgalaxy_picosat_set_verbosity(PicoSATSolver *solver, int new_verbosity_level) {
  picosat_set_verbosity((PicoSAT *)solver, new_verbosity_level);
}

void satgalaxy_picosat_set_plain(PicoSATSolver *solver, int new_plain_value) {
  picosat_set_plain((PicoSAT *)solver, new_plain_value);
}

void satgalaxy_picosat_set_global_default_phase(PicoSATSolver *solver, int phase) {
  picosat_set_global_default_phase((PicoSAT *)solver, phase);
}

void satgalaxy_picosat_set_default_phase_lit(PicoSATSolver *solver, int lit, int phase) {
  picosat_set_default_phase_lit((PicoSAT *)solver, lit, phase);
}

void satgalaxy_picosat_reset_phases(PicoSATSolver *solver) {
  picosat_reset_phases((PicoSAT *)solver);
}

void satgalaxy_picosat_reset_scores(PicoSATSolver *solver) {
  picosat_reset_scores((PicoSAT *)solver);
}

void satgalaxy_picosat_remove_learned(PicoSATSolver *solver, unsigned percentage) {
  picosat_remove_learned((PicoSAT *)solver, percentage);
}

void satgalaxy_picosat_set_more_important_lit(PicoSATSolver *solver, int lit) {
  picosat_set_more_important_lit((PicoSAT *)solver, lit);
}

void satgalaxy_picosat_set_less_important_lit(PicoSATSolver *solver, int lit) {
  picosat_set_less_important_lit((PicoSAT *)solver, lit);
}

void satgalaxy_picosat_message(PicoSATSolver *solver, int verbosity_level, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  picosat_message((PicoSAT *)solver, verbosity_level, fmt, args);
  va_end(args);
}

void satgalaxy_picosat_set_seed(PicoSATSolver *solver, unsigned random_number_generator_seed) {
  picosat_set_seed((PicoSAT *)solver, random_number_generator_seed);
}

int satgalaxy_picosat_enable_trace_generation(PicoSATSolver *solver) {
  return picosat_enable_trace_generation((PicoSAT *)solver);
}

void satgalaxy_picosat_set_incremental_rup_file(PicoSATSolver *solver, FILE *file, int m, int n) {
  picosat_set_incremental_rup_file((PicoSAT *)solver, file, m, n);
}

void satgalaxy_picosat_save_original_clauses(PicoSATSolver *solver) {
  picosat_save_original_clauses((PicoSAT *)solver);
}

int satgalaxy_picosat_inc_max_var(PicoSATSolver *solver) {
  return picosat_inc_max_var((PicoSAT *)solver);
}

int satgalaxy_picosat_push(PicoSATSolver *solver) {
  return picosat_push((PicoSAT *)solver);
}

int satgalaxy_picosat_failed_context(PicoSATSolver *solver, int lit) {
  return picosat_failed_context((PicoSAT *)solver, lit);
}

int satgalaxy_picosat_context(PicoSATSolver *solver) {
  return picosat_context((PicoSAT *)solver);
}

int satgalaxy_picosat_pop(PicoSATSolver *solver) {
  return picosat_pop((PicoSAT *)solver);
}

void satgalaxy_picosat_simplify(PicoSATSolver *solver) {
  picosat_simplify((PicoSAT *)solver);
}

void satgalaxy_picosat_adjust(PicoSATSolver *solver, int max_idx) {
  picosat_adjust((PicoSAT *)solver, max_idx);
}

int satgalaxy_picosat_variables(PicoSATSolver *solver) {
  return picosat_variables((PicoSAT *)solver);
}

int satgalaxy_picosat_added_original_clauses(PicoSATSolver *solver) {
  return picosat_added_original_clauses((PicoSAT *)solver);
}

size_t satgalaxy_picosat_max_bytes_allocated(PicoSATSolver *solver) {
  return picosat_max_bytes_allocated((PicoSAT *)solver);
}

double satgalaxy_picosat_time_stamp(void) {
  return picosat_time_stamp();
}

void satgalaxy_picosat_stats(PicoSATSolver *solver) {
  picosat_stats((PicoSAT *)solver);
}

unsigned long long satgalaxy_picosat_propagations(PicoSATSolver *solver) {
  return picosat_propagations((PicoSAT *)solver);
}

unsigned long long satgalaxy_picosat_decisions(PicoSATSolver *solver) {
  return picosat_decisions((PicoSAT *)solver);
}

unsigned long long satgalaxy_picosat_visits(PicoSATSolver *solver) {
  return picosat_visits((PicoSAT *)solver);
}

double satgalaxy_picosat_seconds(PicoSATSolver *solver) {
  return picosat_seconds((PicoSAT *)solver);
}

int satgalaxy_picosat_add(PicoSATSolver *solver, int lit) {
  return picosat_add((PicoSAT *)solver, lit);
}

int satgalaxy_picosat_add_arg(PicoSATSolver *solver, ...) {
  va_list args;
  int res = picosat_add_arg((PicoSAT *)solver, args);
  return res;
}

int satgalaxy_picosat_add_lits(PicoSATSolver *solver, int *lits) {
  return picosat_add_lits((PicoSAT *)solver, lits);
}

void satgalaxy_picosat_print(PicoSATSolver *solver, FILE *file) {
  picosat_print((PicoSAT *)solver, file);
}

void satgalaxy_picosat_assume(PicoSATSolver *solver, int lit) {
  picosat_assume((PicoSAT *)solver, lit);
}

void satgalaxy_picosat_add_ado_lit(PicoSATSolver *solver, int lit) {
  picosat_add_ado_lit((PicoSAT *)solver, lit);
}

int satgalaxy_picosat_sat(PicoSATSolver *solver, int decision_limit) {
  return picosat_sat((PicoSAT *)solver, decision_limit);
}

void satgalaxy_picosat_set_propagation_limit(PicoSATSolver *solver, unsigned long long limit) {
  picosat_set_propagation_limit((PicoSAT *)solver, limit);
}

int satgalaxy_picosat_res(PicoSATSolver *solver) {
  return picosat_res((PicoSAT *)solver);
}

int satgalaxy_picosat_deref(PicoSATSolver *solver, int lit) {
  return picosat_deref((PicoSAT *)solver, lit);
}

int satgalaxy_picosat_deref_toplevel(PicoSATSolver *solver, int lit) {
  return picosat_deref_toplevel((PicoSAT *)solver, lit);
}

int satgalaxy_picosat_deref_partial(PicoSATSolver *solver, int lit) {
  return picosat_deref_partial((PicoSAT *)solver, lit);
}

int satgalaxy_picosat_inconsistent(PicoSATSolver *solver) {
  return picosat_inconsistent((PicoSAT *)solver);
}

int satgalaxy_picosat_failed_assumption(PicoSATSolver *solver, int lit) {
  return picosat_failed_assumption((PicoSAT *)solver, lit);
}

const int *satgalaxy_picosat_failed_assumptions(PicoSATSolver *solver) {
  return picosat_failed_assumptions((PicoSAT *)solver);
}

const int *satgalaxy_picosat_mus_assumptions(PicoSATSolver *solver, void *state,
                                             void (*callback)(void *, const int *), int fix) {
  return picosat_mus_assumptions((PicoSAT *)solver, state, callback, fix);
}

const int *satgalaxy_picosat_maximal_satisfiable_subset_of_assumptions(PicoSATSolver *solver) {
  return picosat_maximal_satisfiable_subset_of_assumptions((PicoSAT *)solver);
}

const int *satgalaxy_picosat_next_maximal_satisfiable_subset_of_assumptions(PicoSATSolver *solver) {
  return picosat_next_maximal_satisfiable_subset_of_assumptions((PicoSAT *)solver);
}

const int *satgalaxy_picosat_next_minimal_correcting_subset_of_assumptions(PicoSATSolver *solver) {
  return picosat_next_minimal_correcting_subset_of_assumptions((PicoSAT *)solver);
}

const int *satgalaxy_picosat_humus(PicoSATSolver *solver,
                                   void (*callback)(void *, int nmcs, int nhumus),
                                   void *state) {
  return picosat_humus((PicoSAT *)solver, callback, state);
}

int satgalaxy_picosat_changed(PicoSATSolver *solver) {
  return picosat_changed((PicoSAT *)solver);
}

int satgalaxy_picosat_coreclause(PicoSATSolver *solver, int i) {
  return picosat_coreclause((PicoSAT *)solver, i);
}

int satgalaxy_picosat_corelit(PicoSATSolver *solver, int lit) {
  return picosat_corelit((PicoSAT *)solver, lit);
}

void satgalaxy_picosat_write_clausal_core(PicoSATSolver *solver, FILE *core_file) {
  picosat_write_clausal_core((PicoSAT *)solver, core_file);
}

void satgalaxy_picosat_write_compact_trace(PicoSATSolver *solver, FILE *trace_file) {
  picosat_write_compact_trace((PicoSAT *)solver, trace_file);
}

void satgalaxy_picosat_write_extended_trace(PicoSATSolver *solver, FILE *trace_file) {
  picosat_write_extended_trace((PicoSAT *)solver, trace_file);
}

void satgalaxy_picosat_write_rup_trace(PicoSATSolver *solver, FILE *trace_file) {
  picosat_write_rup_trace((PicoSAT *)solver, trace_file);
}

int satgalaxy_picosat_usedlit(PicoSATSolver *solver, int lit) {
  return picosat_usedlit((PicoSAT *)solver, lit);
}