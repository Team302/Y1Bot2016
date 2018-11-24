/*=============================================================================================
 * SoftwareTestChassis.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This file interacts with the hardware (motors and sensors) used to drive the robot.
 *=============================================================================================*/

// WPILib includes
#include <CANTalon.h>                       // Motor Controllers
#include <DigitalInput.h>

// Team 302 includes
#include <SoftwareTestChassis.h>            // This class'
#include <IChassis.h>                       // Interface this class implements'
#include <LimitValue.h>                     // Contains utility to force values within the valid range
#include <SoftwareTestBotMap.h>             // Contains the CAN IDs and Digital IO


//----------------------------------------------------------------------------------
// Method:      SoftwareTestChassis <<Constructor>>
// Description: Create the motor controllers and set whether they are inverted or not.
//----------------------------------------------------------------------------------
SoftwareTestChassis::SoftwareTestChassis() : IChassis(),
                                             m_frontLeftMotor( new CANTalon( LEFT_DRIVE_MOTOR ) ) ,
                                             m_frontRightMotor( new CANTalon( RIGHT_DRIVE_MOTOR ) ),
                                             m_backLeftMotor( new CANTalon( LEFT_DRIVE_MOTOR2 ) ),
                                             m_backRightMotor( new CANTalon( RIGHT_DRIVE_MOTOR2 ) ),
                                             m_bumperSwitch( new DigitalInput( GOAL_DETECTION_SENSOR ) )
{
    // Set whether each drive motor is inverted or not
    m_frontLeftMotor->SetInverted( IS_LEFT_DRIVE_MOTOR_INVERTED );
    m_frontRightMotor->SetInverted( IS_RIGHT_DRIVE_MOTOR_INVERTED );
    m_backLeftMotor->SetInverted( IS_LEFT_DRIVE_MOTOR_INVERTED );
    m_backRightMotor->SetInverted( IS_RIGHT_DRIVE_MOTOR_INVERTED );

    ResetDistance();
}


//----------------------------------------------------------------------------------
// Method:      SetMotorSpeeds
// Description: This will set the motor speeds for the left and right side of the
//              robot.  If a value is specified that is outside the range, the value
//              used will be the closest bounding value (e.g. if 2.0 is passed in and
//              the range is -1.0 to 1.0, 1.0 will be used.
// Returns:     void
//----------------------------------------------------------------------------------
void SoftwareTestChassis::SetMotorSpeeds
(
    const float leftSideSpeeds, // <I> - Speed for the left side of the robot to (range -1.0 to 1.0)
    const float rightSideSpeeds // <I> - Speed for the right side of the robot (range -1.0 to 1.0)
) const
{
    // Make sure the left side speed is within range and then set both left motors to this speed
    float leftSpeed = LimitValue::ForceInRange( leftSideSpeeds, -1.0, 1.0 );
    m_frontLeftMotor->Set( leftSpeed );
    m_backLeftMotor->Set( leftSpeed );

    // Make sure the right side speed is within range and then set both right motors to this speed
    float rightSpeed = LimitValue::ForceInRange( rightSideSpeeds, -1.0, 1.0 );
    m_frontRightMotor->Set( rightSpeed );
    m_backRightMotor->Set( rightSpeed );
}

//----------------------------------------------------------------------------------
// Method:      ResetDistance
// Description: This will reset the distance, so calls to get the distance will
//              relative to this distance.
// Returns:     void
//----------------------------------------------------------------------------------
void SoftwareTestChassis::ResetDistance()
{
    m_frontLeftMotor->SetPosition( 0 );
    m_frontRightMotor->SetPosition( 0 );
    m_backLeftMotor->SetPosition( 0 );
    m_backRightMotor->SetPosition( 0 );
}

//----------------------------------------------------------------------------------
// Method:      GetLeftSideDistance
// Description: This will return the distance the left side has traveled since the
//              last time ResetDistance() was called.
// Returns:     float   distance in feet the left side of the robot has travelled
//                      (positive values are forward and negative values are backward)
//----------------------------------------------------------------------------------
float SoftwareTestChassis::GetLeftSideDistance() const
{
    int frontEncoderCounts = m_frontLeftMotor->GetEncPosition();
    int rearEncoderCounts  = m_backLeftMotor->GetEncPosition();
    return ConvertEncoderCountsToDistance( frontEncoderCounts, rearEncoderCounts );
}

//----------------------------------------------------------------------------------
// Method:      GetRightSideDistance
// Description: This will return the distance the right side has traveled since the
//              last time ResetDistance() was called.
// Returns:     float   distance in feet the right side of the robot has travelled
//                      (positive values are forward and negative values are backward)
//----------------------------------------------------------------------------------
float SoftwareTestChassis::GetRightSideDistance() const
{
    int frontEncoderCounts = m_frontRightMotor->GetEncPosition();
    int rearEncoderCounts  = m_backRightMotor->GetEncPosition();
    return ConvertEncoderCountsToDistance( frontEncoderCounts, rearEncoderCounts );
}

