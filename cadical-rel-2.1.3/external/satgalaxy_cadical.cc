
#include "satgalaxy_cadical.h"
#include "cadical.hpp"
#include "stdlib.h"
#include <cstring>
#include <limits.h>
#include <vector>

struct SatgalaxyTerminator : CaDiCaL::Terminator {
  void *state;
  int (*function) (void *);
  ~SatgalaxyTerminator () {}
  bool terminate () {
    if (!function)
      return false;
    return function (state);
  }
};

struct SatgalaxyLearner : CaDiCaL::Learner {
  void *state;
  int max_length;
  int *begin_clause, *end_clause, *capacity_clause;
  void (*function) (void *, int *);
  ~SatgalaxyLearner () {}
  bool learning (int size) {
    if (!function)
      return false;
    return size <= max_length;
  }

  void learn (int lit) {
    if (end_clause == capacity_clause) {
      size_t count = end_clause - begin_clause;
      size_t size = count ? 2 * count : 1;
      begin_clause = (int *) realloc (begin_clause, size * sizeof (int));
      end_clause = begin_clause + count;
      capacity_clause = begin_clause + size;
    }
    *end_clause++ = lit;
    if (lit)
      return;
    function (state, begin_clause);
    end_clause = begin_clause;
  }
};

SatgalaxyTerminator *terminator = new SatgalaxyTerminator ();
SatgalaxyLearner *learner = new SatgalaxyLearner ();
int last_error = 0;
inline int require_valid_state (CaDiCaL::Solver *solver) {
  if (solver->status () & CaDiCaL::VALID) {
    return 0;
  } else {
    return 100;
  }
}

inline int require_ready_state (CaDiCaL::Solver *solver) {
  int ret = require_valid_state (solver);
  if (ret) {
    return ret;
  }

  if (solver->status () != CaDiCaL::ADDING) {
    return 0;
  } else {
    return 101;
  }
}

inline int require_valid_or_solving_state (CaDiCaL::Solver *solver) {
  int ret = require_ready_state (solver);
  if (ret) {
    return ret;
  }

  if (solver->status () & (CaDiCaL::VALID | CaDiCaL::SOLVING)) {
    return 0;
  } else {
    return 102;
  }
}

inline int require_valid_lit (int lit) {
  if (lit && lit != INT_MIN) {
    return 0;
  }
  return 103;
}

inline int require_satisfied_state (CaDiCaL::Solver *solver) {
  int ret = require_valid_state (solver);
  if (ret) {
    return ret;
  }

  if (solver->status () != CaDiCaL::SATISFIED) {
    return 0;
  } else {
    return 104;
  }
}

inline int require_unsatisfied_state (CaDiCaL::Solver *solver) {
  int ret = require_valid_state (solver);
  if (ret) {
    return ret;
  }

  if (solver->status () != CaDiCaL::UNSATISFIED) {
    return 0;
  } else {
    return 105;
  }
}

inline int require_configuring_state (CaDiCaL::Solver *solver) {
  int ret = require_valid_state (solver);
  if (ret) {
    return ret;
  }

  if (solver->status () != CaDiCaL::CONFIGURING) {
    return 0;
  } else {
    return 106;
  }
}
const char *cadical_error_message(int code) {
  switch (code) {
  case 100:
    return "solver in invalid state";
  case 101:
    return "clause incomplete (terminating zero not added)";
  case 102:
    return "solver neither in valid nor solving state";
  case 103:
    return "invalid literal";
  case 104:
    return "solver is not in satisfied state";
  case 105:
    return "solver is not in unsatisfied state";
  case 106:
    return "solver is not in configuring state";
  case 202:
    return "invalid arena type";
  case 203:
    return "invalid block maximum clause size";
  case 204:
    return "invalid block minimum clause size";
  case 205:
    return "invalid block occurrence limit";
  case 206:
    return "invalid bump reason depth";
  case 207:
    return "invalid proof checking mode";
  case 208:
    return "invalid chronological backtracking mode";
  case 209:
    return "invalid chronological level limit";
  case 210:
    return "invalid compacting interval";
  case 211:
    return "invalid compact limit";
  case 212:
    return "invalid compact minimum";
  case 213:
    return "invalid condition interval";
  case 214:
    return "invalid condition maximum efficiency";
  case 215:
    return "invalid condition maximum ratio";
  case 216:
    return "invalid condition minimum efficiency";
  case 217:
    return "invalid condition relative efficiency";
  case 218:
    return "invalid cover maximum clause size";
  case 219:
    return "invalid cover maximum efficiency";
  case 220:
    return "invalid cover minimum clause size";
  case 221:
    return "invalid cover minimum efficiency";
  case 222:
    return "invalid cover relative efficiency";
  case 223:
    return "invalid decompose rounds";
  case 224:
    return "invalid eager subsume limit";
  case 225:
    return "invalid elimination maximum efficiency";
  case 226:
    return "invalid elimination bound maximum";
  case 227:
    return "invalid elimination bound minimum";
  case 228:
    return "invalid elimination clause size limit";
  case 229:
    return "invalid elimination minimum efficiency";
  case 230:
    return "invalid elimination interval";
  case 231:
    return "invalid elimination occurrence limit";
  case 232:
    return "invalid elimination product weight";
  case 233:
    return "invalid elimination relative efficiency";
  case 234:
    return "invalid elimination rounds";
  case 235:
    return "invalid elimination sum weight";
  case 236:
    return "invalid XOR size limit";
  case 237:
    return "invalid EMA glue fast value";
  case 238:
    return "invalid EMA glue slow value";
  case 239:
    return "invalid EMA jump level";
  case 240:
    return "invalid EMA back-track level";
  case 241:
    return "invalid EMA learned clause size";
  case 242:
    return "invalid EMA trail fast value";
  case 243:
    return "invalid EMA trail slow value";
  case 244:
    return "invalid flush factor";
  case 245:
    return "invalid flush interval";
  case 246:
    return "invalid FRAT proof format";
  case 247:
    return "invalid instantiate clause size limit";
  case 248:
    return "invalid instantiate occurrence limit";
  case 249:
    return "invalid minimize depth";
  case 250:
    return "invalid probing interval";
  case 251:
    return "invalid probing maximum efficiency";
  case 252:
    return "invalid probing minimum efficiency";
  case 253:
    return "invalid probing relative efficiency";
  case 254:
    return "invalid probing rounds";
  case 255:
    return "invalid profiling level";
  case 256:
    return "invalid radix sort limit";
  case 257:
    return "invalid reduce interval";
  case 258:
    return "invalid reduce target";
  case 259:
    return "invalid reduce tier1 glue";
  case 260:
    return "invalid reduce tier2 glue";
  case 261:
    return "invalid reluctant doubling period";
  case 262:
    return "invalid reluctant maximum period";
  case 263:
    return "invalid rephase interval";
  case 264:
    return "invalid restart interval";
  case 265:
    return "invalid restart margin";
  case 266:
    return "invalid restore all mode";
  case 267:
    return "invalid score factor";
  case 268:
    return "invalid random seed";
  case 269:
    return "invalid shrink mode";
  case 270:
    return "invalid stabilize factor";
  case 271:
    return "invalid stabilize interval";
  case 272:
    return "invalid stabilize maximum interval";
  case 273:
    return "invalid subsume binary limit";
  case 274:
    return "invalid subsume clause size limit";
  case 275:
    return "invalid subsume interval";
  case 276:
    return "invalid subsume maximum efficiency";
  case 277:
    return "invalid subsume minimum efficiency";
  case 278:
    return "invalid subsume occurrence limit";
  case 279:
    return "invalid subsume relative efficiency";
  case 280:
    return "invalid target value";
  case 281:
    return "invalid terminate interval";
  case 282:
    return "invalid ternary maximum add";
  case 283:
    return "invalid ternary maximum efficiency";
  case 284:
    return "invalid ternary minimum efficiency";
  case 285:
    return "invalid ternary occurrence limit";
  case 286:
    return "invalid ternary relative efficiency";
  case 287:
    return "invalid ternary rounds";
  case 288:
    return "invalid transitive reduction maximum efficiency";
  case 289:
    return "invalid transitive reduction minimum efficiency";
  case 290:
    return "invalid transitive reduction relative efficiency";
  case 291:
    return "invalid verbose level";
  case 292:
    return "invalid veripb level";
  case 293:
    return "invalid vivify maximum efficiency";
  case 294:
    return "invalid vivify minimum efficiency";
  case 295:
    return "invalid vivify once mode";
  case 296:
    return "invalid vivify redundant efficiency";
  case 297:
    return "invalid vivify relative efficiency";
  case 298:
    return "invalid walk maximum efficiency";
  case 299:
    return "invalid walk minimum efficiency";
  case 300:
    return "invalid walk relative efficiency";
  default:
    return "unknown error code";
  }
}
CaDiCaLSolver *cadical_new_solver () {
  return (CaDiCaLSolver *) new CaDiCaL::Solver ();
}
void cadical_destroy (const CaDiCaLSolver *s) {
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  delete solver;
}

