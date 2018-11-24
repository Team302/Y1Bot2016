/*=============================================================================================
 * IShooterFactory.h
 *=============================================================================================
 *
 * File Description:
 *
 * This creates the IShooter classes.  It will create the shooter based on the value in RobotMap.h.
 *
 *=============================================================================================*/

#ifndef SRC_ISHOOTERFACTORY_H_
#define SRC_ISHOOTERFACTORY_H_


//  Team 302 includes
#include <IShooter.h>


class IShooterFactory
{
    public:
    //----------------------------------------------------------------------------------
    // Method:      GetInstance
    // Description: If there isn't an instance, create it.
    //              Otherwise, hand out the single instance.
    // Returns:     IShooterFactory*    This class
    //----------------------------------------------------------------------------------
    static IShooterFactory* GetInstance();

    //----------------------------------------------------------------------------------
    // Method:      GetIShooter
    // Description: If there isn't an instance of desired IShooter class, create it.
    //              Otherwise, hand out the single instance.
    // Returns:     IShooter*   Chassis class
    //----------------------------------------------------------------------------------
    IShooter*   GetIShooter();

    protected:

    private:
        //--------------------------------------------------------------------
        // Method:      IShooterFactory <<constructor>>
        // Description: This method creates and initializes the objects
        //--------------------------------------------------------------------
        IShooterFactory();      // constructor

        //--------------------------------------------------------------------
        // Method:      ~IShooterFactory <<destructor>>
        // Description: This method is called to delete these objects
        //--------------------------------------------------------------------
        virtual ~IShooterFactory(); // destructor

        // Attributes
        static IShooterFactory*         m_instance;     // the factory
        IShooter*                       m_shooter;

        // Default methods we don't want the compiler to implement for us
        IShooterFactory( const IShooterFactory& ) = delete;
        IShooterFactory& operator= ( const IShooterFactory& ) = delete;
        explicit IShooterFactory( IShooterFactory* other ) = delete;


};

#endif /* SRC_ISHOOTERFACTORY_H_ */
