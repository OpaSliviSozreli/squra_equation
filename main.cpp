#include "equation_solver.h"
#include "math_operator.h"
#include "test.h"
#include "print_roots.h"
#include "input_file.h"

int main()
{
    SquareEquationCoefficients coefficients = {};

    EquationParameters equation_parameters = {};

    choose_how_to_test( &coefficients, &equation_parameters );

    return 0;
}