int cadical_add_clause (const CaDiCaLSolver *s, const int ps[],
                        unsigned long length) {
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  int ret = require_valid_state (solver);
  if (ret) {
    last_error = ret;
    return ret;
  }
  solver->clause (ps, length);
  return 0;
}
int cadical_add_empty_clause (const CaDiCaLSolver *s) {
  return cadical_add (s, 0);
}

int cadical_add (const CaDiCaLSolver *s, int lit) {
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  int ret = require_valid_state (solver);
  if (ret) {
    last_error = ret;
    return ret;
  }
  ret = require_valid_lit (lit);
  if (ret) {
    last_error = ret;
    return ret;
  }
  solver->add (lit);
  return 0;
}

int cadical_assume (const CaDiCaLSolver *s, int lit) {
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  int ret = require_valid_state (solver);
  if (ret) {
    last_error = ret;
    return ret;
  }
  ret = require_valid_lit (lit);
  if (ret) {
    last_error = ret;
    return ret;
  }
  solver->assume (lit);
  return 0;
}
int cadical_solve (const CaDiCaLSolver *s) {
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  int ret = require_ready_state (solver);
  if (ret) {
    last_error = ret;
    return 0;
  }
  return solver->solve ();
}
int cadical_val (const CaDiCaLSolver *s, int lit) {
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  int ret = require_valid_state (solver);
  if (ret) {
    last_error = ret;
    return 0;
  }
  ret = require_valid_lit (lit);
  if (ret) {
    last_error = ret;
    return 0;
  }
  ret = require_satisfied_state (solver);
  if (ret) {
    last_error = ret;
    return 0;
  }
  return solver->val (lit);
}
int cadical_failed (const CaDiCaLSolver *s, int lit) {
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  last_error = require_valid_state (solver);
  if (last_error) {
    return last_error;
  }
  last_error = require_valid_lit (lit);
  if (last_error) {
    return last_error;
  }
  last_error = require_satisfied_state (solver);
  if (last_error) {
    return last_error;
  }
  return solver->failed (lit) ? 1 : 0;
}

int cadical_set_terminate (const CaDiCaLSolver *s, void *state,
                           int (*terminate) (void *state)) {
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  last_error = require_valid_state (solver);
  if (last_error) {
    return last_error;
  }
  if (terminate) {
    terminator->function = terminate;
    terminator->state = state;
    solver->connect_terminator (terminator);
  } else
    solver->disconnect_terminator ();
  return 0;
}

int cadical_set_learn (const CaDiCaLSolver *s, void *state, int max_length,
                       void (*learn) (void *state, int *clause)) {
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  last_error = require_valid_state (solver);
  if (last_error) {
    return last_error;
  }
  learner->state = state;
  learner->max_length = max_length;
  learner->function = learn;
  if (learn)
    solver->connect_learner (learner);
  else
    solver->disconnect_learner ();
}

/*------------------------------------------------------------------------*/

// Non-IPASIR conformant 'C' functions.

int cadical_constrain (const CaDiCaLSolver *s, int lit) {
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  last_error = require_valid_state (solver);
  if (last_error) {
    return last_error;
  }
  if (lit) {
    last_error = require_valid_lit (lit);
    if (last_error) {
      return last_error;
    }
  }

  solver->constrain (lit);
  return 0;
}
int cadical_constraint_failed (const CaDiCaLSolver *s) {
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  last_error = require_valid_state (solver);
  if (last_error) {
    return last_error;
  }
  last_error = require_unsatisfied_state (solver);
  if (last_error) {
    return last_error;
  }
  return solver->constraint_failed () ? 1 : 0;
}
int cadical_set_option (const CaDiCaLSolver *s, const char *name, int val) {
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  last_error = require_valid_state (solver);
  if (last_error) {
    return 0;
  }
  if (strcmp (name, "log") && strcmp (name, "quiet") &&
      strcmp (name, "report") && strcmp (name, "verbose")) {
    last_error = require_configuring_state (solver);
    if (last_error) {
      return 0;
    }
  }
  return solver->set (name, val);
}
int cadical_set_opt_arena (const CaDiCaLSolver *s, int arena) {
  return cadical_set_option (s, "arena", arena);
}
int cadical_limit (const CaDiCaLSolver *s, const char *name, int limit) {
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  last_error = require_valid_state (solver);
  if (last_error) {
    return 0;
  }
  return solver->limit (name, limit);
}
int cadical_get_option (const CaDiCaLSolver *s, const char *name) {
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  last_error = require_valid_or_solving_state (solver);
  if (last_error) {
    return 0;
  }
  return solver->get (name);
}
int cadical_print_statistics (const CaDiCaLSolver *s) {
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  last_error = require_valid_or_solving_state (solver);
  if (last_error) {
    return last_error;
  }
   solver->statistics ();
   return 0;
}
int64_t cadical_active (const CaDiCaLSolver *s){
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  last_error = require_valid_or_solving_state (solver);
  if (last_error) {
    return 0;
  }
   return solver->active ();
}
int64_t cadical_irredundant (const CaDiCaLSolver *s){
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  last_error = require_valid_state (solver);
  if (last_error) {
    return 0;
  }
  return solver->irredundant ();
}
int cadical_fixed (const CaDiCaLSolver *s, int lit){
    CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;

    last_error = require_valid_state (solver);
    if (last_error) {
      return 0;
    }
    last_error = require_valid_lit (lit);
    if (last_error) {
      return 0;
    }
    return solver->fixed (lit);

}
// int cadical_trace_proof (const CaDiCaLSolver *, FILE *, const char *);
// void cadical_close_proof (const CaDiCaLSolver *);
void cadical_conclude (const CaDiCaLSolver *s){
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  solver->conclude ();
}
void cadical_terminate (const CaDiCaLSolver *s){
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  solver->terminate ();
}
void cadical_freeze (const CaDiCaLSolver *s, int lit){
    CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
    solver->freeze (lit);
}
int cadical_frozen (const CaDiCaLSolver *s, int lit){
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
}
void cadical_melt (const CaDiCaLSolver *s, int lit){
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  solver->melt (lit);
}
int cadical_simplify (const CaDiCaLSolver *s){
  CaDiCaL::Solver *solver = (CaDiCaL::Solver *) s;
  return solver->simplify ();
}

