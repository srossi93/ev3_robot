//
//  mod_btcom.c
//  Module Bluetooth Communication file of Mjolnir Robot project.
//
//  Created by OS Group 4 on 13/11/16.
//  Copyright © 2016 OS Group 4. All rights reserved.
//

#include <mod_btcom.h>

/**
 * Connect to Bluetooth server.
 *
 * @return Status of socket after trying to connect
 */
int mod_btcom_connect() {
#ifndef WIFI_CONNECTION
	struct sockaddr_rc addr = { 0 };
#else
	struct sockaddr_in addr = { 0 };
#endif
	int status;
#ifndef WIFI_CONNECTION
	/* allocate a socket */
	s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

	 /* set the connection parameters (who to connect to) */
	addr.rc_family = AF_BLUETOOTH;
	addr.rc_channel = (uint8_t) 1;
	str2ba(SERV_ADDR, &addr.rc_bdaddr);
#else
	/* allocate a socket */
	s = socket(AF_INET, SOCK_STREAM, 0);

	 /* set the connection parameters (who to connect to) */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(INET_PORT);
	if (inet_aton(SERV_ADDR, &addr.sin_addr) == 0) {
		fprintf(stderr, "Invalid IP address\n");
		return -1;
	}
#endif

	printf("Trying to connect...\n");
	/* connect to server */
	status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
	return status;
}

/**
 * Receive data from the BT server
 * @param[in/out]	buffer	Buffer to store data read from server
 * @param[int]		maxSize	Maximum bytes to read
 * @return		Number of bytes have been read
 */
int mod_btcom_receive_from_server(int sock, char *buffer, size_t maxSize) {
	int bytes_read = read(sock, buffer, maxSize);

	if (bytes_read <= 0) {
		fprintf(stderr, "Server unexpectedly closed connection...\n");
		close(s);
		//exit(EXIT_FAILURE);
	}

	return bytes_read;
}

int mod_btcom_send_to_server(char *data, size_t size) {
	return write(s, data, size);
}

int mod_btcom_send_location(int x, int y) {
	char string[9];

	/* Construct the data */
	string[2] = TEAM_ID;
	string[3] = 0xFF;
	string[4] = MSG_POSITION;
	string[5] = x;
	string[6] = 0x00;
	string[7] = y;
	string[8] = 0x00;

	/* Send the string to server */
	return mod_btcom_send_to_server(string, 9);
}

/**
 * Send NEXT or OVER signal.
 * NEXT: 0xff, OVER: ??
 */
int mod_btcom_send_signal(uint8_t signal) {
	char string[5];

	/* Construct the data */
	string[2] = TEAM_ID;
	string[3] = signal;
	string[4] = (signal == NEXT) ? MSG_NEXT : MSG_NEXT; // TODO: MSG_OVER?

	/* Send the string to server */
	return mod_btcom_send_to_server(string, 5);
}

/**
 * Get the role and team side from server.
 * 
 * @return Error if less than 0.
 */
int mod_btcom_get_role(unsigned char *side, unsigned char *role) {
	char string[58];
	int ret;

	ret = mod_btcom_receive_from_server(s, string, 9);

	if (ret >= 0) {
		if (string[4] == MSG_START) {
			*role = (unsigned char) string[5];
			*side = (unsigned char) string[6];
		}
	} else {
		fprintf(stderr, "Error in receiving data from server\n");
		printf("Error code: %d\n", ret);
	}

	return ret;
}

