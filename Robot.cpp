
 /*========================================================================================================
 * Robot.cpp
 *========================================================================================================
 *
 * File Description:
 *
 * This file defines the main robot class
 *========================================================================================================
 *  Modifications:
 *  Date            Name            Description of Change
 *  18-Oct-2016     Joe Witcpalek   Created File
 *========================================================================================================*/

// WPILib includes
#include <IterativeRobot.h>                 // Base Class

#include <SmartDashboard/SendableChooser.h> // Used to select drive mode
#include <SmartDashboard/SmartDashboard.h>  // Smart Dashboard



// Team 302 includes
#include <ArcadeDrive.h>
#include <FollowLine.h>
#include <IChassis.h>               // Class the control the drive motors
#include <IChassisFactory.h>        // Class constructs the correct chassis
#include <IJoystickDrive.h>
#include <LineUpShooter.h>
#include <LoadBall.h>
#include <OperatorInterface.h>
#include <SpinShooterWheel.h>
#include <TankDrive.h>



class Robot: public IterativeRobot
{
    private:

        // Constants for the teleop chooser
        /*
        const std::string   m_teleopDriveMode = "Teleop Drive Mode";
        const std::string   m_driveJoystickTankDrive = "Tank Drive";
        const std::string   m_driveJoystickArcadeDrive = "Arcade Drive";

        // Objects used by teleop
        SendableChooser*    m_teleopChooser;        // Selections for teleop on the dashboard
        std::string         m_selectedTeleopMode;   // selected option on the m_teleopChooser
        */
        IJOYSTICK_DRIVE_IDENTIFIER  m_currentDriveMode; // current drive mode
        OperatorInterface*          m_oi;               // controller interface

        IJoystickDrive*             m_tankDrive;
        IJoystickDrive*             m_arcadeDrive;
        IJoystickDrive*             m_currentDrive;

        LineUpShooter*      m_shooterAlignment;
        LoadBall*           m_loader;
        SpinShooterWheel*   m_shooterWheel;
        FollowLine*         m_followLine;
        bool                m_autonMode;

        IChassis*               m_chassis;


    public:

        //----------------------------------------------------------------------------------
        // Method:      Robot       <<constructor>>
        // Description: Create and intialize the object.
        //----------------------------------------------------------------------------------
        Robot() : IterativeRobot(),
//                  m_teleopChooser( new SendableChooser() ),
                  m_currentDriveMode( TANK_DRIVE ),
                  m_oi( OperatorInterface::GetInstance() ),
                  m_tankDrive(  new TankDrive() ),
                  m_arcadeDrive( new ArcadeDrive()  ),
                  m_currentDrive( m_tankDrive ),
                  m_shooterAlignment( new LineUpShooter() ),
                  m_loader( new LoadBall() ),
                  m_shooterWheel( new SpinShooterWheel() ),
                  m_followLine( new FollowLine() ),
                  m_autonMode( false ),
                  m_chassis( IChassisFactory::GetInstance()->GetIChassis() )

        {
        }

        //----------------------------------------------------------------------------------
        // Method:      RobotInit
        // Description: Initialization routine that is performed once upon the when
        //              the robot is initialized.  This happens before the robot does
        //              anything.
        // Returns:     void
        //----------------------------------------------------------------------------------
        void RobotInit()
        {
            // Put the teleop choices on the dashboard
            /*
            m_teleopChooser->AddObject(m_driveJoystickArcadeDrive, (void*)&m_driveJoystickArcadeDrive );
            m_teleopChooser->AddObject(m_driveJoystickTankDrive, (void*)&m_driveJoystickTankDrive );
            SmartDashboard::PutData( m_teleopDriveMode, m_teleopChooser );
            */
        }

        //----------------------------------------------------------------------------------
        // Method:      DisabledInit
        // Description: Initialization routine that gets called when the robot enters
        //              the disabled mode.
        // Returns:     void
        //----------------------------------------------------------------------------------
        void DisabledInit()
        {
        }

        //----------------------------------------------------------------------------------
        // Method:      DisabledPeriodic
        // Description: This runs after the disabled mode initialization has completed.
        //              It runs every loop (approximately every 20 milliseconds)  while
        //              the robot is disabled.
        // Returns:     void
        //----------------------------------------------------------------------------------
        void DisabledPeriodic()
        {
        }

