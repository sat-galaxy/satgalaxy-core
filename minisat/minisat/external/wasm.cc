// #ifdef EMSCRIPTEN
// #include <emscripten.h>
// #include <stdio.h>
// EMSCRIPTEN_KEEPALIVE
// int minisat_solve() {
//     // // 简化解法接口
//     // SimpSolver solver;
//     // // 添加示例子句
//     // solver.addClause({1, 2, -3});
//     // return solver.solve();
//     return 0;
// }

//  int main(int argc, char const *argv[])
// {
//     printf("hello world\n");
//     return 0;
// }

// #endif
#include <emscripten/bind.h>
#include "minisat/utils/Options.h"
#include "wasm.h"


using namespace emscripten;


// 导出函数到 JavaScript
EMSCRIPTEN_BINDINGS(minisat)
{
    function("set_opt_var_decay", &Minisat::set_opt_var_decay);
    function("set_opt_clause_decay", &Minisat::set_opt_clause_decay);
    function("set_opt_random_var_freq", &Minisat::set_opt_random_var_freq);
    function("set_opt_random_seed", &Minisat::set_opt_random_seed);
    function("set_opt_ccmin_mode", &Minisat::set_opt_ccmin_mode);
    function("set_opt_phase_saving", &Minisat::set_opt_phase_saving);
    function("set_opt_rnd_init_act", &Minisat::set_opt_rnd_init_act);
    function("set_opt_luby_restart", &Minisat::set_opt_luby_restart);
    function("set_opt_restart_first", &Minisat::set_opt_restart_first);
    function("set_opt_restart_inc", &Minisat::set_opt_restart_inc);
    function("set_opt_garbage_frac", &Minisat::set_opt_garbage_frac);
    function("set_opt_min_learnts_lim", &Minisat::set_opt_min_learnts_lim);
    function("set_opt_clause_decay", &Minisat::set_opt_use_asymm);
    function("set_opt_use_asymm", &Minisat::set_opt_clause_decay);
    function("set_opt_use_rcheck", &Minisat::set_opt_use_rcheck);
    function("set_opt_use_elim", &Minisat::set_opt_use_elim);
    function("set_opt_grow", &Minisat::set_opt_grow);
    function("set_opt_clause_lim", &Minisat::set_opt_clause_lim);
    function("set_opt_subsumption_lim", &Minisat::set_opt_subsumption_lim);
    function("set_opt_simp_garbage_frac", &Minisat::set_opt_simp_garbage_frac);
     class_<MinisatSolver>("MinisatSolver")
        .constructor()
        .function("newVar", &MinisatSolver::newVar)
        .function("releaseVar", &MinisatSolver::releaseVar)
        .function("addClause", &MinisatSolver::addClause)
        .function("addEmptyClause", &MinisatSolver::addEmptyClause)
        .function("solve", select_overload<bool(const emscripten::val &, bool, bool)>(&MinisatSolver::solve))
        .function("solveLimited", select_overload<bool(const emscripten::val &, int, int)>(&MinisatSolver::solveLimited))
        .function("solve", select_overload<bool(bool, bool)>(&MinisatSolver::solve))
        .function("eliminate", &MinisatSolver::eliminate)
        .function("nAssigns", &MinisatSolver::nAssigns)
        .function("nClauses", &MinisatSolver::nClauses)
        .function("nVars", &MinisatSolver::nVars)
        .function("nFreeVars", &MinisatSolver::nFreeVars)
        .function("value", &MinisatSolver::value);

}

int main()
{
    return 0;
}