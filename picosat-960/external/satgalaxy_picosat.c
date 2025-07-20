
#include "satgalaxy_picosat.h"
#ifndef ERRORJMP
#define ERRORJMP
#endif
#include "picosat.h"
#include <stdarg.h>

#define CALL_PICOSAT(s,func, ...) \
  do { \
    jmp_buf *buf=picosat_jmp_buf(s->solver);\
    int code =  setjmp(*buf); \
    s->error=code; \
    if (code) { \
      return; \
    }else{ \
      func(s->solver,__VA_ARGS__);\
    }\
  } while (0)

  #define CALL_PICOSAT_ZORE(s,func) \
  do { \
    jmp_buf *buf=picosat_jmp_buf(s->solver);\
    int code =  setjmp(*buf); \
    s->error=code; \
    if (code) { \
      return; \
    }else{ \
      func(s->solver);\
    }\
  } while (0)

#define CALL_PICOSAT_RETURN(s,rv,func, ...) \
  do { \
    jmp_buf *buf=picosat_jmp_buf(s->solver);\
    int code =  setjmp(*buf); \
    s->error=code; \
    if (code) { \
      return rv; \
    }else{ \
      func(s->solver,__VA_ARGS__);\
    }\
  } while (0)

  #define CALL_PICOSAT_ZERO_RETURN(s,rv,func) \
  do { \
    jmp_buf *buf=picosat_jmp_buf(s->solver);\
    int code =  setjmp(*buf); \
    s->error=code; \
    if (code) { \
      return rv; \
    }else{ \
      return func(s->solver);\
    }\
  } while (0)

extern void picosat_enter (PicoSAT *);
extern void picosat_leave (PicoSAT *);

struct PicoSATSolver
{
  /* data */
  PicoSAT *solver;
  int error;
};


const char *picosat_version (void){
  return "PICOSAT_VERSION";
}




PicoSATSolver *picosat_s_init(void) {
  PicoSATSolver *solver = malloc(sizeof(PicoSATSolver));
  solver->solver = (PicoSAT *)picosat_init();
  solver->error = 0;
  return solver;
}

PicoSATSolver *picosat_s_minit(void *state,
                                       picosat_s_malloc m,
                                       picosat_s_realloc r,
                                       picosat_s_free f) {
  PicoSATSolver *solver = malloc(sizeof(PicoSATSolver));
  solver->solver = (PicoSAT *)picosat_minit(state, m, r, f);
  solver->error = 0;
  return solver;
}

void picosat_s_reset(PicoSATSolver *solver) {
  CALL_PICOSAT_ZORE(solver,picosat_reset);
}
void picosat_s_set_output(PicoSATSolver *solver, FILE *file) {
  CALL_PICOSAT(solver,picosat_set_output, file);
}

void picosat_s_enter (PicoSATSolver *solver){
  CALL_PICOSAT_ZORE(solver,picosat_enter);
}
void picosat_s_leave (PicoSATSolver *solver){
  CALL_PICOSAT_ZORE(solver,picosat_leave);
}

void picosat_s_measure_all_calls(PicoSATSolver *solver) {
  CALL_PICOSAT_ZORE(solver,picosat_measure_all_calls);
}

void picosat_s_set_prefix(PicoSATSolver *solver, const char *prefix) {
  CALL_PICOSAT(solver,picosat_set_prefix,prefix);
}

void picosat_s_set_verbosity(PicoSATSolver *solver, int new_verbosity_level) {
  CALL_PICOSAT(solver,picosat_set_verbosity,new_verbosity_level);
}

void picosat_s_set_plain(PicoSATSolver *solver, int new_plain_value) {
  CALL_PICOSAT(solver,picosat_set_plain,new_plain_value);
}

void picosat_s_set_global_default_phase(PicoSATSolver *solver, int phase) {
  CALL_PICOSAT(solver,picosat_set_global_default_phase,phase);
}

void picosat_s_set_default_phase_lit(PicoSATSolver *solver, int lit, int phase) {
  CALL_PICOSAT(solver,picosat_set_default_phase_lit,lit,phase);
}

