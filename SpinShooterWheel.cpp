/*=============================================================================================
 * SpinShooterWheel.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This controls loading a ball into the shooter.
 *=============================================================================================*/

// Team 302 includes
#include <SpinShooterWheel.h>       // This class
#include <IShooter.h>               // Class the control the shooter motors
#include <IShooterFactory.h>        // Class constructs the correct chassis
#include <OperatorInterface.h>      // Controls creating singleton of the gamepads

//--------------------------------------------------------------------
// Method:      SpinShooterWheel <<constructor>>
// Description: This method creates and initializes the objects
//--------------------------------------------------------------------
SpinShooterWheel::SpinShooterWheel() : m_oi( OperatorInterface::GetInstance() ),
                                       m_shooter( IShooterFactory::GetInstance()->GetIShooter() )
{

}


//--------------------------------------------------------------------
// Method:      SpinWheels
// Description: This method will read the gamepad input and if the
//              SPIN_SHOOTER_WHEEL button is pressed, run the wheel.
//              If not, stop the wheel.
// Returns:     void
//--------------------------------------------------------------------
void SpinShooterWheel::SpinWheels() const
{
    // TODO:    Define a motor speed constants in SpinShooterWheel.h
    //
    //          Define a float variable named speed and set it to the stopped speed (one of the
    //          constants that should be 0.0)
    //
    //          Read the gamepad ...
    //              if the SPIN_SHOOTER_WHEEL is pressed set the a speed variable to the
    //              desired wheel speed (constant from above that should be 1.0)
    //
    //          call m_shooter's SetShooterSpeed method passing the speed.

    float speed = m_shooterMotorSpeedStop;
    if (m_oi->GetRawButton(SPIN_SHOOTER_WHEEL) ||
        m_oi->GetRawButton(LOAD_BALL_BUTTON))
    {
        speed = m_shooterMotorSpeedGo;
    }
    else if ( !m_shooter->IsLoaderInPosition() )
    {
        speed = m_shooterMotorSpeedGo;
    }
    else
    {
        speed = m_shooterMotorSpeedStop;
    }
    m_shooter->SetShooterSpeed(speed);
}


