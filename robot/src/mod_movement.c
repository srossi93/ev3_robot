
#include "mjolnir.h"
#include "mod_movement.h"

void test_motor(uint8_t sn) {
	int max_speed;
	int i;
	FLAGS_T state;
	
	/* get max speed of the motor */
	get_tacho_max_speed( sn, &max_speed );
	printf("  max_speed = %d\n", max_speed );
	/* stop */
	set_tacho_stop_action_inx( sn, TACHO_COAST );
	/* set the speed */
	set_tacho_speed_sp( sn, max_speed * 2 / 3 );
	/* set duration of running */
	set_tacho_time_sp( sn, 5000 );
	/* set ramp up */
	set_tacho_ramp_up_sp( sn, 2000 );
	/* set ram down */
	set_tacho_ramp_down_sp( sn, 2000 );
	/* RUN with specified time */
	set_tacho_command_inx( sn, TACHO_RUN_TIMED );
	/* Wait tacho stop */
	Sleep( 100 );
	do {
		get_tacho_state_flags( sn, &state );
	} while ( state );
	printf( "run to relative position...\n" );
	set_tacho_speed_sp( sn, max_speed / 2 );
	set_tacho_ramp_up_sp( sn, 0 );
	set_tacho_ramp_down_sp( sn, 0 );
	/* set position for relative ning */
	set_tacho_position_sp( sn, 90 );
	for ( i = 0; i < 8; i++ ) {
		set_tacho_command_inx( sn, TACHO_RUN_TO_REL_POS );
		Sleep( 500 );
	}
}


void MOVE(uint8_t motor_id, int32_t value) {
	int sn = motor_id;
	int max_speed;
	//FLAGS_T state;

	/* Check if motor available */
	if (sn < 0) {
		printf("Cannot move. No motor availale at specified ID.\n");
		return;
	}

	printf("Move the motor id=%d to the degree=%d\n", motor_id, value);

	/* get max speed of the motor */
	get_tacho_max_speed( sn, &max_speed );
	printf("  max_speed = %d\n", max_speed );
	/* stop */
	set_tacho_stop_action_inx( sn, TACHO_BRAKE );
	/* set the speed */
	set_tacho_speed_sp( sn, max_speed * 1 / 8 );
	/* set duration of running */
	//set_tacho_time_sp( sn, time );
	/* set ramp up and down speed? */
	set_tacho_ramp_up_sp( sn, 0 );
	/* set ramp up and down speed? */
	set_tacho_ramp_down_sp( sn, 0 );
	if ( value != 0 ) {
		/* set position */
#ifdef REVERSE
		set_tacho_position_sp(sn, (-1)*value);
#else
		set_tacho_position_sp(sn, value);
#endif
		/* RUN with specified position */
		set_tacho_command_inx( sn, TACHO_RUN_TO_REL_POS);
	} else {
		set_tacho_command_inx( sn, TACHO_RUN_FOREVER);
	}
}

void STOP(uint8_t motor_id) {
	//MOVE(motor_id, 0);
	int sn = motor_id;
	FLAGS_T state;

	/* Check if motor available */
	if (sn < 0) {
		printf("Cannot move. No motor availale at specified ID.\n");
		return;
	}
	/* stop */
	set_tacho_stop_action_inx( sn, TACHO_BRAKE );
#if 0
	/* set the speed */
	set_tacho_speed_sp( sn, 0);
	/* set ramp up and down speed? */
	set_tacho_ramp_up_sp( sn, 0 );
	/* set ramp up and down speed? */
	set_tacho_ramp_down_sp( sn, 0 );
	/* set position */
	set_tacho_position_sp(sn, 0);
#endif
	/* STOP */
	set_tacho_command_inx( sn, TACHO_STOP);
	/* Wait tacho stop */
	Sleep( 100 );
	do {
		get_tacho_state_flags( sn, &state );
	} while ( state );

	printf("Motor %d stopped. State = %d\n", sn, state);
}

void STOP_ALL(void) {

	printf("Stop both motors.\n");
	STOP(left_motor_id);
	STOP(right_motor_id);
}

void TURN(int isThisLeft) {
	FLAGS_T state_l, state_r;

	/* Stop all motors first */
	STOP_ALL();

	/* Then, move */
	MOVE(left_motor_id, (-1) * isThisLeft * 200);
	MOVE(right_motor_id, isThisLeft * 200);
	/* Wait tacho stop */
	Sleep( 100 );
	do {
		get_tacho_state_flags( left_motor_id, &state_l );
		get_tacho_state_flags( right_motor_id, &state_r );
		printf("Motors state. state_l=%d, state_r=%d\n", state_l, state_r);
	} while ( state_l && state_r ); // until one of the motors stops, state = 0

	/* Stop the other one */
	if ( state_l ) {
		printf("Stop left motor\n");
		STOP(left_motor_id);
	}
	if ( state_r ) {
		printf("Stop right motor\n");
		STOP(right_motor_id);
	}
}

void TURN_LEFT(void) {
	TURN(1);
}

void TURN_RIGHT(void) {
	TURN(-1);
}

void TURN_AROUND(void) {
	TURN_LEFT();
	TURN_LEFT();
}

void GO_STRAIGHT(uint32_t distance) {
	FLAGS_T state_l, state_r;
	int pos;

	/* Calculation of degree to move the wheel */
	pos = (distance * 700 / 40 ); /* 700 degrees of the wheel, it runs for 40 centimet*/

	get_tacho_state_flags( left_motor_id, &state_l );
	get_tacho_state_flags( right_motor_id, &state_r );


	if ( state_l || state_r ) { // if one of the states are not 0 (not stopping)
		printf("state_l=%d, state_r=%d\n", state_l, state_r);
		printf("Motors are still running...Skip forcing them again\n");
		if ( (state_l != TACHO_RUNNING) && (state_l != TACHO_RAMPING) ) {
			printf("Stop left motor\n");
			STOP(left_motor_id);
		}
		if ( (state_r != TACHO_RUNNING) && (state_r != TACHO_RAMPING) ) {
			printf("Stop right motor\n");
			STOP(right_motor_id);
		}
	} else {
		printf("Go straight for %d centimets \n", distance);

		MOVE(right_motor_id, pos);
		MOVE(left_motor_id, pos);
	}
}

