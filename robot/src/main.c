#include "mjolnir.h"
#include "mod_btcom.h"
#include <sys/time.h>

int main(int argc, char* argv[]) {
	//unsigned char gMySide, gMyRole, gTeamMateId;
	//uint8_t actionType;
	//enum robot_state gMyState = NOTSTARTED;
	int count = 0, x, y;
	pthread_t tid;

	printf("Connecting to server:\n");

	/* Try to connect to BT server */
	if (mod_btcom_connect() != 0) {
		printf("Unable to connect to the server.\n");
		return (-1);
	}

	/* Connected OK */
	/* Receiving the information from server */
	while (mod_btcom_get_role(&gMySide, &gMyRole, &gTeamMateId) < 0){
		/* Check after 1000 milisecond */
		sleep(1);
	}
	/* until get the role */
	printf("My role: %d, my side: %d, my team mate ID: %d\n", gMyRole, gMySide, gTeamMateId);

	/* Change state */
	gMyState = STARTED;

	/* Waiting for messages sent by server and others */
	pthread_create(&tid, NULL, __mod_btcom_wait_messages, NULL);

	printf("Bluetooth communication started\n");

	/* Periodically send the location */
	while (1) {
		//printf("Getting msg from server\n");

		/* Send current location every 2 seconds*/
		x = 21; /*TODO*/
		y = 22; /*TODO*/
		if ( (count++ % 2) == 0){
			printf("Sending robot's location x=%d, y=%d\n", x, y);
			mod_btcom_send_POSITION(x, y);
		}

		/* Send the signal to server at the end of journey */
		if (gMyState == DONE) {
			printf("Sending NEXT message to team mate: %d\n", gTeamMateId);
			mod_btcom_send_NEXT(gTeamMateId);
			printf("I become a FINISHER now\n");
			gMyRole = FINISHER;
			gMyState = WAITING;
		}

		/* Loop every 1 second */
		sleep(1);
	}

	return 0;
}
