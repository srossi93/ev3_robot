#include "mjolnir.h"
#include "mod_btcom.h"
#include <sys/time.h>

enum robot_state { 
	NOTSTARTED, 	/* Don't know its role yet. Waiting for instruction from server */
	STARTED,	/* Got its role, ready for run. */
	WAITING,	/* At its location, waiting for NEXT mesg to run */
	RUNNING,	/* On its journey */ 
	DONE,		/* When beginner or finisher completed its journey */
	STOPPED
};

int main(int argc, char* argv[]) {
	unsigned char mySide, myRole, teamMateId;
	uint8_t actionType;
	enum robot_state myState = NOTSTARTED;
	int count = 0, x, y;
	uint8_t arg1;
	int16_t arg2, arg3;
	int ret;

	printf("Connecting to server:\n");

	/* Try to connect to BT server */
	if (mod_btcom_connect() != 0) {
		printf("Unable to connect to the server.\n");
		return (-1);
	}

	/* Connected OK */
	/* Receiving the information from server */
	while (mod_btcom_get_role(&mySide, &myRole, &teamMateId) < 0){
		/* Check after 1000 milisecond */
		sleep(1);
	}
	/* until get the role */
	printf("My role: %d, my side: %d, my team mate ID: %d\n", myRole, mySide, teamMateId);

	/* Change state */
	myState = STARTED;

	/*  */

	/* Periodically send the location */
	while (1) {
		printf("Getting msg from server\n");

		/* Loop to get message from server */
		ret = mod_btcom_get_message(&actionType, &arg1, &arg2, &arg3);

		if (ret > 0) {
			switch (actionType) {
				case MSG_NEXT:
					printf("Got the NEXT message\n");
					if ((myRole == FINISHER) && (myState == WAITING)){
						printf("Okay. The finisher starts right now!\n");
						//finisher_start();
						myState = RUNNING;
					} else {
						printf("I'm not a finisher or I'm running. Skip.\n");
					}
					break;
				case MSG_START:
					printf("I already started. Skip.\n");
					break;
				case MSG_STOP:
					printf("Got the STOP message.\n");
					myState = STOPPED;
					printf("I'm done!\n");
					return 0; /* Exit */
				case MSG_KICK:
					printf("Got the KICK message.\n");
					if (arg1 == TEAM_ID) {
						myState = STOPPED;
						printf("I'm out!\n");
						return 0; /* Exit */
					}
					break;
				case MSG_POSITION:
					printf("Got the POSITION message\n");
					printf("You sent to a wrong address, man: %d!\n", arg1);
					break;
				case MSG_BALL:
					printf("Got the BALL message.\n");
					if (arg1 == DROP) {
						printf("Someone dropped a ball.\n");
						printf("at location x=%d, y=%d\n", arg2, arg3);
					} else {
						printf("Someone picked up the ball.\n");
						printf("at location x=%d, y=%d\n", arg2, arg3);
					}
					/* Send ackowledgement*/
					mod_btcom_send_ACK(teamMateId, 0, ACK_OK);/*TODO*/
					break;
				default:
					printf("Incorrect type of message received: %d\n", actionType);
					break;
			}
		}

		/* Send current location every 2 seconds*/
		x = 21; /*TODO*/
		y = 22; /*TODO*/
		//if ( (count++ % 2) == 0){
			printf("Sending robot's location x=%d, y=%d\n", x, y);
			mod_btcom_send_POSITION(x, y);
		//}

		/* Send the signal to server at the end of journey */
		if (myState == DONE) {
			printf("Sending NEXT message to team mate: %d\n", teamMateId);
			mod_btcom_send_NEXT(teamMateId);
			printf("I become a FINISHER now\n");
			myRole = FINISHER;
			myState = WAITING;
		}

		/* Loop every 1 second */
		sleep(1);
	}

	return 0;
}
