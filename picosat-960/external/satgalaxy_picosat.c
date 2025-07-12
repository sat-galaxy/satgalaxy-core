
#include "satgalaxy_picosat.h"
#include "picosat.h"
#include <stdarg.h>

 struct PicoSATSolver
{
  PicoSAT *solver;
};
static int check_ready(PicoSAT *ps,int* error)
{
  int e= picosat_state(ps) == 0 ? 103 : 0;
  if (error)
  {
    *error = e;
  }
  return e;
}

static int check_sat_state(PicoSAT *ps,int* error)
{
  int e= picosat_state(ps) == 2 ? 0 : 104;
  if (error)
  {
    *error = e;
  }
  return e;
}

static int check_unsat_state(PicoSAT *ps,int* error)
{
  int e= picosat_state(ps) == 3 ? 0 : 105;
  if (error)
  {
    *error = e;
  }
  return e;
}

static int check_sat_or_unsat_or_unknown_state(PicoSAT *ps,int* error)
{
  int e= picosat_state(ps) == 2 || picosat_state(ps) == 3 || picosat_state(ps) == 4 ? 0 : 106;
  if (error)
  {
    *error = e;
  }
  return e;
}

const char *picosat_error_msg(int code)
{
  switch (code)
  {
  case 100:
    return "zero 'picosat_malloc' argument";
  case 101:
    return "zero 'picosat_realloc' argument";
  case 102:
    return "zero 'picosat_free' argument";
  case 103:
    return "uninitialized";
  case 104:
    return "expected to be in SAT state";
  case 105:
    return "expected to be in UNSAT state";
  case 106:
    return "expected to be in SAT, UNSAT, or UNKNOWN state";
  default:
    break;
  }
}

const char *picosat_version(void)
{
  return "PICOSAT_VERSION";
}
PicoSATSolver *satgalaxy_picosat_init(int* error)
{
  PicoSATSolver *solver = (PicoSATSolver *)malloc(sizeof(PicoSATSolver));
  solver->solver = (PicoSAT *)picosat_init();
  if (error)
  {
    *error = 0;
  }
  return solver;
}

PicoSATSolver *satgalaxy_picosat_minit(void *state,
                                       satgalaxy_picosat_malloc m,
                                       satgalaxy_picosat_realloc r,
                                       satgalaxy_picosat_free f,
                                      int* error)
{
  if (!m)
  {
    if (error)
    {
      *error = 100;
    }
    return NULL;
  }
  if (!r)
  {
    if (error)
    {
      *error = 101;
    }
    return NULL;
  }
  if (!f)
  {
    if (error)
    {
      *error = 102;
    }
    return NULL;
  }
  PicoSATSolver *solver = (PicoSATSolver *)malloc(sizeof(PicoSATSolver));
  solver->solver = (PicoSAT *)picosat_minit(state, m, r, f);
  return solver;
}

void satgalaxy_picosat_reset(PicoSATSolver *solver,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }
  picosat_reset(solver->solver);
}
void satgalaxy_picosat_set_output(PicoSATSolver *solver, FILE *file,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }
  picosat_set_output(solver->solver, file);
}

void satgalaxy_picosat_measure_all_calls(PicoSATSolver *solver,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }
  picosat_measure_all_calls(solver->solver);
}

void satgalaxy_picosat_set_prefix(PicoSATSolver *solver, const char *prefix,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }
  picosat_set_prefix(solver->solver, prefix);
}

void satgalaxy_picosat_set_verbosity(PicoSATSolver *solver, int new_verbosity_level,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }

  picosat_set_verbosity(solver->solver, new_verbosity_level);
}

void satgalaxy_picosat_set_plain(PicoSATSolver *solver, int new_plain_value,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }
  picosat_set_plain(solver->solver, new_plain_value);
}

void satgalaxy_picosat_set_global_default_phase(PicoSATSolver *solver, int phase,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }
  picosat_set_global_default_phase(solver->solver, phase);
}

void satgalaxy_picosat_set_default_phase_lit(PicoSATSolver *solver, int lit, int phase,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }
  picosat_set_default_phase_lit(solver->solver, lit, phase);
}

