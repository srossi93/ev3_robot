
#include <stdio.h>
#include "ev3.h"
#include "ev3_port.h"
#include "ev3_tacho.h"
#include "ev3_sensor.h"
// WIN32 /////////////////////////////////////////
#ifdef __WIN32__

#include <windows.h>

// UNIX //////////////////////////////////////////
#else

#include <unistd.h>
#define Sleep( msec ) usleep(( msec ) * 1000 )

//////////////////////////////////////////////////
#endif
const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

// Global ID
int left_motor_id = 1, right_motor_id = 2;

static bool _check_pressed( uint8_t sn )
{
	int val;

	if ( sn == SENSOR__NONE_ ) {
		return ( ev3_read_keys(( uint8_t *) &val ) && ( val & EV3_KEY_UP ));
	}
	return ( get_sensor_value( 0, sn, &val ) && ( val != 0 ));
}

/* Mjolnir: Start - Test motor function */
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
	/* set wtf? */
	set_tacho_ramp_up_sp( sn, 2000 );
	/* set wtf? */
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


void MOVE(uint8_t motor_id, uint32_t time) {
	int sn = motor_id;
	int max_speed;
	FLAGS_T state;
#if 0
	if (direction == LEFT) {
		sn = right_motor_id;
	} else if (direction == RIGHT) {
		sn = left_motor_id;
	} else {
		printf("Wrong direction! Cannot turn!\n");
		return;
	}
#endif
	/* Check if motor available */
	if (sn < 0) {
		printf("Cannot move. No motor availale at specified ID.\n");
		return;
	}

	/* get max speed of the motor */
	get_tacho_max_speed( sn, &max_speed );
	printf("  max_speed = %d\n", max_speed );
	/* stop */
	set_tacho_stop_action_inx( sn, TACHO_COAST );
	/* set the speed */
	set_tacho_speed_sp( sn, max_speed * 2 / 3 );
	/* set duration of running */
	set_tacho_time_sp( sn, time );
	/* set wtf? */
	set_tacho_ramp_up_sp( sn, 500 );
	/* set wtf? */
	set_tacho_ramp_down_sp( sn, 500 );
	/* RUN with specified time */
	set_tacho_command_inx( sn, TACHO_RUN_TIMED );
#if 0
	/* Wait tacho stop */
	Sleep( 100 );
	do {
		get_tacho_state_flags( sn, &state );
	} while ( state );
#endif
}

void STOP(uint8_t motor_id) {
	MOVE(motor_id, 0);
}

void STOP_ALL(void) {
	STOP(left_motor_id);
	STOP(right_motor_id);
}

void TURN_LEFT(void) {
	//MOVE(left_motor_id, 0);
	STOP(left_motor_id);
	MOVE(right_motor_id, 600);
}

void TURN_RIGHT(void) {
	//MOVE(right_motor_id, 0);
	STOP(right_motor_id);
	MOVE(left_motor_id, 600);
}

void TURN_AROUND(void) {
	TURN_LEFT();
	TURN_LEFT();
}

void GO_STRAIGHT(uint32_t time) {
#if 1
	printf("Go straight for %d miliseconds \n", time);
	MOVE(right_motor_id, time);
	MOVE(left_motor_id, time);
#else
	int snr = right_motor_id;
	int snl = left_motor_id;
	int max_speedr, max_speedl;
	FLAGS_T statel, stater;

	/* Check if motor available */
	if ((snr < 0) || (snl < 0) ) {
		printf("Cannot move. No motors availale at specified ID.\n");
		return;
	}

	/* get max speed of the motor */
	get_tacho_max_speed( snr, &max_speedr );
	get_tacho_max_speed( snl, &max_speedl );
	printf("  max_speed right = %d, left = %d\n", max_speedr, max_speedl );
	/* stop */
	set_tacho_stop_action_inx( snl, TACHO_COAST );
	set_tacho_stop_action_inx( snr, TACHO_COAST );
	/* set the speed */
	set_tacho_speed_sp( snl, max_speedl * 2 / 3 );
	set_tacho_speed_sp( snr, max_speedr * 2 / 3 );
	/* set duration of running */
	set_tacho_time_sp( snl, time );
	set_tacho_time_sp( snr, time );
	/* set wtf? */
	set_tacho_ramp_up_sp( snl, 500 );
	set_tacho_ramp_up_sp( snr, 500 );
	/* set wtf? */
	set_tacho_ramp_down_sp( snl, 500 );
	set_tacho_ramp_down_sp( snr, 500 );
	/* RUN with specified time */
	set_tacho_command_inx( snl, TACHO_RUN_TIMED );
	set_tacho_command_inx( snr, TACHO_RUN_TIMED );
#endif
#if 0
	/* Wait tacho stop */
	Sleep( 100 );
	do {
		get_tacho_state_flags( snl, &statel );
		get_tacho_state_flags( snr, &stater );
	} while ( statel && stater );
#endif
}
/* Mjolnir: End. */


