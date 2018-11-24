/*=============================================================================================
 * Year1Shooter.h
 *=============================================================================================
 *
 * File Description:
 *
 * This file interacts with the hardware (motors and sensors) used to drive the robot.  It is a
 * Singleton.
 *=============================================================================================*/
#ifndef SRC_YEAR1SHOOTER_H_
#define SRC_YEAR1SHOOTER_H_

// WPILib includes
#include <CANTalon.h>
#include <DigitalInput.h>

// Team 302 includes
#include <IShooter.h>
#include <IShooterFactory.h>

class Year1Shooter : public IShooter
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
    void SetShooterSpeed
    (
        const float speed   // <I> - Speed for the shooter wheel (range -1.0 to 1.0)
    ) const override;


    //----------------------------------------------------------------------------------
    // Method:      SetBallLoadMotor
    // Description: This will run the loader motor.
    // Returns:     void
    //----------------------------------------------------------------------------------
    void SetBallLoadMotor
    (
        const float speed   // <I> - Speed for the shooter ball loader (range -1.0 to 1.0)
    ) const override;

    //----------------------------------------------------------------------------------
    // Method:      IsLoaderInPosition
    // Description: This will return whether the ball loader is in position or not.
    // Returns:     bool        true  = in postion
    //                          false = not in position
    //----------------------------------------------------------------------------------
    bool IsLoaderInPosition() const override;

    //----------------------------------------------------------------------------------
    // Method:      AlignShooter
    // Description: This will set the motor speed for shooter alignment.
    //              If a value is specified that is outside the range, the value
    //              used will be the closest bounding value (e.g. if 2.0 is passed in and
    //              the range is -1.0 to 1.0, 1.0 will be used.
    // Returns:     void
    //----------------------------------------------------------------------------------
    void AlignShooter
    (
        const float speed   // <I> - Speed for the shooter wheel (range -1.0 to 1.0)
    ) const override;

    //----------------------------------------------------------------------------------
    // Method:      IsShooterAtLeftBound
    // Description: This will return whether the shooter is at left bounds or not.
    // Returns:     bool        true  = at bound position
    //                          false = not in at bound position
    //----------------------------------------------------------------------------------
    bool IsShooterAtLeftBound() const override;

    //----------------------------------------------------------------------------------
    // Method:      IsShooterAtRightBound
    // Description: This will return whether the shooter is at right bounds or not.
    // Returns:     bool        true  = at bound position
    //                          false = not in at bound position
    //----------------------------------------------------------------------------------
    bool IsShooterAtRightBound() const override;

private:
    friend class IShooterFactory;

    //----------------------------------------------------------------------------------
    // Method:      Year1Shooter <<Constructor>>
    // Description: Create the motor controllers and set whether they are inverted or not.
    //----------------------------------------------------------------------------------
    Year1Shooter();

    //----------------------------------------------------------------------------------
    // Method:      ~Year1Shooter <<Destructor>>
    // Description: Delete the motor controll
    //----------------------------------------------------------------------------------
    virtual ~Year1Shooter();

    // Drive Motors
    CANTalon*           m_shooterWheel;
    CANTalon*           m_shooterLoader;
    CANTalon*           m_shooterAlign;

    DigitalInput*       m_loaderPosition;
    DigitalInput*       m_shooterMaxAlign;
};

#endif /* SRC_YEAR1SHOOTER_H_ */