//----------------------------------------------------------------------------------
// Method:      ConvertEncoderCountsToDistance
// Description: This will average the counts and then convert that value to feet
// Returns:     float   distance in feet (positive values are forward and negative
//                      values are backward)
//----------------------------------------------------------------------------------
float SoftwareTestChassis::ConvertEncoderCountsToDistance
(
    int     frontCounts,        // <I> - encoder counts for the front wheel
    int     rearCounts          // <I> - encoder counts for the rear wheel
) const
{
    float avgDist = static_cast<float>( frontCounts + rearCounts ) / 2.0;
    return ( avgDist * ENCODER_DISTANCE_CONVERSION);
}


//----------------------------------------------------------------------------------
// Method:      GetLeftSideVelocity
// Description: This will return the velocity the left side of the robot
// Returns:     float   velocity in feet per second the left side of the robot is moving
//                      (positive values are forward and negative values are backward)
//----------------------------------------------------------------------------------
float SoftwareTestChassis::GetLeftSideVelocity() const
{
    int frontEncoderCounts = m_frontLeftMotor->GetEncVel();
    int rearEncoderCounts  = m_backLeftMotor->GetEncVel();

    return ConvertEncoderCountsToVelocity( frontEncoderCounts, rearEncoderCounts );
}

//----------------------------------------------------------------------------------
// Method:      GetRightSideVelocity
// Description: This will return the velocity the right side of the robot
// Returns:     float   velocity in feet per second the right side of the robot is moving
//                      (positive values are forward and negative values are backward)
//----------------------------------------------------------------------------------
float SoftwareTestChassis::GetRightSideVelocity() const
{
    int frontEncoderCounts = m_frontRightMotor->GetEncVel();
    int rearEncoderCounts  = m_backRightMotor->GetEncVel();

    return ConvertEncoderCountsToVelocity( frontEncoderCounts, rearEncoderCounts );
}

//----------------------------------------------------------------------------------
// Method:      ConvertEncoderCountsToVelocity
// Description: This will average the counts and then convert that value to feet per second
// Returns:     float   velocity in feet per second the robot is moving
//                      (positive values are forward and negative values are backward)
//----------------------------------------------------------------------------------
float SoftwareTestChassis::ConvertEncoderCountsToVelocity
(
    int     frontCounts,        // <I> - encoder counts for the front wheel
    int     rearCounts          // <I> - encoder counts for the rear wheel
) const
{
    float avgDist = static_cast<float>( frontCounts + rearCounts ) / 2.0;
    return ( avgDist * ENCODER_VELOCITY_CONVERSION);
}

//----------------------------------------------------------------------------------
// Method:      SetBrakeMode
// Description: This will set the drive motors to brake mode
// Returns:     void
//----------------------------------------------------------------------------------
void SoftwareTestChassis::SetBrakeMode() const
{
    m_frontLeftMotor->ConfigNeutralMode( CANSpeedController::kNeutralMode_Brake );
    m_frontRightMotor->ConfigNeutralMode( CANSpeedController::kNeutralMode_Brake );
    m_backLeftMotor->ConfigNeutralMode( CANSpeedController::kNeutralMode_Brake );
    m_backRightMotor->ConfigNeutralMode( CANSpeedController::kNeutralMode_Brake );
}


//----------------------------------------------------------------------------------
// Method:      SetCoastMode
// Description: This will set the drive motors to coast mode
// Returns:     void
//----------------------------------------------------------------------------------
void SoftwareTestChassis::SetCoastMode() const
{
    m_frontLeftMotor->ConfigNeutralMode( CANSpeedController::kNeutralMode_Coast );
    m_frontRightMotor->ConfigNeutralMode( CANSpeedController::kNeutralMode_Coast );
    m_backLeftMotor->ConfigNeutralMode( CANSpeedController::kNeutralMode_Coast );
    m_backRightMotor->ConfigNeutralMode( CANSpeedController::kNeutralMode_Coast );
}

//----------------------------------------------------------------------------------
// Method:      IsBumperPressed
// Description: This will return whether the bumper switch is tripped or not
// Returns:     bool        true  = tripped
//                          false = not tripped
//----------------------------------------------------------------------------------
bool SoftwareTestChassis::IsBumperPressed()
{
    return m_bumperSwitch->Get();
}

//----------------------------------------------------------------------------------
// Method:      GetLineTrackerState
// Description: This will return the state of the line trackers
// Returns:     bool        true  = tripped
//                          false = not tripped
//----------------------------------------------------------------------------------
LINE_TRACK_STATE SoftwareTestChassis::GetLineTrackerState()
{
    return LEFT_WHITE_CENTER_WHITE_RIGHT_WHITE;
}

//----------------------------------------------------------------------------------
// Method:      UpdateLineTrackerLights
// Description: This will update the line tracker lights
// Returns:     void
//----------------------------------------------------------------------------------
void SoftwareTestChassis::UpdateLineTrackerLights()
{
    // No-op
}


//----------------------------------------------------------------------------------
// Method:      ~SoftwareTestChassis <<Destructor>>
// Description: Delete the motor controllers
//----------------------------------------------------------------------------------
SoftwareTestChassis::~SoftwareTestChassis()
{
    delete m_frontLeftMotor;
    m_frontLeftMotor = nullptr;

    delete m_frontRightMotor;
    m_frontRightMotor = nullptr;

    delete m_backLeftMotor;
    m_backLeftMotor = nullptr;

    delete m_backRightMotor;
    m_backRightMotor = nullptr;
}

