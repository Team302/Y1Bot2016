/*=============================================================================================
 * Year1Chassis.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This file interacts with the hardware (motors and sensors) used to drive the robot.
 *
 *=============================================================================================*/

// WPILib includes
#include <CANTalon.h>                       // Motor Controllers
#include <DigitalInput.h>
#include <SmartDashboard/SmartDashboard.h>  // Smart Dashboard


// Team 302 includes
#include <Year1Chassis.h>                   // This class'
#include <IChassis.h>                       // Interface this class implements'
#include <LimitValue.h>                     // Contains utility to force values within the valid range
#include <Y1BotMap.h>                       // Contains the CAN IDs and Digital IO


//----------------------------------------------------------------------------------
// Method:      Year1Chassis <<Constructor>>
// Description: Create the motor controllers and set whether they are inverted or not.
//----------------------------------------------------------------------------------
Year1Chassis::Year1Chassis() :  IChassis(),
                                m_leftMotor( new CANTalon( LEFT_DRIVE_MOTOR ) ) ,
                                m_rightMotor( new CANTalon( RIGHT_DRIVE_MOTOR ) ),
                                m_bumperSwitch( new DigitalInput( GOAL_DETECTION_SENSOR ) ),
                                m_leftLineTracker( new LineTracker( LEFT_LINE_TRACKER ) ),
                                m_leftLineIndicator( new DigitalOutput( LEFT_LINE_TRACKER_LIGHT ) ),
                                m_centerLineTracker( new LineTracker( CENTER_LINE_TRACKER ) ),
                                m_centerLineIndicator( new DigitalOutput( CENTER_LINE_TRACKER_LIGHT ) ),
                                m_rightLineTracker( new LineTracker( RIGHT_LINE_TRACKER ) ),
                                m_rightLineIndicator( new DigitalOutput( RIGHT_LINE_TRACKER_LIGHT ) )
{
    // Create each drive motor and set whether it is inverted or not
    m_leftMotor->SetInverted( IS_LEFT_DRIVE_MOTOR_INVERTED );
    m_leftMotor->SetSensorDirection( true );

    m_rightMotor->SetInverted( IS_RIGHT_DRIVE_MOTOR_INVERTED );
    m_rightMotor->SetSensorDirection( true );

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
void Year1Chassis::SetMotorSpeeds
(
    const float leftSideSpeeds, // <I> - Speed for the left side of the robot to (range -1.0 to 1.0)
    const float rightSideSpeeds // <I> - Speed for the right side of the robot (range -1.0 to 1.0)
) const
{
    SmartDashboard::PutNumber(" left input", leftSideSpeeds );
    SmartDashboard::PutNumber(" right input", rightSideSpeeds );

    // Make sure the left side speed is within range and then set both left motors to this speed
    float leftSpeed = LimitValue::ForceInRange( leftSideSpeeds, -1.0, 1.0 );
    m_leftMotor->Set( leftSpeed );

    // Make sure the right side speed is within range and then set both right motors to this speed
    float rightSpeed = LimitValue::ForceInRange( rightSideSpeeds, -1.0, 1.0 );
    m_rightMotor->Set( rightSpeed );

    SmartDashboard::PutNumber(" left speed", GetLeftSideVelocity() );
    SmartDashboard::PutNumber(" right speed", GetRightSideVelocity() );
}

//----------------------------------------------------------------------------------
// Method:      ResetDistance
// Description: This will reset the distance, so calls to get the distance will
//              relative to this distance.
// Returns:     void
//----------------------------------------------------------------------------------
void Year1Chassis::ResetDistance()
{
    m_leftMotor->SetPosition( 0 );
    m_rightMotor->SetPosition( 0 );
}

//----------------------------------------------------------------------------------
// Method:      GetLeftSideDistance
// Description: This will return the distance the left side has traveled since the
//              last time ResetDistance() was called.
// Returns:     float   distance in feet the left side of the robot has travelled
//                      (positive values are forward and negative values are backward)
//----------------------------------------------------------------------------------
float Year1Chassis::GetLeftSideDistance() const
{
    float distance = static_cast<float>( m_leftMotor->GetEncPosition() );
    return ( distance * ENCODER_DISTANCE_CONVERSION );
}

//----------------------------------------------------------------------------------
// Method:      GetRightSideDistance
// Description: This will return the distance the right side has traveled since the
//              last time ResetDistance() was called.
// Returns:     float   distance in feet the right side of the robot has travelled
//                      (positive values are forward and negative values are backward)
//----------------------------------------------------------------------------------
float Year1Chassis::GetRightSideDistance() const
{
    float distance = static_cast<float>( m_rightMotor->GetEncPosition() );
    return ( distance * ENCODER_DISTANCE_CONVERSION );
}


//----------------------------------------------------------------------------------
// Method:      GetLeftSideVelocity
// Description: This will return the velocity the left side of the robot
// Returns:     float   velocity in feet per second the left side of the robot is moving
//                      (positive values are forward and negative values are backward)
//----------------------------------------------------------------------------------
float Year1Chassis::GetLeftSideVelocity() const
{
    float velocity = static_cast<float>( m_leftMotor->GetEncVel() );
    return ( velocity*ENCODER_VELOCITY_CONVERSION );
}

//----------------------------------------------------------------------------------
// Method:      GetRightSideVelocity
// Description: This will return the velocity the right side of the robot
// Returns:     float   velocity in feet per second the right side of the robot is moving
//                      (positive values are forward and negative values are backward)
//----------------------------------------------------------------------------------
float Year1Chassis::GetRightSideVelocity() const
{
    float velocity = static_cast<float>( m_rightMotor->GetEncVel() );
    return ( velocity*ENCODER_VELOCITY_CONVERSION );
}

//----------------------------------------------------------------------------------
// Method:      SetBrakeMode
// Description: This will set the drive motors to brake mode
// Returns:     void
//----------------------------------------------------------------------------------
void Year1Chassis::SetBrakeMode() const
{
    m_leftMotor->ConfigNeutralMode( CANSpeedController::kNeutralMode_Brake );
    m_rightMotor->ConfigNeutralMode( CANSpeedController::kNeutralMode_Brake );
}


//----------------------------------------------------------------------------------
// Method:      SetCoastMode
// Description: This will set the drive motors to coast mode
// Returns:     void
//----------------------------------------------------------------------------------
void Year1Chassis::SetCoastMode() const
{
    m_leftMotor->ConfigNeutralMode( CANSpeedController::kNeutralMode_Coast );
    m_rightMotor->ConfigNeutralMode( CANSpeedController::kNeutralMode_Coast );
}

//----------------------------------------------------------------------------------
// Method:      IsBumperPressed
// Description: This will return whether the bumper switch is tripped or not
// Returns:     bool        true  = tripped
//                          false = not tripped
//----------------------------------------------------------------------------------
bool Year1Chassis::IsBumperPressed()
{
   SmartDashboard::PutBoolean(" bumper tripped ", !m_bumperSwitch->Get() );
   return !m_bumperSwitch->Get();
}

//----------------------------------------------------------------------------------
// Method:      GetLineTrackerState
// Description: This will return the state of the line trackers
// Returns:     bool        true  = tripped
//                          false = not tripped
//----------------------------------------------------------------------------------
LINE_TRACK_STATE Year1Chassis::GetLineTrackerState()
{

    SmartDashboard::PutNumber(" left line tracker", m_leftLineTracker->GetVoltage() );
    SmartDashboard::PutNumber(" center line tracker", m_centerLineTracker->GetVoltage() );
    SmartDashboard::PutNumber(" right line tracker", m_rightLineTracker->GetVoltage() );



    LINE_TRACK_STATE state = UNKNOWN;

    bool IsBlackleft = m_leftLineTracker-> IsBlack();
    bool IsWhiteleft = m_leftLineTracker-> IsWhite();

    bool IsBlackright = m_rightLineTracker-> IsBlack();
    bool IsWhiteright = m_rightLineTracker-> IsWhite();

    bool IsBlackcenter = m_centerLineTracker-> IsBlack();
    bool IsWhitecenter = m_centerLineTracker-> IsWhite();

    if (IsWhiteleft && IsWhitecenter  && IsWhiteright)
    {
        state = LEFT_WHITE_CENTER_WHITE_RIGHT_WHITE;
    }
    else if ( IsWhiteleft && IsBlackcenter && IsWhiteright )
    {
       state = LEFT_WHITE_CENTER_BLACK_RIGHT_WHITE;
    }
    else if ( IsBlackleft && IsBlackcenter && IsBlackright )
    {
        state = LEFT_BLACK_CENTER_BLACK_RIGHT_BLACK;
    }
    else if (IsWhiteleft && IsWhitecenter && IsBlackright )
    {
       state = LEFT_WHITE_CENTER_WHITE_RIGHT_BLACK;
    }
    else if (IsWhiteleft && IsBlackcenter && IsBlackright)
    {
        state = LEFT_WHITE_CENTER_BLACK_RIGHT_BLACK;
    }
    else if (IsBlackleft && IsWhitecenter && IsWhiteright)
    {
        state = LEFT_BLACK_CENTER_WHITE_RIGHT_WHITE;
    }
    else if (IsBlackleft && IsBlackcenter && IsWhiteright)
    {
        state = LEFT_BLACK_CENTER_BLACK_RIGHT_WHITE;
    }
    else if (IsBlackleft && IsWhitecenter && IsBlackright)
    {
        state = LEFT_BLACK_CENTER_WHITE_RIGHT_BLACK;
    }
    else
    {
        state = UNKNOWN;
    }

    return state;
}

//----------------------------------------------------------------------------------
// Method:      UpdateLineTrackerLights
// Description: This will update the line tracker lights
// Returns:     void
//----------------------------------------------------------------------------------
void Year1Chassis::UpdateLineTrackerLights()
{
    m_leftLineIndicator-> Set( m_leftLineTracker-> IsWhite() );
    m_centerLineIndicator-> Set( m_centerLineTracker-> IsWhite() );
    m_rightLineIndicator-> Set( m_rightLineTracker-> IsWhite() );
}


//----------------------------------------------------------------------------------
// Method:      ~Year1Chassis <<Destructor>>
// Description: Delete the motor controllers
//----------------------------------------------------------------------------------
Year1Chassis::~Year1Chassis()
{
    delete m_leftMotor;
    m_leftMotor = nullptr;

    delete m_rightMotor;
    m_rightMotor = nullptr;
}

