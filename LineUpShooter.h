/*=============================================================================================
 * LineUpShooter.h
 *=============================================================================================
 *
 * File Description:
 *
 * This controls shifting the shooter left or right.
 *=============================================================================================*/

#ifndef SRC_LINEUPSHOOTER_H_
#define SRC_LINEUPSHOOTER_H_


//  Team 302 includes
#include <IShooter.h>           // Class that controls the shooter motors
#include <OperatorInterface.h>  // Driver Game pad interface

class LineUpShooter
{
    public:
        //--------------------------------------------------------------------
        // Method:      LineUpShooter <<constructor>>
        // Description: This method creates and initializes the objects
        //--------------------------------------------------------------------
        LineUpShooter();      // constructor

        //--------------------------------------------------------------------
        // Method:      AdjustShooterPosition
        // Description: This method will read the gamepad input and move the
        //              shooter left or right if the correct input is pressed
        // Returns:     void
        //--------------------------------------------------------------------
        void AdjustShooterPosition() const;

        //--------------------------------------------------------------------
        // Method:      ~LineUpShooter <<destructor>>
        // Description: This method is called to delete these objects
        //--------------------------------------------------------------------
        virtual ~LineUpShooter() = default; // destructor

    protected:

        //--------------------------------------------------------------------
        // Method:      ShiftLeft
        // Description: This method will move the shooter to the left
        // Returns:     bool    true  = already at the farthest left postion
        //                      false = can move farther left
        //--------------------------------------------------------------------
        bool ShiftLeft() const;


        //--------------------------------------------------------------------
        // Method:      ShiftRight
        // Description: This method will move the shooter to the right
        // Returns:     bool    true  = already at the farthest right postion
        //                      false = can move farther right
        //--------------------------------------------------------------------
        bool ShiftRight() const;

    private:
        // Attributes
        OperatorInterface*      m_oi;
        IShooter*               m_shooter;

        const float m_leftSpeed = -0.35;
        const float m_rightSpeed = 0.35;
        // Default methods we don't want the compiler to implement for us
        LineUpShooter( const LineUpShooter& ) = delete;
        LineUpShooter& operator= ( const LineUpShooter& ) = delete;
        explicit LineUpShooter( LineUpShooter* other ) = delete;


};

#endif /* SRC_LINEUPSHOOTER_H_ */
