#include "equation_solver.h"
#include <math.h>

bool type_definer( EquationParameters *equation_parameters )
{
    assert( &equation_parameters->coefficients != NULL);

    if ( compare_with_zero( equation_parameters->coefficients.a ) )
    {
        if ( compare_with_zero( equation_parameters->coefficients.b ) )
        {
            equation_parameters->cur_roots.number_of_roots = compare_with_zero( equation_parameters->coefficients.c ) ? SS_INF_ROOTS : ZERO_ROOTS;
            return solver_ok;
        }
        else
        {
            solve_linear( equation_parameters );
            equation_parameters->cur_roots.number_of_roots = ONE_ROOT;
            return solver_ok;
        }
    }
    else if ( compare_with_zero( equation_parameters->coefficients.c ) &&
            ( compare_with_zero( equation_parameters->coefficients.b ) == false) )
    {
        solve_linear( equation_parameters );
        equation_parameters->cur_roots.x1 = 0;
        equation_parameters->cur_roots.number_of_roots = TWO_ROOTS;
        return solver_ok;
    }
    else
    {
        solve_square( equation_parameters );
        return solver_ok;
    }
    return solver_fail;
}

bool solve_square( EquationParameters *equation_parameters )
{
    assert( &equation_parameters->coefficients != NULL);
    assert( &equation_parameters->cur_roots != NULL);

    double d = equation_parameters->coefficients.b * equation_parameters->coefficients.b - 4 * equation_parameters->coefficients.a * equation_parameters->coefficients.c;

    if (compare_with_zero(d))
    {
        equation_parameters->cur_roots.x1 = equation_parameters->cur_roots.x2 = -equation_parameters->coefficients.b / ( 2 * equation_parameters->coefficients.a );
        equation_parameters->cur_roots.number_of_roots = ONE_ROOT;
        return solver_ok;
    }
    else if (d > EPSILON)
    {
        double sqrt_d = sqrt(d);

        equation_parameters->cur_roots.x1 = ( -equation_parameters->coefficients.b - sqrt_d ) / ( 2 * equation_parameters->coefficients.a );
        equation_parameters->cur_roots.x2 = ( -equation_parameters->coefficients.b + sqrt_d ) / ( 2 * equation_parameters->coefficients.a );
        equation_parameters->cur_roots.number_of_roots = TWO_ROOTS;
        return solver_ok;
    }
    else
    {
        equation_parameters->cur_roots.number_of_roots = ZERO_ROOTS;
        return solver_ok;
    }
    return solver_fail;
}

bool solve_linear( EquationParameters *equation_parameters )
{
   equation_parameters->cur_roots.x1 = NAN;
   equation_parameters->cur_roots.x2 = -equation_parameters->coefficients.c / equation_parameters->coefficients.b;
   equation_parameters->cur_roots.number_of_roots = ONE_ROOT;
   return solver_ok;
}
