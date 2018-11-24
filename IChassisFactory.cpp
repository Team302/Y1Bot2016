/*=============================================================================================
 * IChassisFactory.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This creates the IChassis classes.  It will create the chassis based on the value in RobotMap.h.
 *
 *=============================================================================================*/

//  Team 302 includes
#include <IChassisFactory.h>            // This class
#include <IChassis.h>
#include <SoftwareTestChassis.h>
#include <Year1Chassis.h>
#include <RobotDefn.h>                  // Contains the information related to which robot to use


IChassisFactory* IChassisFactory::m_instance = nullptr; // initialize the instance variable to nullptr

//----------------------------------------------------------------------------------
// Method:      GetInstance
// Description: If there isn't an instance of desired IChassisFactory class, create it.
//              Otherwise, hand out the single instance.
// Returns:     IChassisFactory*    Chassis factory
//----------------------------------------------------------------------------------
IChassisFactory*    IChassisFactory::GetInstance()

{
    if ( IChassisFactory::m_instance == nullptr )
    {
        IChassisFactory::m_instance = new IChassisFactory();
    }
    return IChassisFactory::m_instance;
}

//--------------------------------------------------------------------
// Method:      IChassisFactory <<constructor>>
// Description: This method creates and initializes the objects
//--------------------------------------------------------------------
IChassisFactory::IChassisFactory() : m_chassis( nullptr )      // constructor
{
}

//--------------------------------------------------------------------
// Method:      ~IChassisFactory <<destructor>>
// Description: This method cleans up when the object gets deleted
//--------------------------------------------------------------------
IChassisFactory::~IChassisFactory()               // destructor
{
    IChassisFactory::m_instance = nullptr;
}

//----------------------------------------------------------------------------------
// Method:      GetIChassis
// Description: If there isn't an instance of desired IChassis class, create it.
//              Otherwise, hand out the single instance.
// Returns:     IChassis*   Chassis class
//----------------------------------------------------------------------------------
IChassis*   IChassisFactory::GetIChassis()
{
    if ( m_chassis == nullptr )
    {
        switch ( ROBOT_CONFIGURATION )
        {
            case SOFTWARE_BOT:
                m_chassis = new SoftwareTestChassis();
                break;

            case YEAR1_BOT:
                m_chassis = new Year1Chassis();
                break;

            default:
                break;
        }
    }
    return m_chassis;
}

