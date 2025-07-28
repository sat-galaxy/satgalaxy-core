
#include "satgalaxy_glucose.h"
#include "simp/SimpSolver.h"
#include "utils/Options.h"

#define GLUCOSE_G_OPT(NAME, TY, COND, CODE)     \
    int glucose_set_global_opt_##NAME(TY value) \
    {                                           \
        if (COND)                               \
        {                                       \
            return CODE;                        \
        }                                       \
        Glucose::set_opt_##NAME(value);         \
        return 0;                               \
    }

#define GLUCOSE_OPT(NAME, FD, TY, COND, CODE)                   \
    GLUCOSE_G_OPT(NAME, TY, COND, CODE)                         \
                                                                \
    int glucose_set_opt_##NAME(GlucoseSolver *solver, TY value) \
    {                                                           \
        if (COND)                                               \
        {                                                       \
            return CODE;                                        \
        }                                                       \
        solver->solver->FD == value;                            \
        return 0;                                               \
    }

#ifdef ERRORJUMP
#include <csetjmp>
#define CALL_FN(rv, func, ...)                   \
    do                                           \
    {                                            \
        int code = setjmp(*s->solver->jmp_env);  \
        s->last_error = code;                    \
        if (code)                                \
        {                                        \
            return rv;                           \
        }                                        \
        else                                     \
        {                                        \
            return s->solver->func(__VA_ARGS__); \
        }                                        \
    } while (0)
#else
#define CALL_FN(rv, func, ...) return s->solver->func(__VA_ARGS__)
#endif

struct GlucoseSolver
{
    Glucose::SimpSolver *solver;
    int last_error;
};

Glucose::Lit make_lit(Glucose::SimpSolver *solver, int val)
{
    int value = abs(val) - 1;
    while (value >= solver->nVars())
    {
        solver->newVar();
    }
    return Glucose::mkLit(value, val < 0);
}
GlucoseSolver *glucose_new_solver()
{
    GlucoseSolver *s = new GlucoseSolver();
    s->solver = new Glucose::SimpSolver();
    s->last_error = 0;
    return s;
}
void glucose_destroy(GlucoseSolver *s)
{
    delete s->solver;
    delete s;
}
int glucose_new_var(GlucoseSolver *s)
{
    CALL_FN(0, newVar, true, true);
}

int glucose_add_clause(GlucoseSolver *s, const int ps[], unsigned long length)
{
    Glucose::vec<Glucose::Lit> lits;
    for (unsigned long i = 0; i < length; i++)
    {
        lits.push(make_lit(s->solver, ps[i]));
    }
    CALL_FN(0, addClause, lits);
}
int glucose_add_empty_clause(GlucoseSolver *s)
{
    CALL_FN(0, addEmptyClause);
}

int glucose_solve_assumps(GlucoseSolver *s, const int ps[], unsigned long length, int do_simp, int turn_off_simp)
{
    Glucose::vec<Glucose::Lit> lits;
    for (unsigned long i = 0; i < length; i++)
    {
        lits.push(make_lit(s->solver, ps[i]));
    }
    CALL_FN(0, solve, lits, (bool)do_simp, (bool)turn_off_simp);
}

int glucose_solve_limited(GlucoseSolver *s, const int ps[], unsigned long length, int do_simp, int turn_off_simp)
{

#ifdef ERRORJUMP
    int code = setjmp(*s->solver->jmp_env);
    s->last_error = code;
    if (code)
    {
        return 0;
    }
    else
    {
#endif
        Glucose::vec<Glucose::Lit> lits;
        for (unsigned long i = 0; i < length; i++)
        {
            lits.push(make_lit(s->solver, ps[i]));
        }
        return (Glucose::toInt(s->solver->solveLimited(lits, (bool)do_simp, (bool)turn_off_simp)) + 1) * 10;
#ifdef ERRORJUMP
    }
#endif
}

