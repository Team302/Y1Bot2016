/*=============================================================================================
 * TankDrive.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This implements the IJoystickDrive interface to drive the robot using joysticks in a tank
 * drive mode.
 *
 * Thus, the left axis will control the left side of the robot and the right axis will
 * control the right side of the robot.  Turning is achieve by pushing the axis in opposite
 * directions (e.g. right stick forward and left stick backward will turn left).
 *=============================================================================================*/

#include <SmartDashboard/SmartDashboard.h>  // Smart Dashboard

// Team 302 includes
#include <TankDrive.h>              // This class
#include <IChassis.h>               // Class the control the drive motors
#include <IChassisFactory.h>        // Class constructs the correct chassis
#include <OperatorInterface.h>      // Class that owns the driver gamepad

//--------------------------------------------------------------------
// Method:      TankDrive <<Constructor>>
// Description: This method is called to create/initialize this class
//--------------------------------------------------------------------
TankDrive::TankDrive() : IJoystickDrive(),
                         m_oi( OperatorInterface::GetInstance())
{
    // Get the two axis that will be used for tank drive
    // Set their profile to be Cubed
    m_oi->SetAxisProfile( TANK_DRIVE_LEFT_CONTROL, CUBIC_SCALING );
    m_oi->SetAxisProfile( TANK_DRIVE_RIGHT_CONTROL, CUBIC_SCALING );

    // Set to Coast Mode
    m_chassis = IChassisFactory::GetInstance()->GetIChassis();
    m_chassis->SetCoastMode();

}

//--------------------------------------------------------------------
// Method:      DriveWithJoysticks
// Description: This method will be called during the periodic loop
//              to drive the robot.  It will interact with the joysticks
//              to drive in tank drive mode.
// Returns:     void
//--------------------------------------------------------------------
void TankDrive::DriveWithJoysticks() const
{
    // Read the desired motor speeds
    float leftSpeed  = m_oi->GetRawAxis( TANK_DRIVE_LEFT_CONTROL );
    float rightSpeed  = m_oi->GetRawAxis( TANK_DRIVE_RIGHT_CONTROL );

    // Set the motors
    m_chassis->SetMotorSpeeds( leftSpeed, rightSpeed );
}

//--------------------------------------------------------------------
// Method:      GetIdentifier
// Description: This gets the name that identifies the drive mode..
// Returns:     const char*         identifier for the drive
//--------------------------------------------------------------------
const char* TankDrive::GetIdentifier() const
{
    return "Tank Drive";
}