int cadical_set_opt_arena(const CaDiCaLSolver *s, int arena) {
  last_error = 0;
  return cadical_set_option(s, "arena", arena);
}

int cadical_set_opt_arenacompact(const CaDiCaLSolver *s, int arenacompact) {
  last_error = 0;
  return cadical_set_option(s, "arenacompact", arenacompact);
}

int cadical_set_opt_arenasort(const CaDiCaLSolver *s, int arenasort) {
  last_error = 0;
  return cadical_set_option(s, "arenasort", arenasort);
}

int cadical_set_opt_arenatype(const CaDiCaLSolver *s, int arenatype) {
  if (arenatype < 1 || arenatype > 3) {
    last_error = 202;
    return 202;
  }
  last_error = 0;
  return cadical_set_option(s, "arenatype", arenatype);
}

int cadical_set_opt_binary(const CaDiCaLSolver *s, int binary) {
  last_error = 0;
  return cadical_set_option(s, "binary", binary);
}

int cadical_set_opt_block(const CaDiCaLSolver *s, int block) {
  last_error = 0;
  return cadical_set_option(s, "block", block);
}

int cadical_set_opt_blockmaxclslim(const CaDiCaLSolver *s, int blockmaxclslim) {
  if (blockmaxclslim < 1 || blockmaxclslim > 2000000000) {
    last_error = 203;
    return 203;
  }
  last_error = 0;
  return cadical_set_option(s, "blockmaxclslim", blockmaxclslim);
}

int cadical_set_opt_blockminclslim(const CaDiCaLSolver *s, int blockminclslim) {
  if (blockminclslim < 2 || blockminclslim > 2000000000) {
    last_error = 204;
    return 204;
  }
  last_error = 0;
  return cadical_set_option(s, "blockminclslim", blockminclslim);
}

int cadical_set_opt_blockocclim(const CaDiCaLSolver *s, int blockocclim) {
  if (blockocclim < 1 || blockocclim > 2000000000) {
    last_error = 205;
    return 205;
  }
  last_error = 0;
  return cadical_set_option(s, "blockocclim", blockocclim);
}

int cadical_set_opt_bump(const CaDiCaLSolver *s, int bump) {
  last_error = 0;
  return cadical_set_option(s, "bump", bump);
}

int cadical_set_opt_bumpreason(const CaDiCaLSolver *s, int bumpreason) {
  last_error = 0;
  return cadical_set_option(s, "bumpreason", bumpreason);
}

int cadical_set_opt_bumpreasondepth(const CaDiCaLSolver *s, int bumpreasondepth) {
  if (bumpreasondepth < 1 || bumpreasondepth > 3) {
    last_error = 206;
    return 206;
  }
  last_error = 0;
  return cadical_set_option(s, "bumpreasondepth", bumpreasondepth);
}

int cadical_set_opt_check(const CaDiCaLSolver *s, int check) {
  last_error = 0;
  return cadical_set_option(s, "check", check);
}

int cadical_set_opt_checkassumptions(const CaDiCaLSolver *s, int checkassumptions) {
  last_error = 0;
  return cadical_set_option(s, "checkassumptions", checkassumptions);
}

int cadical_set_opt_checkconstraint(const CaDiCaLSolver *s, int checkconstraint) {
  last_error = 0;
  return cadical_set_option(s, "checkconstraint", checkconstraint);
}

int cadical_set_opt_checkfailed(const CaDiCaLSolver *s, int checkfailed) {
  last_error = 0;
  return cadical_set_option(s, "checkfailed", checkfailed);
}

int cadical_set_opt_checkfrozen(const CaDiCaLSolver *s, int checkfrozen) {
  last_error = 0;
  return cadical_set_option(s, "checkfrozen", checkfrozen);
}

int cadical_set_opt_checkproof(const CaDiCaLSolver *s, int checkproof) {
  if (checkproof < 0 || checkproof > 3) {
    last_error = 207;
    return 207;
  }
  last_error = 0;
  return cadical_set_option(s, "checkproof", checkproof);
}

int cadical_set_opt_checkwitness(const CaDiCaLSolver *s, int checkwitness) {
  last_error = 0;
  return cadical_set_option(s, "checkwitness", checkwitness);
}

int cadical_set_opt_chrono(const CaDiCaLSolver *s, int chrono) {
  if (chrono < 0 || chrono > 2) {
    last_error = 208;
    return 208;
  }
  last_error = 0;
  return cadical_set_option(s, "chrono", chrono);
}

int cadical_set_opt_chronoalways(const CaDiCaLSolver *s, int chronoalways) {
  last_error = 0;
  return cadical_set_option(s, "chronoalways", chronoalways);
}

int cadical_set_opt_chronolevelim(const CaDiCaLSolver *s, int chronolevelim) {
  if (chronolevelim < 0 || chronolevelim > 2000000000) {
    last_error = 209;
    return 209;
  }
  last_error = 0;
  return cadical_set_option(s, "chronolevelim", chronolevelim);
}

int cadical_set_opt_chronoreusetrail(const CaDiCaLSolver *s, int chronoreusetrail) {
  last_error = 0;
  return cadical_set_option(s, "chronoreusetrail", chronoreusetrail);
}

int cadical_set_opt_compact(const CaDiCaLSolver *s, int compact) {
  last_error = 0;
  return cadical_set_option(s, "compact", compact);
}

int cadical_set_opt_compactint(const CaDiCaLSolver *s, int compactint) {
  if (compactint < 1 || compactint > 2000000000) {
    last_error = 210;
    return 210;
  }
  last_error = 0;
  return cadical_set_option(s, "compactint", compactint);
}

int cadical_set_opt_compactlim(const CaDiCaLSolver *s, int compactlim) {
  if (compactlim < 0 || compactlim > 1000) {
    last_error = 211;
    return 211;
  }
  last_error = 0;
  return cadical_set_option(s, "compactlim", compactlim);
}

int cadical_set_opt_compactmin(const CaDiCaLSolver *s, int compactmin) {
  if (compactmin < 1 || compactmin > 2000000000) {
    last_error = 212;
    return 212;
  }
  last_error = 0;
  return cadical_set_option(s, "compactmin", compactmin);
}

int cadical_set_opt_condition(const CaDiCaLSolver *s, int condition) {
  last_error = 0;
  return cadical_set_option(s, "condition", condition);
}

int cadical_set_opt_conditionint(const CaDiCaLSolver *s, int conditionint) {
  if (conditionint < 1 || conditionint > 2000000000) {
    last_error = 213;
    return 213;
  }
  last_error = 0;
  return cadical_set_option(s, "conditionint", conditionint);
}

int cadical_set_opt_conditionmaxeff(const CaDiCaLSolver *s, int conditionmaxeff) {
  if (conditionmaxeff < 0 || conditionmaxeff > 2000000000) {
    last_error = 214;
    return 214;
  }
  last_error = 0;
  return cadical_set_option(s, "conditionmaxeff", conditionmaxeff);
}

