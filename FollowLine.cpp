/*=============================================================================================
 * FollowLine.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This class will follow a white line surrounded by black lines.
 *=============================================================================================*/

#include <DigitalOutput.h>
#include <SmartDashboard/SmartDashboard.h>  // Smart Dashboard

// Team 302 includes
#include <FollowLine.h>            // This class
#include <IChassis.h>               // Class the control the drive motors
#include <IChassisFactory.h>        // Class constructs the correct chassis
#include <LineTracker.h>
#include <RobotMap.h>
#include <Y1BotMap.h>

//--------------------------------------------------------------------
// Method:      FollowLine <<constructor>>
// Description: This method creates and initializes the objects
//--------------------------------------------------------------------
FollowLine::FollowLine() : m_chassis( IChassisFactory::GetInstance()->GetIChassis() ),
                           m_previousState( STOPPED )

{
    m_chassis->SetBrakeMode();  // set to brake mode, so we don't continue moving
}

//--------------------------------------------------------------------
// Method:      Drive
// Description: This method will follow a line.
// Returns:     void
//--------------------------------------------------------------------
void FollowLine::Drive()
{
    //      Check whether each line tracker is sensing black or white using
    //        the IsBlack() and IsWhite() methods.
    //
    //        Set up the conditions such that if the sensors from left to right are:
    //          - W W W =  You are on the right path, drive straight
    //          - W W B =  There is a black on the right, turn left slightly
    //          - W B B =  There are 2 blacks on the right, turn left a lot
    //          - B W W =  There is a black on the left, turn right slightly
    //          - B B W =  Tgere are 2 blacks on the left, turn right a lot
    //          - B B B =  Something messed up, turn back. If it's still black then stop.
    //          - N N N =  It's time to stop.



    m_chassis->UpdateLineTrackerLights();
    LINE_TRACK_STATE state = m_chassis->GetLineTrackerState();

    if ( state == LEFT_WHITE_CENTER_WHITE_RIGHT_WHITE )  //This is telling the robot to keep moving: Condition W W W
    {
        SmartDashboard::PutString("Line Mode State ", "straight" );
        DriveStraight();

    }
    else if ( state ==  LEFT_WHITE_CENTER_BLACK_RIGHT_WHITE )  //This is telling the robot to keep moving: Condition W W W
    {
        SmartDashboard::PutString("Line Mode State ", "straight2" );
        DriveStraight();
    }
    else if ( state ==  LEFT_WHITE_CENTER_BLACK_RIGHT_WHITE )  //This is telling the robot to keep moving: Condition W W W
    {
        SmartDashboard::PutString("Line Mode State ", "straight2" );
        DriveStraight();
    }
    else if ( state == LEFT_BLACK_CENTER_WHITE_RIGHT_BLACK )  //This is telling the robot to redo what it did, otherwise known as going backward: Condition B B B
    {
        SmartDashboard::PutString("Line Mode State ", "back" );
        m_previousState = DRIVE_STRAIGHT;
        DriveStraightBack();
    }
    else if ( state == LEFT_WHITE_CENTER_WHITE_RIGHT_BLACK )  //This is telling the robot to move slightly to the left: Condition W W B
    {
        SmartDashboard::PutString("Line Mode State ", "slight left" );
        DriveSlightLeft();
    }
    else if (state == LEFT_WHITE_CENTER_BLACK_RIGHT_BLACK )  //This is telling the robot to make a big turn to the left: Condition W B B
    {
        SmartDashboard::PutString("Line Mode State ", "sharp left" );
        DriveSharpLeft();
    }
    else if (state == LEFT_BLACK_CENTER_WHITE_RIGHT_WHITE)  //This is telling the robot to move slightly to the right: Condition B W W
    {
        SmartDashboard::PutString("Line Mode State ", "slight right" );
        DriveSlightRight();
    }
    else if (state == LEFT_BLACK_CENTER_BLACK_RIGHT_WHITE)  //This is telling the robot to make a big turn to the right: Condition B B W
    {
        SmartDashboard::PutString("Line Mode State ", "sharp right" );
        DriveSharpRight();
    }
    else  // This is telling the robot to stop if none of the conditions above are met: Condition N N N
    {
        SmartDashboard::PutString("Line Mode State ", "lost" );
        Stop();
    }



}






//--------------------------------------------------------------------
// Method:      DriveStraight
// Description: This method will drive straight
// Returns:     void
//--------------------------------------------------------------------
void FollowLine::DriveStraight()
{
    // Defined constants in FollowLine.h and passed them to SetMotorSpeeds
    m_chassis->SetMotorSpeeds( STRAIGHT_DRIVE,STRAIGHT_DRIVE );
}

//--------------------------------------------------------------------
// Method:      DriveSlightLeft
// Description: This method will drive slightly to the left
// Returns:     void
//--------------------------------------------------------------------
void FollowLine::DriveSlightLeft()
{
    // Defined constants in FollowLine.h and passed them to SetMotorSpeeds
    m_chassis->SetMotorSpeeds( DRIVE_SLIGHT_LEFT_LEFT_MOTOR,DRIVE_SLIGHT_LEFT_RIGHT_MOTOR );
}

//--------------------------------------------------------------------
// Method:      DriveSharpLeft
// Description: This method will drive Hardly to the left
// Returns:     void
//--------------------------------------------------------------------
void FollowLine::DriveSharpLeft()
{
    // Defined constants in FollowLine.h and passed them to SetMotorSpeeds
    m_chassis->SetMotorSpeeds( DRIVE_SHARP_LEFT_LEFT_MOTOR,DRIVE_SHARP_LEFT_RIGHT_MOTOR );
}

//--------------------------------------------------------------------
// Method:      DriveSlightRight
// Description: This method will drive slightly to the right
// Returns:     void
//--------------------------------------------------------------------
void FollowLine::DriveSlightRight()
{
    // Defined constants in FollowLine.h and passed them to SetMotorSpeeds
    m_chassis->SetMotorSpeeds( DRIVE_SLIGHT_RIGHT_LEFT_MOTOR, DRIVE_SLIGHT_RIGHT_RIGHT_MOTOR );
}

//--------------------------------------------------------------------
// Method:      DriveSharpRight
// Description: This method will drive Hardly to the right
// Returns:     void
//--------------------------------------------------------------------
void FollowLine::DriveSharpRight()
{
    // Defined constants in FollowLine.h and passed them to SetMotorSpeeds
    m_chassis->SetMotorSpeeds( DRIVE_SHARP_RIGHT_LEFT_MOTOR, DRIVE_SHARP_RIGHT_RIGHT_MOTOR );
}

//--------------------------------------------------------------------
// Method:      Stop
// Description: This method will stop
// Returns:     void
//--------------------------------------------------------------------
void FollowLine::Stop()
{
    // Defined constants in FollowLine.h and passed them to SetMotorSpeeds
    m_chassis->SetMotorSpeeds( 0.0, 0.0 );
}
void FollowLine::DriveStraightBack()
{
    m_chassis->SetMotorSpeeds( STRAIGHT_DRIVE_BACK, STRAIGHT_DRIVE_BACK );

}

