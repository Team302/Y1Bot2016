/*=============================================================================================
 * IShooterFactory.cpp
 *=============================================================================================
 *
 * File Description:
 *
 * This creates the IShooter classes.  It will create the shooter based on the value in RobotMap.h.
 *
 *=============================================================================================*/

//  Team 302 includes
#include <IShooterFactory.h>            // This class
#include <IShooter.h>
#include <SoftwareTestShooter.h>
#include <Year1Shooter.h>
#include <RobotDefn.h>                  // Contains the information related to which robot to use


IShooterFactory* IShooterFactory::m_instance = nullptr; // initialize the instance variable to nullptr

//----------------------------------------------------------------------------------
// Method:      GetInstance
// Description: If there isn't an instance of desired IShooterFactory class, create it.
//              Otherwise, hand out the single instance.
// Returns:     IShooterFactory*    Shooter factory
//----------------------------------------------------------------------------------
IShooterFactory*    IShooterFactory::GetInstance()

{
    if ( IShooterFactory::m_instance == nullptr )
    {
        IShooterFactory::m_instance = new IShooterFactory();
    }
    return IShooterFactory::m_instance;
}

//--------------------------------------------------------------------
// Method:      IShooterFactory <<constructor>>
// Description: This method creates and initializes the objects
//--------------------------------------------------------------------
IShooterFactory::IShooterFactory() : m_shooter( nullptr )      // constructor
{
}

//--------------------------------------------------------------------
// Method:      ~IShooterFactory <<destructor>>
// Description: This method cleans up when the object gets deleted
//--------------------------------------------------------------------
IShooterFactory::~IShooterFactory()               // destructor
{
    IShooterFactory::m_instance = nullptr;
}

//----------------------------------------------------------------------------------
// Method:      GetIShooter
// Description: If there isn't an instance of desired IShooter class, create it.
//              Otherwise, hand out the single instance.
// Returns:     IShooter*   Chassis class
//----------------------------------------------------------------------------------
IShooter*   IShooterFactory::GetIShooter()
{
    if ( m_shooter == nullptr )
    {
        switch ( ROBOT_CONFIGURATION )
        {
            case SOFTWARE_BOT:
                m_shooter = new SoftwareTestShooter();
                break;

            case YEAR1_BOT:
                m_shooter = new Year1Shooter();
                break;

            default:
                break;
        }
    }
    return m_shooter;
}

