/*========================================================================================================
 * DragonStick.cpp
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

// Standard includes
#include <algorithm>    // std::fill
#include <cmath>        // std:abs
#include <vector>       // std::vector

// WPILIB includes
#include <Joystick.h>
#include <SmartDashboard/SmartDashboard.h>  // Smart Dashboard

// Team 302 includes
#include <DragonStick.h>
#include <LimitValue.h>

//------------------------------------------------------------------
// Method:      DragonStick     <<constructor>>
// Description: Create and initialize the joystick.
//------------------------------------------------------------------
DragonStick::DragonStick
(
    uint32_t    port        // <I> - input port identifier
) : Joystick( port ),
    m_axisScale(),
    m_axisInvertScale(),
    m_axisProfile(),
    m_buttonPressedPreviously()
{
    // initialize axis scale factor
    m_axisScale.resize( MAX_AXIS );
    std::fill( m_axisScale.begin(), m_axisScale.end(), 1.0 );

    // initialize axis reversed
    m_axisInvertScale.resize( MAX_AXIS );
    std::fill( m_axisInvertScale.begin(), m_axisInvertScale.end(), 1.0 );
    m_axisInvertScale[Y_AXIS_LEFT_JOYSTICK] = -1.0;     // forward is negative so, make forward positive
    m_axisInvertScale[Y_AXIS_RIGHT_JOYSTICK] = -1.0;    // forward is negative so, make forward positive

    // initialize the axis profile
    m_axisProfile.resize( MAX_AXIS );
    std::fill( m_axisProfile.begin(), m_axisProfile.end(), LINEAR_SCALING );

    // initialize all buttons not pressed
    m_buttonPressedPreviously.resize( MAX_BUTTONS );
    std::fill( m_buttonPressedPreviously.begin(), m_buttonPressedPreviously.end(), false );
}

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
void DragonStick::SetScaleFactor
(
    uint32_t    axis,               // <I> - axis number to update
    float       scaleFactor         // <I> - scale factor used to limit the range
)
{
    if ( axis < m_axisScale.size() )    // only if it is a valid axis
    {
        // verify the value is within range and then set the attribute
        float scale = LimitValue::ForceInRange( scaleFactor, 0.0, 1.0 );
        m_axisScale[axis] = scale;
    }
}

//------------------------------------------------------------------
// Method:      SetAxisProfile
// Description: Sets the axis profile for the specifed axis
// Returns:     void
//------------------------------------------------------------------
void DragonStick::SetAxisProfile
(
    uint32_t    axis,           // <I> - axis number to update
    AXIS_PROFILE profile        // <I> - profile to use
)
{
    if ( axis < m_axisProfile.size() )  // only if it is a valid axis
    {
        m_axisProfile[axis] = profile;
    }
}

//------------------------------------------------------------------
// Method:      GetRawAxis
// Description: Reads the joystick axis, removes any deadband (small
//              value) and then scales as requested.
// Returns:     float   -  scaled axis value
//------------------------------------------------------------------
float DragonStick::GetRawAxis(uint32_t axis) const
{
    float output = Joystick::GetRawAxis(axis);                  //Get original value from joystick

    SmartDashboard::PutNumber(" deadband", DragonStick::m_DEAD_BAND_THRESHOLD );

    SmartDashboard::PutNumber(" raw value - left x ", Joystick::GetRawAxis( X_AXIS_LEFT_JOYSTICK ) );
    SmartDashboard::PutNumber(" profile - left x", GetAxisProfile( X_AXIS_LEFT_JOYSTICK ) );
    SmartDashboard::PutNumber(" scale - left x", GetAxisScaleFactor( X_AXIS_LEFT_JOYSTICK ) );

    SmartDashboard::PutNumber(" raw value - left y ", Joystick::GetRawAxis( Y_AXIS_LEFT_JOYSTICK ) );
    SmartDashboard::PutNumber(" profile - left y", GetAxisProfile( Y_AXIS_LEFT_JOYSTICK ) );
    SmartDashboard::PutNumber(" scale - left y", GetAxisScaleFactor( Y_AXIS_LEFT_JOYSTICK ) );

    SmartDashboard::PutNumber(" raw value - right x ", Joystick::GetRawAxis( X_AXIS_RIGHT_JOYSTICK ) );
    SmartDashboard::PutNumber(" profile - right x", GetAxisProfile( X_AXIS_RIGHT_JOYSTICK ) );
    SmartDashboard::PutNumber(" scale - right x", GetAxisScaleFactor( X_AXIS_RIGHT_JOYSTICK ) );

    SmartDashboard::PutNumber(" raw value - right y ", Joystick::GetRawAxis( Y_AXIS_RIGHT_JOYSTICK ) );
    SmartDashboard::PutNumber(" profile - right y", GetAxisProfile( Y_AXIS_RIGHT_JOYSTICK ) );
    SmartDashboard::PutNumber(" scale - right y", GetAxisScaleFactor( Y_AXIS_RIGHT_JOYSTICK ) );

    if( std::abs(output) < DragonStick::m_DEAD_BAND_THRESHOLD ) //Check if the joystick value is within the dead band threshold
    {
        output = 0.0;
    }
    else
    {
        if ( GetAxisProfile( axis ) == CUBIC_SCALING )
        {
            output = std::pow( output, 3.0 );
        }
        output *= GetAxisScaleFactor( axis );   //Multiply output by m_scale and invert if necessary
    }

    return output;
}

//------------------------------------------------------------------
// Method:      GetRawButton
// Description: Reads the button value.  Also allows POV, bumpers,
//              and triggers to be treated as buttons.
// Returns:     bool   -  scaled axis value
//------------------------------------------------------------------
bool DragonStick::GetRawButton
(
    uint32_t button           // <I> - button number to query
) const
{
    bool pressed = false;
    if ( button < LEFT_TRIGGER_PRESSED )
    {
        pressed = Joystick::GetRawButton( button );
    }
    else if ( button == LEFT_TRIGGER_PRESSED )
    {
        pressed = ( Joystick::GetRawAxis( LEFT_TRIGGER ) > m_TRIGGER_PRESSED_THRESHOLD );
    }
    else if ( button == RIGHT_TRIGGER_PRESSED )
    {
        pressed = ( Joystick::GetRawAxis( RIGHT_TRIGGER ) > m_TRIGGER_PRESSED_THRESHOLD );
    }
    else
    {
        int povPressed = Joystick::GetPOV();
        if ( povPressed > -1 )
        {
            if ( button == POV_0_PRESSED )
            {
                pressed = ( povPressed == 0 );
            }
            else if ( button == POV_45_PRESSED )
            {
                pressed = ( povPressed == 45 );
            }
            else if ( button == POV_90_PRESSED )
            {
                pressed = ( povPressed == 90 );
            }
            else if ( button == POV_135_PRESSED )
            {
                pressed = ( povPressed == 135 );
            }
            else if ( button == POV_180_PRESSED )
            {
                pressed = ( povPressed == 180 );
            }
            else if ( button == POV_225_PRESSED )
            {
                pressed = ( povPressed == 225 );
            }
            else if ( button == POV_270_PRESSED )
            {
                pressed = ( povPressed == 270 );
            }
            else if ( button == POV_315_PRESSED )
            {
                pressed = ( povPressed == 315 );
            }
        }
    }
    return pressed;
}

//------------------------------------------------------------------
// Method:      GetButtonState
// Description: Reads the button value and compares it to the last
//              time the button state was checked.
// Returns:     BUTTON_STATE   -  button state as documented above
//------------------------------------------------------------------
BUTTON_STATE DragonStick::GetButtonState
(
    uint32_t button           // <I> - button number to query
)
{
    BUTTON_STATE state = BUTTON_NOT_PRESSED;
    bool prevPressed = GetButtonPressedPrev( button );
    bool isPressed = GetRawButton( button );
    if ( prevPressed )
    {
        if ( isPressed )
        {
            state = BUTTON_HELD;
        }
        else
        {
            state = BUTTON_RELEASED;
        }
    }
    else
    {
        if ( isPressed )
        {
            state = BUTTON_PRESSED;
        }
        else
        {
            state = BUTTON_NOT_PRESSED;
        }
    }

    return state;
}
//------------------------------------------------------------------
// Method:      GetButtonPressedPrev
// Description: returns whether the button was previously press or not
// Returns:     bool        true - it was previously pressed
//                          false - it wasn't previously pressed
//------------------------------------------------------------------
bool DragonStick::GetButtonPressedPrev
(
    uint32_t button           // <I> - button number to query
) const
{
    return (( button < m_buttonPressedPreviously.size() ) ? m_buttonPressedPreviously[button] : false);
}


//------------------------------------------------------------------
// Method:      GetAxisScaleFactor
// Description: returns the scale factor for axis which includes
//              inversion, if necessary.
// Returns:     float       scale factor
//------------------------------------------------------------------
float DragonStick::GetAxisScaleFactor
(
       uint32_t axis           // <I> - axis number to query
) const
{
    float scale = 1.0;
    if ( axis < m_axisInvertScale.size() && axis < m_axisScale.size() ) // only if it is a valid axis
    {
        scale = m_axisInvertScale[axis] * m_axisScale[axis];
    }
    return scale;
}

//------------------------------------------------------------------
// Method:      GetAxisProfile
// Description: returns the axis profile for the specifed axis
// Returns:     AXIS_PROFILE    - axis profile as documented above
//------------------------------------------------------------------
AXIS_PROFILE DragonStick::GetAxisProfile
(
       uint32_t axis           // <I> - axis number to query
) const
{
    return ( ( axis < m_axisProfile.size() ) ? m_axisProfile[axis] : LINEAR_SCALING );
}




