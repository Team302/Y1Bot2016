/*=============================================================================================
 * GoToShootingPosition.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This class will follow get into shooting position by driving to the target and when it
 * detects the target with the digital input, it will back up to the shooting position.
 *=============================================================================================*/

#include <DigitalInput.h>

// Team 302 includes
#include <GoToShootingPosition.h>   // This class
#include <IChassis.h>               // Class the control the drive motors
#include <IChassisFactory.h>        // Class constructs the correct chassis
#include <RobotMap.h>
#include <DigitalInput.h>

//--------------------------------------------------------------------
// Method:      GoToShootingPosition <<constructor>>
// Description: This method creates and initializes the objects
//--------------------------------------------------------------------
GoToShootingPosition::GoToShootingPosition() : m_chassis( IChassisFactory::GetInstance()->GetIChassis() ),
                                               m_state( DRIVE_TO_GOAL )

{
    m_chassis->SetBrakeMode();  // set to brake mode, so we don't continue moving
    ChangeState( READY_TO_START );
}

//--------------------------------------------------------------------
// Method:      Drive
// Description: This method will drive to the shooting position by
//              detecting where the goal is and then backing up to
//              the desired location.
// Returns:     bool    -  true  = shooting position reached
//                         false = still traversing to the shooting position
//--------------------------------------------------------------------
bool GoToShootingPosition::Drive()
{
    bool isDone = false;

    // Check the current state (m_state) and call its method
    //        if it is DRIVE_TO_GOAL:
    //            call DriveToGoal
    //
    //        if it is BACK_UP_TO_POSITION:
    //            call BackToPosition
    //
    //        if it is STOP_AT_SHOOTING_POSITION
    //            change isDone to true

    if ( m_state == READY_TO_START )				// Got called, so change the state from ready to drive
    {
        ChangeState( DRIVE_TO_GOAL );
    }
    else if (m_state == DRIVE_TO_GOAL)			// Approaching the Goal - Call DriveToGoal
	{
		DriveToGoal();
	}
	else if (m_state == BACK_UP_TO_POSITION)	// Already reached the goal, so back up - Call BackToPosition
	{
		BackToPosition();
	}
	else										// Otherwise we are done, so stop
	{
		isDone = true;
		m_state = READY_TO_START;
	}
    return isDone;
}


//--------------------------------------------------------------------
// Method:      DriveToGoal
// Description: This method will drive straight until the digital input
//              is tripped
// Returns:     void
//--------------------------------------------------------------------
void GoToShootingPosition::DriveToGoal()
{
	// Change states when the bumper is pressed
	if ( m_chassis->IsBumperPressed() )
	{
		ChangeState(BACK_UP_TO_POSITION);
	}
}

//--------------------------------------------------------------------
// Method:      BackToPosition
// Description: This method will drive backwards to the shooting position
// Returns:     void
//--------------------------------------------------------------------
void GoToShootingPosition::BackToPosition()
{
    // TODO:
    //       Get the average distance by averaging the outputs from
    //       GetLeftSideDistance and GetRightSideDistance methods on m_chassis
    //
    //       compare the average distance travelled to the target distance (BACK_UP_DISTANCE)
    //
    //       when the distance travelled is the desired distance (allow for overshoot),
    //       call ChangeState with STOP_AT_SHOOTING_POSITION

	
	float distance = ((m_chassis-> GetLeftSideDistance() + m_chassis-> GetRightSideDistance()) / 2.0);
	
	if (distance >= BACK_UP_DISTANCE )
	{
		ChangeState(STOP_AT_SHOOTING_POSITION);
	}
}


//--------------------------------------------------------------------
// Method:      ChangeState
// Description: This method will change the state for this operation
// Returns:     void
//--------------------------------------------------------------------
void GoToShootingPosition::ChangeState
(
    POSITIONING_STATE       newState        // <I> - new state for this operation
)
{
    float speed = 0.0;
    switch ( newState )
    {
        case DRIVE_TO_GOAL:
            //  set speed equal to APPROACH_SPEED
			speed = APPROACH_SPEED;
            break;

        case BACK_UP_TO_POSITION:
            // set speed equal to BACKUP_SPEED
            // call the ResetDistance method on m_chassis
			speed = BACKUP_SPEED; 
			m_chassis->ResetDistance(); // call for ResetDistance method in m_chassis
            break;

        case STOP_AT_SHOOTING_POSITION:
            //  set speed equal to STOP_SPEED
			speed = STOP_SPEED;

            break;

        case READY_TO_START:
            //  set speed equal to STOP_SPEED
			speed = STOP_SPEED;
			
            break;

        default:
            break;

    }
    m_state = newState;
    m_chassis->SetMotorSpeeds( speed, speed );
}


