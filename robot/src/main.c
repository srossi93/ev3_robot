#include "mjolnir.h"
#include "mod_btcom.h"
#include <sys/time.h>

int main(int argc, char* argv[]) {
	unsigned char mySide, myRole;
	int count = 0;

	printf("Connecting to server:\n");

	/* Try to connect to BT server */
	if (mod_btcom_connect() != 0) {
		printf("Unable to connect to the server.\n");
		return (-1);
	}

	/* Connected OK */
	/* Receiving the information from server */
	while (mod_btcom_get_role(&mySide, &myRole) < 0){
		/* Check after 1000 milisecond */
		sleep(1);
	}
	/* until get the role */
	printf("My role: %d, my side: %d\n", myRole, mySide);

	/* Periodically send the location */
	while (count++ < 15) {
		mod_btcom_send_location(21, 22);
		sleep(2);
	}

	/* Send the signal to server at the end of journey */
	mod_btcom_send_signal(NEXT); /*for BEGINNER*/
	//mod_btcom_send_signal(OVER); /*for FINISHER*/	

	return 0;
}
