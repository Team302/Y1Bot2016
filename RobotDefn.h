/*=============================================================================================
 * RobotDefn.h
 *=============================================================================================
 *
 * File Description:
 *
 * The RobotDefn defines the constants used by the factories to select the correct concrete
 * class for running.
 *=============================================================================================*/

#ifndef SRC_ROBOTDEFN_H_
#define SRC_ROBOTDEFN_H_


    // These are all of the robots that can be deployed to
    const int YEAR1_BOT = 3029;
    const int SOFTWARE_BOT = 3025;


// Uncomment the line below to select the robot that the software is being deployed to
// Then the ROBOT_CONFIGURATION will be set correctly (so the factories create the correct
// targets

//#define RUN_SOFTWARE_BOT
#define RUN_YEAR1_BOT
//#define RUN_COMPETITION_BOT


#ifdef RUN_SOFTWARE_BOT
    const int ROBOT_CONFIGURATION = 3025;
#elif defined( RUN_YEAR1_BOT )
    const int ROBOT_CONFIGURATION   = 3029;
#endif



#endif /* SRC_ROBOTDEFN_H_ */
