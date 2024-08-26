//#define  TX_COMPILED
#include "TXLib.h"
#include <assert.h>
#include <stdio.h>

#include "test.h"
#include "equation_solver.h"
#include "math_operator.h"
#include "print_roots.h"
#include "input_file.h"

int run_test( const test_data *data )
{
    assert( data != NULL );

    Roots cur_roots = {};

    type_definer( &data->coefficients, &cur_roots );
    define_number_of_roots( data, &cur_roots );
}

int define_number_of_roots( const test_data *data, Roots *cur_roots )
{
    int number_of_roots = cur_roots->number_of_roots;

    if ( number_of_roots != data->expected_roots.number_of_roots )
    {
        txSetConsoleAttr( FOREGROUND_RED | BACKGROUND_WHITE );
        printf( "#Error number of roots = %d Expected: number of roots = %d\n", number_of_roots, data->expected_roots.number_of_roots );

        return PROGRAM_ERROR;
    }

    return_number_of_roots( data, cur_roots );

    return PROGRAM_ERROR;
}

int test_solver()
{
    assert( parameters != NULL );

    int count_of_correct_tests = 0;

    for ( int i = 0; i < NUMBER_OF_TESTS; i++ )
    {
        count_of_correct_tests += run_test( &parameters[i] );
    }

    printf( "#Number of test done right = %d out of 5\n", count_of_correct_tests );
    return count_of_correct_tests;
}

void choose_how_to_test( SquareEquationCoefficients *coefficients, EquationParameters *equation_parameters )
{
    printf( "#If you want test solver automatically please enter 1, otherwise please enter 2\n" );

    switch( getchar() )
    {
        case AUTOMATICALLY:
            test_solver();
            break;
        case SPECIFIC_CASE:
            standard_mode_run( coefficients, equation_parameters );
            break;
        default:
            txSetConsoleAttr( FOREGROUND_RED | BACKGROUND_BLACK );
            printf( "main(): ERROR: wrong number of roots" );
            break;
    }
}

void standard_mode_run( SquareEquationCoefficients *coefficients, EquationParameters *equation_parameters )
{
    Roots cur_roots = {};
    get_coefficients( coefficients );
    equation_parameters->coefficients = *coefficients;
    type_definer( coefficients, &cur_roots );
    print_roots( &equation_parameters->cur_roots );
}

int return_number_of_roots( const test_data *data, Roots *cur_roots )
{
    int number_of_roots = cur_roots->number_of_roots;

    switch( number_of_roots )
    {
        case ZERO_ROOTS:
            return ZERO_ROOTS;
            break;
        case ONE_ROOT:
            if ( compare_with_zero( cur_roots->x1 - data->expected_roots.x1 ) )
            {
                txSetConsoleAttr( FOREGROUND_GREEN | BACKGROUND_BLACK );
                printf( "#OK\n" );

                return ONE_ROOT;
            }
            else
            {
                txSetConsoleAttr( FOREGROUND_RED | BACKGROUND_WHITE );
                printf( "#Error Test, a = %lg, b = %lg, c = %lg, x = %lg, number of roots = 1\n",
                        data->coefficients.a, data->coefficients.b, data->coefficients.c, cur_roots->x1 );
                printf( "#Expected x = %lg\n", data->expected_roots.x1 );
                return SOLVER_FAIL;
            }
        case TWO_ROOTS:
            if ( ( ( ( compare_with_zero(   cur_roots->x1 - data->expected_roots.x1 ) ) &&
                     ( compare_with_zero(   cur_roots->x2 - data->expected_roots.x2 ) ) ) )  ||
                   ( ( compare_with_zero( ( cur_roots->x2 - data->expected_roots.x1 ) ) &&
                     ( compare_with_zero(   cur_roots->x1 - data->expected_roots.x2 ) ) ) ) )
            {
                txSetConsoleAttr( FOREGROUND_GREEN | BACKGROUND_BLACK );
                printf( "#OK\n" );

                return TWO_ROOTS;
            }
            else
            {
                txSetConsoleAttr( FOREGROUND_RED | BACKGROUND_WHITE );
                printf( "#Error Test, a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, number of roots = 2\n",
                        data->coefficients.a, data->coefficients.b,
                        data->coefficients.c, cur_roots->x1, cur_roots->x2 );
                printf( "#Expected x1 = %lg, x2 = %lg\n",
                        data->expected_roots.x1, data->expected_roots.x2 );
                return SOLVER_FAIL;
            }
        case SS_INF_ROOTS:
            txSetConsoleAttr( FOREGROUND_GREEN | BACKGROUND_BLACK );
            printf( "#OK\n" );
            return SS_INF_ROOTS;
        default:
            txSetConsoleAttr( FOREGROUND_RED | BACKGROUND_BLACK );
            printf( "main(): ERROR: wrong number of roots" );
            return PROGRAM_ERROR;
    }

    return PROGRAM_ERROR;
}
