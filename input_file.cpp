#include <assert.h>
#include <stdio.h>

#include "input_file.h"

bool get_coefficients( SquareEquationCoefficients *coefficients )
{
    assert( coefficients != NULL );

    while ( scanf( "%lg%lg%lg", &coefficients->a, &coefficients->b, &coefficients->c ) != 3 )
    {
        printf( "#Enter a again" );
        clean_buff();
    }
    for ( char i = getchar(); i != '\n'; i != WINDOWS_EOF )
    {
        if ( i == ' ' )
            return SCAN_CORRECT;
        else
            printf("#Input is incorrect\n");

            return SCAN_INCORRECT;
    }
}

void clean_buff()
{
    while ( getchar() != '\n' && getchar() != WINDOWS_EOF );
}
