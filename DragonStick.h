/*========================================================================================================
 * DragonStick.h
 *========================================================================================================
 *
 * File Description:
 *
 * This implements basic joystick functionality with deadband and scaling on the axis.
 *========================================================================================================
 *  Modifications:
 *  Date            Name            Description of Change
 *  18-Oct-2016     Joe Witcpalek   Created File
 *========================================================================================================*/

#ifndef SRC_DRAGONSTICK_H_
#define SRC_DRAGONSTICK_H_

#include <Joystick.h>
enum BUTTON_IDENTIFIER
{
    A_BUTTON,
    B_BUTTON,
    X_BUTTON,
    Y_BUTTON,
    LEFT_BUMPER,
    RIGHT_BUMPER,
    SELECT_BUTTON,
    START_BUTTON,
    PRESS_LEFT_STICK,
    PRESS_RIGHT_STICK,
    LEFT_TRIGGER_PRESSED,
    RIGHT_TRIGGER_PRESSED,
    POV_0_PRESSED,
    POV_45_PRESSED,
    POV_90_PRESSED,
    POV_135_PRESSED,
    POV_180_PRESSED,
    POV_225_PRESSED,
    POV_270_PRESSED,
    POV_315_PRESSED,
    MAX_BUTTONS
};

enum BUTTON_STATE
{
    BUTTON_NOT_PRESSED, // previous check the button wasn't pressed and it still isn't
    BUTTON_PRESSED,     // previous check the button wasn't pressed and now it is
    BUTTON_HELD,        // previous check the button was pressed and it still is
    BUTTON_RELEASED     // previous check the button was pressed and now it isn't
};

enum AXIS_IDENTIFIER
{
    X_AXIS_LEFT_JOYSTICK,
    Y_AXIS_LEFT_JOYSTICK,
    LEFT_TRIGGER,
    RIGHT_TRIGGER,
    X_AXIS_RIGHT_JOYSTICK,
    Y_AXIS_RIGHT_JOYSTICK,
    MAX_AXIS
};

enum AXIS_PROFILE
{
    LINEAR_SCALING,     // the value is just returned
    CUBIC_SCALING       // the value is cubed before it is returned
};

class DragonStick : public Joystick
{
    public:



        //------------------------------------------------------------------
        // Method:      DragonStick     <<constructor>>
        // Description: Create and initialize the joystick.
        //------------------------------------------------------------------
        DragonStick
        (
            uint32_t    port        // <I> - input port identifier
        );

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
            uint32_t axis,              // <I> - axis number to update
            float    scaleFactor        // <I> - scale factor used to limit the range
        );

        //------------------------------------------------------------------
        // Method:      SetAxisProfile
        // Description: Sets the axis profile for the specifed axis
        // Returns:     void
        //------------------------------------------------------------------
        void SetAxisProfile
        (
               uint32_t     axis,           // <I> - axis number to update
               AXIS_PROFILE profile         // <I> - profile to use
        );

        //------------------------------------------------------------------
        // Method:      GetRawAxis
        // Description: Reads the joystick axis, removes any deadband (small
        //              value) and then scales as requested.
        // Returns:     float   -  scaled axis value
        //------------------------------------------------------------------
        float GetRawAxis
        (
            uint32_t axis           // <I> - axis number to query
        ) const override;

        //------------------------------------------------------------------
        // Method:      GetRawButton
        // Description: Reads the button value.  Also allows POV, bumpers,
        //              and triggers to be treated as buttons.
        // Returns:     bool   -  scaled axis value
        //------------------------------------------------------------------
        bool GetRawButton
        (
            uint32_t button           // <I> - button number to query
        ) const override;


        //------------------------------------------------------------------
        // Method:      GetButtonState
        // Description: Reads the button value and compares it to the last
        //              time the button state was checked.
        // Returns:     BUTTON_STATE   -  button state as documented above
        //------------------------------------------------------------------
        BUTTON_STATE GetButtonState
        (
            uint32_t button           // <I> - button number to query
        );


        virtual ~DragonStick() = default;

    private:
        //------------------------------------------------------------------
        // Method:      GetAxisScaleFactor
        // Description: returns the scale factor for axis which includes
        //              inversion, if necessary.
        // Returns:     float       scale factor
        //------------------------------------------------------------------
        float GetAxisScaleFactor
        (
               uint32_t axis           // <I> - axis number to query
        ) const;

        //------------------------------------------------------------------
        // Method:      GetAxisProfile
        // Description: returns the axis profile for the specifed axis
        // Returns:     AXIS_PROFILE    - axis profile as documented above
        //------------------------------------------------------------------
        AXIS_PROFILE GetAxisProfile
        (
               uint32_t axis           // <I> - axis number to query
        ) const;

        //------------------------------------------------------------------
        // Method:      GetButtonPressedPrev
        // Description: returns whether the button was previously press or not
        // Returns:     bool        true - it was previously pressed
        //                          false - it wasn't previously pressed
        //------------------------------------------------------------------
        bool GetButtonPressedPrev
        (
            uint32_t button           // <I> - button number to query
        ) const;

        //------------------------------------------------------------------
        // Method:      SetButtonPressedPrev
        // Description: caches the buttons current setting
        // Returns:     void
        //------------------------------------------------------------------
        void SetButtonPressedPrev
        (
            uint32_t button,            // <I> - button number to query
            bool     isPressed          // <I> - true = button is pressed
                                        //       false = button is not pressed
        ) ;

        // Constants
        const float m_DEAD_BAND_THRESHOLD = 0.2; // Axis Deadband Constant - if < abs of this, it is considered 0.0
        const float m_TRIGGER_PRESSED_THRESHOLD = 0.4; // When treating a trigger as a button, greater than this value means it is pressed

        //------------------------------------------------------------------
        // Attributes
        //------------------------------------------------------------------
        std::vector<float>          m_axisScale;                // scale factor used to limit the range of axis values
                                                                // returned

        std::vector<float>          m_axisInvertScale;          // scale factors used to invert the axis values (always 1.0
                                                                // or -1.0) the index into the vector is AXIS_IDENTIFIER.

        std::vector<AXIS_PROFILE>   m_axisProfile;              // the profile for "scaling" the axis values
                                                                // the index into the vector is AXIS_IDENTIFIER.

        std::vector<bool>           m_buttonPressedPreviously;  // indicates whether the button was press on its last query
                                                                // or notBUTTON_IDENTIFIER is the index into the vector.

        // Default methods we don't want the compiler to implement for us
        DragonStick() = delete;
        DragonStick( const DragonStick& ) = delete;
        DragonStick& operator= ( const DragonStick& ) = delete;
        explicit DragonStick( DragonStick* other ) = delete;
};

#endif /* SRC_DRAGONSTICK_H_ */
