//#define   TX_COMPILED
#include "TXLib.h"
#include <assert.h>
#include <stdio.h>

#include "print_roots.h"

int print_roots( Roots *cur_roots )
{
    assert( cur_roots != NULL );

    switch( cur_roots->number_of_roots )
    {
        case ZERO_ROOTS:
            printf( "No roots\n" );
            return ZERO_ROOTS;
        case ONE_ROOT:
            printf( "x = %lg\n", cur_roots->x1 );
            return ONE_ROOT;
        case TWO_ROOTS:
            printf( "x1 = %lg, x2 = %lg\n", cur_roots->x1, cur_roots->x2 );
            return TWO_ROOTS;
        case SS_INF_ROOTS:
            printf( "Any roots\n" );
            return SS_INF_ROOTS;
        default:
            txSetConsoleAttr( FOREGROUND_RED | BACKGROUND_BLACK );
            printf( "main(): ERROR: wrong number of roots" );
            return PROGRAM_ERROR;
    }

    return PROGRAM_ERROR;
}
