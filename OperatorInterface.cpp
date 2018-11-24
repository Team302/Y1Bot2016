/*========================================================================================================
 * OperatorInterface.cpp
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

#include <SmartDashboard/SmartDashboard.h>  // Smart Dashboard

// Team 302 includes
#include <OperatorInterface.h>
#include <DragonStick.h>
#include <RobotMap.h>


//----------------------------------------------------------------------------------
// Method:      GetInstance
// Description: If there isn't an instance of this class, it will create one.  The
//              single class instance will be returned.
// Returns:     OperatorInterface*  instance of this class
//----------------------------------------------------------------------------------
OperatorInterface* OperatorInterface::m_instance = nullptr; // initialize the instance variable to nullptr
OperatorInterface* OperatorInterface::GetInstance()
{
    if ( OperatorInterface::m_instance == nullptr )
    {
        OperatorInterface::m_instance = new OperatorInterface();
    }
    return OperatorInterface::m_instance;
}
//----------------------------------------------------------------------------------
// Method:      OperatorInterface <<constructor>>
// Description: This will construct and initialize the object.
//              It creates the driver controller and the co-pilot controller and
//              them maps the functions to the buttons/axis.
//----------------------------------------------------------------------------------
OperatorInterface::OperatorInterface() : m_gamePads()
{
    m_gamePads[ m_driverStick ]  = new DragonStick( m_driverStick );
    m_gamePads[ m_copilotStick ] = new DragonStick( m_copilotStick );
    Mapper();
}

//----------------------------------------------------------------------------------
// Method:      Mapper
// Description: This will map the external enums to the actual control button/axis
// Returns:     void
//----------------------------------------------------------------------------------
void OperatorInterface::Mapper()
{
    // Initialize the items to not defined
    for ( int inx=0; inx<m_maxFunctions; ++inx )
    {
        m_gamePadIDs[inx] = m_undefinedMapping;
        m_axisIDs[inx]    = m_undefinedMapping;
        m_buttonIDs[inx]  = m_undefinedMapping;
    }

    // Map the functions to the axis/buttons on the dragonstick
    m_gamePadIDs[ TANK_DRIVE_LEFT_CONTROL ] = m_driverStick;
    m_axisIDs[ TANK_DRIVE_LEFT_CONTROL ]    = Y_AXIS_LEFT_JOYSTICK;

//    SmartDashboard::PutNumber(" tdrive left", Y_AXIS_LEFT_JOYSTICK );


    m_gamePadIDs[ TANK_DRIVE_RIGHT_CONTROL ] = m_driverStick;
    m_axisIDs[ TANK_DRIVE_RIGHT_CONTROL ]    = Y_AXIS_RIGHT_JOYSTICK;

//    SmartDashboard::PutNumber(" tdrive right", Y_AXIS_RIGHT_JOYSTICK );

    m_gamePadIDs[ ARCADE_DRIVE_THROTTLE ] = m_driverStick;
    m_axisIDs[ ARCADE_DRIVE_THROTTLE ]    = Y_AXIS_LEFT_JOYSTICK;

    m_gamePadIDs[ ARCADE_DRIVE_STEER ] = m_driverStick;
    m_axisIDs[ ARCADE_DRIVE_STEER ]    = X_AXIS_RIGHT_JOYSTICK;

    m_gamePadIDs[ SWITCH_DRIVE_MODE ] = m_driverStick;
    m_buttonIDs[ SWITCH_DRIVE_MODE ]  = SELECT_BUTTON;

    m_gamePadIDs[ ALIGN_SHOOTER_LEFT_BUTTON ] = m_driverStick;
    m_buttonIDs[ ALIGN_SHOOTER_LEFT_BUTTON ]  = POV_270_PRESSED;

    m_gamePadIDs[ ALIGN_SHOOTER_RIGHT_BUTTON ] = m_driverStick;
    m_buttonIDs[ ALIGN_SHOOTER_RIGHT_BUTTON ]  = POV_90_PRESSED;

    m_gamePadIDs[ LOAD_BALL_BUTTON ] = m_driverStick;
    m_buttonIDs[ LOAD_BALL_BUTTON ]  = LEFT_TRIGGER_PRESSED;

    m_gamePadIDs[ SPIN_SHOOTER_WHEEL ] = m_driverStick;
    m_buttonIDs[ SPIN_SHOOTER_WHEEL ]  = RIGHT_TRIGGER_PRESSED;

    m_gamePadIDs[ START_AUTON_MODE ] = m_driverStick;
    m_buttonIDs[ START_AUTON_MODE ]  = X_BUTTON;

    m_gamePadIDs[ STOP_AUTON_MODE ] = m_driverStick;
    m_buttonIDs[ STOP_AUTON_MODE ]  = Y_BUTTON;
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
void OperatorInterface::SetScaleFactor
(
    FUNCTION_IDENTIFIER     function,      // <I> - function that will update an axis
    float                   scaleFactor    // <I> - scale factor used to limit the range
)
{
    DragonStick* stick = GetStick( function );
    if ( stick != nullptr )
    {
        if ( m_axisIDs[ function ] != m_undefinedMapping )
        {
            stick->SetScaleFactor( m_axisIDs[ function ], scaleFactor );
        }
    }
}

//------------------------------------------------------------------
// Method:      SetAxisProfile
// Description: Sets the axis profile for the specifed axis
// Returns:     void
//------------------------------------------------------------------
void OperatorInterface::SetAxisProfile
(
    FUNCTION_IDENTIFIER     function,       // <I> - function that will update an axis
    AXIS_PROFILE            profile         // <I> - profile to use
)
{
    DragonStick* stick = GetStick( function );
    if ( stick != nullptr )
    {
        if ( m_axisIDs[ function ] != m_undefinedMapping )
        {
            stick->SetAxisProfile( m_axisIDs[ function ], profile );
        }
    }
}

//------------------------------------------------------------------
// Method:      GetRawAxis
// Description: Reads the joystick axis, removes any deadband (small
//              value) and then scales as requested.
// Returns:     float   -  scaled axis value
//------------------------------------------------------------------
float OperatorInterface::GetRawAxis
(
    FUNCTION_IDENTIFIER     function        // <I> - function that whose axis will be read
) const
{
    float value = 0.0;
    DragonStick* stick = GetStick( function );
    if ( stick != nullptr )
    {
        if ( m_axisIDs[ function ] != m_undefinedMapping )
        {
            value = stick->GetRawAxis( m_axisIDs[ function ] );
        }
    }
    return value;
}

//------------------------------------------------------------------
// Method:      GetRawButton
// Description: Reads the button value.  Also allows POV, bumpers,
//              and triggers to be treated as buttons.
// Returns:     bool   -  scaled axis value
//------------------------------------------------------------------
bool OperatorInterface::GetRawButton
(
    FUNCTION_IDENTIFIER     function        // <I> - function that whose button will be read
) const
{
    bool isSelected = false;
    DragonStick* stick = GetStick( function );
    if ( stick != nullptr )
    {
        if ( m_buttonIDs[ function ] != m_undefinedMapping )
        {
            isSelected = stick->GetRawButton( m_buttonIDs[ function ] );
        }
    }
    return isSelected;
}


//------------------------------------------------------------------
// Method:      GetButtonState
// Description: Reads the button value and compares it to the last
//              time the button state was checked.
// Returns:     BUTTON_STATE   -  button state as documented above
//------------------------------------------------------------------
BUTTON_STATE OperatorInterface::GetButtonState
(
    FUNCTION_IDENTIFIER     function        // <I> - function that whose button will be read
)
{
    BUTTON_STATE state = BUTTON_NOT_PRESSED;
    DragonStick* stick = GetStick( function );
    if ( stick != nullptr )
    {
        if ( m_buttonIDs[ function ] != m_undefinedMapping )
        {
            state = stick->GetButtonState( m_buttonIDs[ function ] );
        }
    }
    return state;
}

DragonStick* OperatorInterface::GetStick
(
        FUNCTION_IDENTIFIER function        // <I> - function being processed
) const
{
    DragonStick* stick = nullptr;
    if ( m_gamePadIDs[ function ] != m_undefinedMapping )
    {
        stick = m_gamePads[ m_gamePadIDs[ function ] ];
    }
    return stick;
}



//----------------------------------------------------------------------------------
// Method:      ~OperatorInterface <<destructor>>
// Description: This will clean up the object
//----------------------------------------------------------------------------------
OperatorInterface::~OperatorInterface()
{
    delete m_gamePads[ m_driverStick ];
    m_gamePads[ m_driverStick ] = nullptr;

    delete m_gamePads[ m_copilotStick ];
    m_gamePads[ m_copilotStick ] = nullptr;
}