int main( void )
{
	int i;
	uint8_t sn;
	uint8_t sn_touch;
//	uint8_t sn_color;
//	uint8_t sn_compass;
	uint8_t sn_sonar;
//	uint8_t sn_mag;
	char s[ 256 ];
	int val;
	float value;
	uint32_t n, ii;
#ifndef __ARM_ARCH_4T__
	/* Disable auto-detection of the brick (you have to set the correct address below) */
	ev3_brick_addr = "192.168.0.204";

#endif
	if ( ev3_init() == -1 ) return ( 1 );

#ifndef __ARM_ARCH_4T__
	printf( "The EV3 brick auto-detection is DISABLED,\nwaiting %s online with plugged tacho...\n", ev3_brick_addr );

#else
	printf( "Waiting tacho is plugged...\n" );

#endif
	while ( ev3_tacho_init() < 1 ) Sleep( 1000 );

	printf( "*** ( EV3 ) Hello! ***\n" );

	printf( "Found tacho motors:\n" );
	for ( i = 0; i < DESC_LIMIT; i++ ) {
		if ( ev3_tacho[ i ].type_inx != TACHO_TYPE__NONE_ ) {
			printf( "  type = %s\n", ev3_tacho_type( ev3_tacho[ i ].type_inx ));
			printf( "  port = %s\n", ev3_tacho_port_name( i, s ));
		}
	}
	//Note that you may need to change this code depending on the order and type of your motors
	if ( ev3_search_tacho( LEGO_EV3_M_MOTOR, &sn, 0 )) {
		printf( "LEGO_EV3_M_MOTOR 1 is found ...\n" );
		//test_motor(sn);
	} else {
		printf( "LEGO_EV3_M_MOTOR 1 is NOT found\n" );
	}
	if ( ev3_search_tacho( LEGO_EV3_L_MOTOR, &sn, 0 )) {
		printf( "LEGO_EV3_L_MOTOR 1 is found ...\n" );
		//test_motor(sn);
		/* assign LEFT motor */
		//left_motor_id = sn;
		printf("LEFT motor ID is: %d\n", left_motor_id);
	} else {
		printf( "LEGO_EV3_L_MOTOR 1 is NOT found\n" );
	}
	if ( ev3_search_tacho( LEGO_EV3_L_MOTOR, &sn, 1 )) {
		printf( "LEGO_EV3_L_MOTOR 2 is found ...\n" );
		//test_motor(sn);
		/* assign RIGHT motor */
		//right_motor_id = sn;
		printf("RIGHT motor ID is: %d\n", right_motor_id);
	} else {
		printf( "LEGO_EV3_L_MOTOR 2 is NOT found\n" );
	}
	if ( ev3_search_tacho( LEGO_EV3_L_MOTOR, &sn, 2 )) {
		printf( "LEGO_EV3_L_MOTOR 3 is found, run for 5 sec...\n" );
		//test_motor(sn);
	} else {
		printf( "LEGO_EV3_L_MOTOR 3 is NOT found\n" );
	}
	if ( ev3_search_tacho( LEGO_EV3_L_MOTOR, &sn, 3 )) {
		printf( "LEGO_EV3_L_MOTOR 4 is found, run for 5 sec...\n" );
		//test_motor(sn);
	} else {
		printf( "LEGO_EV3_L_MOTOR 4 is NOT found\n" );
	}

// Some demo
#if 0
	printf("Demo: turning left now...");
	TURN_LEFT();
	Sleep(1000);
	printf("Demo: turning right now...");
	TURN_RIGHT();
	Sleep(1000);
	TURN_RIGHT();
	Sleep(1000);
	TURN_LEFT();
	Sleep(1000);
	TURN_AROUND();
#endif
	GO_STRAIGHT(20000);

//Run all sensors
	ev3_sensor_init();

	printf( "Found sensors:\n" );
	for ( i = 0; i < DESC_LIMIT; i++ ) {
		if ( ev3_sensor[ i ].type_inx != SENSOR_TYPE__NONE_ ) {
			printf( "  type = %s\n", ev3_sensor_type( ev3_sensor[ i ].type_inx ));
			printf( "  port = %s\n", ev3_sensor_port_name( i, s ));
			if ( get_sensor_mode( i, s, sizeof( s ))) {
				printf( "  mode = %s\n", s );
			}
			if ( get_sensor_num_values( i, &n )) {
				for ( ii = 0; ii < n; ii++ ) {
					if ( get_sensor_value( ii, i, &val )) {
						printf( "  value%d = %d\n", ii, val );
					}
				}
			}
		}
	}
	if ( ev3_search_sensor( LEGO_EV3_TOUCH, &sn_touch, 0 )) {
		printf( "TOUCH sensor is found, press BUTTON for EXIT...\n" );
	} 
	for ( ; ; ){
#if 0
	    	if ( ev3_search_sensor( LEGO_EV3_COLOR, &sn_color, 0 )) {
			printf( "COLOR sensor is found, reading COLOR...\n" );
			if ( !get_sensor_value( 0, sn_color, &val ) || ( val < 0 ) || ( val >= COLOR_COUNT )) {
				val = 0;
			}
			printf( "\r(%s) \n", color[ val ]);
			fflush( stdout );
		}
	    	if (ev3_search_sensor(HT_NXT_COMPASS, &sn_compass,0)){
			printf("COMPASS found, reading compass...\n");
		 	if ( !get_sensor_value0(sn_compass, &value )) {
				value = 0;
			}
			printf( "\r(%f) \n", value);
			fflush( stdout );
	    	}
#endif
		if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar,0)){
			printf("SONAR found, reading sonar...\n");
			if ( !get_sensor_value0(sn_sonar, &value )) {
				value = 0;
			} else if ( value  < 200 ) {
				printf( "                  It's too close: \r(%f) \n", value);
				printf(" TURN LEFT!!\n");
				//TURN_LEFT();
				STOP_ALL();
				Sleep(1000);
#if 0
				printf(" Stop the motor!!\n");
				set_tacho_stop_action_inx( left_motor_id, TACHO_COAST );
				set_tacho_speed_sp( left_motor_id, 0 );
				set_tacho_stop_action_inx( right_motor_id, TACHO_COAST );
				set_tacho_speed_sp( right_motor_id, 0 );
#endif
			} else if (value > 200 ) {
				GO_STRAIGHT(5000);
				Sleep(500);
			}
			fflush( stdout );
	    	}
#if 0
		if (ev3_search_sensor(NXT_ANALOG, &sn_mag,0)){
			printf("Magnetic sensor found, reading magnet...\n");
			if ( !get_sensor_value0(sn_mag, &value )) {
				value = 0;
			}
			printf( "\r(%f) \n", value);
			fflush( stdout );
	    	}
#endif
		if ( _check_pressed( sn_touch )) break;
		Sleep( 200 );
		printf( "\r        " );
		fflush( stdout );
		if ( _check_pressed( sn_touch )) break;
		Sleep( 200 );
	}
	STOP_ALL();
	ev3_uninit();
	printf( "*** ( EV3 ) Bye! ***\n" );

	return ( 0 );
}
