/*=============================================================================================
 * GoToShootingPosition.h
 *=============================================================================================
 *
 * File Description:
 *
 * This class will follow get into shooting position by driving to the target and when it
 * detects the target with the digital input, it will back up to the shooting position.
 *=============================================================================================*/

#ifndef SRC_GOTOSHOOTINGPOSITION_H_
#define SRC_GOTOSHOOTINGPOSITION_H_


#include <DigitalInput.h>

//  Team 302 includes
#include <IJoystickDrive.h>     // Interface being implemented
#include <IChassis.h>           // Class that controls the motors on the drive chassis

enum POSITIONING_STATE
{
    DRIVE_TO_GOAL,
    BACK_UP_TO_POSITION,
    STOP_AT_SHOOTING_POSITION,
	READY_TO_START
};

class GoToShootingPosition
{
    public:
        //--------------------------------------------------------------------
        // Method:      GoToShootingPosition <<constructor>>
        // Description: This method creates and initializes the objects
        //--------------------------------------------------------------------
        GoToShootingPosition();      // constructor

        //--------------------------------------------------------------------
        // Method:      Drive
        // Description: This method will drive to the shooting position by
        //              detecting where the goal is and then backing up to
        //              the desired location.
        // Returns:     bool    -  true  = shooting position reached
        //                         false = still traversing to the shooting position
        //--------------------------------------------------------------------
        bool Drive();

        //--------------------------------------------------------------------
        // Method:      ~GoToShootingPosition <<destructor>>
        // Description: This method is called to delete these objects
        //--------------------------------------------------------------------
        virtual ~GoToShootingPosition() = default; // destructor

        //--------------------------------------------------------------------
        // Method:      ChangeState
        // Description: This method will change the state for this operation
        // Returns:     void
        //--------------------------------------------------------------------
        void ChangeState
        (
            POSITIONING_STATE       newState        // <I> - new state for this operation
        );

    protected:

        //--------------------------------------------------------------------
        // Method:      DriveToGoal
        // Description: This method will drive straight until the digital input
        //              is tripped
        // Returns:     void
        //--------------------------------------------------------------------
        void DriveToGoal();

        //--------------------------------------------------------------------
        // Method:      BackToPosition
        // Description: This method will drive backwards to the shooting position
        // Returns:     void
        //--------------------------------------------------------------------
        void BackToPosition();

    private:
        // Attributes
        IChassis*           m_chassis;

        POSITIONING_STATE   m_state;

        const float         BACK_UP_DISTANCE = 2.0;     // distance in feet

        const float         APPROACH_SPEED = 0.5;       // speed when driving toward goal

        const float         BACKUP_SPEED = -0.5;        // speed when robot backs up when goal is reached

        const float         STOP_SPEED = 0.0;           // stop when desired distance from goal is reached


        // Default methods we don't want the compiler to implement for us
        GoToShootingPosition( const GoToShootingPosition& ) = delete;
        GoToShootingPosition& operator= ( const GoToShootingPosition& ) = delete;
        explicit GoToShootingPosition( GoToShootingPosition* other ) = delete;


};

#endif /* SRC_GoToShootingPosition_H_ */
