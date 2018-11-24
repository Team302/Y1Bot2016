/*=============================================================================================
 * RobotMap.h
 *=============================================================================================
 *
 * File Description:
 *
 * The RobotMap defines the identifiers (e.g. what is the CAN ID of a particular Talon) for the
 * various motor controllers, sensors, etc.  It provides a constant that defines how the robot
 * is wired, so that if wiring changes, the constants in this file can be updated without impacting
 * the rest of the code.
 *=============================================================================================*/

#ifndef SRC_ROBOTMAP_H_
#define SRC_ROBOTMAP_H_


//#define RUN_SOFTWARE_BOT
#define RUN_YEAR1_BOT
//#define RUN_COMPETITION_BOT

    const int YEAR1_BOT = 3029;
    const int SOFTWARE_BOT = 3025;


#ifdef RUN_SOFTWARE_BOT
    const int ROBOT_CONFIGURATION = 3025;

#elif defined( RUN_YEAR1_BOT )
    const int ROBOT_CONFIGURATION   = 3029;

#endif



#endif /* SRC_ROBOTMAP_H_ */