        //----------------------------------------------------------------------------------
        // Method:      AutonomousInit
        // Description: Initialization routine that gets called when the robot enters
        //              the autonomous (no human interation) mode.
        // Returns:     void
        //----------------------------------------------------------------------------------
        void AutonomousInit()
        {
        }

        //----------------------------------------------------------------------------------
        // Method:      AutonomousPeriodic
        // Description: This runs after the autonomous mode initialization has completed.
        //              It runs every loop (approximately every 20 milliseconds)  while
        //              the robot is in autonomous mode.
        // Returns:     void
        //----------------------------------------------------------------------------------
        void AutonomousPeriodic()
        {
        }

        //----------------------------------------------------------------------------------
        // Method:      TeleopInit
        // Description: Initialization routine that gets called when the robot enters
        //              the teleop (human controlled) mode.
        // Returns:     void
        //----------------------------------------------------------------------------------
        void TeleopInit()
        {
//          m_currentDriveMode = ARCADE_DRIVE;
//          m_currentDrive = m_arcadeDrive;

//          m_currentDriveMode = TANK_DRIVE;
//          m_currentDrive = m_tankDrive;

            // Run the teleop drive
            m_currentDriveMode = ARCADE_DRIVE;          // default
            m_currentDrive = m_arcadeDrive;             // default

            /*
            m_selectedTeleopMode = *((std::string*) m_teleopChooser->GetSelected() );
            if (m_selectedTeleopMode == m_driveJoystickTankDrive )
            {
                m_currentDriveMode = TANK_DRIVE;
                m_currentDrive = m_tankDrive;
            }
            */
        }

        //----------------------------------------------------------------------------------
        // Method:      TeleopPeriodic
        // Description: This runs after the teleop mode initialization has completed.
        //              It runs every loop (approximately every 20 milliseconds)  while
        //              the robot is in teleop mode.
        // Returns:     void
        //----------------------------------------------------------------------------------
        void TeleopPeriodic()
        {
            SmartDashboard::PutNumber(" Drive mode", m_currentDriveMode );
            SmartDashboard::PutString(" Drive type", m_currentDrive->GetIdentifier() );

            m_chassis->UpdateLineTrackerLights();
            if ( m_oi->GetRawButton( STOP_AUTON_MODE ) )
            {
                m_followLine->Stop();
                m_autonMode = false;
            }
            else if ( m_oi->GetRawButton( START_AUTON_MODE ) )
            {
                m_autonMode = true;
            }
            SmartDashboard::PutBoolean(" auton ", m_autonMode );

            if ( m_autonMode )
            {
               m_followLine->Drive();
            }
            else
            {
 //                BUTTON_STATE state = m_oi->GetButtonState( SWITCH_DRIVE_MODE );
 //                if ( state == BUTTON_PRESSED )
 //               {
 //                   float target = 0.0;
 //                   switch ( m_currentDriveMode )
 //                   {
 //                   case TANK_DRIVE:
 //                       m_currentDriveMode = ARCADE_DRIVE;
 //                       m_currentDrive = m_arcadeDrive;
 //                       break;

 //                   case ARCADE_DRIVE:
 //                       m_currentDriveMode = TANK_DRIVE;
 //                       m_currentDrive = m_tankDrive;
 //                       break;

 //                   default:
 //                       m_currentDriveMode = TANK_DRIVE;
 //                       m_currentDrive = m_tankDrive;
 //                      break;
 //                   }
 //               }

                // teleop drive
                m_currentDrive->DriveWithJoysticks();

                // handle the teleop shoot code
                m_loader->CycleLoader();
                m_shooterAlignment->AdjustShooterPosition();
                m_shooterWheel->SpinWheels();
            }
        }

        //----------------------------------------------------------------------------------
        // Method:      TestInit
        // Description: Initialization routine that gets called when the robot enters
        //              the test (diagnostics) mode.
        // Returns:     void
        //----------------------------------------------------------------------------------
        void TestInit()
        {
        }

        //----------------------------------------------------------------------------------
        // Method:      TestPeriodic
        // Description: This runs after the test mode initialization has completed.
        //              It runs every loop (approximately every 20 milliseconds)  while
        //              the robot is in test mode.
        // Returns:     void
        //----------------------------------------------------------------------------------
        void TestPeriodic()
        {
        }
};

START_ROBOT_CLASS(Robot)