int cadical_set_opt_conditionmaxrat(const CaDiCaLSolver *s, int conditionmaxrat) {
  if (conditionmaxrat < 1 || conditionmaxrat > 2000000000) {
    last_error = 215;
    return 215;
  }
  last_error = 0;
  return cadical_set_option(s, "conditionmaxrat", conditionmaxrat);
}

int cadical_set_opt_conditionmineff(const CaDiCaLSolver *s, int conditionmineff) {
  if (conditionmineff < 0 || conditionmineff > 2000000000) {
    last_error = 216;
    return 216;
  }
  last_error = 0;
  return cadical_set_option(s, "conditionmineff", conditionmineff);
}

int cadical_set_opt_conditionreleff(const CaDiCaLSolver *s, int conditionreleff) {
  if (conditionreleff < 1 || conditionreleff > 100000) {
    last_error = 217;
    return 217;
  }
  last_error = 0;
  return cadical_set_option(s, "conditionreleff", conditionreleff);
}

int cadical_set_opt_cover(const CaDiCaLSolver *s, int cover) {
  last_error = 0;
  return cadical_set_option(s, "cover", cover);
}

int cadical_set_opt_covermaxclslim(const CaDiCaLSolver *s, int covermaxclslim) {
  if (covermaxclslim < 1 || covermaxclslim > 2000000000) {
    last_error = 218;
    return 218;
  }
  last_error = 0;
  return cadical_set_option(s, "covermaxclslim", covermaxclslim);
}

int cadical_set_opt_covermaxeff(const CaDiCaLSolver *s, int covermaxeff) {
  if (covermaxeff < 0 || covermaxeff > 2000000000) {
    last_error = 219;
    return 219;
  }
  last_error = 0;
  return cadical_set_option(s, "covermaxeff", covermaxeff);
}

int cadical_set_opt_coverminclslim(const CaDiCaLSolver *s, int coverminclslim) {
  if (coverminclslim < 2 || coverminclslim > 2000000000) {
    last_error = 220;
    return 220;
  }
  last_error = 0;
  return cadical_set_option(s, "coverminclslim", coverminclslim);
}

int cadical_set_opt_covermineff(const CaDiCaLSolver *s, int covermineff) {
  if (covermineff < 0 || covermineff > 2000000000) {
    last_error = 221;
    return 221;
  }
  last_error = 0;
  return cadical_set_option(s, "covermineff", covermineff);
}

int cadical_set_opt_coverreleff(const CaDiCaLSolver *s, int coverreleff) {
  if (coverreleff < 1 || coverreleff > 100000) {
    last_error = 222;
    return 222;
  }
  last_error = 0;
  return cadical_set_option(s, "coverreleff", coverreleff);
}

int cadical_set_opt_decompose(const CaDiCaLSolver *s, int decompose) {
  last_error = 0;
  return cadical_set_option(s, "decompose", decompose);
}

int cadical_set_opt_decomposerounds(const CaDiCaLSolver *s, int decomposerounds) {
  if (decomposerounds < 1 || decomposerounds > 16) {
    last_error = 223;
    return 223;
  }
  last_error = 0;
  return cadical_set_option(s, "decomposerounds", decomposerounds);
}

int cadical_set_opt_deduplicate(const CaDiCaLSolver *s, int deduplicate) {
  last_error = 0;
  return cadical_set_option(s, "deduplicate", deduplicate);
}

int cadical_set_opt_eagersubsume(const CaDiCaLSolver *s, int eagersubsume) {
  last_error = 0;
  return cadical_set_option(s, "eagersubsume", eagersubsume);
}

int cadical_set_opt_eagersubsumelim(const CaDiCaLSolver *s, int eagersubsumelim) {
  if (eagersubsumelim < 1 || eagersubsumelim > 1000) {
    last_error = 224;
    return 224;
  }
  last_error = 0;
  return cadical_set_option(s, "eagersubsumelim", eagersubsumelim);
}

int cadical_set_opt_elim(const CaDiCaLSolver *s, int elim) {
  last_error = 0;
  return cadical_set_option(s, "elim", elim);
}

int cadical_set_opt_elimands(const CaDiCaLSolver *s, int elimands) {
  last_error = 0;
  return cadical_set_option(s, "elimands", elimands);
}

int cadical_set_opt_elimaxeff(const CaDiCaLSolver *s, int elimaxeff) {
  if (elimaxeff < 0 || elimaxeff > 2000000000) {
    last_error = 225;
    return 225;
  }
  last_error = 0;
  return cadical_set_option(s, "elimaxeff", elimaxeff);
}

int cadical_set_opt_elimbackward(const CaDiCaLSolver *s, int elimbackward) {
  last_error = 0;
  return cadical_set_option(s, "elimbackward", elimbackward);
}

int cadical_set_opt_elimboundmax(const CaDiCaLSolver *s, int elimboundmax) {
  if (elimboundmax < -1 || elimboundmax > 2000000) {
    last_error = 226;
    return 226;
  }
  last_error = 0;
  return cadical_set_option(s, "elimboundmax", elimboundmax);
}

int cadical_set_opt_elimboundmin(const CaDiCaLSolver *s, int elimboundmin) {
  if (elimboundmin < -1 || elimboundmin > 2000000) {
    last_error = 227;
    return 227;
  }
  last_error = 0;
  return cadical_set_option(s, "elimboundmin", elimboundmin);
}

int cadical_set_opt_elimclslim(const CaDiCaLSolver *s, int elimclslim) {
  if (elimclslim < 2 || elimclslim > 2000000000) {
    last_error = 228;
    return 228;
  }
  last_error = 0;
  return cadical_set_option(s, "elimclslim", elimclslim);
}

int cadical_set_opt_elimequivs(const CaDiCaLSolver *s, int elimequivs) {
  last_error = 0;
  return cadical_set_option(s, "elimequivs", elimequivs);
}

int cadical_set_opt_elimineff(const CaDiCaLSolver *s, int elimineff) {
  if (elimineff < 0 || elimineff > 2000000000) {
    last_error = 229;
    return 229;
  }
  last_error = 0;
  return cadical_set_option(s, "elimineff", elimineff);
}

int cadical_set_opt_elimint(const CaDiCaLSolver *s, int elimint) {
  if (elimint < 1 || elimint > 2000000000) {
    last_error = 230;
    return 230;
  }
  last_error = 0;
  return cadical_set_option(s, "elimint", elimint);
}

int cadical_set_opt_elimites(const CaDiCaLSolver *s, int elimites) {
  last_error = 0;
  return cadical_set_option(s, "elimites", elimites);
}

int cadical_set_opt_elimlimited(const CaDiCaLSolver *s, int elimlimited) {
  last_error = 0;
  return cadical_set_option(s, "elimlimited", elimlimited);
}

int cadical_set_opt_elimocclim(const CaDiCaLSolver *s, int elimocclim) {
  if (elimocclim < 0 || elimocclim > 2000000000) {
    last_error = 231;
    return 231;
  }
  last_error = 0;
  return cadical_set_option(s, "elimocclim", elimocclim);
}

int cadical_set_opt_elimprod(const CaDiCaLSolver *s, int elimprod) {
  if (elimprod < 0 || elimprod > 10000) {
    last_error = 232;
    return 232;
  }
  last_error = 0;
  return cadical_set_option(s, "elimprod", elimprod);
}

int cadical_set_opt_elimreleff(const CaDiCaLSolver *s, int elimreleff) {
  if (elimreleff < 1 || elimreleff > 100000) {
    last_error = 233;
    return 233;
  }
  last_error = 0;
  return cadical_set_option(s, "elimreleff", elimreleff);
}

