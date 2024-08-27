#ifndef _INPUT_FILE_
#define _INPUT_FILE_

struct SquareEquationCoefficients
{
    double a;
    double b;
    double c;
};

const double EPSILON = 1e-10;

void get_coefficients( SquareEquationCoefficients *coefficients );
bool compare_with_zero( double number );
void clean_buff();

#endif
