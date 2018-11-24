/*=============================================================================================
 * IJoystickDrive.h
 *=============================================================================================
 *
 * File Description:
 *
 * This is an interface to the various drive test commands
 *=============================================================================================*/
#ifndef SRC_IJOYSTICKDRIVE_H_
#define SRC_IJOYSTICKDRIVE_H_

enum IJOYSTICK_DRIVE_IDENTIFIER
{
    ARCADE_DRIVE,
    TANK_DRIVE,
    MAX_DRIVE_MODES
};

class IJoystickDrive
{

    public:
        //--------------------------------------------------------------------
        // Method:      DriveWithJoysticks
        // Description: This method will be called during the periodic loop
        //              to drive the robot.
        // Returns:     void
        //--------------------------------------------------------------------
        virtual void DriveWithJoysticks() const = 0;

        //--------------------------------------------------------------------
        // Method:      GetIdentifier
        // Description: This gets the name that identifies the drive mode..
        // Returns:     const char*         identifier for the drive
        //--------------------------------------------------------------------
        virtual const char* GetIdentifier() const = 0;


    protected:
        IJoystickDrive() = default;             // default constructor used by the implementors of this interface
        virtual ~IJoystickDrive() = default;    // default destructors used by implementors of this interface

    private:

        // Default methods we don't want the compiler to implement for us
        IJoystickDrive( const IJoystickDrive& ) = delete;
        IJoystickDrive& operator= ( const IJoystickDrive& ) = delete;
        explicit IJoystickDrive( IJoystickDrive* other ) = delete;

};


#endif /* SRC_IJoystickDrive_H_ */
