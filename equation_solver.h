#ifndef _EQUATION_SOLVER_H_
#define _EQUATION_SOLVER_H_

#include "math_operator.h"

struct SquareEquationCoefficients
{
    double a;
    double b;
    double c;
};

struct Roots
{
    double x1;
    double x2;

    int number_of_roots;
};

enum SolveStatus
{
    SOLVER_FAIL = 0,
    SOLVER_OK = 1,
    PROGRAM_ERROR = 0
};

enum NumberOfRoots
{
    ZERO_ROOTS   =  0,
    ONE_ROOT     =  1,
    TWO_ROOTS    =  2,
    SS_INF_ROOTS = -1
};

SolveStatus define_type_of_equation( const SquareEquationCoefficients *coefficients, Roots *cur_roots );
SolveStatus solve_square( const SquareEquationCoefficients *coefficients, Roots *cur_roots );
SolveStatus solve_linear( const SquareEquationCoefficients *coefficients, Roots *cur_roots );
SolveStatus specific_case_of_equation( const SquareEquationCoefficients *coefficients, Roots *cur_roots );

#endif
