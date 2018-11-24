/*=============================================================================================
 * IChassis.h
 *=============================================================================================
 *
 * File Description:
 *
 * This is the interface for the driving hardware.  All concrete (physical) drive systems will implement
 * this interface.
 *=============================================================================================*/
#ifndef SRC_ICHASSIS_H_
#define SRC_ICHASSIS_H_

// WPILib includes

// Team 302 includes

enum LINE_TRACK_STATE
{
    LEFT_BLACK_CENTER_BLACK_RIGHT_BLACK,    // 0    x
    LEFT_BLACK_CENTER_BLACK_RIGHT_WHITE,    // 1    x
    LEFT_BLACK_CENTER_WHITE_RIGHT_BLACK,    // 10
    LEFT_BLACK_CENTER_WHITE_RIGHT_WHITE,    // 11   x
    LEFT_WHITE_CENTER_BLACK_RIGHT_BLACK,    // 100  x
    LEFT_WHITE_CENTER_BLACK_RIGHT_WHITE,    // 101  x
    LEFT_WHITE_CENTER_WHITE_RIGHT_BLACK,    // 110  x
    LEFT_WHITE_CENTER_WHITE_RIGHT_WHITE,    // 111  x
    UNKNOWN
};


class IChassis
{
public:
    //----------------------------------------------------------------------------------
    // Method:      SetMotorSpeeds
    // Description: This will set the motor speeds for the left and right side of the
    //              robot.  If a value is specified that is outside the range, the value
    //              used will be the closest bounding value (e.g. if 2.0 is passed in and
    //              the range is -1.0 to 1.0, 1.0 will be used.
    // Returns:     void
    //----------------------------------------------------------------------------------
    virtual void SetMotorSpeeds
    (
        const float leftSideSpeeds, // <I> - Speed for the left side of the robot to (range -1.0 to 1.0)
        const float rightSideSpeeds // <I> - Speed for the right side of the robot (range -1.0 to 1.0)
    ) const = 0;

    //----------------------------------------------------------------------------------
    // Method:      ResetDistance
    // Description: This will reset the distance, so calls to get the distance will
    //              relative to this distance.
    // Returns:     void
    //----------------------------------------------------------------------------------
    virtual void ResetDistance() = 0;

    //----------------------------------------------------------------------------------
    // Method:      GetLeftSideDistance
    // Description: This will return the distance the left side has traveled since the
    //              last time ResetDistance() was called.
    // Returns:     float   distance in feet the left side of the robot has travelled
    //                      (positive values are forward and negative values are backward)
    //----------------------------------------------------------------------------------
    virtual float GetLeftSideDistance() const = 0;

    //----------------------------------------------------------------------------------
    // Method:      GetRightSideDistance
    // Description: This will return the distance the right side has traveled since the
    //              last time ResetDistance() was called.
    // Returns:     float   distance in feet the right side of the robot has travelled
    //                      (positive values are forward and negative values are backward)
    //----------------------------------------------------------------------------------
    virtual float GetRightSideDistance() const = 0;

    //----------------------------------------------------------------------------------
    // Method:      GetLeftSideVelocity
    // Description: This will return the velocity the left side of the robot
    // Returns:     float   velocity in feet per second the left side of the robot is moving
    //                      (positive values are forward and negative values are backward)
    //----------------------------------------------------------------------------------
    virtual float GetLeftSideVelocity() const = 0;

    //----------------------------------------------------------------------------------
    // Method:      GetRightSideVelocity
    // Description: This will return the velocity the right side of the robot
    // Returns:     float   velocity in feet per second the right side of the robot is moving
    //                      (positive values are forward and negative values are backward)
    //----------------------------------------------------------------------------------
    virtual float GetRightSideVelocity() const = 0;


    //----------------------------------------------------------------------------------
    // Method:      SetBrakeMode
    // Description: This will set the drive motors to brake mode
    // Returns:     void
    //----------------------------------------------------------------------------------
    virtual void SetBrakeMode() const = 0;


    //----------------------------------------------------------------------------------
    // Method:      SetCoastMode
    // Description: This will set the drive motors to coast mode
    // Returns:     void
    //----------------------------------------------------------------------------------
    virtual void SetCoastMode() const = 0;


    //----------------------------------------------------------------------------------
    // Method:      IsBumperPressed
    // Description: This will return whether the bumper switch is tripped or not
    // Returns:     bool        true  = tripped
    //                          false = not tripped
    //----------------------------------------------------------------------------------
    virtual bool IsBumperPressed() = 0;

    //----------------------------------------------------------------------------------
    // Method:      GetLineTrackerState
    // Description: This will return the state of the line trackers
    // Returns:     bool        true  = tripped
    //                          false = not tripped
    //----------------------------------------------------------------------------------
    virtual LINE_TRACK_STATE GetLineTrackerState() = 0;

    //----------------------------------------------------------------------------------
    // Method:      UpdateLineTrackerLights
    // Description: This will update the line tracker lights
    // Returns:     void
    //----------------------------------------------------------------------------------
    virtual void UpdateLineTrackerLights() = 0;


    protected:
        IChassis() = default;           // default constructor used by the implementors of this interface
        virtual ~IChassis() = default;  // default destructors used by implementors of this interface

private:

};

#endif /* SRC_CHASSIS_H_ */