int glucose_solve(GlucoseSolver *s, int do_simp, int turn_off_simp)
{
    CALL_FN(0, solve, (bool)do_simp, (bool)turn_off_simp);
}

int glucose_eliminate(GlucoseSolver *s, int turn_off_elim)
{
    CALL_FN(0, eliminate, (bool)turn_off_elim);
}

int glucose_nassigns(GlucoseSolver *s)
{
    CALL_FN(0, nAssigns);
}
int glucose_nclauses(GlucoseSolver *s)
{
    CALL_FN(0, nClauses);
}
int glucose_nlearnts(GlucoseSolver *s)
{
    CALL_FN(0, nLearnts);
}
int glucose_nvars(GlucoseSolver *s)
{
    CALL_FN(0, nVars);
}
int glucose_nfree_vars(GlucoseSolver *s)
{
    CALL_FN(0, nFreeVars);
}
int glucose_value(GlucoseSolver *s, int val)
{
#ifdef ERRORJUMP
    int code = setjmp(*s->solver->jmp_env);
    s->last_error = code;
    if (code)
    {
        return 0;
    }
    else
    {
#endif
        int abs_val = abs(val);
        Glucose::SimpSolver *solver = s->solver;
        if (abs_val == 0 || abs_val > solver->nVars())
        {
            return 0;
        }
        return ((val < 0) ^ (solver->value(abs_val - 1) == l_True));
#ifdef ERRORJUMP
    }
#endif
}
int glucose_model_value(GlucoseSolver *s, int val)
{
#ifdef ERRORJUMP
    int code = setjmp(*s->solver->jmp_env);
    s->last_error = code;
    if (code)
    {
        return 0;
    }
    else
    {
#endif
        int abs_val = abs(val);

        Glucose::SimpSolver *solver = s->solver;
        if (abs_val == 0 || abs_val > solver->nVars())
        {
            return 0;
        }
        return (int)(((val < 0) ^ solver->model[abs_val - 1] == l_True));
#ifdef ERRORJUMP
    }
#endif
}
int glucose_okay(GlucoseSolver *s)
{
    CALL_FN(0, okay, );
}
const char *glucose_error_msg(int code)
{
    switch (code)
    {
    case 100:
        return "K must be in (0, 1)";
    case 101:
        return "R must be at least 10";
    case 102:
        return "size_lbd_queue must be at least 10";
    case 103:
        return "size_trail_queue must be at least 10";
    case 104:
        return "first_reduce_db must be a non-negative integer";
    case 105:
        return "inc_reduce_db must be a non-negative integer";
    case 106:
        return "spec_inc_reduce_db must be a non-negative integer";
    case 107:
        return "lb_lbd_frozen_clause must be a non-negative integer";
    case 108:
        return "chanseok_limit must be a positive integer greater than 1";
    case 109:
        return "lb_size_minimzing_clause must be at least 3";
    case 110:
        return "var_decay must in (0,1)";
    case 111:
        return "max_var_decay must be in (0,1)";
    case 112:
        return "clause_decay must be in (0,1)";
    case 113:
        return "random_var_freq  must be in [0, 1]";
    case 114:
        return "random_seed must be positive";
    case 115:
        return "ccmin_mode must be  0, 1, or 2";
    case 116:
        return "phase_saving  must be 0, 1, or 2";
    case 117:
        return "garbage_frac must >0";
    case 118:
        return "restart_inc must >=1.0";
    case 119:
        return "luby_restart_factor must >=1";
    case 120:
        return "randomize_phase must be 0-3";
    case 121:
        return "grow must >=0";
    case 122:
        return "clause_lim must >=-1";
    case 123:
        return "subsumption_lim must >=-1";
    case 124:
        return "simp_garbage_frac must >0";
    case 125:
        return "verbosity must be 0-2";
    case 200:
        return "file write error: could not write to file";
    case 201:
        return "trying to set incremental mode, but not compiled properly for this";
    case 202:
        return "can not use incremental and certified unsat in the same time";
    default:
        return "Unknown error";
    }
}
GLUCOSE_OPT(K, K, double, value <= 0 || value >= 1, 100)
GLUCOSE_OPT(R, R, double, value <= 0 || value >= 5, 101)
GLUCOSE_OPT(size_lbd_queue, sizeLBDQueue, int, value < 10, 102)
GLUCOSE_OPT(size_trail_queue, sizeTrailQueue, int, value < 0, 103)
GLUCOSE_OPT(first_reduce_db, firstReduceDB, int, value < 0, 104)
GLUCOSE_OPT(inc_reduce_db, incReduceDB, int, value < 0, 105)
GLUCOSE_G_OPT(spec_inc_reduce_db, int, value < 0, 106)
GLUCOSE_OPT(lb_lbd_frozen_clause, lbLBDFrozenClause, int, value < 0, 107)
GLUCOSE_G_OPT(chanseok_hack, int, 0, 0)
GLUCOSE_OPT(chanseok_limit, coLBDBound, int, value < 2, 108)
GLUCOSE_OPT(lb_size_minimzing_clause, lbSizeMinimizingClause,int, value < 3, 109)
GLUCOSE_OPT(lb_lbd_minimzing_clause, lbLBDMinimizingClause,int, value < 3, 109)
GLUCOSE_OPT(lcm, useLCM,int, 0, 0)
GLUCOSE_OPT(lcm_update_lbd, LCMUpdateLBD,int, 0, 0)
GLUCOSE_OPT(var_decay,var_decay, double, value >= 1 || value <= 0, 110)
GLUCOSE_OPT(max_var_decay,max_var_decay, double, value >= 1 || value <= 0, 111)
GLUCOSE_OPT(clause_decay,clause_decay, double, value >= 1 || value <= 0, 112)
GLUCOSE_OPT(random_var_freq,random_var_freq, double, value > 1 || value < 0, 113)
GLUCOSE_OPT(random_seed,random_seed, double, value <= 0, 114)
GLUCOSE_OPT(ccmin_mode,ccmin_mode, int, value < 0 || value > 2, 115)
GLUCOSE_OPT(phase_saving,phase_saving, int, value < 0 || value > 2, 116)
GLUCOSE_OPT(rnd_init_act,rnd_init_act, int, 0, 0)
GLUCOSE_OPT(garbage_frac,garbage_frac, double, value <= 0, 117)
GLUCOSE_G_OPT(glu_reduction, int, 0, 0)
GLUCOSE_G_OPT(luby_restart, int, 0, 0)
GLUCOSE_G_OPT(restart_inc, double, value < 1, 118)
GLUCOSE_G_OPT(luby_restart_factor, int, value < 1, 119)
GLUCOSE_G_OPT(randomize_phase_on_restarts, int, value < 0 || value > 3, 120)
GLUCOSE_G_OPT(fixed_randomize_phase_on_restarts, int, 0, 0)
GLUCOSE_G_OPT(adapt, int, 0, 0)
GLUCOSE_G_OPT(forceunsat, int, 0, 0)
GLUCOSE_OPT(use_asymm,use_asymm, int, 0, 0)
GLUCOSE_OPT(use_rcheck,use_rcheck, int, 0, 0)
GLUCOSE_OPT(use_elim,use_elim, int, 0, 0)
GLUCOSE_OPT(grow,grow, int, value < 0, 121)
GLUCOSE_OPT(clause_lim,clause_lim, int, value < -1, 122)
GLUCOSE_OPT(subsumption_lim,subsumption_lim, int, value < -1, 123)
GLUCOSE_OPT(simp_garbage_frac,simp_garbage_frac, double, value <= 0, 124)
GLUCOSE_OPT(verbosity,verbosity, int, value < 0 || value > 2, 125)