void picosat_s_reset_phases(PicoSATSolver *solver) {
  CALL_PICOSAT_ZORE(solver,picosat_reset_phases);
}

void picosat_s_reset_scores(PicoSATSolver *solver) {
  CALL_PICOSAT_ZORE(solver,picosat_reset_scores);
}

void picosat_s_remove_learned(PicoSATSolver *solver, unsigned percentage) {
  CALL_PICOSAT(solver,picosat_remove_learned,percentage);
}

void picosat_s_set_more_important_lit(PicoSATSolver *solver, int lit) {
  CALL_PICOSAT(solver,picosat_set_more_important_lit,lit);
}

void picosat_s_set_less_important_lit(PicoSATSolver *solver, int lit) {
  CALL_PICOSAT(solver,picosat_set_less_important_lit,lit);
}

void picosat_s_message(PicoSATSolver *solver, int verbosity_level, const char *fmt, ...) {
  va_list args;
  CALL_PICOSAT(solver,picosat_message,verbosity_level,fmt,args);
}

void picosat_s_set_seed(PicoSATSolver *solver, unsigned random_number_generator_seed) {
  CALL_PICOSAT(solver,picosat_set_seed,random_number_generator_seed);
}

int picosat_s_enable_trace_generation(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_enable_trace_generation);
}

void picosat_s_set_incremental_rup_file(PicoSATSolver *solver, FILE *file, int m, int n) {
  CALL_PICOSAT(solver,picosat_set_incremental_rup_file,file,m,n);
}

void picosat_s_save_original_clauses(PicoSATSolver *solver) {
  CALL_PICOSAT_ZORE(solver,picosat_save_original_clauses);
}

int picosat_s_inc_max_var(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_inc_max_var);
}

int picosat_s_push(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_push);
}

int picosat_s_failed_context(PicoSATSolver *solver, int lit) {
  CALL_PICOSAT_RETURN(solver,0,picosat_failed_context,lit);
}

int picosat_s_context(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_context);
}

int picosat_s_pop(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_pop);
}

void picosat_s_simplify(PicoSATSolver *solver) {
  CALL_PICOSAT_ZORE(solver,picosat_simplify);
}

void picosat_s_adjust(PicoSATSolver *solver, int max_idx) {
  CALL_PICOSAT(solver,picosat_adjust,max_idx);
}

int picosat_s_variables(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_variables);
}

int picosat_s_added_original_clauses(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_added_original_clauses);
}

size_t picosat_s_max_bytes_allocated(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_max_bytes_allocated);
}

double picosat_s_time_stamp(void) {
  return picosat_s_time_stamp();
}

void picosat_s_stats(PicoSATSolver *solver) {
  CALL_PICOSAT_ZORE(solver,picosat_stats);
}

unsigned long long picosat_s_propagations(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_propagations);
}

unsigned long long picosat_s_decisions(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_decisions);
}

unsigned long long picosat_s_visits(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_visits);
}

double picosat_s_seconds(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_seconds);
}

int picosat_s_add(PicoSATSolver *solver, int lit) {
  CALL_PICOSAT_RETURN(solver,0,picosat_add,lit);
}

int picosat_s_add_arg(PicoSATSolver *solver, ...) {
  va_list args;
  CALL_PICOSAT_RETURN(solver,0,picosat_add_arg,args);
}
int _picosat_s_add_lits(PicoSAT *solver,const int *lits, size_t len) {
  int i;
  for (i = 0; i < len; i++) {
    picosat_add(solver, lits[i]);
  }
  return picosat_add(solver, 0); // Add a zero terminator to the clause
}
int picosat_s_add_lits(PicoSATSolver *solver,const int *lits, size_t len) {

  CALL_PICOSAT_RETURN(solver,0,_picosat_s_add_lits,lits,len);
}

void picosat_s_print(PicoSATSolver *solver, FILE *file) {
  CALL_PICOSAT(solver,picosat_print,file);
}

