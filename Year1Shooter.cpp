/*=============================================================================================
 * Year1Shooter.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This file interacts with the hardware (motors and sensors) used to shoot the ping pong balls
 *=============================================================================================*/

// WPILib includes
#include <CANTalon.h>                       // Motor Controllers
#include <DigitalInput.h>                   // Prox Switch
#include <SmartDashboard/SmartDashboard.h>  // Smart Dashboard

// Team 302 includes
#include <Year1Shooter.h>                   // This class
#include <IShooter.h>                       // Interface this class implements'
#include <LimitValue.h>                     // Contains utility to force values within the valid range
#include <Y1BotMap.h>                       // Contains the CAN IDs and Digital IO


//----------------------------------------------------------------------------------
// Method:      Year1Shooter <<Constructor>>
// Description: Create the motor controllers and set whether they are inverted or not.
//----------------------------------------------------------------------------------
Year1Shooter::Year1Shooter() : IShooter(),
                               m_shooterWheel( new CANTalon( SHOOTER_WHEEL_MOTOR ) ),
                               m_shooterLoader( new CANTalon( SHOOTER_LOAD_MOTOR ) ),
                               m_shooterAlign( new CANTalon( SHOOTER_ALIGN_MOTOR ) ),
                               m_loaderPosition( new DigitalInput( BALL_LOAD_SENSOR ) ),
                               m_shooterMaxAlign( new DigitalInput( MAX_ANGLE_SENSOR ) )
{

    // Shooter Alignment
    m_shooterAlign->SetInverted( IS_SHOOTER_ALIGN_MOTOR_INVERTED );                 // make sure it moves in the correct direction
    m_shooterAlign->ConfigNeutralMode( CANSpeedController::kNeutralMode_Brake );    // Make it stop immediately

    // Shooter wheels
    m_shooterWheel->SetInverted( IS_SHOOTER_WHEEL_MOTOR_INVERTED );                 // make sure the wheel is spinning in the correct direction
    m_shooterWheel->ConfigNeutralMode( CANSpeedController::kNeutralMode_Coast );    // Let wheel coast after power is stopped

    // Shooter Loader
    m_shooterLoader->SetInverted( IS_SHOOTER_LOAD_MOTOR_INVERTED );                 // make sure rotating in the correct direction
    m_shooterLoader->ConfigNeutralMode( CANSpeedController::kNeutralMode_Brake );   // Make it stop immediately
}


//----------------------------------------------------------------------------------
// Method:      SetShooterSpeed
// Description: This will set the motor speed for the shooter wheel.
//              If a value is specified that is outside the range, the value
//              used will be the closest bounding value (e.g. if 2.0 is passed in and
//              the range is -1.0 to 1.0, 1.0 will be used.
// Returns:     void
//----------------------------------------------------------------------------------
void Year1Shooter::SetShooterSpeed
(
    const float speed   // <I> - Speed for the shooter wheel (range -1.0 to 1.0)
) const
{
    SmartDashboard::PutNumber(" shooter input", speed );
    m_shooterWheel->Set( LimitValue::ForceInRange( speed, -1.0, 1.0 ) );
}

//----------------------------------------------------------------------------------
// Method:      SetBallLoadMotor
// Description: This will run the loader motor.
// Returns:     void
//----------------------------------------------------------------------------------
void Year1Shooter::SetBallLoadMotor
(
    const float speed   // <I> - Speed for the shooter ball loader (range -1.0 to 1.0)
) const
{
    SmartDashboard::PutNumber(" shooter load", speed );
    m_shooterLoader->Set( LimitValue::ForceInRange( speed, -1.0, 1.0 )  );
}

//----------------------------------------------------------------------------------
// Method:      IsLoaderInPosition
// Description: This will return whether the loader is in position or not.
// Returns:     bool        true  = in position
//                          false = not in position
//----------------------------------------------------------------------------------
bool Year1Shooter::IsLoaderInPosition() const
{
    return !m_loaderPosition->Get();
}

//----------------------------------------------------------------------------------
// Method:      AlignShooter
// Description: This will set the motor speed for shooter alignment.
//              If a value is specified that is outside the range, the value
//              used will be the closest bounding value (e.g. if 2.0 is passed in and
//              the range is -1.0 to 1.0, 1.0 will be used.
// Returns:     void
//----------------------------------------------------------------------------------
void Year1Shooter::AlignShooter
(
    const float speed   // <I> - Speed for the shooter wheel (range -1.0 to 1.0)
) const
{
    SmartDashboard::PutNumber(" shooter align", speed );
    m_shooterAlign->Set( LimitValue::ForceInRange( speed, -1.0, 1.0 )  );
}

//----------------------------------------------------------------------------------
// Method:      IsShooterAtLeftBound
// Description: This will return whether the shooter is at left bounds or not.
// Returns:     bool        true  = at bound position
//                          false = not in at bound position
//----------------------------------------------------------------------------------
bool Year1Shooter::IsShooterAtLeftBound() const
{
	SmartDashboard::PutBoolean("Max Angle Tripped", m_shooterMaxAlign->Get());

    return false;
//    return !m_shooterMaxAlign->Get();
}

//----------------------------------------------------------------------------------
// Method:      IsShooterAtRightBound
// Description: This will return whether the shooter is at right bounds or not.
// Returns:     bool        true  = at bound position
//                          false = not in at bound position
//----------------------------------------------------------------------------------
bool Year1Shooter::IsShooterAtRightBound() const
{
	SmartDashboard::PutBoolean("Max Angle Tripped", m_shooterMaxAlign->Get());

	//return false;
   return !m_shooterMaxAlign->Get();
}

//----------------------------------------------------------------------------------
// Method:      ~Year1Shooter <<Destructor>>
// Description: Delete the motor controllers
//----------------------------------------------------------------------------------
Year1Shooter::~Year1Shooter()
{
    delete m_shooterWheel;
    m_shooterWheel = nullptr;

    delete m_shooterLoader;
    m_shooterLoader = nullptr;

    delete m_shooterAlign;
    m_shooterAlign = nullptr;

    delete m_loaderPosition;
    m_loaderPosition = nullptr;
}

