//#define   TX_COMPILED
#include "TXLib.h"
#include <assert.h>
#include <stdio.h>

#include "input_file.h"

InputStatus get_coefficients( SquareEquationCoefficients *coefficients )
{
    assert( coefficients != NULL );

    while ( scanf( "%lg%lg%lg", &coefficients->a, &coefficients->b, &coefficients->c ) != 3 )
    {
        printf( "#Enter a, b, c again" );
        clean_buff();
    }
    check_input_after_coeff();

    return SCAN_INCORRECT;
}

void clean_buff()
{
    InputStatus check_input_after_coeff( SquareEquationCoefficients *coefficients );
    while ( getchar() != '\n' && getchar() != WINDOWS_EOF );
}

InputStatus check_input_after_coeff()
{
    for ( char i = (char)getchar(); i != '\n' && i != WINDOWS_EOF;  )
    {
        if ( i == ' ' )
            return SCAN_CORRECT;
        else
            printf("#Input is incorrect\n");

            return SCAN_INCORRECT;
    }

    return SCAN_INCORRECT;
}
