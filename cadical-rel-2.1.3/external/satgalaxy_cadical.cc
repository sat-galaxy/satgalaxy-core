
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

struct CaDiCaLSolver
{
  SatgalaxyTerminator *terminator;
  SatgalaxyLearner *learner;
  int last_error;
  CaDiCaL::Solver *solver;
};

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
  CaDiCaLSolver *solver = new CaDiCaLSolver ();
  solver->terminator = new SatgalaxyTerminator ();
  solver->learner = new SatgalaxyLearner ();
  solver->last_error = 0;
  solver->solver = new CaDiCaL::Solver ();
  return solver;
}
void cadical_destroy (CaDiCaLSolver *s) {
  CaDiCaL::Solver *solver = s->solver;
  delete s->terminator;
  delete s->learner;
  delete solver;
  delete s;
}

void cadical_add_clause (CaDiCaLSolver *s, const int ps[],
                        unsigned long length) {
  CaDiCaL::Solver *solver = s->solver;
  // int ret = require_valid_state (solver);
  // if (ret) {
  //   s->last_error = ret;
  //   return ret;
  // }
  solver->clause (ps, length);
  // return 0;
}
void cadical_add_empty_clause (CaDiCaLSolver *s) {
  return cadical_add (s, 0);
}

void cadical_add (CaDiCaLSolver *s, int lit) {
  CaDiCaL::Solver *solver = s->solver;
  // int ret = require_valid_state (solver);
  // if (ret) {
  //   s->last_error = ret;
  //   return ret;
  // }
  // ret = require_valid_lit (lit);
  // if (ret) {
  //   s->last_error = ret;
  //   return ret;
  // }
  solver->add (lit);
  // return 0;
}

void cadical_assume (CaDiCaLSolver *s, int lit) {
  CaDiCaL::Solver *solver = s->solver;
  // int ret = require_valid_state (solver);
  // if (ret) {
  //   s->last_error = ret;
  //   return ret;
  // }
  // ret = require_valid_lit (lit);
  // if (ret) {
  //   s->last_error = ret;
  //   return ret;
  // }
  solver->assume (lit);
  // return 0;
}
int cadical_solve (CaDiCaLSolver *s) {
  CaDiCaL::Solver *solver = s->solver;
  // int ret = require_ready_state (solver);
  // if (ret) {
  //   s->last_error = ret;
  //   return 0;
  // }
  int ret = solver->solve ();
  return ret? ret: 30;
}
int cadical_val (CaDiCaLSolver *s, int lit) {
  CaDiCaL::Solver *solver = s->solver;
  // int ret = require_valid_state (solver);
  // if (ret) {
  //   s->last_error = ret;
  //   return 0;
  // }
  // ret = require_valid_lit (lit);
  // if (ret) {
  //   s->last_error = ret;
  //   return 0;
  // }
  // ret = require_satisfied_state (solver);
  // if (ret) {
  //   s->last_error = ret;
  //   return 0;
  // }
  return solver->val (lit);
}
int cadical_failed (CaDiCaLSolver *s, int lit) {
  CaDiCaL::Solver *solver = s->solver;
  // s->last_error = require_valid_state (solver);
  // if (last_error) {
  //   return s->last_error;
  // }
  // s->last_error = require_valid_lit (lit);
  // if (last_error) {
  //   return s->last_error;
  // }
  // s->last_error = require_satisfied_state (solver);
  // if (last_error) {
  //   return s->last_error;
  // }
  return solver->failed (lit) ? 1 : 0;
}

void cadical_set_terminate (CaDiCaLSolver *s, void *state,
                           int (*terminate) (void *state)) {
  CaDiCaL::Solver *solver = s->solver;
  // s->last_error = require_valid_state (solver);
  // if (last_error) {
  //   return s->last_error;
  // }
  if (terminate) {
    s->terminator->function = terminate;
    s->terminator->state = state;
    solver->connect_terminator (s->terminator);
  } else
    solver->disconnect_terminator ();
  // return 0;
}

