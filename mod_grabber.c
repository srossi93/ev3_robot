
#include "mjolnir.h"
#include "mod_movement.h"
#include "mod_grabber.h"

/* Pick the ball up */
void mod_grab_pick_up(void) {
	// TODO:
	//if (motor_angle != -1360){		//starting position:down
		//MOVE(arm_motor_id,-1360);
	//}
	MOVE(arm_motor_id,-1105);
	GO_STRAIGHT(3);					//go a little bit towards the ball
	MOVE(arm_motor_id,+336);		//close the arm
	//check that there is the ball actually
	MOVE(arm_motor_id,+714);		// pick up the ball: final position up
}

/* Put the ball down */
void mod_grab_put_down(void) {
	// TODO:
	//if (motor_angle != -310){		//starting position: up
	//	MOVE(arm_motor_id,-310);
	//}
	MOVE(arm_motor_id,-336);		//put down the ball
	MOVE(arm_motor_id,-714);		//open the arm
	GO_STRAIGHT(-3);				// the the distance from the ball
	MOVE(arm_motor_id,+1105);		// close the arm and put it in the up position
	
	
}
