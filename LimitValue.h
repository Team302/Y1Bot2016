/*=============================================================================================
 * LimitValue.h
 *=============================================================================================
 *
 * File Description:
 *
 * This has a static function to limit the range of a value
 *=============================================================================================*/


#ifndef SRC_LIMITVALUE_H_
#define SRC_LIMITVALUE_H_

class LimitValue
{
public:

    //----------------------------------------------------------------------------------
    // Method:      ForceInRange
    // Description: This will compare a value to a range.  If the value is outside of the
    //              range, the nearest bounding value will be returned
    //              robot.
    // Returns:     float value to use which is in range
    //----------------------------------------------------------------------------------
    static float ForceInRange
    (
        const float value,          // <I> - value to check
        const float lowerBound, // <I> - lower bound to check against
        const float upperBound  // <I> - upper bound to check against
    );

    // Static functions, so no creator or destructor
    LimitValue() = delete;
    virtual ~LimitValue() = delete;
};

#endif /* SRC_LIMITVALUE_H_ */
