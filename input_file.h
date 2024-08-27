#ifndef _INPUT_FILE_H_
#define _INPUT_FILE_H_

#include "equation_solver.h"

const int WINDOWS_EOF = 26;

enum InputStatus
{
    SCAN_CORRECT   = 1,
    SCAN_INCORRECT = 0
};

InputStatus get_coefficients( SquareEquationCoefficients *coefficients );
InputStatus check_input_after_coeff();
void        clean_buff();

#endif
