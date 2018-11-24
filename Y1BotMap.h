/*=============================================================================================
 * Y1BotMap.h
 *=============================================================================================
 *
 * File Description:
 *
 * The Y1BotMap defines the identifiers (e.g. what is the CAN ID of a particular Talon) for the
 * various motor controllers, sensors, etc.  It provides a constant that defines how the robot
 * is wired, so that if wiring changes, the constants in this file can be updated without impacting
 * the rest of the code.
 *=============================================================================================*/

#ifndef SRC_Y1BOTMAP_H_
#define SRC_Y1BOTMAP_H_

    //==========================================================================================
    // CAN PORTS
    //==========================================================================================
    const int LEFT_DRIVE_MOTOR      = 5;
    const int RIGHT_DRIVE_MOTOR     = 4;
    const int LEFT_DRIVE_MOTOR2     = 0;
    const int RIGHT_DRIVE_MOTOR2    = 0;

    const int SHOOTER_WHEEL_MOTOR   = 3;
    const int SHOOTER_LOAD_MOTOR    = 2;
    const int SHOOTER_ALIGN_MOTOR   = 1;

    //==========================================================================================
    // TALON (Motor) inversion settings
    //==========================================================================================
    const bool IS_LEFT_DRIVE_MOTOR_INVERTED     = true;
    const bool IS_RIGHT_DRIVE_MOTOR_INVERTED    = false;

    const bool IS_SHOOTER_WHEEL_MOTOR_INVERTED  = true;
    const bool IS_SHOOTER_LOAD_MOTOR_INVERTED   = false;
    const bool IS_SHOOTER_ALIGN_MOTOR_INVERTED  = true;

    //==========================================================================================
    // Drive Encoder conversion rates to convert from counts to feet and feet per second
    //==========================================================================================
    const float ENCODER_DISTANCE_CONVERSION = 0.0010908307638889; // encoder counts to feet
    const float ENCODER_VELOCITY_CONVERSION = 0.0109083076388889; // encoder counts per 0.1 sec to feet per second

    //==========================================================================================
    // Analog Input Devices
    //==========================================================================================
    const unsigned int LEFT_LINE_TRACKER    = 0;
    const unsigned int CENTER_LINE_TRACKER  = 1;
    const unsigned int RIGHT_LINE_TRACKER   = 2;

    //==========================================================================================
    // Digital Input/Output PORTS
    //==========================================================================================
    const unsigned int GOAL_DETECTION_SENSOR        = 0;

    const unsigned int BALL_LOAD_SENSOR             = 1;

    const unsigned int LEFT_LINE_TRACKER_LIGHT      = 2;
    const unsigned int CENTER_LINE_TRACKER_LIGHT    = 3;
    const unsigned int RIGHT_LINE_TRACKER_LIGHT     = 4;

    const unsigned int MAX_ANGLE_SENSOR             = 5;


    //==========================================================================================
    // PWM Output Ports
    //==========================================================================================


    //==========================================================================================
    // PNEUMATIC SOLENOID Ports
    //==========================================================================================

#endif /* SRC_Y1BOTMAP_H_ */
