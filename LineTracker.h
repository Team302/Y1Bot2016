/*=============================================================================================
 * LineTracker.h
 *=============================================================================================
 *
 * File Description:
 *
 * This class wraps an analog input line tracker simpifying the input to have methods to
 * return whether the line tracker sees white or black.
 *=============================================================================================*/

#ifndef SRC_LINETRACKER_H_
#define SRC_LINETRACKER_H_

// WPILIB includes
#include <AnalogInput.h>        // parent class

//  Team 302 includes

class LineTracker : public AnalogInput
{
    public:
        //--------------------------------------------------------------------
        // Method:      LineTracker <<constructor>>
        // Description: This method creates and initializes the objects
        //--------------------------------------------------------------------
        LineTracker
        (
            uint32_t        channel     // <I> - analog input channel
        );      // constructor

        //--------------------------------------------------------------------
        // Method:      IsBlack
        // Description: This method returns whether the line tracker sees black
        //              or not.
        // Returns:     bool        true  = sees black
        //                          false = doesn't see black
        //--------------------------------------------------------------------
        bool IsBlack() const;

        //--------------------------------------------------------------------
        // Method:      IsWhite
        // Description: This method returns whether the line tracker sees white
        //              or not.
        // Returns:     bool        true  = sees white
        //                          false = doesn't see white
        //--------------------------------------------------------------------
        bool IsWhite() const;

        //--------------------------------------------------------------------
        // Method:      ~LineTracker <<destructor>>
        // Description: This method is called to delete these objects
        //--------------------------------------------------------------------
        virtual ~LineTracker() = default; // destructor

    protected:

    private:

        const float     LOWER_WHITE_VALUE  = 0.0;
        const float     UPPER_WHITE_VALUE  = 2.4;

        const float     LOWER_BLACK_VALUE  = 2.6;
        const float     UPPER_BLACK_VALUE  = 5.0;

        // Default methods we don't want the compiler to implement for us
        LineTracker() = delete;
        LineTracker( const LineTracker& ) = delete;
        LineTracker& operator= ( const LineTracker& ) = delete;
        explicit LineTracker( LineTracker* other ) = delete;


};

#endif /* SRC_LINETRACKER_H_ */
