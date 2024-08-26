#ifndef _TEST_H_
#define _TEST_H_

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
    struct SquareEquationCoefficients coefficients;
    struct Roots expected_roots;
};

enum NumberOfRoots
{
    ZERO_ROOTS   =  0,
    ONE_ROOT     =  1,
    TWO_ROOTS    =  2,
    SS_INF_ROOTS = -1
};

enum SolveStatus
{
    SOLVER_FAIL,
    SOLVER_OK
};

const int PROGRAM_ERROR = 0;

const int NUMBER_OF_TESTS = 5;
const test_data parameters[NUMBER_OF_TESTS] = {    {{ 1,   2,   -3}, {   -3,     1,  2}},
                                                   {{ 1,   2,   -3}, {    1,    -3,  2}},
                                                   {{ 0,   2,   -5}, {  2.5,   NAN,  1}},
                                                   {{ 0,   0,    0}, {    4,    78, -1}},
                                                   {{25,  40,   16}, { -0.8,   NAN,  1}}
                                               };

const char AUTOMATICALLY = '1';
const char SPECIFIC_CASE = '2';

void choose_how_to_test( SquareEquationCoefficients *coefficients, EquationParameters *equation_parameters );
void standard_mode_run( SquareEquationCoefficients *coefficients, EquationParameters *equation_parameters );
bool specific_case( const SquareEquationCoefficients *coefficients, Roots *cur_roots );
int  run_test( const test_data *data );
int  test_solver();
int  return_number_of_roots( const test_data *data, Roots *cur_roots );
int  define_number_of_roots( const test_data *data, Roots *cur_roots );

#endif
