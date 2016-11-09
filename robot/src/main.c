
#include "mjolnir.h"
#include "mjolnir_tacho.h"

const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

// Global ID
//int left_motor_id = 1, right_motor_id = 2;

static bool _check_pressed( uint8_t sn )
{
	int val;

	if ( sn == SENSOR__NONE_ ) {
		return ( ev3_read_keys(( uint8_t *) &val ) && ( val & EV3_KEY_UP ));
	}
	return ( get_sensor_value( 0, sn, &val ) && ( val != 0 ));
}

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
	GO_STRAIGHT(10000);
#endif

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
