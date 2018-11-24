/*=============================================================================================
 * IShooter.h
 *=============================================================================================
 *
 * File Description:
 *
 * This is the interface for the shooting hardware.  All concrete (physical) shooting systems will implement
 * this interface.
 *=============================================================================================*/
#ifndef SRC_ISHOOTER_H_
#define SRC_ISHOOTER_H_

// WPILib includes

// Team 302 includes

class IShooter
{
public:
    //----------------------------------------------------------------------------------
    // Method:      SetShooterSpeed
    // Description: This will set the motor speed for the shooter wheel.
    //              If a value is specified that is outside the range, the value
    //              used will be the closest bounding value (e.g. if 2.0 is passed in and
    //              the range is -1.0 to 1.0, 1.0 will be used.
    // Returns:     void
    //----------------------------------------------------------------------------------
    virtual void SetShooterSpeed
    (
        const float speed   // <I> - Speed for the shooter wheel (range -1.0 to 1.0)
    ) const = 0;

    //----------------------------------------------------------------------------------
    // Method:      SetBallLoadMotor
    // Description: This will run the loader motor.
    // Returns:     void
    //----------------------------------------------------------------------------------
    virtual void SetBallLoadMotor
    (
        const float speed   // <I> - Speed for the shooter ball loader (range -1.0 to 1.0)
    ) const = 0;

    //----------------------------------------------------------------------------------
    // Method:      IsLoaderInPosition
    // Description: This will return whether the loader is in position or not.
    // Returns:     bool        true  = in postion
    //                          false = not in position
    //----------------------------------------------------------------------------------
    virtual bool IsLoaderInPosition() const = 0;

    //----------------------------------------------------------------------------------
    // Method:      AlignShooter
    // Description: This will set the motor speed for shooter alignment.
    //              If a value is specified that is outside the range, the value
    //              used will be the closest bounding value (e.g. if 2.0 is passed in and
    //              the range is -1.0 to 1.0, 1.0 will be used.
    // Returns:     void
    //----------------------------------------------------------------------------------
    virtual void AlignShooter
    (
        const float speed   // <I> - Speed for the shooter wheel (range -1.0 to 1.0)
    ) const = 0;

    //----------------------------------------------------------------------------------
    // Method:      IsShooterAtLeftBound
    // Description: This will return whether the shooter is at left bounds or not.
    // Returns:     bool        true  = at bound position
    //                          false = not in at bound position
    //----------------------------------------------------------------------------------
    virtual bool IsShooterAtLeftBound() const = 0;

    //----------------------------------------------------------------------------------
    // Method:      IsShooterAtRightBound
    // Description: This will return whether the shooter is at right bounds or not.
    // Returns:     bool        true  = at bound position
    //                          false = not in at bound position
    //----------------------------------------------------------------------------------
    virtual bool IsShooterAtRightBound() const = 0;

    protected:
        IShooter() = default;           // default constructor used by the implementors of this interface
        virtual ~IShooter() = default;  // default destructors used by implementors of this interface

private:

};

#endif /* SRC_CHASSIS_H_ */
