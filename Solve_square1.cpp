//#define   TX_COMPILED
#include "TXLib.h"
#include <stdio.h>
#include <math.h>

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

struct EquationParameters
{
    struct SquareEquationCoefficients coefficients;
    struct Roots cur_roots;
};

struct test_data
{
    struct EquationParameters equation_parameters;
    struct Roots expected_roots;
};

const double EPSILON = 1e-10;

enum NumberOfRoots
{
    ZERO_ROOTS   =  0,
    ONE_ROOT     =  1,
    TWO_ROOTS    =  2,
    SS_INF_ROOTS = -1
};

enum SolveStatus
{
    solver_fail,
    solver_ok
};

const int NUMBER_OF_TESTS = 5;

const char AUTOMATICALLY = '1';
const char SPECIFIC_CASE = '2';


void get_coefficients( SquareEquationCoefficients *coefficients );
void clean_buff();
void  choose_how_to_test( test_data parameters[], SquareEquationCoefficients *coefficients, EquationParameters *equation_parameters );
bool compare_with_zero( double number );
int  print_roots( Roots *cur_roots );
bool  solve_square( EquationParameters *equation_parameters );
int  run_test( test_data *data );
int  test_solver( test_data parameters[] );
bool  solve_linear( EquationParameters *equation_parameters );
bool  type_definer( EquationParameters *equation_parameters );
int  count_correct_number_of_roots( Roots *cur_roots, Roots *expected_roots );

int main()
{
    SquareEquationCoefficients coefficients = {};

    Roots cur_roots = {};
    EquationParameters equation_parameters = {};

    test_data parameters[NUMBER_OF_TESTS] =
    {
        {{ 1,   2,   -3}, {   -3,     1,  2}},
        {{ 1,   2,   -3}, {    1,    -3,  2}},
        {{ 0,   2,   -5}, {  2.5,   2.5,  1}},
        {{ 0,   0,    0}, {    4,    78, -1}},
        {{25,  40,   16}, { -0.8,  -0.8,  1}}
    };

    choose_how_to_test( parameters, &coefficients, &equation_parameters );
}

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

void get_coefficients( SquareEquationCoefficients *coefficients )
{
    assert( coefficients != NULL);

    while ( scanf( "%lg%lg%lg", &coefficients->a, &coefficients->b, &coefficients->c ) != 3 )
    {
        printf( "#Enter a again" );
        clean_buff();
    }
    clean_buff();
}

bool compare_with_zero( double number )
{
    if ( fabs(number) < EPSILON )
        return true;
    return false;
}

void clean_buff()
{
    while ( getchar() != '\n' && getchar() != 'EOF' );
}

int print_roots( Roots *cur_roots )
{
    assert( cur_roots != NULL );

    switch( cur_roots->number_of_roots )
    {
        case ZERO_ROOTS:
            printf( "No roots\n" );
            break;
        case ONE_ROOT:
            printf( "x = %lg\n", cur_roots->x1 );
            break;
        case TWO_ROOTS:
            printf( "x1 = %lg, x2 = %lg\n", cur_roots->x1, cur_roots->x2 );
            break;
        case SS_INF_ROOTS:
            printf( "Any roots\n" );
            break;
        default:
            txSetConsoleAttr( FOREGROUND_RED | BACKGROUND_BLACK );
            printf( "main(): ERROR: wrong number of roots" );
            return 1;
    }
}

int run_test( test_data *data )
{
    assert( data != NULL );

    type_definer( &data->equation_parameters );
    int number_of_roots = data->equation_parameters.cur_roots.number_of_roots;
    int count_of_correct_tests = 0;

    if ( number_of_roots != data->expected_roots.number_of_roots )
    {
        txSetConsoleAttr( FOREGROUND_RED | BACKGROUND_WHITE );
        printf( "#Error number of roots = %d Expected: number of roots = %d", number_of_roots, data->expected_roots.number_of_roots );
    }

    switch( number_of_roots )
    {
        case ZERO_ROOTS:
            return ZERO_ROOTS;
            break;
        case ONE_ROOT:
            if ( compare_with_zero( data->equation_parameters.cur_roots.x2 - data->expected_roots.x2 ) )
            {
                txSetConsoleAttr( FOREGROUND_GREEN | BACKGROUND_BLACK );
                printf( "#OK\n" );
                return ONE_ROOT;
            }
            else
            {
                txSetConsoleAttr( FOREGROUND_RED | BACKGROUND_WHITE );
                printf( "#Error Test, a = %lg, b = %lg, c = %lg, x = %lg, number of roots = 1\n",
                        data->equation_parameters.coefficients.a, data->equation_parameters.coefficients.b, data->equation_parameters.coefficients.c, data->equation_parameters.cur_roots.x1 );
                printf( "#Expected x = %lg", data->expected_roots.x1 );
                break;
            }
        case TWO_ROOTS:
            if ( ( ( ( compare_with_zero(   data->equation_parameters.cur_roots.x1 - data->expected_roots.x1 ) ) &&
                     ( compare_with_zero(   data->equation_parameters.cur_roots.x2 - data->expected_roots.x2 ) ) ) )  ||
                   ( ( compare_with_zero( ( data->equation_parameters.cur_roots.x2 - data->expected_roots.x1 ) ) &&
                     ( compare_with_zero(   data->equation_parameters.cur_roots.x1 - data->expected_roots.x2 ) ) ) ) )
            {
                txSetConsoleAttr( FOREGROUND_GREEN | BACKGROUND_BLACK );
                printf( "#OK\n" );
                return TWO_ROOTS;
            }
            else
            {
                txSetConsoleAttr( FOREGROUND_RED | BACKGROUND_WHITE );
                printf( "#Error Test, a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, number of roots = 2\n",
                        data->equation_parameters.coefficients.a, data->equation_parameters.coefficients.b,
                        data->equation_parameters.coefficients.c, data->equation_parameters.cur_roots.x1,
                        data->equation_parameters.cur_roots.x2 );
                printf( "#Expected x1 = %lg, x2 = %lg",
                        data->expected_roots.x1, data->expected_roots.x2 );
                break;
            }
        case SS_INF_ROOTS:
            txSetConsoleAttr( FOREGROUND_GREEN | BACKGROUND_BLACK );
            printf( "#OK\n" );
            return SS_INF_ROOTS;
    }
}

int test_solver( test_data parameters[] )
{
    assert( parameters != NULL );

    for ( int i = 0; i < NUMBER_OF_TESTS; i++ )
    {
        run_test( &parameters[i] );
        int count_of_correct_tests = 0;
        for ( i = 0; i < NUMBER_OF_TESTS; i++ )
        {
            count_of_correct_tests += run_test( &parameters[i] );
        }
        printf( "#Number of test done right = %d out of 5", count_of_correct_tests );
        return count_of_correct_tests;
    }
}

void choose_how_to_test( test_data parameters[], SquareEquationCoefficients *coefficients, EquationParameters *equation_parameters )
{
    printf( "#If you want test solver automatically please enter 1, otherwise please enter 2\n" );
    switch( getchar() )
    {
        case AUTOMATICALLY:
            test_solver( parameters );
            break;
        case SPECIFIC_CASE:
            get_coefficients( coefficients );
            equation_parameters->coefficients = *coefficients;
            type_definer( equation_parameters );
            print_roots( &equation_parameters->cur_roots );
            break;
    }
}






