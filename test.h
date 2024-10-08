#ifndef _TEST_H_
#define _TEST_H_

#include <math.h>

#include "equation_solver.h"

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

enum TestStatus
{
    TEST_OK = 1,
    TEST_FAIL = 0
};

const int NUMBER_OF_TESTS = 5;
const test_data parameters[NUMBER_OF_TESTS] = {    {{ 1,   2,   -3}, {   -3,     1,  2}},
                                                   {{ 1,   2,   -3}, {    1,    -3,  2}},
                                                   {{ 0,   2,   -5}, {  2.5,   NAN,  1}},
                                                   {{ 0,   0,    0}, {    4,    78, -1}},
                                                   {{25,  40,   16}, { -0.8,   NAN,  1}}
                                               };

const char AUTOMATICALLY = '1';
const char SPECIFIC_CASE = '2';

void        standard_mode_run();
bool        specific_case( const SquareEquationCoefficients *coefficients, Roots *cur_roots );
int         run_test( const test_data *data );
int         test_solver();
TestStatus  print_test_results( const test_data *data, Roots *cur_roots );
TestStatus  compare_number_of_roots( const test_data *data, Roots *cur_roots );

#endif
