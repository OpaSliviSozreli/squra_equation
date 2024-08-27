#include <math.h>
#include "input_file.h"
#include <stdio.h>

void get_coefficients( SquareEquationCoefficients *coefficients )// TODO: put to input file
{
    assert( coefficients != NULL);

    while ( scanf( "%lg%lg%lg", &coefficients->a, &coefficients->b, &coefficients->c ) != 3 )
    {
        printf( "#Enter a again" );
        clean_buff();
    }
    clean_buff();
}

bool compare_with_zero( double number ) // TODO: put to math_operation file
{
    if ( fabs(number) < EPSILON )
        return true;
    return false;
}

void clean_buff()// TODO: put to input file
{
    while ( getchar() != '\n' && getchar() != EOF );  // TODO: MAKE AS WINDOWS_EOF
}
