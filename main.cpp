//#define   TX_COMPILED
#include "TXLib.h"
#include <stdio.h>
#include "equation_solver.h"
#include "math_operator.h"
#include "test.h"
#include "print_roots.h"
#include "input_file.h"

int main( const int argc, const char *argv[] )
{
    switch( argc )
    {
        case 1:
            standard_mode_run();
            break;
        case 2:
            if ( strcmp( argv[1], "-t" ) == 0 )
                test_solver();
            break;
        case 3:
            if ( strcmp(argv[1], "-t" ) == 0 )
                test_solver();
            break;
        default:
            txSetConsoleAttr( FOREGROUND_RED | BACKGROUND_BLACK );
            printf( "main(): ERROR" );
            break;
    }

    return 0;
}
