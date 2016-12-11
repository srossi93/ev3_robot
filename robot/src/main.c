
#include "mjolnir.h"
#include "mod_movement.h"

const char const *color[] = { "?", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN" };
#define COLOR_COUNT  (( int )( sizeof( color ) / sizeof( color[ 0 ])))

#define COLISION_DISTANCE	250	/* milimets */

static bool _check_pressed( uint8_t sn )
{
	int val;

	if ( sn == SENSOR__NONE_ ) {
		return ( ev3_read_keys(( uint8_t *) &val ) && ( val & EV3_KEY_UP ));
	}
	return ( get_sensor_value( 0, sn, &val ) && ( val != 0 ));
}

static bool _is_too_close (uint8_t distance)
{
	float value;
	uint8_t sn_sonar;

	if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar,0)){
		//printf("SONAR found, reading sonar...\n");
		if ( !get_sensor_value0(sn_sonar, &value )) {
			value = 0;
			/* it's better to temporarily stop the motors */
			//STOP_ALL();
			return 1;
		} else if ( value  < distance) {
			printf( "                  It's too close: \r(%f) \n", value);
			printf(" STOP!!\n");
			//TURN_LEFT();
			//STOP_ALL();
			//running = false;
			//Sleep(1000);
			return 1;
		}
		fflush( stdout );
	}

	return 0;
}

void _check_colision (uint8_t distance)
{
	FLAGS_T state_l, state_r;

	/* Check if there is an obstacle*/
	do {
		printf("Checking colision...");
		get_tacho_state_flags( left_motor_id, &state_l );
		get_tacho_state_flags( right_motor_id, &state_r );
		if (_is_too_close( distance )) {
			printf("...DANGEROUS!\n");
			STOP_ALL();
			break;
		} else {
			printf("...safe!\n");
			Sleep(200);
		}
	} while ( state_l && state_r ); // until one of the motors stops, state = 0

	return;
}

void TEST1 (void)
{
	printf("TEST1 Start!");

	GO_STRAIGHT(115);
	/* Check if there is an obstacle*/
	_check_colision( COLISION_DISTANCE );

	STOP_ALL();

	printf("TEST1 DONE!\n");
}

void TEST2 (void)
{
	GO_STRAIGHT(87);
	TURN_RIGHT();
	GO_STRAIGHT(18);
	TURN_LEFT();
	GO_STRAIGHT(75);
}

void TEST3 (void)
{
	GO_STRAIGHT(115);
	TURN_RIGHT();
	GO_STRAIGHT(100);
	TURN_LEFT();
	GO_STRAIGHT(60);
	TURN_LEFT();
	GO_STRAIGHT(100);
	TURN_RIGHT();
	GO_STRAIGHT(115);

}

void TEST4 (void)
{
	GO_STRAIGHT(115);
	TURN_RIGHT();
	GO_STRAIGHT(100);
	TURN_LEFT();
	GO_STRAIGHT(60);
	TURN_LEFT();
	GO_STRAIGHT(50);

}

void TEST5 (void)
{

}

