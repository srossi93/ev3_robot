//
//  mod_btcom.h
//  Module Bluetooth Communication header file of Mjolnir Robot project.
//
//  Created by OS Group 4 on 13/11/16.
//  Copyright © 2016 OS Group 4. All rights reserved.
//

#ifndef MJOLNIR_MOD_BTCOM_H
#define MJOLNIR_MOD_BTCOM_H

#include <mjolnir.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#ifndef WIFI_CONNECTION
#define SERV_ADDR   "dc:53:60:ad:61:90"     /* Whatever the address of the server is */
#else /*! WIFI_CONNECTION */
//#define SERV_ADDR   "10.42.0.1"     
#define SERV_ADDR   "172.17.0.1"     /* Whatever the address of the server is */
#define INET_PORT	8888
#endif

#define TEAM_ID     4                       /* Your team ID */

#define MSG_ACK     0
#define MSG_NEXT    1
#define MSG_START   2
#define MSG_STOP    3
#define MSG_CUSTOM  4
#define MSG_KICK    5
#define MSG_POSITION 6
#define MSG_BALL     7

#define NEXT	0xFF
#define	OVER	0xFF	/*TODO: value?*/

#define SIDE_LEFT	0x01
#define SIDE_RIGHT	0x00

#define BEGINNER	0x00
#define FINISHER	0x01

/* Bluetooth socket */
int s;

/**
 * Connect to Bluetooth server.
 *
 * @return Status of socket after trying to connect
 * 	0	:OK
 *	Other	:ERROR
 */
int mod_btcom_connect();

/**
 * Receive data from the BT server
 * @param[in/out]	buffer	Buffer to store data read from server
 * @param[int]		maxSize	Maximum bytes to read
 * @return		Number of bytes have been read
 */
int mod_btcom_receive_from_server(int sock, char *buffer, size_t maxSize);

int mod_btcom_send_to_server(char *data, size_t size);

int mod_btcom_send_location(int x, int y);

/**
 * Send NEXT or OVER signal.
 * NEXT: 0xff, OVER: ??
 */
int mod_btcom_send_signal(uint8_t signal);

/**
 * Get the role and team side from server.
 * 
 * @return Error if less than 0.
 */
int mod_btcom_get_role(unsigned char *side, unsigned char *role);

/* Optional */
int mod_btcom_send_to_teammate(unsigned int teamMateId, char *customMessage, size_t size);

#endif /* MJOLNIR_MOD_BTCOM_H */
