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
	printf("Connecting with BT connection...\n");
	/* allocate a socket */
	s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

	 /* set the connection parameters (who to connect to) */
	addr.rc_family = AF_BLUETOOTH;
	addr.rc_channel = (uint8_t) 1;
	str2ba(SERV_ADDR, &addr.rc_bdaddr);
#else
	printf("Connecting with LAN connection...\n");
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

	printf("Trying to connect to %s...\n", SERV_ADDR);
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

/**
 * Send ACK
 * Used to acknowledge the reception of messages
 * Messages sent by the server should not be acknowledged
 */
int mod_btcom_send_ACK(uint8_t dst, int16_t id_ack, int8_t state) {
	char string[8];

	/* Construct the data */
	*((uint16_t *) string) = 0;
	string[2] = TEAM_ID;	/* src */
	string[3] = dst;	/* dst */
	string[4] = MSG_ACK;	/* type */
	string[5] = id_ack;
	string[6] = 0x00;
	string[7] = state;	/* OK or ERROR */

	/* Send the string to server */
	return mod_btcom_send_to_server(string, 9);
	
}

/**
 * Send BALL
 */
int mod_btcom_send_BALL(uint8_t act, int16_t x, int16_t y) {
	char string[10];

	/* Construct the data */
	*((uint16_t *) string) = 0;
	string[2] = TEAM_ID;	/* src */
	string[3] = 0xFF;	/* dst */
	string[4] = MSG_BALL;
	string[5] = act;	/* DROP or PICKUP */
	string[6] = x;
	string[7] = 0x00;
	string[8] = y;
	string[9] = 0x00;

	/* Send the string to server */
	return mod_btcom_send_to_server(string, 9);
}


/**
 * Send POSITION
 */
int mod_btcom_send_POSITION(int x, int y) {
	char string[9];

	/* Construct the data */
	*((uint16_t *) string) = 0;
	string[2] = TEAM_ID;	/* src */
	string[3] = 0xFF;	/* dst */
	string[4] = MSG_POSITION;
	string[5] = x;
	string[6] = 0x00;
	string[7] = y;
	string[8] = 0x00;

	/* Send the string to server */
	return mod_btcom_send_to_server(string, 9);
}

/**
 * Send NEXT message whenever finishing my turn
 */
int mod_btcom_send_NEXT(uint8_t dst) {
	char string[5];

	/* Construct the data */
	*((uint16_t *) string) = 0;
	string[2] = TEAM_ID;	/* src */
	string[3] = dst;	/* dst */
	string[4] = MSG_NEXT;	/* 0x01 */

	/* Send the string to server */
	return mod_btcom_send_to_server(string, 5);
}

/**
 * Get the role and team side from server.
 * 
 * @return Error if less than 0.
 */
int mod_btcom_get_role(unsigned char *side, unsigned char *role, unsigned char *ally) {
	char string[58];
	int ret;

	ret = mod_btcom_receive_from_server(s, string, 9);

	if (ret >= 0) {
		if (string[4] == MSG_START) {
			*role = (unsigned char) string[5];
			*side = (unsigned char) string[6];
			*ally = (unsigned char) string[7];
		}
	} else {
		fprintf(stderr, "Error in receiving data from server\n");
		printf("Error code: %d\n", ret);
	}

	return ret;
}

/**
 * Get the generic message from server
 * 
 * @return Error if less than 0.
 */
int mod_btcom_get_message(uint8_t *actionType, uint8_t *arg1, int16_t *arg2, int16_t *arg3) {
	char string[58];
	int ret;
	uint8_t dst;

	ret = mod_btcom_receive_from_server(s, string, 58);

	//printf("Received %d bytes from server.\n", ret);

	if (ret >= 0) {
		*actionType = (uint8_t) string[4];
		dst = (unsigned char) string[3];
	} else {
		fprintf(stderr, "Error in receiving data from server\n");
		printf("Error code: %d\n", ret);
	}

	/* Only take care messages sent to us */
	if (dst != TEAM_ID) {
		printf("Received a message, but not for us. dst = %d. Skip!\n", dst);
		return -1;
	}

	switch (*actionType) {
		case MSG_ACK:
			break;	/* no additional info needed */
		case MSG_NEXT:
			break;	/* no additional info needed */
		case MSG_START:
			break;	/* no additional info needed */
		case MSG_STOP:
			break;	/* no additional info needed */
		case MSG_CUSTOM:
			break;	/* no additional info needed */
		case MSG_KICK:
			*arg1 = (uint8_t ) string[5];
			break;
		case MSG_POSITION:
			*arg1 = (uint8_t ) string[2]; /* src */
			break;	/* no additional info needed */
		case MSG_BALL:
			*arg1 = (uint8_t ) string[5];
			*arg2 = (int16_t ) string[6];
			*arg3 = (int16_t ) string[8];
			break;
		default:
			printf("Invalid type of message.\n");
			ret = -2;	
			break;
	}

	return ret;
}