void cadical_set_learn (CaDiCaLSolver *s, void *state, int max_length,
                       void (*learn) (void *state, int *clause)) {
  CaDiCaL::Solver *solver = s->solver;
  // s->last_error = require_valid_state (solver);
  // if (last_error) {
  //   return s->last_error;
  // }
  SatgalaxyLearner *learner=s->learner;
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

void cadical_constrain (CaDiCaLSolver *s, int lit) {
  CaDiCaL::Solver *solver = s->solver;
  // s->last_error = require_valid_state (solver);
  // if (last_error) {
  //   return s->last_error;
  // }
  // if (lit) {
  //   s->last_error = require_valid_lit (lit);
  //   if (last_error) {
  //     return s->last_error;
  //   }
  // }

  solver->constrain (lit);
  // return 0;
}
int cadical_constraint_failed (CaDiCaLSolver *s) {
  CaDiCaL::Solver *solver = s->solver;
  // s->last_error = require_valid_state (solver);
  // if (last_error) {
  //   return s->last_error;
  // }
  // s->last_error = require_unsatisfied_state (solver);
  // if (last_error) {
  //   return s->last_error;
  // }
  return solver->constraint_failed () ? 1 : 0;
}
int cadical_set_option (CaDiCaLSolver *s, const char *name, int val) {
  CaDiCaL::Solver *solver = s->solver;
  // s->last_error = require_valid_state (solver);
  // if (last_error) {
  //   return 0;
  // }
  if (strcmp (name, "log") && strcmp (name, "quiet") &&
      strcmp (name, "report") && strcmp (name, "verbose")) {
    // s->last_error = require_configuring_state (solver);
    // if (last_error) {
    //   return 0;
    // }
  }
  return solver->set (name, val);
}

int cadical_limit (CaDiCaLSolver *s, const char *name, int limit) {
  CaDiCaL::Solver *solver = s->solver;
  // s->last_error = require_valid_state (solver);
  // if (last_error) {
  //   return 0;
  // }
  return solver->limit (name, limit);
}
int cadical_get_option (CaDiCaLSolver *s, const char *name) {
  CaDiCaL::Solver *solver = s->solver;
  // s->last_error = require_valid_or_solving_state (solver);
  // if (last_error) {
  //   return 0;
  // }
  return solver->get (name);
}
void  cadical_print_statistics (CaDiCaLSolver *s) {
  CaDiCaL::Solver *solver = s->solver;
  // s->last_error = require_valid_or_solving_state (solver);
  // if (last_error) {
  //   return s->last_error;
  // }
   solver->statistics ();
  //  return 0;
}
int64_t cadical_active (CaDiCaLSolver *s){
  CaDiCaL::Solver *solver = s->solver;
  // s->last_error = require_valid_or_solving_state (solver);
  // if (last_error) {
  //   return 0;
  // }
   return solver->active ();
}
int64_t cadical_irredundant (CaDiCaLSolver *s){
  CaDiCaL::Solver *solver = s->solver;
  // s->last_error = require_valid_state (solver);
  // if (last_error) {
  //   return 0;
  // }
  return solver->irredundant ();
}
int cadical_fixed (CaDiCaLSolver *s, int lit){
    CaDiCaL::Solver *solver = s->solver;

    // s->last_error = require_valid_state (solver);
    // if (last_error) {
    //   return 0;
    // }
    // s->last_error = require_valid_lit (lit);
    // if (last_error) {
    //   return 0;
    // }
    return solver->fixed (lit);

}
// int cadical_trace_proof (CaDiCaLSolver *, FILE *, const char *);
// void cadical_close_proof (CaDiCaLSolver *);
void cadical_conclude (CaDiCaLSolver *s){
  CaDiCaL::Solver *solver = s->solver;
  solver->conclude ();
}
void cadical_terminate (CaDiCaLSolver *s){
  CaDiCaL::Solver *solver = s->solver;
  solver->terminate ();
}
void cadical_freeze (CaDiCaLSolver *s, int lit){
    CaDiCaL::Solver *solver = s->solver;
    solver->freeze (lit);
}
int cadical_frozen (CaDiCaLSolver *s, int lit){
  CaDiCaL::Solver *solver = s->solver;
  return solver->frozen (lit);

}
void cadical_melt (CaDiCaLSolver *s, int lit){
  CaDiCaL::Solver *solver = s->solver;
  solver->melt (lit);
}
int cadical_simplify (CaDiCaLSolver *s){
  CaDiCaL::Solver *solver = s->solver;
  int res= solver->simplify ();
  return res?res:30;
}

int cadical_set_opt_arena(CaDiCaLSolver *s, int arena) {
  s->last_error = 0;
  return cadical_set_option(s, "arena", arena);
}

int cadical_set_opt_arenacompact(CaDiCaLSolver *s, int arenacompact) {
  s->last_error = 0;
  return cadical_set_option(s, "arenacompact", arenacompact);
}

int cadical_set_opt_arenasort(CaDiCaLSolver *s, int arenasort) {
  s->last_error = 0;
  return cadical_set_option(s, "arenasort", arenasort);
}

int cadical_set_opt_arenatype(CaDiCaLSolver *s, int arenatype) {
  if (arenatype < 1 || arenatype > 3) {
    s->last_error = 202;
    return 202;
  }
  s->last_error = 0;
  return cadical_set_option(s, "arenatype", arenatype);
}

int cadical_set_opt_binary(CaDiCaLSolver *s, int binary) {
  s->last_error = 0;
  return cadical_set_option(s, "binary", binary);
}

int cadical_set_opt_block(CaDiCaLSolver *s, int block) {
  s->last_error = 0;
  return cadical_set_option(s, "block", block);
}

int cadical_set_opt_blockmaxclslim(CaDiCaLSolver *s, int blockmaxclslim) {
  if (blockmaxclslim < 1 || blockmaxclslim > 2000000000) {
    s->last_error = 203;
    return 203;
  }
  s->last_error = 0;
  return cadical_set_option(s, "blockmaxclslim", blockmaxclslim);
}

int cadical_set_opt_blockminclslim(CaDiCaLSolver *s, int blockminclslim) {
  if (blockminclslim < 2 || blockminclslim > 2000000000) {
    s->last_error = 204;
    return 204;
  }
  s->last_error = 0;
  return cadical_set_option(s, "blockminclslim", blockminclslim);
}

int cadical_set_opt_blockocclim(CaDiCaLSolver *s, int blockocclim) {
  if (blockocclim < 1 || blockocclim > 2000000000) {
    s->last_error = 205;
    return 205;
  }
  s->last_error = 0;
  return cadical_set_option(s, "blockocclim", blockocclim);
}

int cadical_set_opt_bump(CaDiCaLSolver *s, int bump) {
  s->last_error = 0;
  return cadical_set_option(s, "bump", bump);
}

int cadical_set_opt_bumpreason(CaDiCaLSolver *s, int bumpreason) {
  s->last_error = 0;
  return cadical_set_option(s, "bumpreason", bumpreason);
}

int cadical_set_opt_bumpreasondepth(CaDiCaLSolver *s, int bumpreasondepth) {
  if (bumpreasondepth < 1 || bumpreasondepth > 3) {
    s->last_error = 206;
    return 206;
  }
  s->last_error = 0;
  return cadical_set_option(s, "bumpreasondepth", bumpreasondepth);
}

int cadical_set_opt_check(CaDiCaLSolver *s, int check) {
  s->last_error = 0;
  return cadical_set_option(s, "check", check);
}

int cadical_set_opt_checkassumptions(CaDiCaLSolver *s, int checkassumptions) {
  s->last_error = 0;
  return cadical_set_option(s, "checkassumptions", checkassumptions);
}

int cadical_set_opt_checkconstraint(CaDiCaLSolver *s, int checkconstraint) {
  s->last_error = 0;
  return cadical_set_option(s, "checkconstraint", checkconstraint);
}

int cadical_set_opt_checkfailed(CaDiCaLSolver *s, int checkfailed) {
  s->last_error = 0;
  return cadical_set_option(s, "checkfailed", checkfailed);
}

int cadical_set_opt_checkfrozen(CaDiCaLSolver *s, int checkfrozen) {
  s->last_error = 0;
  return cadical_set_option(s, "checkfrozen", checkfrozen);
}

int cadical_set_opt_checkproof(CaDiCaLSolver *s, int checkproof) {
  if (checkproof < 0 || checkproof > 3) {
    s->last_error = 207;
    return 207;
  }
  s->last_error = 0;
  return cadical_set_option(s, "checkproof", checkproof);
}

int cadical_set_opt_checkwitness(CaDiCaLSolver *s, int checkwitness) {
  s->last_error = 0;
  return cadical_set_option(s, "checkwitness", checkwitness);
}

int cadical_set_opt_chrono(CaDiCaLSolver *s, int chrono) {
  if (chrono < 0 || chrono > 2) {
    s->last_error = 208;
    return 208;
  }
  s->last_error = 0;
  return cadical_set_option(s, "chrono", chrono);
}

int cadical_set_opt_chronoalways(CaDiCaLSolver *s, int chronoalways) {
  s->last_error = 0;
  return cadical_set_option(s, "chronoalways", chronoalways);
}

int cadical_set_opt_chronolevelim(CaDiCaLSolver *s, int chronolevelim) {
  if (chronolevelim < 0 || chronolevelim > 2000000000) {
    s->last_error = 209;
    return 209;
  }
  s->last_error = 0;
  return cadical_set_option(s, "chronolevelim", chronolevelim);
}

int cadical_set_opt_chronoreusetrail(CaDiCaLSolver *s, int chronoreusetrail) {
  s->last_error = 0;
  return cadical_set_option(s, "chronoreusetrail", chronoreusetrail);
}

int cadical_set_opt_compact(CaDiCaLSolver *s, int compact) {
  s->last_error = 0;
  return cadical_set_option(s, "compact", compact);
}

int cadical_set_opt_compactint(CaDiCaLSolver *s, int compactint) {
  if (compactint < 1 || compactint > 2000000000) {
    s->last_error = 210;
    return 210;
  }
  s->last_error = 0;
  return cadical_set_option(s, "compactint", compactint);
}

int cadical_set_opt_compactlim(CaDiCaLSolver *s, int compactlim) {
  if (compactlim < 0 || compactlim > 1000) {
    s->last_error = 211;
    return 211;
  }
  s->last_error = 0;
  return cadical_set_option(s, "compactlim", compactlim);
}

int cadical_set_opt_compactmin(CaDiCaLSolver *s, int compactmin) {
  if (compactmin < 1 || compactmin > 2000000000) {
    s->last_error = 212;
    return 212;
  }
  s->last_error = 0;
  return cadical_set_option(s, "compactmin", compactmin);
}

int cadical_set_opt_condition(CaDiCaLSolver *s, int condition) {
  s->last_error = 0;
  return cadical_set_option(s, "condition", condition);
}

int cadical_set_opt_conditionint(CaDiCaLSolver *s, int conditionint) {
  if (conditionint < 1 || conditionint > 2000000000) {
    s->last_error = 213;
    return 213;
  }
  s->last_error = 0;
  return cadical_set_option(s, "conditionint", conditionint);
}

int cadical_set_opt_conditionmaxeff(CaDiCaLSolver *s, int conditionmaxeff) {
  if (conditionmaxeff < 0 || conditionmaxeff > 2000000000) {
    s->last_error = 214;
    return 214;
  }
  s->last_error = 0;
  return cadical_set_option(s, "conditionmaxeff", conditionmaxeff);
}

int cadical_set_opt_conditionmaxrat(CaDiCaLSolver *s, int conditionmaxrat) {
  if (conditionmaxrat < 1 || conditionmaxrat > 2000000000) {
    s->last_error = 215;
    return 215;
  }
  s->last_error = 0;
  return cadical_set_option(s, "conditionmaxrat", conditionmaxrat);
}

int cadical_set_opt_conditionmineff(CaDiCaLSolver *s, int conditionmineff) {
  if (conditionmineff < 0 || conditionmineff > 2000000000) {
    s->last_error = 216;
    return 216;
  }
  s->last_error = 0;
  return cadical_set_option(s, "conditionmineff", conditionmineff);
}

int cadical_set_opt_conditionreleff(CaDiCaLSolver *s, int conditionreleff) {
  if (conditionreleff < 1 || conditionreleff > 100000) {
    s->last_error = 217;
    return 217;
  }
  s->last_error = 0;
  return cadical_set_option(s, "conditionreleff", conditionreleff);
}

int cadical_set_opt_cover(CaDiCaLSolver *s, int cover) {
  s->last_error = 0;
  return cadical_set_option(s, "cover", cover);
}

int cadical_set_opt_covermaxclslim(CaDiCaLSolver *s, int covermaxclslim) {
  if (covermaxclslim < 1 || covermaxclslim > 2000000000) {
    s->last_error = 218;
    return 218;
  }
  s->last_error = 0;
  return cadical_set_option(s, "covermaxclslim", covermaxclslim);
}

int cadical_set_opt_covermaxeff(CaDiCaLSolver *s, int covermaxeff) {
  if (covermaxeff < 0 || covermaxeff > 2000000000) {
    s->last_error = 219;
    return 219;
  }
  s->last_error = 0;
  return cadical_set_option(s, "covermaxeff", covermaxeff);
}

int cadical_set_opt_coverminclslim(CaDiCaLSolver *s, int coverminclslim) {
  if (coverminclslim < 2 || coverminclslim > 2000000000) {
    s->last_error = 220;
    return 220;
  }
  s->last_error = 0;
  return cadical_set_option(s, "coverminclslim", coverminclslim);
}

int cadical_set_opt_covermineff(CaDiCaLSolver *s, int covermineff) {
  if (covermineff < 0 || covermineff > 2000000000) {
    s->last_error = 221;
    return 221;
  }
  s->last_error = 0;
  return cadical_set_option(s, "covermineff", covermineff);
}

int cadical_set_opt_coverreleff(CaDiCaLSolver *s, int coverreleff) {
  if (coverreleff < 1 || coverreleff > 100000) {
    s->last_error = 222;
    return 222;
  }
  s->last_error = 0;
  return cadical_set_option(s, "coverreleff", coverreleff);
}

int cadical_set_opt_decompose(CaDiCaLSolver *s, int decompose) {
  s->last_error = 0;
  return cadical_set_option(s, "decompose", decompose);
}

int cadical_set_opt_decomposerounds(CaDiCaLSolver *s, int decomposerounds) {
  if (decomposerounds < 1 || decomposerounds > 16) {
    s->last_error = 223;
    return 223;
  }
  s->last_error = 0;
  return cadical_set_option(s, "decomposerounds", decomposerounds);
}

int cadical_set_opt_deduplicate(CaDiCaLSolver *s, int deduplicate) {
  s->last_error = 0;
  return cadical_set_option(s, "deduplicate", deduplicate);
}

int cadical_set_opt_eagersubsume(CaDiCaLSolver *s, int eagersubsume) {
  s->last_error = 0;
  return cadical_set_option(s, "eagersubsume", eagersubsume);
}

int cadical_set_opt_eagersubsumelim(CaDiCaLSolver *s, int eagersubsumelim) {
  if (eagersubsumelim < 1 || eagersubsumelim > 1000) {
    s->last_error = 224;
    return 224;
  }
  s->last_error = 0;
  return cadical_set_option(s, "eagersubsumelim", eagersubsumelim);
}

int cadical_set_opt_elim(CaDiCaLSolver *s, int elim) {
  s->last_error = 0;
  return cadical_set_option(s, "elim", elim);
}

int cadical_set_opt_elimands(CaDiCaLSolver *s, int elimands) {
  s->last_error = 0;
  return cadical_set_option(s, "elimands", elimands);
}

int cadical_set_opt_elimaxeff(CaDiCaLSolver *s, int elimaxeff) {
  if (elimaxeff < 0 || elimaxeff > 2000000000) {
    s->last_error = 225;
    return 225;
  }
  s->last_error = 0;
  return cadical_set_option(s, "elimaxeff", elimaxeff);
}

int cadical_set_opt_elimbackward(CaDiCaLSolver *s, int elimbackward) {
  s->last_error = 0;
  return cadical_set_option(s, "elimbackward", elimbackward);
}

int cadical_set_opt_elimboundmax(CaDiCaLSolver *s, int elimboundmax) {
  if (elimboundmax < -1 || elimboundmax > 2000000) {
    s->last_error = 226;
    return 226;
  }
  s->last_error = 0;
  return cadical_set_option(s, "elimboundmax", elimboundmax);
}

int cadical_set_opt_elimboundmin(CaDiCaLSolver *s, int elimboundmin) {
  if (elimboundmin < -1 || elimboundmin > 2000000) {
    s->last_error = 227;
    return 227;
  }
  s->last_error = 0;
  return cadical_set_option(s, "elimboundmin", elimboundmin);
}

int cadical_set_opt_elimclslim(CaDiCaLSolver *s, int elimclslim) {
  if (elimclslim < 2 || elimclslim > 2000000000) {
    s->last_error = 228;
    return 228;
  }
  s->last_error = 0;
  return cadical_set_option(s, "elimclslim", elimclslim);
}

int cadical_set_opt_elimequivs(CaDiCaLSolver *s, int elimequivs) {
  s->last_error = 0;
  return cadical_set_option(s, "elimequivs", elimequivs);
}

int cadical_set_opt_elimineff(CaDiCaLSolver *s, int elimineff) {
  if (elimineff < 0 || elimineff > 2000000000) {
    s->last_error = 229;
    return 229;
  }
  s->last_error = 0;
  return cadical_set_option(s, "elimineff", elimineff);
}

int cadical_set_opt_elimint(CaDiCaLSolver *s, int elimint) {
  if (elimint < 1 || elimint > 2000000000) {
    s->last_error = 230;
    return 230;
  }
  s->last_error = 0;
  return cadical_set_option(s, "elimint", elimint);
}

int cadical_set_opt_elimites(CaDiCaLSolver *s, int elimites) {
  s->last_error = 0;
  return cadical_set_option(s, "elimites", elimites);
}

int cadical_set_opt_elimlimited(CaDiCaLSolver *s, int elimlimited) {
  s->last_error = 0;
  return cadical_set_option(s, "elimlimited", elimlimited);
}

int cadical_set_opt_elimocclim(CaDiCaLSolver *s, int elimocclim) {
  if (elimocclim < 0 || elimocclim > 2000000000) {
    s->last_error = 231;
    return 231;
  }
  s->last_error = 0;
  return cadical_set_option(s, "elimocclim", elimocclim);
}

int cadical_set_opt_elimprod(CaDiCaLSolver *s, int elimprod) {
  if (elimprod < 0 || elimprod > 10000) {
    s->last_error = 232;
    return 232;
  }
  s->last_error = 0;
  return cadical_set_option(s, "elimprod", elimprod);
}

int cadical_set_opt_elimreleff(CaDiCaLSolver *s, int elimreleff) {
  if (elimreleff < 1 || elimreleff > 100000) {
    s->last_error = 233;
    return 233;
  }
  s->last_error = 0;
  return cadical_set_option(s, "elimreleff", elimreleff);
}

int cadical_set_opt_elimrounds(CaDiCaLSolver *s, int elimrounds) {
  if (elimrounds < 1 || elimrounds > 512) {
    s->last_error = 234;
    return 234;
  }
  s->last_error = 0;
  return cadical_set_option(s, "elimrounds", elimrounds);
}

int cadical_set_opt_elimsubst(CaDiCaLSolver *s, int elimsubst) {
  s->last_error = 0;
  return cadical_set_option(s, "elimsubst", elimsubst);
}

int cadical_set_opt_elimsum(CaDiCaLSolver *s, int elimsum) {
  if (elimsum < 0 || elimsum > 10000) {
    s->last_error = 235;
    return 235;
  }
  s->last_error = 0;
  return cadical_set_option(s, "elimsum", elimsum);
}

int cadical_set_opt_elimxorlim(CaDiCaLSolver *s, int elimxorlim) {
  if (elimxorlim < 2 || elimxorlim > 27) {
    s->last_error = 236;
    return 236;
  }
  s->last_error = 0;
  return cadical_set_option(s, "elimxorlim", elimxorlim);
}

int cadical_set_opt_elimxors(CaDiCaLSolver *s, int elimxors) {
  s->last_error = 0;
  return cadical_set_option(s, "elimxors", elimxors);
}

int cadical_set_opt_emagluefast(CaDiCaLSolver *s, int emagluefast) {
  if (emagluefast < 1 || emagluefast > 2000000000) {
    s->last_error = 237;
    return 237;
  }
  s->last_error = 0;
  return cadical_set_option(s, "emagluefast", emagluefast);
}

int cadical_set_opt_emaglueslow(CaDiCaLSolver *s, int emaglueslow) {
  if (emaglueslow < 1 || emaglueslow > 2000000000) {
    s->last_error = 238;
    return 238;
  }
  s->last_error = 0;
  return cadical_set_option(s, "emaglueslow", emaglueslow);
}

int cadical_set_opt_emajump(CaDiCaLSolver *s, int emajump) {
  if (emajump < 1 || emajump > 2000000000) {
    s->last_error = 239;
    return 239;
  }
  s->last_error = 0;
  return cadical_set_option(s, "emajump", emajump);
}

int cadical_set_opt_emalevel(CaDiCaLSolver *s, int emalevel) {
  if (emalevel < 1 || emalevel > 2000000000) {
    s->last_error = 240;
    return 240;
  }
  s->last_error = 0;
  return cadical_set_option(s, "emalevel", emalevel);
}

int cadical_set_opt_emasize(CaDiCaLSolver *s, int emasize) {
  if (emasize < 1 || emasize > 2000000000) {
    s->last_error = 241;
    return 241;
  }
  s->last_error = 0;
  return cadical_set_option(s, "emasize", emasize);
}

int cadical_set_opt_ematrailfast(CaDiCaLSolver *s, int ematrailfast) {
  if (ematrailfast < 1 || ematrailfast > 2000000000) {
    s->last_error = 242;
    return 242;
  }
  s->last_error = 0;
  return cadical_set_option(s, "ematrailfast", ematrailfast);
}

int cadical_set_opt_ematrailslow(CaDiCaLSolver *s, int ematrailslow) {
  if (ematrailslow < 1 || ematrailslow > 2000000000) {
    s->last_error = 243;
    return 243;
  }
  s->last_error = 0;
  return cadical_set_option(s, "ematrailslow", ematrailslow);
}

int cadical_set_opt_exteagerreasons(CaDiCaLSolver *s, int exteagerreasons) {
  s->last_error = 0;
  return cadical_set_option(s, "exteagerreasons", exteagerreasons);
}

int cadical_set_opt_exteagerrecalc(CaDiCaLSolver *s, int exteagerrecalc) {
  s->last_error = 0;
  return cadical_set_option(s, "exteagerrecalc", exteagerrecalc);
}

int cadical_set_opt_externallrat(CaDiCaLSolver *s, int externallrat) {
  s->last_error = 0;
  return cadical_set_option(s, "externallrat", externallrat);
}

int cadical_set_opt_flush(CaDiCaLSolver *s, int flush) {
  s->last_error = 0;
  return cadical_set_option(s, "flush", flush);
}

int cadical_set_opt_flushfactor(CaDiCaLSolver *s, int flushfactor) {
  if (flushfactor < 1 || flushfactor > 1000) {
    s->last_error = 244;
    return 244;
  }
  s->last_error = 0;
  return cadical_set_option(s, "flushfactor", flushfactor);
}

int cadical_set_opt_flushint(CaDiCaLSolver *s, int flushint) {
  if (flushint < 1 || flushint > 2000000000) {
    s->last_error = 245;
    return 245;
  }
  s->last_error = 0;
  return cadical_set_option(s, "flushint", flushint);
}

int cadical_set_opt_forcephase(CaDiCaLSolver *s, int forcephase) {
  s->last_error = 0;
  return cadical_set_option(s, "forcephase", forcephase);
}

int cadical_set_opt_frat(CaDiCaLSolver *s, int frat) {
  if (frat < 0 || frat > 2) {
    s->last_error = 246;
    return 246;
  }
  s->last_error = 0;
  return cadical_set_option(s, "frat", frat);
}

int cadical_set_opt_idrup(CaDiCaLSolver *s, int idrup) {
  s->last_error = 0;
  return cadical_set_option(s, "idrup", idrup);
}

int cadical_set_opt_ilb(CaDiCaLSolver *s, int ilb) {
  s->last_error = 0;
  return cadical_set_option(s, "ilb", ilb);
}

int cadical_set_opt_ilbassumptions(CaDiCaLSolver *s, int ilbassumptions) {
  s->last_error = 0;
  return cadical_set_option(s, "ilbassumptions", ilbassumptions);
}

int cadical_set_opt_inprocessing(CaDiCaLSolver *s, int inprocessing) {
  s->last_error = 0;
  return cadical_set_option(s, "inprocessing", inprocessing);
}

int cadical_set_opt_instantiate(CaDiCaLSolver *s, int instantiate) {
  s->last_error = 0;
  return cadical_set_option(s, "instantiate", instantiate);
}

int cadical_set_opt_instantiateclslim(CaDiCaLSolver *s, int instantiateclslim) {
  if (instantiateclslim < 2 || instantiateclslim > 2000000000) {
    s->last_error = 247;
    return 247;
  }
  s->last_error = 0;
  return cadical_set_option(s, "instantiateclslim", instantiateclslim);
}

int cadical_set_opt_instantiateocclim(CaDiCaLSolver *s, int instantiateocclim) {
  if (instantiateocclim < 1 || instantiateocclim > 2000000000) {
    s->last_error = 248;
    return 248;
  }
  s->last_error = 0;
  return cadical_set_option(s, "instantiateocclim", instantiateocclim);
}

int cadical_set_opt_instantiateonce(CaDiCaLSolver *s, int instantiateonce) {
  s->last_error = 0;
  return cadical_set_option(s, "instantiateonce", instantiateonce);
}

int cadical_set_opt_lidrup(CaDiCaLSolver *s, int lidrup) {
  s->last_error = 0;
  return cadical_set_option(s, "lidrup", lidrup);
}

int cadical_set_opt_log(CaDiCaLSolver *s, int log) {
  s->last_error = 0;
  return cadical_set_option(s, "log", log);
}

int cadical_set_opt_logsort(CaDiCaLSolver *s, int logsort) {
  s->last_error = 0;
  return cadical_set_option(s, "logsort", logsort);
}

int cadical_set_opt_lrat(CaDiCaLSolver *s, int lrat) {
  s->last_error = 0;
  return cadical_set_option(s, "lrat", lrat);
}

int cadical_set_opt_lucky(CaDiCaLSolver *s, int lucky) {
  s->last_error = 0;
  return cadical_set_option(s, "lucky", lucky);
}

int cadical_set_opt_minimize(CaDiCaLSolver *s, int minimize) {
  s->last_error = 0;
  return cadical_set_option(s, "minimize", minimize);
}

int cadical_set_opt_minimizedepth(CaDiCaLSolver *s, int minimizedepth) {
  if (minimizedepth < 0 || minimizedepth > 1000) {
    s->last_error = 249;
    return 249;
  }
  s->last_error = 0;
  return cadical_set_option(s, "minimizedepth", minimizedepth);
}

int cadical_set_opt_otfs(CaDiCaLSolver *s, int otfs) {
  s->last_error = 0;
  return cadical_set_option(s, "otfs", otfs);
}

int cadical_set_opt_phase(CaDiCaLSolver *s, int phase) {
  s->last_error = 0;
  return cadical_set_option(s, "phase", phase);
}

int cadical_set_opt_probe(CaDiCaLSolver *s, int probe) {
  s->last_error = 0;
  return cadical_set_option(s, "probe", probe);
}

int cadical_set_opt_probehbr(CaDiCaLSolver *s, int probehbr) {
  s->last_error = 0;
  return cadical_set_option(s, "probehbr", probehbr);
}

int cadical_set_opt_probeint(CaDiCaLSolver *s, int probeint) {
  if (probeint < 1 || probeint > 2000000000) {
    s->last_error = 250;
    return 250;
  }
  s->last_error = 0;
  return cadical_set_option(s, "probeint", probeint);
}

int cadical_set_opt_probemaxeff(CaDiCaLSolver *s, int probemaxeff) {
  if (probemaxeff < 0 || probemaxeff > 2000000000) {
    s->last_error = 251;
    return 251;
  }
  s->last_error = 0;
  return cadical_set_option(s, "probemaxeff", probemaxeff);
}

int cadical_set_opt_probemineff(CaDiCaLSolver *s, int probemineff) {
  if (probemineff < 0 || probemineff > 2000000000) {
    s->last_error = 252;
    return 252;
  }
  s->last_error = 0;
  return cadical_set_option(s, "probemineff", probemineff);
}

int cadical_set_opt_probereleff(CaDiCaLSolver *s, int probereleff) {
  if (probereleff < 1 || probereleff > 100000) {
    s->last_error = 253;
    return 253;
  }
  s->last_error = 0;
  return cadical_set_option(s, "probereleff", probereleff);
}

int cadical_set_opt_proberounds(CaDiCaLSolver *s, int proberounds) {
  if (proberounds < 1 || proberounds > 16) {
    s->last_error = 254;
    return 254;
  }
  s->last_error = 0;
  return cadical_set_option(s, "proberounds", proberounds);
}

int cadical_set_opt_profile(CaDiCaLSolver *s, int profile) {
  if (profile < 0 || profile > 4) {
    s->last_error = 255;
    return 255;
  }
  s->last_error = 0;
  return cadical_set_option(s, "profile", profile);
}

int cadical_set_opt_quiet(CaDiCaLSolver *s, int quiet) {
  s->last_error = 0;
  return cadical_set_option(s, "quiet", quiet);
}

int cadical_set_opt_radixsortlim(CaDiCaLSolver *s, int radixsortlim) {
  if (radixsortlim < 0 || radixsortlim > 2000000000) {
    s->last_error = 256;
    return 256;
  }
  s->last_error = 0;
  return cadical_set_option(s, "radixsortlim", radixsortlim);
}

int cadical_set_opt_realtime(CaDiCaLSolver *s, int realtime) {
  s->last_error = 0;
  return cadical_set_option(s, "realtime", realtime);
}

int cadical_set_opt_reduce(CaDiCaLSolver *s, int reduce) {
  s->last_error = 0;
  return cadical_set_option(s, "reduce", reduce);
}

int cadical_set_opt_reduceint(CaDiCaLSolver *s, int reduceint) {
  if (reduceint < 10 || reduceint > 1000000) {
    s->last_error = 257;
    return 257;
  }
  s->last_error = 0;
  return cadical_set_option(s, "reduceint", reduceint);
}

int cadical_set_opt_reducetarget(CaDiCaLSolver *s, int reducetarget) {
  if (reducetarget < 10 || reducetarget > 100) {
    s->last_error = 258;
    return 258;
  }
  s->last_error = 0;
  return cadical_set_option(s, "reducetarget", reducetarget);
}

int cadical_set_opt_reducetier1glue(CaDiCaLSolver *s, int reducetier1glue) {
  if (reducetier1glue < 1 || reducetier1glue > 2000000000) {
    s->last_error = 259;
    return 259;
  }
  s->last_error = 0;
  return cadical_set_option(s, "reducetier1glue", reducetier1glue);
}

int cadical_set_opt_reducetier2glue(CaDiCaLSolver *s, int reducetier2glue) {
  if (reducetier2glue < 1 || reducetier2glue > 2000000000) {
    s->last_error = 260;
    return 260;
  }
  s->last_error = 0;
  return cadical_set_option(s, "reducetier2glue", reducetier2glue);
}

int cadical_set_opt_reluctant(CaDiCaLSolver *s, int reluctant) {
  if (reluctant < 0 || reluctant > 2000000000) {
    s->last_error = 261;
    return 261;
  }
  s->last_error = 0;
  return cadical_set_option(s, "reluctant", reluctant);
}

int cadical_set_opt_reluctantmax(CaDiCaLSolver *s, int reluctantmax) {
  if (reluctantmax < 0 || reluctantmax > 2000000000) {
    s->last_error = 262;
    return 262;
  }
  s->last_error = 0;
  return cadical_set_option(s, "reluctantmax", reluctantmax);
}

int cadical_set_opt_rephase(CaDiCaLSolver *s, int rephase) {
  s->last_error = 0;
  return cadical_set_option(s, "rephase", rephase);
}

int cadical_set_opt_rephaseint(CaDiCaLSolver *s, int rephaseint) {
  if (rephaseint < 1 || rephaseint > 2000000000) {
    s->last_error = 263;
    return 263;
  }
  s->last_error = 0;
  return cadical_set_option(s, "rephaseint", rephaseint);
}

int cadical_set_opt_report(CaDiCaLSolver *s, int report) {
  s->last_error = 0;
  return cadical_set_option(s, "report", report);
}

int cadical_set_opt_reportall(CaDiCaLSolver *s, int reportall) {
  s->last_error = 0;
  return cadical_set_option(s, "reportall", reportall);
}

int cadical_set_opt_reportsolve(CaDiCaLSolver *s, int reportsolve) {
  s->last_error = 0;
  return cadical_set_option(s, "reportsolve", reportsolve);
}

int cadical_set_opt_restart(CaDiCaLSolver *s, int restart) {
  s->last_error = 0;
  return cadical_set_option(s, "restart", restart);
}

int cadical_set_opt_restartint(CaDiCaLSolver *s, int restartint) {
  if (restartint < 1 || restartint > 2000000000) {
    s->last_error = 264;
    return 264;
  }
  s->last_error = 0;
  return cadical_set_option(s, "restartint", restartint);
}

int cadical_set_opt_restartmargin(CaDiCaLSolver *s, int restartmargin) {
  if (restartmargin < 0 || restartmargin > 100) {
    s->last_error = 265;
    return 265;
  }
  s->last_error = 0;
  return cadical_set_option(s, "restartmargin", restartmargin);
}

int cadical_set_opt_restartreusetrail(CaDiCaLSolver *s, int restartreusetrail) {
  s->last_error = 0;
  return cadical_set_option(s, "restartreusetrail", restartreusetrail);
}

int cadical_set_opt_restoreall(CaDiCaLSolver *s, int restoreall) {
  if (restoreall < 0 || restoreall > 2) {
    s->last_error = 266;
    return 266;
  }
  s->last_error = 0;
  return cadical_set_option(s, "restoreall", restoreall);
}

int cadical_set_opt_restoreflush(CaDiCaLSolver *s, int restoreflush) {
  s->last_error = 0;
  return cadical_set_option(s, "restoreflush", restoreflush);
}

int cadical_set_opt_reverse(CaDiCaLSolver *s, int reverse) {
  s->last_error = 0;
  return cadical_set_option(s, "reverse", reverse);
}

int cadical_set_opt_score(CaDiCaLSolver *s, int score) {
  s->last_error = 0;
  return cadical_set_option(s, "score", score);
}

int cadical_set_opt_scorefactor(CaDiCaLSolver *s, int scorefactor) {
  if (scorefactor < 500 || scorefactor > 1000) {
    s->last_error = 267;
    return 267;
  }
  s->last_error = 0;
  return cadical_set_option(s, "scorefactor", scorefactor);
}

int cadical_set_opt_seed(CaDiCaLSolver *s, int seed) {
  if (seed < 0 || seed > 2000000000) {
    s->last_error = 268;
    return 268;
  }
  s->last_error = 0;
  return cadical_set_option(s, "seed", seed);
}

int cadical_set_opt_shrink(CaDiCaLSolver *s, int shrink) {
  if (shrink < 0 || shrink > 3) {
    s->last_error = 269;
    return 269;
  }
  s->last_error = 0;
  return cadical_set_option(s, "shrink", shrink);
}

int cadical_set_opt_shrinkreap(CaDiCaLSolver *s, int shrinkreap) {
  s->last_error = 0;
  return cadical_set_option(s, "shrinkreap", shrinkreap);
}

int cadical_set_opt_shuffle(CaDiCaLSolver *s, int shuffle) {
  s->last_error = 0;
  return cadical_set_option(s, "shuffle", shuffle);
}

int cadical_set_opt_shufflequeue(CaDiCaLSolver *s, int shufflequeue) {
  s->last_error = 0;
  return cadical_set_option(s, "shufflequeue", shufflequeue);
}

int cadical_set_opt_shufflerandom(CaDiCaLSolver *s, int shufflerandom) {
  s->last_error = 0;
  return cadical_set_option(s, "shufflerandom", shufflerandom);
}

int cadical_set_opt_shufflescores(CaDiCaLSolver *s, int shufflescores) {
  s->last_error = 0;
  return cadical_set_option(s, "shufflescores", shufflescores);
}

int cadical_set_opt_stabilize(CaDiCaLSolver *s, int stabilize) {
  s->last_error = 0;
  return cadical_set_option(s, "stabilize", stabilize);
}

int cadical_set_opt_stabilizefactor(CaDiCaLSolver *s, int stabilizefactor) {
  if (stabilizefactor < 101 || stabilizefactor > 2000000000) {
    s->last_error = 270;
    return 270;
  }
  s->last_error = 0;
  return cadical_set_option(s, "stabilizefactor", stabilizefactor);
}

int cadical_set_opt_stabilizeint(CaDiCaLSolver *s, int stabilizeint) {
  if (stabilizeint < 1 || stabilizeint > 2000000000) {
    s->last_error = 271;
    return 271;
  }
  s->last_error = 0;
  return cadical_set_option(s, "stabilizeint", stabilizeint);
}

int cadical_set_opt_stabilizemaxint(CaDiCaLSolver *s, int stabilizemaxint) {
  if (stabilizemaxint < 1 || stabilizemaxint > 2000000000) {
    s->last_error = 272;
    return 272;
  }
  s->last_error = 0;
  return cadical_set_option(s, "stabilizemaxint", stabilizemaxint);
}

int cadical_set_opt_stabilizeonly(CaDiCaLSolver *s, int stabilizeonly) {
  s->last_error = 0;
  return cadical_set_option(s, "stabilizeonly", stabilizeonly);
}

int cadical_set_opt_stats(CaDiCaLSolver *s, int stats) {
  s->last_error = 0;
  return cadical_set_option(s, "stats", stats);
}

int cadical_set_opt_subsume(CaDiCaLSolver *s, int subsume) {
  s->last_error = 0;
  return cadical_set_option(s, "subsume", subsume);
}

int cadical_set_opt_subsumebinlim(CaDiCaLSolver *s, int subsumebinlim) {
  if (subsumebinlim < 0 || subsumebinlim > 2000000000) {
    s->last_error = 273;
    return 273;
  }
  s->last_error = 0;
  return cadical_set_option(s, "subsumebinlim", subsumebinlim);
}

int cadical_set_opt_subsumeclslim(CaDiCaLSolver *s, int subsumeclslim) {
  if (subsumeclslim < 0 || subsumeclslim > 2000000000) {
    s->last_error = 274;
    return 274;
  }
  s->last_error = 0;
  return cadical_set_option(s, "subsumeclslim", subsumeclslim);
}

int cadical_set_opt_subsumeint(CaDiCaLSolver *s, int subsumeint) {
  if (subsumeint < 1 || subsumeint > 2000000000) {
    s->last_error = 275;
    return 275;
  }
  s->last_error = 0;
  return cadical_set_option(s, "subsumeint", subsumeint);
}

int cadical_set_opt_subsumelimited(CaDiCaLSolver *s, int subsumelimited) {
  s->last_error = 0;
  return cadical_set_option(s, "subsumelimited", subsumelimited);
}

int cadical_set_opt_subsumemaxeff(CaDiCaLSolver *s, int subsumemaxeff) {
  if (subsumemaxeff < 0 || subsumemaxeff > 2000000000) {
    s->last_error = 276;
    return 276;
  }
  s->last_error = 0;
  return cadical_set_option(s, "subsumemaxeff", subsumemaxeff);
}

int cadical_set_opt_subsumemineff(CaDiCaLSolver *s, int subsumemineff) {
  if (subsumemineff < 0 || subsumemineff > 2000000000) {
    s->last_error = 277;
    return 277;
  }
  s->last_error = 0;
  return cadical_set_option(s, "subsumemineff", subsumemineff);
}

int cadical_set_opt_subsumeocclim(CaDiCaLSolver *s, int subsumeocclim) {
  if (subsumeocclim < 0 || subsumeocclim > 2000000000) {
    s->last_error = 278;
    return 278;
  }
  s->last_error = 0;
  return cadical_set_option(s, "subsumeocclim", subsumeocclim);
}

int cadical_set_opt_subsumereleff(CaDiCaLSolver *s, int subsumereleff) {
  if (subsumereleff < 1 || subsumereleff > 100000) {
    s->last_error = 279;
    return 279;
  }
  s->last_error = 0;
  return cadical_set_option(s, "subsumereleff", subsumereleff);
}

int cadical_set_opt_subsumestr(CaDiCaLSolver *s, int subsumestr) {
  s->last_error = 0;
  return cadical_set_option(s, "subsumestr", subsumestr);
}

int cadical_set_opt_target(CaDiCaLSolver *s, int target) {
  if (target < 0 || target > 2) {
    s->last_error = 280;
    return 280;
  }
  s->last_error = 0;
  return cadical_set_option(s, "target", target);
}

int cadical_set_opt_terminateint(CaDiCaLSolver *s, int terminateint) {
  if (terminateint < 0 || terminateint > 10000) {
    s->last_error = 281;
    return 281;
  }
  s->last_error = 0;
  return cadical_set_option(s, "terminateint", terminateint);
}

int cadical_set_opt_ternary(CaDiCaLSolver *s, int ternary) {
  s->last_error = 0;
  return cadical_set_option(s, "ternary", ternary);
}

int cadical_set_opt_ternarymaxadd(CaDiCaLSolver *s, int ternarymaxadd) {
  if (ternarymaxadd < 0 || ternarymaxadd > 10000) {
    s->last_error = 282;
    return 282;
  }
  s->last_error = 0;
  return cadical_set_option(s, "ternarymaxadd", ternarymaxadd);
}

int cadical_set_opt_ternarymaxeff(CaDiCaLSolver *s, int ternarymaxeff) {
  if (ternarymaxeff < 0 || ternarymaxeff > 2000000000) {
    s->last_error = 283;
    return 283;
  }
  s->last_error = 0;
  return cadical_set_option(s, "ternarymaxeff", ternarymaxeff);
}

int cadical_set_opt_ternarymineff(CaDiCaLSolver *s, int ternarymineff) {
  if (ternarymineff < 1 || ternarymineff > 2000000000) {
    s->last_error = 284;
    return 284;
  }
  s->last_error = 0;
  return cadical_set_option(s, "ternarymineff", ternarymineff);
}

int cadical_set_opt_ternaryocclim(CaDiCaLSolver *s, int ternaryocclim) {
  if (ternaryocclim < 1 || ternaryocclim > 2000000000) {
    s->last_error = 285;
    return 285;
  }
  s->last_error = 0;
  return cadical_set_option(s, "ternaryocclim", ternaryocclim);
}

int cadical_set_opt_ternaryreleff(CaDiCaLSolver *s, int ternaryreleff) {
  if (ternaryreleff < 1 || ternaryreleff > 100000) {
    s->last_error = 286;
    return 286;
  }
  s->last_error = 0;
  return cadical_set_option(s, "ternaryreleff", ternaryreleff);
}

int cadical_set_opt_ternaryrounds(CaDiCaLSolver *s, int ternaryrounds) {
  if (ternaryrounds < 1 || ternaryrounds > 16) {
    s->last_error = 287;
    return 287;
  }
  s->last_error = 0;
  return cadical_set_option(s, "ternaryrounds", ternaryrounds);
}

int cadical_set_opt_transred(CaDiCaLSolver *s, int transred) {
  s->last_error = 0;
  return cadical_set_option(s, "transred", transred);
}

int cadical_set_opt_transredmaxeff(CaDiCaLSolver *s, int transredmaxeff) {
  if (transredmaxeff < 0 || transredmaxeff > 2000000000) {
    s->last_error = 288;
    return 288;
  }
  s->last_error = 0;
  return cadical_set_option(s, "transredmaxeff", transredmaxeff);
}

int cadical_set_opt_transredmineff(CaDiCaLSolver *s, int transredmineff) {
  if (transredmineff < 0 || transredmineff > 2000000000) {
    s->last_error = 289;
    return 289;
  }
  s->last_error = 0;
  return cadical_set_option(s, "transredmineff", transredmineff);
}

int cadical_set_opt_transredreleff(CaDiCaLSolver *s, int transredreleff) {
  if (transredreleff < 1 || transredreleff > 100000) {
    s->last_error = 290;
    return 290;
  }
  s->last_error = 0;
  return cadical_set_option(s, "transredreleff", transredreleff);
}

int cadical_set_opt_verbose(CaDiCaLSolver *s, int verbose) {
  if (verbose < 0 || verbose > 3) {
    s->last_error = 291;
    return 291;
  }
  s->last_error = 0;
  return cadical_set_option(s, "verbose", verbose);
}

int cadical_set_opt_veripb(CaDiCaLSolver *s, int veripb) {
  if (veripb < 0 || veripb > 4) {
    s->last_error = 292;
    return 292;
  }
  s->last_error = 0;
  return cadical_set_option(s, "veripb", veripb);
}

int cadical_set_opt_vivify(CaDiCaLSolver *s, int vivify) {
  s->last_error = 0;
  return cadical_set_option(s, "vivify", vivify);
}

int cadical_set_opt_vivifyinst(CaDiCaLSolver *s, int vivifyinst) {
  s->last_error = 0;
  return cadical_set_option(s, "vivifyinst", vivifyinst);
}

int cadical_set_opt_vivifymaxeff(CaDiCaLSolver *s, int vivifymaxeff) {
  if (vivifymaxeff < 0 || vivifymaxeff > 2000000000) {
    s->last_error = 293;
    return 293;
  }
  s->last_error = 0;
  return cadical_set_option(s, "vivifymaxeff", vivifymaxeff);
}

int cadical_set_opt_vivifymineff(CaDiCaLSolver *s, int vivifymineff) {
  if (vivifymineff < 0 || vivifymineff > 2000000000) {
    s->last_error = 294;
    return 294;
  }
  s->last_error = 0;
  return cadical_set_option(s, "vivifymineff", vivifymineff);
}

int cadical_set_opt_vivifyonce(CaDiCaLSolver *s, int vivifyonce) {
  if (vivifyonce < 0 || vivifyonce > 2) {
    s->last_error = 295;
    return 295;
  }
  s->last_error = 0;
  return cadical_set_option(s, "vivifyonce", vivifyonce);
}

int cadical_set_opt_vivifyredeff(CaDiCaLSolver *s, int vivifyredeff) {
  if (vivifyredeff < 0 || vivifyredeff > 1000) {
    s->last_error = 296;
    return 296;
  }
  s->last_error = 0;
  return cadical_set_option(s, "vivifyredeff", vivifyredeff);
}

int cadical_set_opt_vivifyreleff(CaDiCaLSolver *s, int vivifyreleff) {
  if (vivifyreleff < 1 || vivifyreleff > 100000) {
    s->last_error = 297;
    return 297;
  }
  s->last_error = 0;
  return cadical_set_option(s, "vivifyreleff", vivifyreleff);
}

int cadical_set_opt_walk(CaDiCaLSolver *s, int walk) {
  s->last_error = 0;
  return cadical_set_option(s, "walk", walk);
}

int cadical_set_opt_walkmaxeff(CaDiCaLSolver *s, int walkmaxeff) {
  if (walkmaxeff < 0 || walkmaxeff > 2000000000) {
    s->last_error = 298;
    return 298;
  }
  s->last_error = 0;
  return cadical_set_option(s, "walkmaxeff", walkmaxeff);
}

int cadical_set_opt_walkmineff(CaDiCaLSolver *s, int walkmineff) {
  if (walkmineff < 0 || walkmineff > 10000000) {
    s->last_error = 299;
    return 299;
  }
  s->last_error = 0;
  return cadical_set_option(s, "walkmineff", walkmineff);
}

int cadical_set_opt_walknonstable(CaDiCaLSolver *s, int walknonstable) {
  s->last_error = 0;
  return cadical_set_option(s, "walknonstable", walknonstable);
}

int cadical_set_opt_walkredundant(CaDiCaLSolver *s, int walkredundant) {
  s->last_error = 0;
  return cadical_set_option(s, "walkredundant", walkredundant);
}

int cadical_set_opt_walkreleff(CaDiCaLSolver *s, int walkreleff) {
  if (walkreleff < 1 || walkreleff > 100000) {
    s->last_error = 300;
    return 300;
  }
  s->last_error = 0;
  return cadical_set_option(s, "walkreleff", walkreleff);
}