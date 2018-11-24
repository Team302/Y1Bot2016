/*=============================================================================================
 * LimitValue.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This implements the IDrive interface to drive the robot using joysticks in a tank
 * drive mode.
 *=============================================================================================*/

// Team 302 includes
#include <LimitValue.h>


//----------------------------------------------------------------------------------
// Method:      ForceInRange
// Description: This will compare a value to a range.  If the value is outside of the
//              range, the nearest bounding value will be returned
//              robot.
// Returns:     float value to use which is in range
//----------------------------------------------------------------------------------
float LimitValue::ForceInRange
(
    const float value,      // <I> - value to check
    const float lowerBound, // <I> - lower bound to check against
    const float upperBound  // <I> - upper bound to check against
)
{
    // If the value is less than the lower bound set the output value to the lower bound
    // otherwise the output is the value passed in.
    float output = ( value < lowerBound ) ? lowerBound : value;

    // If the output value is greater than the upper bound, set the output value to the upper bound
    // otherwise the output value is unchanged.
    output = ( output > upperBound ) ? upperBound : output;

    // return the limited value to the caller
    return output;
}

