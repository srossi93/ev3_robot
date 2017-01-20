//
//  mod_btcom.h
//  Module Bluetooth Communication header file of Mjolnir Robot project.
//
//  Created by OS Group 4 on 13/11/16.
//  Updated on: 20/01/2017 (by Duy KHUONG <khuong@eurecom.fr>
//
//  Copyright © 2016 OS Group 4. All rights reserved.
//

#ifndef MJOLNIR_MOD_BTCOM_H
#define MJOLNIR_MOD_BTCOM_H

#include <mjolnir.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#ifndef WIFI_CONNECTION
#define SERV_ADDR   "dc:53:60:ad:61:90"
#else /*! WIFI_CONNECTION */
//#define SERV_ADDR   "10.42.0.1"     
#define SERV_ADDR   "172.17.0.1"    
#define INET_PORT	8888
#endif

#define TEAM_ID     4                      

#define MSG_ACK     0
#define MSG_NEXT    1
#define MSG_START   2
#define MSG_STOP    3
#define MSG_CUSTOM  4
#define MSG_KICK    5
#define MSG_POSITION 6
#define MSG_BALL     7

#define NEXT		0x01

#define SIDE_LEFT	0x01
#define SIDE_RIGHT	0x00

#define BEGINNER	0x00
#define FINISHER	0x01

/* Action for the ball */
#define DROP		0x00
#define PICKUP		0x01

/* State OK or ERROR*/
#define ACK_OK		0x00
#define ACK_ERROR	0x01

/* Bluetooth socket */
int s;

/* Message ID */
//uint16_t msgId = 0;

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

/**
 * Send ACK
 * Used to acknowledge the reception of messages
 * Messages sent by the server should not be acknowledged
 */
int mod_btcom_send_ACK(uint8_t dst, int16_t id_ack, int8_t status);

/**
 * Send BALL 
 */
int mod_btcom_send_BALL(uint8_t act, int16_t x, int16_t y);

/**
 * Send POSITION
 */
int mod_btcom_send_POSITION(int x, int y);

/**
 * Send NEXT 
 */
int mod_btcom_send_NEXT(uint8_t dst);

/**
 * Get the role and team side from server.
 * 
 * @return Error if less than 0.
 */
int mod_btcom_get_role(unsigned char *side, unsigned char *role, unsigned char *ally);

/**
 * Get the generic message from server
 * 
 * @return Error if less than 0.
 */
int mod_btcom_get_message(uint8_t *actionType, uint8_t *arg1, int16_t *arg2, int16_t *arg3);

/* Optional */
int mod_btcom_send_to_teammate(unsigned int teamMateId, char *customMessage, size_t size);

/* Thread functions */
void *__mod_btcom_wait_messages(void);
void *__mod_btcom_send_location(void);

#endif /* MJOLNIR_MOD_BTCOM_H */
