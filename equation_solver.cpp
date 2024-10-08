#include <assert.h>
#include <stdio.h>
#include <math.h>

#include "equation_solver.h"

SolveStatus define_type_of_equation( const SquareEquationCoefficients *coefficients, Roots *cur_roots )
{
    assert( coefficients != NULL );
    assert( cur_roots != NULL);

    if ( specific_case_of_equation( coefficients, cur_roots ) == SOLVER_OK )
        return SOLVER_OK;

    if ( solve_square( coefficients, cur_roots ) == SOLVER_OK )
        return SOLVER_OK;

    return SOLVER_FAIL;
}

SolveStatus solve_square( const SquareEquationCoefficients *coefficients, Roots *cur_roots )
{
    assert( coefficients != NULL );
    assert( cur_roots != NULL );

    double coeff_a = coefficients->a;
    double coeff_b = coefficients->b;
    double coeff_c = coefficients->c;

    double discriminant = coeff_b * coeff_b - 4 * coeff_a * coeff_c;

    if ( compare_with_zero( discriminant ) )
    {
        cur_roots->x1 = -coeff_b / ( 2 * coeff_a );
        cur_roots->x2 = NAN;
        cur_roots->number_of_roots = ONE_ROOT;

        return SOLVER_OK;
    }
    else if ( discriminant > EPSILON )
    {
        double sqrt_discriminant = sqrt( discriminant );

        cur_roots->x1 = ( -coeff_b - sqrt_discriminant ) / ( 2 * coeff_a );
        cur_roots->x2 = ( -coeff_b + sqrt_discriminant ) / ( 2 * coeff_a );
        cur_roots->number_of_roots = TWO_ROOTS;

        return SOLVER_OK;
    }
    else
    {
        cur_roots->number_of_roots = ZERO_ROOTS;

        return SOLVER_OK;
    }

    return SOLVER_FAIL;
}

SolveStatus solve_linear( const SquareEquationCoefficients *coefficients, Roots *cur_roots )
{
    assert( cur_roots != NULL );
    assert( coefficients != NULL );

    cur_roots->x1 = -coefficients->c / coefficients->b;
    cur_roots->x2 = NAN;
    cur_roots->number_of_roots = ONE_ROOT;

    return SOLVER_OK;
}

SolveStatus specific_case_of_equation( const SquareEquationCoefficients *coefficients, Roots *cur_roots )
{
    assert( coefficients != NULL );
    assert( cur_roots != NULL );

    double coeff_a = coefficients->a;
    double coeff_b = coefficients->b;
    double coeff_c = coefficients->c;

    if ( compare_with_zero( coeff_a ) )
    {
        if ( compare_with_zero( coeff_b ) )
        {
            cur_roots->number_of_roots = compare_with_zero( coeff_c ) ? SS_INF_ROOTS : ZERO_ROOTS;
            return SOLVER_OK;
        }
        else
        {
            solve_linear( coefficients, cur_roots );
            return SOLVER_OK;
        }
    }
    else if ( compare_with_zero( coeff_c ) && ( !compare_with_zero( coeff_b ) ) )
    {
        solve_linear( coefficients, cur_roots );
        cur_roots->x2 = 0;
        cur_roots->number_of_roots = TWO_ROOTS;
        return SOLVER_OK;
    }

    return SOLVER_FAIL;
}

