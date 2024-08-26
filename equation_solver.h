#ifndef _EQUATION_SOLVER_H_
#define _EQUATION_SOLVER_H_

#include "test.h"
#include "math_operator.h"

bool type_definer( const SquareEquationCoefficients *coefficients, Roots *cur_roots );
bool solve_square( const SquareEquationCoefficients *coefficients, Roots *cur_roots );
bool solve_linear( const SquareEquationCoefficients *coefficients, Roots *cur_roots );

#endif