int cadical_set_opt_elimrounds(const CaDiCaLSolver *s, int elimrounds) {
  if (elimrounds < 1 || elimrounds > 512) {
    last_error = 234;
    return 234;
  }
  last_error = 0;
  return cadical_set_option(s, "elimrounds", elimrounds);
}

int cadical_set_opt_elimsubst(const CaDiCaLSolver *s, int elimsubst) {
  last_error = 0;
  return cadical_set_option(s, "elimsubst", elimsubst);
}

int cadical_set_opt_elimsum(const CaDiCaLSolver *s, int elimsum) {
  if (elimsum < 0 || elimsum > 10000) {
    last_error = 235;
    return 235;
  }
  last_error = 0;
  return cadical_set_option(s, "elimsum", elimsum);
}

int cadical_set_opt_elimxorlim(const CaDiCaLSolver *s, int elimxorlim) {
  if (elimxorlim < 2 || elimxorlim > 27) {
    last_error = 236;
    return 236;
  }
  last_error = 0;
  return cadical_set_option(s, "elimxorlim", elimxorlim);
}

int cadical_set_opt_elimxors(const CaDiCaLSolver *s, int elimxors) {
  last_error = 0;
  return cadical_set_option(s, "elimxors", elimxors);
}

int cadical_set_opt_emagluefast(const CaDiCaLSolver *s, int emagluefast) {
  if (emagluefast < 1 || emagluefast > 2000000000) {
    last_error = 237;
    return 237;
  }
  last_error = 0;
  return cadical_set_option(s, "emagluefast", emagluefast);
}

int cadical_set_opt_emaglueslow(const CaDiCaLSolver *s, int emaglueslow) {
  if (emaglueslow < 1 || emaglueslow > 2000000000) {
    last_error = 238;
    return 238;
  }
  last_error = 0;
  return cadical_set_option(s, "emaglueslow", emaglueslow);
}

int cadical_set_opt_emajump(const CaDiCaLSolver *s, int emajump) {
  if (emajump < 1 || emajump > 2000000000) {
    last_error = 239;
    return 239;
  }
  last_error = 0;
  return cadical_set_option(s, "emajump", emajump);
}

int cadical_set_opt_emalevel(const CaDiCaLSolver *s, int emalevel) {
  if (emalevel < 1 || emalevel > 2000000000) {
    last_error = 240;
    return 240;
  }
  last_error = 0;
  return cadical_set_option(s, "emalevel", emalevel);
}

int cadical_set_opt_emasize(const CaDiCaLSolver *s, int emasize) {
  if (emasize < 1 || emasize > 2000000000) {
    last_error = 241;
    return 241;
  }
  last_error = 0;
  return cadical_set_option(s, "emasize", emasize);
}

int cadical_set_opt_ematrailfast(const CaDiCaLSolver *s, int ematrailfast) {
  if (ematrailfast < 1 || ematrailfast > 2000000000) {
    last_error = 242;
    return 242;
  }
  last_error = 0;
  return cadical_set_option(s, "ematrailfast", ematrailfast);
}

int cadical_set_opt_ematrailslow(const CaDiCaLSolver *s, int ematrailslow) {
  if (ematrailslow < 1 || ematrailslow > 2000000000) {
    last_error = 243;
    return 243;
  }
  last_error = 0;
  return cadical_set_option(s, "ematrailslow", ematrailslow);
}

int cadical_set_opt_exteagerreasons(const CaDiCaLSolver *s, int exteagerreasons) {
  last_error = 0;
  return cadical_set_option(s, "exteagerreasons", exteagerreasons);
}

int cadical_set_opt_exteagerrecalc(const CaDiCaLSolver *s, int exteagerrecalc) {
  last_error = 0;
  return cadical_set_option(s, "exteagerrecalc", exteagerrecalc);
}

int cadical_set_opt_externallrat(const CaDiCaLSolver *s, int externallrat) {
  last_error = 0;
  return cadical_set_option(s, "externallrat", externallrat);
}

int cadical_set_opt_flush(const CaDiCaLSolver *s, int flush) {
  last_error = 0;
  return cadical_set_option(s, "flush", flush);
}

int cadical_set_opt_flushfactor(const CaDiCaLSolver *s, int flushfactor) {
  if (flushfactor < 1 || flushfactor > 1000) {
    last_error = 244;
    return 244;
  }
  last_error = 0;
  return cadical_set_option(s, "flushfactor", flushfactor);
}

int cadical_set_opt_flushint(const CaDiCaLSolver *s, int flushint) {
  if (flushint < 1 || flushint > 2000000000) {
    last_error = 245;
    return 245;
  }
  last_error = 0;
  return cadical_set_option(s, "flushint", flushint);
}

int cadical_set_opt_forcephase(const CaDiCaLSolver *s, int forcephase) {
  last_error = 0;
  return cadical_set_option(s, "forcephase", forcephase);
}

int cadical_set_opt_frat(const CaDiCaLSolver *s, int frat) {
  if (frat < 0 || frat > 2) {
    last_error = 246;
    return 246;
  }
  last_error = 0;
  return cadical_set_option(s, "frat", frat);
}

int cadical_set_opt_idrup(const CaDiCaLSolver *s, int idrup) {
  last_error = 0;
  return cadical_set_option(s, "idrup", idrup);
}

int cadical_set_opt_ilb(const CaDiCaLSolver *s, int ilb) {
  last_error = 0;
  return cadical_set_option(s, "ilb", ilb);
}

int cadical_set_opt_ilbassumptions(const CaDiCaLSolver *s, int ilbassumptions) {
  last_error = 0;
  return cadical_set_option(s, "ilbassumptions", ilbassumptions);
}

int cadical_set_opt_inprocessing(const CaDiCaLSolver *s, int inprocessing) {
  last_error = 0;
  return cadical_set_option(s, "inprocessing", inprocessing);
}

int cadical_set_opt_instantiate(const CaDiCaLSolver *s, int instantiate) {
  last_error = 0;
  return cadical_set_option(s, "instantiate", instantiate);
}

int cadical_set_opt_instantiateclslim(const CaDiCaLSolver *s, int instantiateclslim) {
  if (instantiateclslim < 2 || instantiateclslim > 2000000000) {
    last_error = 247;
    return 247;
  }
  last_error = 0;
  return cadical_set_option(s, "instantiateclslim", instantiateclslim);
}

int cadical_set_opt_instantiateocclim(const CaDiCaLSolver *s, int instantiateocclim) {
  if (instantiateocclim < 1 || instantiateocclim > 2000000000) {
    last_error = 248;
    return 248;
  }
  last_error = 0;
  return cadical_set_option(s, "instantiateocclim", instantiateocclim);
}

int cadical_set_opt_instantiateonce(const CaDiCaLSolver *s, int instantiateonce) {
  last_error = 0;
  return cadical_set_option(s, "instantiateonce", instantiateonce);
}

int cadical_set_opt_lidrup(const CaDiCaLSolver *s, int lidrup) {
  last_error = 0;
  return cadical_set_option(s, "lidrup", lidrup);
}

int cadical_set_opt_log(const CaDiCaLSolver *s, int log) {
  last_error = 0;
  return cadical_set_option(s, "log", log);
}

int cadical_set_opt_logsort(const CaDiCaLSolver *s, int logsort) {
  last_error = 0;
  return cadical_set_option(s, "logsort", logsort);
}