void satgalaxy_picosat_reset_phases(PicoSATSolver *solver,int* error)
{
  if (error)
  {
    *error=0;
  }
  picosat_reset_phases(solver->solver);
}

void satgalaxy_picosat_reset_scores(PicoSATSolver *solver,int* error)
{
  if (error)
  {
    *error=0;
  }
  picosat_reset_scores(solver->solver);
}

void satgalaxy_picosat_remove_learned(PicoSATSolver *solver, unsigned percentage,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }
  picosat_remove_learned(solver->solver, percentage);
}

void satgalaxy_picosat_set_more_important_lit(PicoSATSolver *solver, int lit,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }
  picosat_set_more_important_lit(solver->solver, lit);
}

void satgalaxy_picosat_set_less_important_lit(PicoSATSolver *solver, int lit,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }

  picosat_set_less_important_lit(solver->solver, lit);
}

void satgalaxy_picosat_message(PicoSATSolver *solver, int verbosity_level, const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  picosat_message(solver->solver, verbosity_level, fmt, args);
  va_end(args);
}

void satgalaxy_picosat_set_seed(PicoSATSolver *solver, unsigned random_number_generator_seed,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }
  picosat_set_seed(solver->solver, random_number_generator_seed);
}

int satgalaxy_picosat_enable_trace_generation(PicoSATSolver *solver,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }
  return picosat_enable_trace_generation(solver->solver);
}

void satgalaxy_picosat_set_incremental_rup_file(PicoSATSolver *solver, FILE *file, int m, int n,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }
  picosat_set_incremental_rup_file(solver->solver, file, m, n);
}

void satgalaxy_picosat_save_original_clauses(PicoSATSolver *solver,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }
  picosat_save_original_clauses(solver->solver);
}

int satgalaxy_picosat_inc_max_var(PicoSATSolver *solver,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }
  return picosat_inc_max_var(solver->solver);
}

int satgalaxy_picosat_push(PicoSATSolver *solver,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }
  return picosat_push(solver->solver);
}

int satgalaxy_picosat_failed_context(PicoSATSolver *solver, int lit,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }
  return picosat_failed_context(solver->solver, lit);
}

int satgalaxy_picosat_context(PicoSATSolver *solver,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }
  return picosat_context(solver->solver);
}

int satgalaxy_picosat_pop(PicoSATSolver *solver,int* error)
{
  if (check_ready(solver->solver,error))
  {
    return;
  }
  return picosat_pop(solver->solver);
}

void satgalaxy_picosat_simplify(PicoSATSolver *solver)
{
  picosat_simplify(solver->solver);
}

void satgalaxy_picosat_adjust(PicoSATSolver *solver, int max_idx)
{
  picosat_adjust(solver->solver, max_idx);
}

int satgalaxy_picosat_variables(PicoSATSolver *solver)
{
  return picosat_variables(solver->solver);
}

int satgalaxy_picosat_added_original_clauses(PicoSATSolver *solver)
{
  return picosat_added_original_clauses(solver->solver);
}

size_t satgalaxy_picosat_max_bytes_allocated(PicoSATSolver *solver)
{
  return picosat_max_bytes_allocated(solver->solver);
}

double satgalaxy_picosat_time_stamp(void)
{
  return picosat_time_stamp();
}

void satgalaxy_picosat_stats(PicoSATSolver *solver)
{
  picosat_stats(solver->solver);
}

unsigned long long satgalaxy_picosat_propagations(PicoSATSolver *solver)
{
  return picosat_propagations(solver->solver);
}

unsigned long long satgalaxy_picosat_decisions(PicoSATSolver *solver)
{
  return picosat_decisions(solver->solver);
}

unsigned long long satgalaxy_picosat_visits(PicoSATSolver *solver)
{
  return picosat_visits(solver->solver);
}

double satgalaxy_picosat_seconds(PicoSATSolver *solver)
{
  return picosat_seconds(solver->solver);
}

int satgalaxy_picosat_add(PicoSATSolver *solver, int lit)
{
  return picosat_add(solver->solver, lit);
}

int satgalaxy_picosat_add_arg(PicoSATSolver *solver, ...)
{
  va_list args;
  int res = picosat_add_arg(solver->solver, args);
  return res;
}

int satgalaxy_picosat_add_lits(PicoSATSolver *solver, int *lits)
{
  return picosat_add_lits(solver->solver, lits);
}

