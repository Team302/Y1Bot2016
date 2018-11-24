/*========================================================================================================
 * OperatorInterface.h
 *========================================================================================================
 *
 * File Description:
 *
 * This implements holds onto the instances of the game controllers used by driver and the co-pilot.
 *========================================================================================================
 *  Modifications:
 *  Date            Name            Description of Change
 *  18-Oct-2016     Joe Witcpalek   Created File
 *========================================================================================================*/


#ifndef SRC_OPERATORINTERFACE_H_
#define SRC_OPERATORINTERFACE_H_

// Team 302 includes
#include <DragonStick.h>

enum FUNCTION_IDENTIFIER
{
    TANK_DRIVE_LEFT_CONTROL,
    TANK_DRIVE_RIGHT_CONTROL,
    ARCADE_DRIVE_THROTTLE,
    ARCADE_DRIVE_STEER,
    SWITCH_DRIVE_MODE,
    ALIGN_SHOOTER_LEFT_BUTTON,
    ALIGN_SHOOTER_RIGHT_BUTTON,
    LOAD_BALL_BUTTON,
    SPIN_SHOOTER_WHEEL,
    START_AUTON_MODE,
    STOP_AUTON_MODE,
    MAX_FUNCTIONS
};

class OperatorInterface
{
    public:
        //----------------------------------------------------------------------------------
        // Method:      GetInstance
        // Description: If there isn't an instance of this class, it will create one.  The
        //              single class instance will be returned.
        // Returns:     OperatorInterface*  instance of this class
        //----------------------------------------------------------------------------------
        static OperatorInterface* GetInstance();


        //------------------------------------------------------------------
        // Method:      SetScaleFactor
        // Description: Allow the range of values to be set smaller than
        //              -1.0 to 1.0.  By providing a scale factor between 0.0
        //              and 1.0, the range can be made smaller.  If a value
        //              outside the range is provided, then the value will
        //              be set to the closest bounding value (e.g. 1.5 will
        //              become 1.0)
        // Returns:     void
        //------------------------------------------------------------------
        void SetScaleFactor
        (
            FUNCTION_IDENTIFIER     axis,          // <I> - axis number to update
            float                   scaleFactor    // <I> - scale factor used to limit the range
        );

        //------------------------------------------------------------------
        // Method:      SetAxisProfile
        // Description: Sets the axis profile for the specifed axis
        // Returns:     void
        //------------------------------------------------------------------
        void SetAxisProfile
        (
            FUNCTION_IDENTIFIER     axis,           // <I> - axis number to update
            AXIS_PROFILE            profile         // <I> - profile to use
        );

        //------------------------------------------------------------------
        // Method:      GetRawAxis
        // Description: Reads the joystick axis, removes any deadband (small
        //              value) and then scales as requested.
        // Returns:     float   -  scaled axis value
        //------------------------------------------------------------------
        float GetRawAxis
        (
            FUNCTION_IDENTIFIER     axis          // <I> - axis number to update
        ) const;

        //------------------------------------------------------------------
        // Method:      GetRawButton
        // Description: Reads the button value.  Also allows POV, bumpers,
        //              and triggers to be treated as buttons.
        // Returns:     bool   -  scaled axis value
        //------------------------------------------------------------------
        bool GetRawButton
        (
            FUNCTION_IDENTIFIER button           // <I> - button number to query
        ) const;


        //------------------------------------------------------------------
        // Method:      GetButtonState
        // Description: Reads the button value and compares it to the last
        //              time the button state was checked.
        // Returns:     BUTTON_STATE   -  button state as documented above
        //------------------------------------------------------------------
        BUTTON_STATE GetButtonState
        (
            FUNCTION_IDENTIFIER button           // <I> - button number to query
        );


        //----------------------------------------------------------------------------------
        // Method:      GetDriverController
        // Description: This will return a pointer to the driver controller (DragonStick*).
        // Returns:     DragonStick*    the driver controller
        //----------------------------------------------------------------------------------
//        inline DragonStick* GetDriverController() const { return m_gamePads[ m_driverStick ]; }

        //----------------------------------------------------------------------------------
        // Method:      GetCopilotController
        // Description: This will return a pointer to the co-pilot's controller (DragonStick*).
        // Returns:     DragonStick*    the co-pilot's controller
        //----------------------------------------------------------------------------------
//        inline DragonStick* GetCopilotController() const { return m_gamePads[ m_copilotStick ]; }

    private:

        //----------------------------------------------------------------------------------
        // Method:      Mapper
        // Description: This will map the external enums to the actual control button/axis
        // Returns:     void
        //----------------------------------------------------------------------------------
        void Mapper();

        //----------------------------------------------------------------------------------
        // Method:      OperatorInterface <<constructor>>
        // Description: This will construct and initialize the object
        //----------------------------------------------------------------------------------
        OperatorInterface();

        //----------------------------------------------------------------------------------
        // Method:      ~OperatorInterface <<destructor>>
        // Description: This will clean up the object
        //----------------------------------------------------------------------------------
        virtual ~OperatorInterface();

        DragonStick* GetStick( FUNCTION_IDENTIFIER function ) const;

        //----------------------------------------------------------------------------------
        // Attributes
        //----------------------------------------------------------------------------------
        static OperatorInterface*   m_instance; // Singleton instance of this class

        const uint32_t              m_driverStick   = 0;    // index in m_gamePads for driver controller
        const uint32_t              m_copilotStick  = 1;    // index in m_gamePads for co-pilot controller
        DragonStick*                m_gamePads[2];          // gamepad controller

        const int                   m_maxFunctions = 100;
        const int                   m_undefinedMapping = -1000;
        int                         m_gamePadIDs[100];       //
        int                         m_axisIDs[100];          //
        int                         m_buttonIDs[100];        //

};

#endif /* SRC_OPERATORINTERFACE_H_ */