int cadical_set_opt_lrat(const CaDiCaLSolver *s, int lrat) {
  last_error = 0;
  return cadical_set_option(s, "lrat", lrat);
}

int cadical_set_opt_lucky(const CaDiCaLSolver *s, int lucky) {
  last_error = 0;
  return cadical_set_option(s, "lucky", lucky);
}

int cadical_set_opt_minimize(const CaDiCaLSolver *s, int minimize) {
  last_error = 0;
  return cadical_set_option(s, "minimize", minimize);
}

int cadical_set_opt_minimizedepth(const CaDiCaLSolver *s, int minimizedepth) {
  if (minimizedepth < 0 || minimizedepth > 1000) {
    last_error = 249;
    return 249;
  }
  last_error = 0;
  return cadical_set_option(s, "minimizedepth", minimizedepth);
}

int cadical_set_opt_otfs(const CaDiCaLSolver *s, int otfs) {
  last_error = 0;
  return cadical_set_option(s, "otfs", otfs);
}

int cadical_set_opt_phase(const CaDiCaLSolver *s, int phase) {
  last_error = 0;
  return cadical_set_option(s, "phase", phase);
}

int cadical_set_opt_probe(const CaDiCaLSolver *s, int probe) {
  last_error = 0;
  return cadical_set_option(s, "probe", probe);
}

int cadical_set_opt_probehbr(const CaDiCaLSolver *s, int probehbr) {
  last_error = 0;
  return cadical_set_option(s, "probehbr", probehbr);
}

int cadical_set_opt_probeint(const CaDiCaLSolver *s, int probeint) {
  if (probeint < 1 || probeint > 2000000000) {
    last_error = 250;
    return 250;
  }
  last_error = 0;
  return cadical_set_option(s, "probeint", probeint);
}

int cadical_set_opt_probemaxeff(const CaDiCaLSolver *s, int probemaxeff) {
  if (probemaxeff < 0 || probemaxeff > 2000000000) {
    last_error = 251;
    return 251;
  }
  last_error = 0;
  return cadical_set_option(s, "probemaxeff", probemaxeff);
}

int cadical_set_opt_probemineff(const CaDiCaLSolver *s, int probemineff) {
  if (probemineff < 0 || probemineff > 2000000000) {
    last_error = 252;
    return 252;
  }
  last_error = 0;
  return cadical_set_option(s, "probemineff", probemineff);
}

int cadical_set_opt_probereleff(const CaDiCaLSolver *s, int probereleff) {
  if (probereleff < 1 || probereleff > 100000) {
    last_error = 253;
    return 253;
  }
  last_error = 0;
  return cadical_set_option(s, "probereleff", probereleff);
}

int cadical_set_opt_proberounds(const CaDiCaLSolver *s, int proberounds) {
  if (proberounds < 1 || proberounds > 16) {
    last_error = 254;
    return 254;
  }
  last_error = 0;
  return cadical_set_option(s, "proberounds", proberounds);
}

int cadical_set_opt_profile(const CaDiCaLSolver *s, int profile) {
  if (profile < 0 || profile > 4) {
    last_error = 255;
    return 255;
  }
  last_error = 0;
  return cadical_set_option(s, "profile", profile);
}

int cadical_set_opt_quiet(const CaDiCaLSolver *s, int quiet) {
  last_error = 0;
  return cadical_set_option(s, "quiet", quiet);
}

int cadical_set_opt_radixsortlim(const CaDiCaLSolver *s, int radixsortlim) {
  if (radixsortlim < 0 || radixsortlim > 2000000000) {
    last_error = 256;
    return 256;
  }
  last_error = 0;
  return cadical_set_option(s, "radixsortlim", radixsortlim);
}

int cadical_set_opt_realtime(const CaDiCaLSolver *s, int realtime) {
  last_error = 0;
  return cadical_set_option(s, "realtime", realtime);
}

int cadical_set_opt_reduce(const CaDiCaLSolver *s, int reduce) {
  last_error = 0;
  return cadical_set_option(s, "reduce", reduce);
}

int cadical_set_opt_reduceint(const CaDiCaLSolver *s, int reduceint) {
  if (reduceint < 10 || reduceint > 1000000) {
    last_error = 257;
    return 257;
  }
  last_error = 0;
  return cadical_set_option(s, "reduceint", reduceint);
}

int cadical_set_opt_reducetarget(const CaDiCaLSolver *s, int reducetarget) {
  if (reducetarget < 10 || reducetarget > 100) {
    last_error = 258;
    return 258;
  }
  last_error = 0;
  return cadical_set_option(s, "reducetarget", reducetarget);
}

int cadical_set_opt_reducetier1glue(const CaDiCaLSolver *s, int reducetier1glue) {
  if (reducetier1glue < 1 || reducetier1glue > 2000000000) {
    last_error = 259;
    return 259;
  }
  last_error = 0;
  return cadical_set_option(s, "reducetier1glue", reducetier1glue);
}

int cadical_set_opt_reducetier2glue(const CaDiCaLSolver *s, int reducetier2glue) {
  if (reducetier2glue < 1 || reducetier2glue > 2000000000) {
    last_error = 260;
    return 260;
  }
  last_error = 0;
  return cadical_set_option(s, "reducetier2glue", reducetier2glue);
}

int cadical_set_opt_reluctant(const CaDiCaLSolver *s, int reluctant) {
  if (reluctant < 0 || reluctant > 2000000000) {
    last_error = 261;
    return 261;
  }
  last_error = 0;
  return cadical_set_option(s, "reluctant", reluctant);
}

int cadical_set_opt_reluctantmax(const CaDiCaLSolver *s, int reluctantmax) {
  if (reluctantmax < 0 || reluctantmax > 2000000000) {
    last_error = 262;
    return 262;
  }
  last_error = 0;
  return cadical_set_option(s, "reluctantmax", reluctantmax);
}

int cadical_set_opt_rephase(const CaDiCaLSolver *s, int rephase) {
  last_error = 0;
  return cadical_set_option(s, "rephase", rephase);
}

int cadical_set_opt_rephaseint(const CaDiCaLSolver *s, int rephaseint) {
  if (rephaseint < 1 || rephaseint > 2000000000) {
    last_error = 263;
    return 263;
  }
  last_error = 0;
  return cadical_set_option(s, "rephaseint", rephaseint);
}

int cadical_set_opt_report(const CaDiCaLSolver *s, int report) {
  last_error = 0;
  return cadical_set_option(s, "report", report);
}

int cadical_set_opt_reportall(const CaDiCaLSolver *s, int reportall) {
  last_error = 0;
  return cadical_set_option(s, "reportall", reportall);
}

int cadical_set_opt_reportsolve(const CaDiCaLSolver *s, int reportsolve) {
  last_error = 0;
  return cadical_set_option(s, "reportsolve", reportsolve);
}

int cadical_set_opt_restart(const CaDiCaLSolver *s, int restart) {
  last_error = 0;
  return cadical_set_option(s, "restart", restart);
}

int cadical_set_opt_restartint(const CaDiCaLSolver *s, int restartint) {
  if (restartint < 1 || restartint > 2000000000) {
    last_error = 264;
    return 264;
  }
  last_error = 0;
  return cadical_set_option(s, "restartint", restartint);
}

int cadical_set_opt_restartmargin(const CaDiCaLSolver *s, int restartmargin) {
  if (restartmargin < 0 || restartmargin > 100) {
    last_error = 265;
    return 265;
  }
  last_error = 0;
  return cadical_set_option(s, "restartmargin", restartmargin);
}

