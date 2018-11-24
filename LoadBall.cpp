/*=============================================================================================
 * LoadBall.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This controls loading a ball into the shooter.
 *=============================================================================================*/
#include <SmartDashboard/SmartDashboard.h>  // Smart Dashboard


// Team 302 includes
#include <LoadBall.h>               // This class
#include <IShooter.h>               // Class the control the shooter motors
#include <IShooterFactory.h>        // Class constructs the correct chassis
#include <OperatorInterface.h>      // Controls creating singleton of the gamepads

//--------------------------------------------------------------------
// Method:      LoadBall <<constructor>>
// Description: This method creates and initializes the objects
//--------------------------------------------------------------------
LoadBall::LoadBall() : m_oi( OperatorInterface::GetInstance() ),
                       m_shooter( IShooterFactory::GetInstance()->GetIShooter() ),
					   m_switchTripped( false )
{


}


//--------------------------------------------------------------------
// Method:      CycleLoader
// Description: This method will read the gamepad input and move run
//              loader motor until the sensor detects it is back in
//              load position
// Returns:     void
//--------------------------------------------------------------------
void LoadBall::CycleLoader()
{
	SmartDashboard::PutBoolean("load tripped", m_shooter->IsLoaderInPosition());


	m_switchTripped = m_shooter->IsLoaderInPosition();

    // If the button is pressed, load a ball
    if (m_oi->GetRawButton(LOAD_BALL_BUTTON))
    {
        m_shooter->SetBallLoadMotor(m_shooterSpeedRun);
        m_switchTripped = false;
    }

    // If the loader isn't in position, keep running the loader
    else if (m_shooter->IsLoaderInPosition() == false && !m_switchTripped )
    {
        m_shooter->SetBallLoadMotor(m_shooterSpeedRun);
    }

    // Otherwise stop the loader
    else
    {
        m_shooter->SetBallLoadMotor(m_shooterSpeedStopped);  // fixed case
    }
}


