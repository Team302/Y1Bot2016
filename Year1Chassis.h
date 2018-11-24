/*=============================================================================================
 * Year1Chassis.h
 *=============================================================================================
 *
 * File Description:
 *
 * This file interacts with the hardware (motors and sensors) used to drive the robot.  It is a
 * Singleton.
 *=============================================================================================*/
#ifndef SRC_YEAR1CHASSIS_H_
#define SRC_YEAR1CHASSIS_H_

// WPILib includes
#include <CANTalon.h>
#include <DigitalInput.h>
#include <DigitalOutput.h>
#include <LineTracker.h>

// Team 302 includes
#include <IChassis.h>
#include <IChassisFactory.h>

class Year1Chassis : public IChassis
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
    void SetMotorSpeeds
    (
        const float leftSideSpeeds, // <I> - Speed for the left side of the robot to (range -1.0 to 1.0)
        const float rightSideSpeeds // <I> - Speed for the right side of the robot (range -1.0 to 1.0)
    ) const override;


    //----------------------------------------------------------------------------------
    // Method:      ResetDistance
    // Description: This will reset the distance, so calls to get the distance will
    //              relative to this distance.
    // Returns:     void
    //----------------------------------------------------------------------------------
    void ResetDistance() override;

    //----------------------------------------------------------------------------------
    // Method:      GetLeftSideDistance
    // Description: This will return the distance the left side has traveled since the
    //              last time ResetDistance() was called.
    // Returns:     float   distance in feet the left side of the robot has travelled
    //                      (positive values are forward and negative values are backward)
    //----------------------------------------------------------------------------------
    float GetLeftSideDistance() const override;

    //----------------------------------------------------------------------------------
    // Method:      GetRightSideDistance
    // Description: This will return the distance the right side has traveled since the
    //              last time ResetDistance() was called.
    // Returns:     float   distance in feet the right side of the robot has travelled
    //                      (positive values are forward and negative values are backward)
    //----------------------------------------------------------------------------------
    float GetRightSideDistance() const override;

    //----------------------------------------------------------------------------------
    // Method:      GetLeftSideVelocity
    // Description: This will return the velocity the left side of the robot
    // Returns:     float   velocity in feet per second the left side of the robot is moving
    //                      (positive values are forward and negative values are backward)
    //----------------------------------------------------------------------------------
    float GetLeftSideVelocity() const override;

    //----------------------------------------------------------------------------------
    // Method:      GetRightSideVelocity
    // Description: This will return the velocity the right side of the robot
    // Returns:     float   velocity in feet per second the right side of the robot is moving
    //                      (positive values are forward and negative values are backward)
    //----------------------------------------------------------------------------------
    float GetRightSideVelocity() const override;


    //----------------------------------------------------------------------------------
    // Method:      SetBrakeMode
    // Description: This will set the drive motors to brake mode
    // Returns:     void
    //----------------------------------------------------------------------------------
    void SetBrakeMode() const override;


    //----------------------------------------------------------------------------------
    // Method:      SetCoastMode
    // Description: This will set the drive motors to coast mode
    // Returns:     void
    //----------------------------------------------------------------------------------
    void SetCoastMode() const override;

    //----------------------------------------------------------------------------------
    // Method:      IsBumperPressed
    // Description: This will return whether the bumper switch is tripped or not
    // Returns:     bool        true  = tripped
    //                          false = not tripped
    //----------------------------------------------------------------------------------
    bool IsBumperPressed() override;

    //----------------------------------------------------------------------------------
    // Method:      GetLineTrackerState
    // Description: This will return the state of the line trackers
    // Returns:     bool        true  = tripped
    //                          false = not tripped
    //----------------------------------------------------------------------------------
    LINE_TRACK_STATE GetLineTrackerState() override;

    //----------------------------------------------------------------------------------
    // Method:      UpdateLineTrackerLights
    // Description: This will update the line tracker lights
    // Returns:     void
    //----------------------------------------------------------------------------------
    void UpdateLineTrackerLights() override;


private:
    friend class IChassisFactory;

    //----------------------------------------------------------------------------------
    // Method:      Year1Chassis <<Constructor>>
    // Description: Create the motor controllers and set whether they are inverted or not.
    //----------------------------------------------------------------------------------
    Year1Chassis();

    //----------------------------------------------------------------------------------
    // Method:      ~Year1Chassis <<Destructor>>
    // Description: Delete the motor controll
    //----------------------------------------------------------------------------------
    virtual ~Year1Chassis();

    // Drive Motors
    CANTalon*           m_leftMotor;
    CANTalon*           m_rightMotor;

    // Bumper Switch
    DigitalInput*       m_bumperSwitch;

    // Line Trackers
    LineTracker*            m_leftLineTracker;
    DigitalOutput*          m_leftLineIndicator;

    LineTracker*            m_centerLineTracker;
    DigitalOutput*          m_centerLineIndicator;

    LineTracker*            m_rightLineTracker;
    DigitalOutput*          m_rightLineIndicator;
};

#endif /* SRC_YEAR1CHASSIS_H_ */
