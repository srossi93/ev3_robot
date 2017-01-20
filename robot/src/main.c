#include "mjolnir.h"
#include "mod_btcom.h"
#include <sys/time.h>

int main(int argc, char* argv[]) {
	pthread_t tid, tid2;

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

	/* Periodically send the location */
	pthread_create(&tid2, NULL, __mod_btcom_send_location, NULL);

	printf("Bluetooth communication started\n");

	while (1) {
		/* Send the signal to server at the end of journey */
		if (gMyState == DONE) {
			printf("Sending NEXT message to team mate: %d\n", gTeamMateId);
			mod_btcom_send_NEXT(gTeamMateId);
			printf("I become a FINISHER now\n");
			gMyRole = FINISHER;
			gMyState = WAITING;
		}

		if ( (gMyState == STOPPED) && (gMyState == KICKED) ) {
			printf("We are done! Gotta stop now!\n");
			break;
		}
		/* Loop every 1 second */
		sleep(1);
	}

	pthread_join(tid, NULL);
	pthread_join(tid2, NULL);

	printf("Bye!\n");

	return 0;
}
