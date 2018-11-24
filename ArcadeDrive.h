/*=============================================================================================
 * ArcadeDrive.h
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

#ifndef SRC_ARCADEDRIVE_H_
#define SRC_ARCADEDRIVE_H_

#include <OperatorInterface.h>

//  Team 302 includes
#include <IJoystickDrive.h>     // Interface being implemented
#include <IChassis.h>           // Class that controls the motors on the drive chassis

class ArcadeDrive: public IJoystickDrive
{
    public:
        //--------------------------------------------------------------------
        // Method:      ArcadeDrive <<constructor>>
        // Description: This method creates and initializes the objects
        //--------------------------------------------------------------------
        ArcadeDrive();      // constructor

        //--------------------------------------------------------------------
        // Method:      DriveWithJoysticks
        // Description: This method will be called during the periodic loop
        //              to drive the robot.  It will interact with the joysticks
        //              to drive in arcade drive mode.
        // Returns:     void
        //--------------------------------------------------------------------
        void DriveWithJoysticks() const override;

        //--------------------------------------------------------------------
        // Method:      GetIdentifier
        // Description: This gets the name that identifies the drive mode..
        // Returns:     const char*         identifier for the drive
        //--------------------------------------------------------------------
        const char* GetIdentifier() const override;


        //--------------------------------------------------------------------
        // Method:      ~ArcadeDrive <<destructor>>
        // Description: This method is called to delete these objects
        //--------------------------------------------------------------------
        virtual ~ArcadeDrive() = default; // destructor

    protected:

    private:
        // Attributes
        IChassis*               m_chassis;
        OperatorInterface*      m_oi;

        // Default methods we don't want the compiler to implement for us
        ArcadeDrive( const ArcadeDrive& ) = delete;
        ArcadeDrive& operator= ( const ArcadeDrive& ) = delete;
        explicit ArcadeDrive( ArcadeDrive* other ) = delete;


};

#endif /* SRC_ARCADEDRIVE_H_ */
