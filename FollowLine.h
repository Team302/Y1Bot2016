/*=============================================================================================
 * FollowLine.h
 *=============================================================================================
 *
 * File Description:
 *
 * This class will follow a white line surrounded by black lines.
 *=============================================================================================*/

#ifndef SRC_FOLLOWLINE_H_
#define SRC_FOLLOWLINE_H_


//  Team 302 includes
#include <IJoystickDrive.h>     // Interface being implemented
#include <IChassis.h>           // Class that controls the motors on the drive chassis
#include <DragonStick.h>        // Driver Game pad

enum LINE_TRACKER_STATES
{
    DRIVE_STRAIGHT,
    DRIVE_SLIGHT_LEFT,
    DRIVE_SLIGHT_RIGHT,
    DRIVE_SHARP_LEFT,
    DRIVE_SHARP_RIGHT,
    LOST,
    BACKINGUP,
    STOPPED
};

class FollowLine
{
    public:
        //--------------------------------------------------------------------
        // Method:      FollowLine <<constructor>>
        // Description: This method creates and initializes the objects
        //--------------------------------------------------------------------
        FollowLine();      // constructor

        //--------------------------------------------------------------------
        // Method:      Drive
        // Description: This method will follow a line.
        // Returns:     void
        //--------------------------------------------------------------------
        void Drive();

        //--------------------------------------------------------------------
        // Method:      Stop
        // Description: This method will stop
        // Returns:     void
        //--------------------------------------------------------------------
        void Stop();

        //--------------------------------------------------------------------
        // Method:      ~FollowLine <<destructor>>
        // Description: This method is called to delete these objects
        //--------------------------------------------------------------------
        virtual ~FollowLine() = default; // destructor

    protected:

    /*  Const float StraightDriveLeft = 0.5;
    *   DriveSharp->SetMotorSpeeds */

        //--------------------------------------------------------------------
        // Method:      DriveStraight
        // Description: This method will drive straight
        // Returns:     void
        //--------------------------------------------------------------------
        void DriveStraight();

        //--------------------------------------------------------------------
        // Method:      DriveSlightLeft
        // Description: This method will drive slightly to the left
        // Returns:     void
        //--------------------------------------------------------------------
        void DriveSlightLeft();


        //--------------------------------------------------------------------
        // Method:      DriveSharpLeft
        // Description: This method will drive sharply to the left
        // Returns:     void
        //--------------------------------------------------------------------
        void DriveSharpLeft();


        //--------------------------------------------------------------------
        // Method:      DriveSlightRight
        // Description: This method will drive slightly to the right
        // Returns:     void
        //--------------------------------------------------------------------
        void DriveSlightRight();

        //--------------------------------------------------------------------
        // Method:      DriveSharpRight
        // Description: This method will drive sharply to the right
        // Returns:     void
        //--------------------------------------------------------------------
        void DriveSharpRight();

        //--------------------------------------------------------------------
        // Method:      DriveStraightBack
        // Description: This method will drive straight back
        // Returns:     void
        //--------------------------------------------------------------------


        void DriveStraightBack();


    private:
        // Attributes

        IChassis*               m_chassis;


                const float STRAIGHT_DRIVE = 0.15;
                const float STRAIGHT_DRIVE_BACK = -0.15;


                const float DRIVE_SLIGHT_LEFT_LEFT_MOTOR = 0.1;
                const float DRIVE_SLIGHT_LEFT_RIGHT_MOTOR = 0.2;


                const float DRIVE_SHARP_LEFT_LEFT_MOTOR = -0.15;
                const float DRIVE_SHARP_LEFT_RIGHT_MOTOR = 0.15;


                const float DRIVE_SLIGHT_RIGHT_RIGHT_MOTOR = 0.1;
                const float DRIVE_SLIGHT_RIGHT_LEFT_MOTOR = 0.2;

                const float DRIVE_SHARP_RIGHT_RIGHT_MOTOR = -0.15;
                const float DRIVE_SHARP_RIGHT_LEFT_MOTOR = 0.15;


         LINE_TRACKER_STATES     m_previousState;

        // Default methods we don't want the compiler to implement for us
        FollowLine( const FollowLine& ) = delete;
        FollowLine& operator= ( const FollowLine& ) = delete;
        explicit FollowLine( FollowLine* other ) = delete;


};

#endif /* SRC_FOLLOWLINE_H_ */
