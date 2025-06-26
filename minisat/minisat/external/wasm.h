#pragma once
#include <emscripten/val.h>
#include "minisat/simp/SimpSolver.h"
#include <vector>

Minisat::Lit makeLit(Minisat::SimpSolver *solver, int val)
{
    int value = abs(val) - 1;
    while (value >= solver->nVars())
    {
        solver->newVar();
    }
    return Minisat::mkLit(value, val < 0);
}
class MinisatSolver
{
private:
    Minisat::SimpSolver *inner;

public:
    MinisatSolver()
    {
        inner = new Minisat::SimpSolver();
    }
    ~MinisatSolver()
    {
        delete inner;
    }
    int newVar()
    {
        return inner->newVar();
    }
    void releaseVar(int l)
    {
        inner->releaseVar(makeLit(inner, l));
    }
    int addClause(const emscripten::val &jsArray)
    {
        if (!jsArray.isArray())
        {
            throw std::runtime_error("Expected a JavaScript array");
        }
        size_t len = jsArray["length"].as<size_t>();
        Minisat::vec<Minisat::Lit> lits;
        for (unsigned long i = 0; i < len; i++)
        {
            lits.push(makeLit(inner, jsArray[i].as<int>()));
        }
        return inner->addClause(lits);
    }
    int addEmptyClause()
    {
        return inner->addEmptyClause();
    }
    bool solve(const emscripten::val &jsArray, bool do_simp, bool turn_off_simp)
    {
        if (!jsArray.isArray())
        {
            throw std::runtime_error("Expected a JavaScript array");
        }
        size_t len = jsArray["length"].as<size_t>();
        Minisat::vec<Minisat::Lit> assumps;
        for (unsigned long i = 0; i < len; i++)
        {
            assumps.push(makeLit(inner, jsArray[i].as<int>()));
        }
        return inner->solve(assumps, do_simp, turn_off_simp);
    }
    bool solveLimited(const emscripten::val &jsArray, int do_simp, int turn_off_simp)
    {
               if (!jsArray.isArray())
        {
            throw std::runtime_error("Expected a JavaScript array");
        }
        size_t len = jsArray["length"].as<size_t>();
        Minisat::vec<Minisat::Lit> assumps;
        for (unsigned long i = 0; i < len; i++)
        {
            assumps.push(makeLit(inner, jsArray[i].as<int>()));
        }
        return inner->solveLimited(assumps, do_simp, turn_off_simp)== Minisat::l_True;
    }
    bool solve(bool do_simp, bool turn_off_simp)
    {
        return inner->solve(do_simp, turn_off_simp);
    }
    bool eliminate(bool turn_off_elim)
    {
        return inner->eliminate(turn_off_elim);
    }
    int nAssigns()
    {
        return inner->nAssigns();
    }
    int nClauses()
    {
        return inner->nClauses();
    }
    int nVars()
    {
        return inner->nVars();
    }
    int nFreeVars()
    {
        return inner->nFreeVars();
    }
    bool value(int x)
    {
        return inner->value(x)== Minisat::l_True;
    }
};