int cadical_set_opt_restartreusetrail(const CaDiCaLSolver *s, int restartreusetrail) {
  last_error = 0;
  return cadical_set_option(s, "restartreusetrail", restartreusetrail);
}

int cadical_set_opt_restoreall(const CaDiCaLSolver *s, int restoreall) {
  if (restoreall < 0 || restoreall > 2) {
    last_error = 266;
    return 266;
  }
  last_error = 0;
  return cadical_set_option(s, "restoreall", restoreall);
}

int cadical_set_opt_restoreflush(const CaDiCaLSolver *s, int restoreflush) {
  last_error = 0;
  return cadical_set_option(s, "restoreflush", restoreflush);
}

int cadical_set_opt_reverse(const CaDiCaLSolver *s, int reverse) {
  last_error = 0;
  return cadical_set_option(s, "reverse", reverse);
}

int cadical_set_opt_score(const CaDiCaLSolver *s, int score) {
  last_error = 0;
  return cadical_set_option(s, "score", score);
}

int cadical_set_opt_scorefactor(const CaDiCaLSolver *s, int scorefactor) {
  if (scorefactor < 500 || scorefactor > 1000) {
    last_error = 267;
    return 267;
  }
  last_error = 0;
  return cadical_set_option(s, "scorefactor", scorefactor);
}

int cadical_set_opt_seed(const CaDiCaLSolver *s, int seed) {
  if (seed < 0 || seed > 2000000000) {
    last_error = 268;
    return 268;
  }
  last_error = 0;
  return cadical_set_option(s, "seed", seed);
}

int cadical_set_opt_shrink(const CaDiCaLSolver *s, int shrink) {
  if (shrink < 0 || shrink > 3) {
    last_error = 269;
    return 269;
  }
  last_error = 0;
  return cadical_set_option(s, "shrink", shrink);
}

int cadical_set_opt_shrinkreap(const CaDiCaLSolver *s, int shrinkreap) {
  last_error = 0;
  return cadical_set_option(s, "shrinkreap", shrinkreap);
}

int cadical_set_opt_shuffle(const CaDiCaLSolver *s, int shuffle) {
  last_error = 0;
  return cadical_set_option(s, "shuffle", shuffle);
}

int cadical_set_opt_shufflequeue(const CaDiCaLSolver *s, int shufflequeue) {
  last_error = 0;
  return cadical_set_option(s, "shufflequeue", shufflequeue);
}

int cadical_set_opt_shufflerandom(const CaDiCaLSolver *s, int shufflerandom) {
  last_error = 0;
  return cadical_set_option(s, "shufflerandom", shufflerandom);
}

int cadical_set_opt_shufflescores(const CaDiCaLSolver *s, int shufflescores) {
  last_error = 0;
  return cadical_set_option(s, "shufflescores", shufflescores);
}

int cadical_set_opt_stabilize(const CaDiCaLSolver *s, int stabilize) {
  last_error = 0;
  return cadical_set_option(s, "stabilize", stabilize);
}

int cadical_set_opt_stabilizefactor(const CaDiCaLSolver *s, int stabilizefactor) {
  if (stabilizefactor < 101 || stabilizefactor > 2000000000) {
    last_error = 270;
    return 270;
  }
  last_error = 0;
  return cadical_set_option(s, "stabilizefactor", stabilizefactor);
}

int cadical_set_opt_stabilizeint(const CaDiCaLSolver *s, int stabilizeint) {
  if (stabilizeint < 1 || stabilizeint > 2000000000) {
    last_error = 271;
    return 271;
  }
  last_error = 0;
  return cadical_set_option(s, "stabilizeint", stabilizeint);
}

int cadical_set_opt_stabilizemaxint(const CaDiCaLSolver *s, int stabilizemaxint) {
  if (stabilizemaxint < 1 || stabilizemaxint > 2000000000) {
    last_error = 272;
    return 272;
  }
  last_error = 0;
  return cadical_set_option(s, "stabilizemaxint", stabilizemaxint);
}

int cadical_set_opt_stabilizeonly(const CaDiCaLSolver *s, int stabilizeonly) {
  last_error = 0;
  return cadical_set_option(s, "stabilizeonly", stabilizeonly);
}

int cadical_set_opt_stats(const CaDiCaLSolver *s, int stats) {
  last_error = 0;
  return cadical_set_option(s, "stats", stats);
}

int cadical_set_opt_subsume(const CaDiCaLSolver *s, int subsume) {
  last_error = 0;
  return cadical_set_option(s, "subsume", subsume);
}

int cadical_set_opt_subsumebinlim(const CaDiCaLSolver *s, int subsumebinlim) {
  if (subsumebinlim < 0 || subsumebinlim > 2000000000) {
    last_error = 273;
    return 273;
  }
  last_error = 0;
  return cadical_set_option(s, "subsumebinlim", subsumebinlim);
}

int cadical_set_opt_subsumeclslim(const CaDiCaLSolver *s, int subsumeclslim) {
  if (subsumeclslim < 0 || subsumeclslim > 2000000000) {
    last_error = 274;
    return 274;
  }
  last_error = 0;
  return cadical_set_option(s, "subsumeclslim", subsumeclslim);
}

int cadical_set_opt_subsumeint(const CaDiCaLSolver *s, int subsumeint) {
  if (subsumeint < 1 || subsumeint > 2000000000) {
    last_error = 275;
    return 275;
  }
  last_error = 0;
  return cadical_set_option(s, "subsumeint", subsumeint);
}

int cadical_set_opt_subsumelimited(const CaDiCaLSolver *s, int subsumelimited) {
  last_error = 0;
  return cadical_set_option(s, "subsumelimited", subsumelimited);
}

int cadical_set_opt_subsumemaxeff(const CaDiCaLSolver *s, int subsumemaxeff) {
  if (subsumemaxeff < 0 || subsumemaxeff > 2000000000) {
    last_error = 276;
    return 276;
  }
  last_error = 0;
  return cadical_set_option(s, "subsumemaxeff", subsumemaxeff);
}

int cadical_set_opt_subsumemineff(const CaDiCaLSolver *s, int subsumemineff) {
  if (subsumemineff < 0 || subsumemineff > 2000000000) {
    last_error = 277;
    return 277;
  }
  last_error = 0;
  return cadical_set_option(s, "subsumemineff", subsumemineff);
}

int cadical_set_opt_subsumeocclim(const CaDiCaLSolver *s, int subsumeocclim) {
  if (subsumeocclim < 0 || subsumeocclim > 2000000000) {
    last_error = 278;
    return 278;
  }
  last_error = 0;
  return cadical_set_option(s, "subsumeocclim", subsumeocclim);
}

int cadical_set_opt_subsumereleff(const CaDiCaLSolver *s, int subsumereleff) {
  if (subsumereleff < 1 || subsumereleff > 100000) {
    last_error = 279;
    return 279;
  }
  last_error = 0;
  return cadical_set_option(s, "subsumereleff", subsumereleff);
}

int cadical_set_opt_subsumestr(const CaDiCaLSolver *s, int subsumestr) {
  last_error = 0;
  return cadical_set_option(s, "subsumestr", subsumestr);
}

int cadical_set_opt_target(const CaDiCaLSolver *s, int target) {
  if (target < 0 || target > 2) {
    last_error = 280;
    return 280;
  }
  last_error = 0;
  return cadical_set_option(s, "target", target);
}