void satgalaxy_picosat_print(PicoSATSolver *solver, FILE *file)
{
  picosat_print(solver->solver, file);
}

void satgalaxy_picosat_assume(PicoSATSolver *solver, int lit)
{
  picosat_assume(solver->solver, lit);
}

void satgalaxy_picosat_add_ado_lit(PicoSATSolver *solver, int lit)
{
  picosat_add_ado_lit(solver->solver, lit);
}

int satgalaxy_picosat_sat(PicoSATSolver *solver, int decision_limit)
{
  return picosat_sat(solver->solver, decision_limit);
}

void satgalaxy_picosat_set_propagation_limit(PicoSATSolver *solver, unsigned long long limit)
{
  picosat_set_propagation_limit(solver->solver, limit);
}

int satgalaxy_picosat_res(PicoSATSolver *solver)
{
  return picosat_res(solver->solver);
}

int satgalaxy_picosat_deref(PicoSATSolver *solver, int lit)
{
  return picosat_deref(solver->solver, lit);
}

int satgalaxy_picosat_deref_toplevel(PicoSATSolver *solver, int lit)
{
  return picosat_deref_toplevel(solver->solver, lit);
}

int satgalaxy_picosat_deref_partial(PicoSATSolver *solver, int lit)
{
  return picosat_deref_partial(solver->solver, lit);
}

int satgalaxy_picosat_inconsistent(PicoSATSolver *solver)
{
  return picosat_inconsistent(solver->solver);
}

int satgalaxy_picosat_failed_assumption(PicoSATSolver *solver, int lit)
{
  return picosat_failed_assumption(solver->solver, lit);
}

const int *satgalaxy_picosat_failed_assumptions(PicoSATSolver *solver)
{
  return picosat_failed_assumptions(solver->solver);
}

const int *satgalaxy_picosat_mus_assumptions(PicoSATSolver *solver, void *state,
                                             void (*callback)(void *, const int *), int fix)
{
  return picosat_mus_assumptions(solver->solver, state, callback, fix);
}

const int *satgalaxy_picosat_maximal_satisfiable_subset_of_assumptions(PicoSATSolver *solver)
{
  return picosat_maximal_satisfiable_subset_of_assumptions(solver->solver);
}

const int *satgalaxy_picosat_next_maximal_satisfiable_subset_of_assumptions(PicoSATSolver *solver)
{
  return picosat_next_maximal_satisfiable_subset_of_assumptions(solver->solver);
}

const int *satgalaxy_picosat_next_minimal_correcting_subset_of_assumptions(PicoSATSolver *solver)
{
  return picosat_next_minimal_correcting_subset_of_assumptions(solver->solver);
}

const int *satgalaxy_picosat_humus(PicoSATSolver *solver,
                                   void (*callback)(void *, int nmcs, int nhumus),
                                   void *state)
{
  return picosat_humus(solver->solver, callback, state);
}

int satgalaxy_picosat_changed(PicoSATSolver *solver)
{
  return picosat_changed(solver->solver);
}

int satgalaxy_picosat_coreclause(PicoSATSolver *solver, int i)
{
  return picosat_coreclause(solver->solver, i);
}

int satgalaxy_picosat_corelit(PicoSATSolver *solver, int lit)
{
  return picosat_corelit(solver->solver, lit);
}

void satgalaxy_picosat_write_clausal_core(PicoSATSolver *solver, FILE *core_file)
{
  picosat_write_clausal_core(solver->solver, core_file);
}

void satgalaxy_picosat_write_compact_trace(PicoSATSolver *solver, FILE *trace_file)
{
  picosat_write_compact_trace(solver->solver, trace_file);
}

void satgalaxy_picosat_write_extended_trace(PicoSATSolver *solver, FILE *trace_file)
{
  picosat_write_extended_trace(solver->solver, trace_file);
}

void satgalaxy_picosat_write_rup_trace(PicoSATSolver *solver, FILE *trace_file)
{
  picosat_write_rup_trace(solver->solver, trace_file);
}

int satgalaxy_picosat_usedlit(PicoSATSolver *solver, int lit)
{
  return picosat_usedlit(solver->solver, lit);
}