void picosat_s_assume(PicoSATSolver *solver, int lit) {
  CALL_PICOSAT(solver,picosat_assume,lit);
}

void picosat_s_add_ado_lit(PicoSATSolver *solver, int lit) {
  CALL_PICOSAT(solver,picosat_add_ado_lit,lit);
}

int picosat_s_sat(PicoSATSolver *solver, int decision_limit) {
  CALL_PICOSAT_RETURN(solver,0,picosat_sat,decision_limit);
}

void picosat_s_set_propagation_limit(PicoSATSolver *solver, unsigned long long limit) {
  CALL_PICOSAT(solver,picosat_set_propagation_limit,limit);
}

int picosat_s_res(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_res);
}

int picosat_s_deref(PicoSATSolver *solver, int lit) {
  CALL_PICOSAT_RETURN(solver,0,picosat_deref,lit);
}

int picosat_s_deref_toplevel(PicoSATSolver *solver, int lit) {
  CALL_PICOSAT_RETURN(solver,0,picosat_deref_toplevel,lit);
}

int picosat_s_deref_partial(PicoSATSolver *solver, int lit) {
  CALL_PICOSAT_RETURN(solver,0,picosat_deref_partial,lit);
}

int picosat_s_inconsistent(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_inconsistent);
}

int picosat_s_failed_assumption(PicoSATSolver *solver, int lit) {
  CALL_PICOSAT_RETURN(solver,0,picosat_failed_assumption,lit);
}

const int *picosat_s_failed_assumptions(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_failed_assumptions);
}

const int *picosat_s_mus_assumptions(PicoSATSolver *solver, void *state,
                                             void (*callback)(void *, const int *), int fix) {
  CALL_PICOSAT_RETURN(solver,0,picosat_mus_assumptions,state,callback,fix);
}

const int *picosat_s_maximal_satisfiable_subset_of_assumptions(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_maximal_satisfiable_subset_of_assumptions);
}

const int *picosat_s_next_maximal_satisfiable_subset_of_assumptions(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_next_maximal_satisfiable_subset_of_assumptions);
}

const int *picosat_s_next_minimal_correcting_subset_of_assumptions(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_next_minimal_correcting_subset_of_assumptions);
}

const int *picosat_s_humus(PicoSATSolver *solver,
                                   void (*callback)(void *, int nmcs, int nhumus),
                                   void *state) {
  CALL_PICOSAT_RETURN(solver,0,picosat_humus,callback,state);
}

int picosat_s_changed(PicoSATSolver *solver) {
  CALL_PICOSAT_ZERO_RETURN(solver,0,picosat_changed);
}

int picosat_s_coreclause(PicoSATSolver *solver, int i) {
  CALL_PICOSAT_RETURN(solver,0,picosat_coreclause,i);
}

int picosat_s_corelit(PicoSATSolver *solver, int lit) {
  CALL_PICOSAT_RETURN(solver,0,picosat_corelit,lit);
}

void picosat_s_write_clausal_core(PicoSATSolver *solver, FILE *core_file) {
  CALL_PICOSAT(solver,picosat_write_clausal_core,core_file);
}

void picosat_s_write_compact_trace(PicoSATSolver *solver, FILE *trace_file) {
  CALL_PICOSAT(solver,picosat_write_compact_trace,trace_file);
}

void picosat_s_write_extended_trace(PicoSATSolver *solver, FILE *trace_file) {
  CALL_PICOSAT(solver,picosat_write_extended_trace,trace_file);
}

void picosat_s_write_rup_trace(PicoSATSolver *solver, FILE *trace_file) {
  CALL_PICOSAT(solver,picosat_write_rup_trace,trace_file);
}

int picosat_s_usedlit(PicoSATSolver *solver, int lit) {
  CALL_PICOSAT_RETURN(solver,0,picosat_usedlit,lit);
}

int picosat_s_error(PicoSATSolver *solver){
  return solver->error;
}
const char* picosat_s_errmsg(int code){
  return picosat_error_message(code);
}