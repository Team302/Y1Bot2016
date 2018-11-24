/*=============================================================================================
 * ArcadeDrive.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This implements the IJoystickDrive interface to drive the robot using joysticks in a arcade
 * drive mode.
 *
 * Thus, the left axis will control speed (throttle) and the right axis will control direction
 * (steering). The speed control (throttle) will get a cubic profile while the steer control
 * will be direct (linear).
 *
 * Then, the left and right speeds are set by using the arcade drive equations where
 * the left side adds the steer value to the throttle value and the right side
 * subtracts the steer value from the trottle.
 *=============================================================================================*/

#include <SmartDashboard/SmartDashboard.h>  // Smart Dashboard

// Team 302 includes
#include <ArcadeDrive.h>            // This class
#include <IChassis.h>               // Class the control the drive motors
#include <IChassisFactory.h>        // Class constructs the correct chassis
#include <OperatorInterface.h>      // Controls creating singleton of the gamepads

//--------------------------------------------------------------------
// Method:      ArcadeDrive <<constructor>>
// Description: This method creates and initializes the objects
//--------------------------------------------------------------------
ArcadeDrive::ArcadeDrive() : IJoystickDrive(),
                             m_oi( OperatorInterface::GetInstance())
{
    m_oi->SetAxisProfile( ARCADE_DRIVE_THROTTLE, CUBIC_SCALING );
    m_oi->SetAxisProfile( ARCADE_DRIVE_STEER, CUBIC_SCALING );
    m_oi->SetScaleFactor( ARCADE_DRIVE_STEER, 0.5 );

    // Set to Coast Mode
    m_chassis = IChassisFactory::GetInstance()->GetIChassis();
    m_chassis->SetCoastMode();
}

//--------------------------------------------------------------------
// Method:      DriveWithJoysticks
// Description: This method will be called during the periodic loop
//              to drive the robot.  It will interact with the joysticks
//              to drive in arcade drive mode.
// Returns:     void
//--------------------------------------------------------------------
void ArcadeDrive::DriveWithJoysticks() const
{
    // Read the desired motor speeds
    float steer  = m_oi->GetRawAxis( ARCADE_DRIVE_STEER );
    float throttle  = m_oi->GetRawAxis( ARCADE_DRIVE_THROTTLE );

    // Convert to using arcade equations to give motor speeds on
    // both sides of the robot.
    float leftSpeed  = throttle + steer;
    float rightSpeed = throttle - steer;

    // Set the motors
    m_chassis->SetMotorSpeeds( leftSpeed, rightSpeed );
}

//--------------------------------------------------------------------
// Method:      GetIdentifier
// Description: This gets the name that identifies the drive mode..
// Returns:     const char*         identifier for the drive
//--------------------------------------------------------------------
const char* ArcadeDrive::GetIdentifier() const
{
    return "Arcade Drive";
}
