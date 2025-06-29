#include "Options.h"

using namespace Glucose;

double Glucose::opt_K = 0.8;
double Glucose::opt_R = 1.4;
int Glucose::opt_size_lbd_queue = 50;
int Glucose::opt_size_trail_queue = 5000;

int Glucose::opt_first_reduce_db = 2000;
int Glucose::opt_inc_reduce_db = 300;
int Glucose::opt_spec_inc_reduce_db = 1000;
int Glucose::opt_lb_lbd_frozen_clause = 30;
bool Glucose::opt_chanseok_hack = false;
int Glucose::opt_chanseok_limit = 5;

int Glucose::opt_lb_size_minimzing_clause = 30;
int Glucose::opt_lb_lbd_minimzing_clause = 6;
bool Glucose::opt_lcm = true;
bool Glucose::opt_lcm_update_lbd = false;

double Glucose::opt_var_decay = 0.8;
double Glucose::opt_max_var_decay = 0.95;
double Glucose::opt_clause_decay = 0.999;
double Glucose::opt_random_var_freq = 0;
double Glucose::opt_random_seed = 91648253;
int Glucose::opt_ccmin_mode = 2; // 0=none, 1=basic, 2=deep
int Glucose::opt_phase_saving = 0;
bool Glucose::opt_rnd_init_act = false;
double Glucose::opt_garbage_frac = 0.1;
bool Glucose::opt_glu_reduction = true;
bool Glucose::opt_luby_restart = false;
double Glucose::opt_restart_inc = 1.5;
int Glucose::opt_luby_restart_factor = 100;

int Glucose::opt_randomize_phase_on_restarts = 0;
bool Glucose::opt_fixed_randomize_phase_on_restarts = false;

bool Glucose::opt_adapt = true;

bool Glucose::opt_forceunsat = true;

bool Glucose::opt_use_asymm = false;
bool Glucose::opt_use_rcheck = false;
bool Glucose::opt_use_elim = true;
int Glucose::opt_grow = 0; // 0 means no grow, >0 means grow by this many clauses
int Glucose::opt_clause_lim = 20;
int Glucose::opt_subsumption_lim = 1000;
double Glucose::opt_simp_garbage_frac = 0.5;
int Glucose::opt_verbosity = 1; // 0=silent, 1=some, 2=verbose

void Glucose::set_opt_K(double value)
{
    opt_K = value;
}

void Glucose::set_opt_R(double value)
{
    opt_R = value;
}

void Glucose::set_opt_size_lbd_queue(int value)
{
    opt_size_lbd_queue = value;
}

void Glucose::set_opt_size_trail_queue(int value)
{
    opt_size_trail_queue = value;
}

void Glucose::set_opt_first_reduce_db(int value)
{
    opt_first_reduce_db = value;
}

void Glucose::set_opt_inc_reduce_db(int value)
{
    opt_inc_reduce_db = value;
}

void Glucose::set_opt_spec_inc_reduce_db(int value)
{
    opt_spec_inc_reduce_db = value;
}

void Glucose::set_opt_lb_lbd_frozen_clause(int value)
{
    opt_lb_lbd_frozen_clause = value;
}

void Glucose::set_opt_chanseok_hack(bool value)
{
    opt_chanseok_hack = value;
}

void Glucose::set_opt_chanseok_limit(int value)
{
    opt_chanseok_limit = value;
}

void Glucose::set_opt_lb_size_minimzing_clause(int value)
{
    opt_lb_size_minimzing_clause = value;
}

void Glucose::set_opt_lb_lbd_minimzing_clause(int value)
{
    opt_lb_lbd_minimzing_clause = value;
}

void Glucose::set_opt_lcm(bool value)
{
    opt_lcm = value;
}

void Glucose::set_opt_lcm_update_lbd(bool value)
{
    opt_lcm_update_lbd = value;
}

void Glucose::set_opt_var_decay(double value)
{
    opt_var_decay = value;
}

void Glucose::set_opt_max_var_decay(double value)
{
    opt_max_var_decay = value;
}

void Glucose::set_opt_clause_decay(double value)
{
    opt_clause_decay = value;
}

void Glucose::set_opt_random_var_freq(double value)
{
    opt_random_var_freq = value;
}

void Glucose::set_opt_random_seed(double value)
{
    opt_random_seed = value;
}

void Glucose::set_opt_ccmin_mode(int value)
{
    opt_ccmin_mode = value;
}

void Glucose::set_opt_phase_saving(int value)
{
    opt_phase_saving = value;
}

void Glucose::set_opt_rnd_init_act(bool value)
{
    opt_rnd_init_act = value;
}

void Glucose::set_opt_garbage_frac(double value)
{
    opt_garbage_frac = value;
}

void Glucose::set_opt_glu_reduction(bool value)
{
    opt_glu_reduction = value;
}

void Glucose::set_opt_luby_restart(bool value)
{
    opt_luby_restart = value;
}

void Glucose::set_opt_restart_inc(double value)
{
    opt_restart_inc = value;
}

void Glucose::set_opt_luby_restart_factor(int value)
{
    opt_luby_restart_factor = value;
}

void Glucose::set_opt_randomize_phase_on_restarts(int value)
{
    opt_randomize_phase_on_restarts = value;
}

void Glucose::set_opt_fixed_randomize_phase_on_restarts(bool value)
{
    opt_fixed_randomize_phase_on_restarts = value;
}

void Glucose::set_opt_adapt(bool value)
{
    opt_adapt = value;
}

void Glucose::set_opt_forceunsat(bool value)
{
    opt_forceunsat = value;
}

void Glucose::set_opt_use_asymm(bool value)
{
    opt_use_asymm = value;
}

void Glucose::set_opt_use_rcheck(bool value)
{
    opt_use_rcheck = value;
}

void Glucose::set_opt_use_elim(bool value)
{
    opt_use_elim = value;
}

void Glucose::set_opt_grow(int value)
{
    opt_grow = value;
}

void Glucose::set_opt_clause_lim(int value)
{
    opt_clause_lim = value;
}

void Glucose::set_opt_subsumption_lim(int value)
{
    opt_subsumption_lim = value;
}

void Glucose::set_opt_simp_garbage_frac(double value)
{
    opt_simp_garbage_frac = value;
}

void Glucose::set_opt_verbosity(int value)
{
    opt_verbosity = value;
}