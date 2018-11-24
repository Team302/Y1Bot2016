/*=============================================================================================
 * LineTracker.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This class wraps an analog input line tracker simpifying the input to have methods to
 * return whether the line tracker sees white or black.
 *=============================================================================================*/


// WPILIB includes
#include <AnalogInput.h>        // parent class
#include <SmartDashboard/SmartDashboard.h>  // Smart Dashboard

// Team 302 includes
#include <LineTracker.h>            // This class

//--------------------------------------------------------------------
// Method:      LineTracker <<constructor>>
// Description: This method creates and initializes the objects
//--------------------------------------------------------------------
LineTracker::LineTracker
(
    uint32_t        channel     // <I> - analog input channel
) : AnalogInput( channel )      // initialize the parent class
{
}

//--------------------------------------------------------------------
// Method:      IsBlack
// Description: This method returns whether the line tracker sees black
//              or not.
// Returns:     bool        true  = sees black
//                          false = doesn't see black
//--------------------------------------------------------------------
bool LineTracker::IsBlack() const
{
    bool seesBlack = false;
    float voltage = GetVoltage();
    SmartDashboard::PutNumber(" isBlack", voltage );

    if ( voltage >= LOWER_BLACK_VALUE && voltage <= UPPER_BLACK_VALUE )
    {
        seesBlack = true;
    }
    return seesBlack;
}

//--------------------------------------------------------------------
// Method:      IsWhite
// Description: This method returns whether the line tracker sees white
//              or not.
// Returns:     bool        true  = sees white
//                          false = doesn't see white
//--------------------------------------------------------------------
bool LineTracker::IsWhite() const
{
    bool seesWhite = false;
    float voltage = GetVoltage();
    SmartDashboard::PutNumber(" isBlack", voltage );
    if ( voltage >= LOWER_WHITE_VALUE && voltage <= UPPER_WHITE_VALUE )
    {
        seesWhite = true;
    }
    return seesWhite;
}


