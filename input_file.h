#ifndef _AUXILIARY_FUNC_H_
#define _AUXILIARY_FUNC_H_

#include "test.h"

const int WINDOWS_EOF = 26;

enum InputCorrect
{
    SCAN_CORRECT   = 1,
    SCAN_INCORRECT = 0
};

bool get_coefficients( SquareEquationCoefficients *coefficients );
void clean_buff();

#endif
