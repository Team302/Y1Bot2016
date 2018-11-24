/*=============================================================================================
 * IChassisFactory.h
 *=============================================================================================
 *
 * File Description:
 *
 * This creates the IChassis classes.  It will create the chassis based on the value in RobotMap.h.
 *
 *=============================================================================================*/

#ifndef SRC_ICHASSISFACTORY_H_
#define SRC_ICHASSISFACTORY_H_


//  Team 302 includes
#include <IChassis.h>


class IChassisFactory
{
    public:
    //----------------------------------------------------------------------------------
    // Method:      GetInstance
    // Description: If there isn't an instance, create it.
    //              Otherwise, hand out the single instance.
    // Returns:     IChassisFactory*    This class
    //----------------------------------------------------------------------------------
    static IChassisFactory* GetInstance();

    //----------------------------------------------------------------------------------
    // Method:      GetIChassis
    // Description: If there isn't an instance of desired IChassis class, create it.
    //              Otherwise, hand out the single instance.
    // Returns:     IChassis*   Chassis class
    //----------------------------------------------------------------------------------
    IChassis*   GetIChassis();

    protected:

    private:
        //--------------------------------------------------------------------
        // Method:      IChassisFactory <<constructor>>
        // Description: This method creates and initializes the objects
        //--------------------------------------------------------------------
        IChassisFactory();      // constructor

        //--------------------------------------------------------------------
        // Method:      ~IChassisFactory <<destructor>>
        // Description: This method is called to delete these objects
        //--------------------------------------------------------------------
        virtual ~IChassisFactory(); // destructor

        // Attributes
        static IChassisFactory*         m_instance;     // the factory
        IChassis*                       m_chassis;

        // Default methods we don't want the compiler to implement for us
        IChassisFactory( const IChassisFactory& ) = delete;
        IChassisFactory& operator= ( const IChassisFactory& ) = delete;
        explicit IChassisFactory( IChassisFactory* other ) = delete;


};

#endif /* SRC_ICHASSISFACTORY_H_ */