int cadical_set_opt_terminateint(const CaDiCaLSolver *s, int terminateint) {
  if (terminateint < 0 || terminateint > 10000) {
    last_error = 281;
    return 281;
  }
  last_error = 0;
  return cadical_set_option(s, "terminateint", terminateint);
}

int cadical_set_opt_ternary(const CaDiCaLSolver *s, int ternary) {
  last_error = 0;
  return cadical_set_option(s, "ternary", ternary);
}

int cadical_set_opt_ternarymaxadd(const CaDiCaLSolver *s, int ternarymaxadd) {
  if (ternarymaxadd < 0 || ternarymaxadd > 10000) {
    last_error = 282;
    return 282;
  }
  last_error = 0;
  return cadical_set_option(s, "ternarymaxadd", ternarymaxadd);
}

int cadical_set_opt_ternarymaxeff(const CaDiCaLSolver *s, int ternarymaxeff) {
  if (ternarymaxeff < 0 || ternarymaxeff > 2000000000) {
    last_error = 283;
    return 283;
  }
  last_error = 0;
  return cadical_set_option(s, "ternarymaxeff", ternarymaxeff);
}

int cadical_set_opt_ternarymineff(const CaDiCaLSolver *s, int ternarymineff) {
  if (ternarymineff < 1 || ternarymineff > 2000000000) {
    last_error = 284;
    return 284;
  }
  last_error = 0;
  return cadical_set_option(s, "ternarymineff", ternarymineff);
}

int cadical_set_opt_ternaryocclim(const CaDiCaLSolver *s, int ternaryocclim) {
  if (ternaryocclim < 1 || ternaryocclim > 2000000000) {
    last_error = 285;
    return 285;
  }
  last_error = 0;
  return cadical_set_option(s, "ternaryocclim", ternaryocclim);
}

int cadical_set_opt_ternaryreleff(const CaDiCaLSolver *s, int ternaryreleff) {
  if (ternaryreleff < 1 || ternaryreleff > 100000) {
    last_error = 286;
    return 286;
  }
  last_error = 0;
  return cadical_set_option(s, "ternaryreleff", ternaryreleff);
}

int cadical_set_opt_ternaryrounds(const CaDiCaLSolver *s, int ternaryrounds) {
  if (ternaryrounds < 1 || ternaryrounds > 16) {
    last_error = 287;
    return 287;
  }
  last_error = 0;
  return cadical_set_option(s, "ternaryrounds", ternaryrounds);
}

int cadical_set_opt_transred(const CaDiCaLSolver *s, int transred) {
  last_error = 0;
  return cadical_set_option(s, "transred", transred);
}

int cadical_set_opt_transredmaxeff(const CaDiCaLSolver *s, int transredmaxeff) {
  if (transredmaxeff < 0 || transredmaxeff > 2000000000) {
    last_error = 288;
    return 288;
  }
  last_error = 0;
  return cadical_set_option(s, "transredmaxeff", transredmaxeff);
}

int cadical_set_opt_transredmineff(const CaDiCaLSolver *s, int transredmineff) {
  if (transredmineff < 0 || transredmineff > 2000000000) {
    last_error = 289;
    return 289;
  }
  last_error = 0;
  return cadical_set_option(s, "transredmineff", transredmineff);
}

int cadical_set_opt_transredreleff(const CaDiCaLSolver *s, int transredreleff) {
  if (transredreleff < 1 || transredreleff > 100000) {
    last_error = 290;
    return 290;
  }
  last_error = 0;
  return cadical_set_option(s, "transredreleff", transredreleff);
}

int cadical_set_opt_verbose(const CaDiCaLSolver *s, int verbose) {
  if (verbose < 0 || verbose > 3) {
    last_error = 291;
    return 291;
  }
  last_error = 0;
  return cadical_set_option(s, "verbose", verbose);
}

int cadical_set_opt_veripb(const CaDiCaLSolver *s, int veripb) {
  if (veripb < 0 || veripb > 4) {
    last_error = 292;
    return 292;
  }
  last_error = 0;
  return cadical_set_option(s, "veripb", veripb);
}

int cadical_set_opt_vivify(const CaDiCaLSolver *s, int vivify) {
  last_error = 0;
  return cadical_set_option(s, "vivify", vivify);
}

int cadical_set_opt_vivifyinst(const CaDiCaLSolver *s, int vivifyinst) {
  last_error = 0;
  return cadical_set_option(s, "vivifyinst", vivifyinst);
}

int cadical_set_opt_vivifymaxeff(const CaDiCaLSolver *s, int vivifymaxeff) {
  if (vivifymaxeff < 0 || vivifymaxeff > 2000000000) {
    last_error = 293;
    return 293;
  }
  last_error = 0;
  return cadical_set_option(s, "vivifymaxeff", vivifymaxeff);
}

int cadical_set_opt_vivifymineff(const CaDiCaLSolver *s, int vivifymineff) {
  if (vivifymineff < 0 || vivifymineff > 2000000000) {
    last_error = 294;
    return 294;
  }
  last_error = 0;
  return cadical_set_option(s, "vivifymineff", vivifymineff);
}

int cadical_set_opt_vivifyonce(const CaDiCaLSolver *s, int vivifyonce) {
  if (vivifyonce < 0 || vivifyonce > 2) {
    last_error = 295;
    return 295;
  }
  last_error = 0;
  return cadical_set_option(s, "vivifyonce", vivifyonce);
}

int cadical_set_opt_vivifyredeff(const CaDiCaLSolver *s, int vivifyredeff) {
  if (vivifyredeff < 0 || vivifyredeff > 1000) {
    last_error = 296;
    return 296;
  }
  last_error = 0;
  return cadical_set_option(s, "vivifyredeff", vivifyredeff);
}

int cadical_set_opt_vivifyreleff(const CaDiCaLSolver *s, int vivifyreleff) {
  if (vivifyreleff < 1 || vivifyreleff > 100000) {
    last_error = 297;
    return 297;
  }
  last_error = 0;
  return cadical_set_option(s, "vivifyreleff", vivifyreleff);
}

int cadical_set_opt_walk(const CaDiCaLSolver *s, int walk) {
  last_error = 0;
  return cadical_set_option(s, "walk", walk);
}

int cadical_set_opt_walkmaxeff(const CaDiCaLSolver *s, int walkmaxeff) {
  if (walkmaxeff < 0 || walkmaxeff > 2000000000) {
    last_error = 298;
    return 298;
  }
  last_error = 0;
  return cadical_set_option(s, "walkmaxeff", walkmaxeff);
}

int cadical_set_opt_walkmineff(const CaDiCaLSolver *s, int walkmineff) {
  if (walkmineff < 0 || walkmineff > 10000000) {
    last_error = 299;
    return 299;
  }
  last_error = 0;
  return cadical_set_option(s, "walkmineff", walkmineff);
}

int cadical_set_opt_walknonstable(const CaDiCaLSolver *s, int walknonstable) {
  last_error = 0;
  return cadical_set_option(s, "walknonstable", walknonstable);
}

int cadical_set_opt_walkredundant(const CaDiCaLSolver *s, int walkredundant) {
  last_error = 0;
  return cadical_set_option(s, "walkredundant", walkredundant);
}

int cadical_set_opt_walkreleff(const CaDiCaLSolver *s, int walkreleff) {
  if (walkreleff < 1 || walkreleff > 100000) {
    last_error = 300;
    return 300;
  }
  last_error = 0;
  return cadical_set_option(s, "walkreleff", walkreleff);
}