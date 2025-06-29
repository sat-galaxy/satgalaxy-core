#include "Options.h"

using namespace Minisat;

double Minisat::opt_var_decay = 0.95;        // The variable activity decay factor
double Minisat::opt_clause_decay = 0.999;    // The clause activity decay factor
double Minisat::opt_random_var_freq = 0;     // The frequency with which the decision heuristic tries to choose a random variable
double Minisat::opt_random_seed = 91648253;  // Used by the random variable selection
int Minisat::opt_ccmin_mode = 2;             // Controls conflict clause minimization (0=none, 1=basic, 2=deep)
int Minisat::opt_phase_saving = 2;           // Controls the level of phase saving (0=none, 1=limited, 2=full)
bool Minisat::opt_rnd_init_act = false;      // Randomize the initial activity
bool Minisat::opt_luby_restart = true;       // Use the Luby restart sequence
int Minisat::opt_restart_first = 100;        // The base restart interval
double Minisat::opt_restart_inc = 2;         // Restart interval increase factor
double Minisat::opt_garbage_frac = 0.20;     // The fraction of wasted memory allowed before a garbage collection is triggered
int Minisat::opt_min_learnts_lim = 0;        // Minimum learnt clause limit
bool Minisat::opt_use_asymm = false;         // Shrink clauses by asymmetric branching.
bool Minisat::opt_use_rcheck = false;        // Check if a clause is already implied. (costly)
bool Minisat::opt_use_elim = true;           // Perform variable elimination.
int Minisat::opt_grow = 0;                   // Allow a variable elimination step to grow by a number of clauses.
int Minisat::opt_clause_lim = 20;            // Variables are not eliminated if it produces a resolvent with a length above this limit. -1 means no limit
int Minisat::opt_subsumption_lim = 1000;     // Do not check if subsumption against a clause larger than this. -1 means no limit.
double Minisat::opt_simp_garbage_frac = 0.5; // The fraction of wasted memory allowed before a garbage collection is triggered during simplification.
int Minisat::opt_verbosity =0; // 0=silent, 1=some, 2=verbose

void Minisat::set_opt_var_decay(double decay){
    opt_var_decay = decay;
}
void Minisat::set_opt_clause_decay(double decay){
    opt_clause_decay = decay;
}
void Minisat::set_opt_random_var_freq(double freq){
    opt_random_var_freq = freq;
}
void Minisat::set_opt_random_seed(double seed){
    opt_random_seed = seed;
}
void Minisat::set_opt_ccmin_mode(int mode){
    opt_ccmin_mode = mode;
}
void Minisat::set_opt_phase_saving(int mode){
    opt_phase_saving = mode;
}
void Minisat::set_opt_rnd_init_act(bool flag){
    opt_rnd_init_act = flag;
}
void Minisat::set_opt_luby_restart(bool flag){
    opt_luby_restart = flag;
}
void Minisat::set_opt_restart_first(int restart_first){
    opt_restart_first = restart_first;
}
void Minisat::set_opt_restart_inc(double restart_inc){
    opt_restart_inc = restart_inc;
}
void Minisat::set_opt_garbage_frac(double garbage_frac){
    opt_garbage_frac = garbage_frac;
}
void Minisat::set_opt_min_learnts_lim(int min_learnts_lim){
    opt_min_learnts_lim = min_learnts_lim;
}
void Minisat::set_opt_use_asymm(bool opt_use_asymm){
    opt_use_asymm = opt_use_asymm;
}
void Minisat::set_opt_use_rcheck(bool opt_use_rcheck){
    opt_use_rcheck = opt_use_rcheck;
}
void Minisat::set_opt_use_elim(bool opt_use_elim){
    opt_use_elim = opt_use_elim;
}
void Minisat::set_opt_grow(int opt_grow){
    opt_grow = opt_grow;
}
void Minisat::set_opt_clause_lim(int opt_clause_lim){
    opt_clause_lim = opt_clause_lim;
}
void Minisat::set_opt_subsumption_lim(int opt_subsumption_lim){
    opt_subsumption_lim = opt_subsumption_lim;
}
void Minisat::set_opt_simp_garbage_frac(double opt_simp_garbage_frac){
    opt_simp_garbage_frac = opt_simp_garbage_frac;
}
void Minisat::set_opt_verbosity(int opt_verbosity){
    opt_verbosity = opt_verbosity;
}
