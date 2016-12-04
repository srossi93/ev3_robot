
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

	/* get max speed of the motor */
	get_tacho_max_speed( sn, &max_speed );
	printf("  max_speed = %d\n", max_speed );
	/* stop */
	set_tacho_stop_action_inx( sn, TACHO_BRAKE );
	/* set the speed */
	set_tacho_speed_sp( sn, max_speed * 1 / 8 );
	/* set duration of running */
	//set_tacho_time_sp( sn, time );
	/* set wtf? */
	set_tacho_ramp_up_sp( sn, 0 );
	/* set wtf? */
	set_tacho_ramp_down_sp( sn, 0 );
	/* set position */
#ifdef REVERSE
	set_tacho_position_sp(sn, (-1)*value);
#else
	set_tacho_position_sp(sn, value);
#endif
	/* RUN with specified position */
	set_tacho_command_inx( sn, TACHO_RUN_TO_REL_POS);
}

void STOP(uint8_t motor_id) {
	MOVE(motor_id, 0);
}

void STOP_ALL(void) {
	STOP(left_motor_id);
	STOP(right_motor_id);
}

void TURN_LEFT(void) {
	MOVE(left_motor_id, -180);
	//STOP(left_motor_id);
	MOVE(right_motor_id, 180);
}

void TURN_RIGHT(void) {
	MOVE(right_motor_id, -180);
	//STOP(right_motor_id);
	MOVE(left_motor_id, 180);
}

void TURN_AROUND(void) {
	TURN_LEFT();
	TURN_LEFT();
}

void GO_STRAIGHT(uint32_t distance) {
	int pos = (distance / 15 ) * 360;

	printf("Go straight for %d centimets \n", distance);

	MOVE(right_motor_id, pos);
	MOVE(left_motor_id, pos);
}

