#include <math.h>

#include "math_operator.h"

bool compare_with_zero( double number )
{
    return (fabs(number) < EPSILON);
}
