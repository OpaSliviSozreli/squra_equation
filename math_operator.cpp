#include <math.h>

#include "math_operator.h"

bool compare_with_zero( double number )
{
    if ( fabs(number) < EPSILON )
        return true;
    return false;
}
