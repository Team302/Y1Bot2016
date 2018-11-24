/*=============================================================================================
 * LineUpShooter.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This controls shifting the shooter left or right.
 *=============================================================================================*/

// Team 302 includes
#include <LineUpShooter.h>          // This class
#include <IShooter.h>               // Class the control the shooter motors
#include <IShooterFactory.h>        // Class constructs the correct chassis
#include <OperatorInterface.h>      // Controls creating singleton of the gamepads
#include <DigitalInput.h>
#include <Year1Shooter.h>
//--------------------------------------------------------------------
// Method:      LineUpShooter <<constructor>>
// Description: This method creates and initializes the objects
//--------------------------------------------------------------------
LineUpShooter::LineUpShooter() : m_oi( OperatorInterface::GetInstance() ),
                                 m_shooter( IShooterFactory::GetInstance()->GetIShooter() )


{
}


//--------------------------------------------------------------------
// Method:      AdjustShooterPosition
// Description: This method will read the gamepad input and move the
//              shooter left or right if the correct input is pressed
// Returns:     void
//--------------------------------------------------------------------
void LineUpShooter::AdjustShooterPosition() const
{
    // TODO:    Read the gamepad ...
    //              if the ALIGN_SHOOTER_RIGHT_BUTTON is pressed move the shooter to the right call ShiftRight).
    //              if the ALIGN_SHOOTER_LEFT_BUTTON is pressed move the shooter to the left (call ShiftLeft).



    if (m_oi-> GetRawButton(ALIGN_SHOOTER_RIGHT_BUTTON))
    {
        ShiftRight();

    }

    else if (m_oi-> GetRawButton(ALIGN_SHOOTER_LEFT_BUTTON))
    {
        ShiftLeft();
    }
    else
    {
        m_shooter->AlignShooter ( 0.0 );
    }
}

//--------------------------------------------------------------------
// Method:      ShiftLeft
// Description: This method will move the shooter to the left
// Returns:     bool    true  = already at the farthest left postion
//                      false = can move farther left
//--------------------------------------------------------------------
bool LineUpShooter::ShiftLeft() const
{
    // TODO:    Set up speed constant in LineUpShooter.h
    //          call m_shooter's AlignShooter method with this speed

    bool    atBound = m_shooter->IsShooterAtLeftBound();
    float   speed = 0.0;
    if ( atBound )
    {
        speed = 0.0;
    }
    else
    {
        speed = m_leftSpeed;
    }
    m_shooter->AlignShooter (speed);
    return false;
}

//--------------------------------------------------------------------
// Method:      ShiftRight
// Description: This method will move the shooter to the right
// Returns:     bool    true  = already at the farthest right postion
//                      false = can move farther right
//--------------------------------------------------------------------
bool LineUpShooter::ShiftRight() const
{
    // TODO:    Set up speed constant in LineUpShooter.h

//          call m_shooter's AlignShooter method with this speed
    bool    atBound = m_shooter->IsShooterAtRightBound();
    float   speed = 0.0;
    if ( atBound )
    {
        speed = 0.0;
    }
    else
    {
        speed = m_rightSpeed;
    }
    m_shooter->AlignShooter (speed);
    return false;
}