int main( int argc, char* argv[] )
{
	int i;
//	uint8_t sn;
	uint8_t sn_touch;
//	uint8_t sn_color;
//	uint8_t sn_compass;
//	uint8_t sn_sonar;
//	uint8_t sn_mag;
	char s[ 256 ];
	int val;
//	float value;
	uint32_t n, ii;
//	bool running = false;

/* Getting parameters */
        if ( argc < 5 ) {
		printf("Usage: %s [role] [area] [part] [action]\n", argv[0] );
		printf("Options:\n");
		printf("\t role\t \t 'b' or 'f' or 'g'\t(beginner or finisher, or (just for test) grabber)\n");
		printf("\t area\t \t 'l' or 's' \t(large or small)\n");
		printf("\t part\t \t 'l' or 'r' \t(left or right, valid only with LARGE area.)\n");
		printf("\t action\t \t 'g' or 'b' \t(just Go or place a Ball)\n");

                return 1;
        }

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

	while ( ev3_sensor_init() < 1) Sleep( 1000 );

	printf( "*** ( EV3 ) Hello! ***\n" );

	printf( "Found tacho motors:\n" );
	for ( i = 0; i < DESC_LIMIT; i++ ) {
		if ( ev3_tacho[ i ].type_inx != TACHO_TYPE__NONE_ ) {
			printf( "  type = %s\n", ev3_tacho_type( ev3_tacho[ i ].type_inx ));
			printf( " i =%d,  port = %s\n", i, ev3_tacho_port_name( i, s ));
			if (strcmp(ev3_tacho_port_name( i, s ), RIGHT_MOTOR_PORT) == 0) {
				right_motor_id = i;
				printf("Right motor id=%d\n", right_motor_id);
			} else if (strcmp(ev3_tacho_port_name( i, s ), LEFT_MOTOR_PORT) == 0) {
				left_motor_id = i;
				printf("Left motor id=%d\n", left_motor_id);
			} else if (strcmp(ev3_tacho_port_name( i, s ), ARM_MOTOR_PORT) == 0) {
				arm_motor_id = i;
				printf("Arm motor id=%d\n", arm_motor_id);
			} else  {
				//do nothing
			}
		}
	}

// Some demo
#if 0
	printf("Demo: turning left now...");
	TURN_LEFT();
	Sleep(2000);
	printf("Demo: turning right now...");
	TURN_RIGHT();
	Sleep(2000);
	TURN_RIGHT();
	Sleep(2000);
	TURN_LEFT();
	Sleep(2000);
	TURN_AROUND();
	//GO_STRAIGHT(10000);
#endif

       /* BEGINNER + SMALL */
        if ( (strcmp(argv[1], "b") == 0) && (strcmp(argv[2], "s") == 0) ) {
                if ( strcmp(argv[4], "g") == 0 ) { /* Just go */
                        printf("TEST 1 start!\n");
                        TEST1();
                        printf("Mission completed!\n");
                        return 1;
                } else if ( strcmp(argv[4], "b") == 0 ) { /* with placing the ball */
                        printf("TEST 2 start!\n");
                        TEST2();
                        printf("Mission completed!\n");
                        return 1;
                }

        }

        /* BEGINNER + LARGE */
        if ( (strcmp(argv[1], "b") == 0) && (strcmp(argv[2], "l") == 0) ) {
                if ( strcmp(argv[4], "g") == 0 ) { /* Just go */
                        printf("TEST 3 start!\n");
                        TEST3();
                        printf("Mission completed!\n");
                        return 1;
                } else if ( strcmp(argv[4], "b") == 0 ) { /* with placing the ball */
                        printf("TEST 4 start!\n");
                        TEST4();
                        printf("Mission completed!\n");
                        return 1;
                }
        }

        /* GRABBER TEST */
        if (strcmp(argv[1], "g") == 0)  {
                printf("TEST 5 start!\n");
                TEST5();
                printf("Mission completed!\n");
                return 1;
        }

//Run all sensors

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
#if 0
		if (ev3_search_sensor(LEGO_EV3_US, &sn_sonar,0)){
			printf("SONAR found, reading sonar...\n");
			if ( !get_sensor_value0(sn_sonar, &value )) {
				value = 0;
				/* it's better to temporarily stop the motors */
				STOP_ALL();
			} else if ( value  < COLISION_DISTANCE ) {
				printf( "                  It's too close: \r(%f) \n", value);
				printf(" TURN LEFT!!\n");
				TURN_LEFT();
				//STOP_ALL();
				//running = false;
				Sleep(1000);
#if 0
				printf(" Stop the motor!!\n");
				set_tacho_stop_action_inx( left_motor_id, TACHO_COAST );
				set_tacho_speed_sp( left_motor_id, 0 );
				set_tacho_stop_action_inx( right_motor_id, TACHO_COAST );
				set_tacho_speed_sp( right_motor_id, 0 );
#endif
			} else if (value >= COLISION_DISTANCE ) {
				//running = true;
				GO_STRAIGHT(50);
				//Sleep(500);
			}
			fflush( stdout );
	    	}
#endif
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
