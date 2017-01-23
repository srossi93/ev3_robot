//
//  mod_btcom.c
//  Module Bluetooth Communication file of Mjolnir Robot project.
//
//  Created by OS Group 4 on 13/11/16.
//  Copyright © 2016 OS Group 4. All rights reserved.
//

#include <mod_btcom.h>
#include <byteswap.h>
#include <math.h> 

//pthread_cond_t cv_next;
//pthread_mutex_t bt_mutex;

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
	printf(" [BT] Connecting with BT connection...\n");
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

	printf(" [BT] Trying to connect to %s...\n", SERV_ADDR);
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
		fprintf(stderr, " [ERROR] Server unexpectedly closed connection...\n");
		close(s);
    gGameState = GAME_STOPPED;
    
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
	*((uint16_t *) string) = msgId++;
	string[2] = TEAM_ID;	/* src */
	string[3] = dst;	/* dst */
	string[4] = MSG_ACK;	/* type */
	string[5] = id_ack;
	string[6] = 0x00;
	string[7] = state;	/* OK or ERROR */

	/* Send the string to server */
	return mod_btcom_send_to_server(string, 8);
	
}
 
/**
 * Send BALL
 */
int mod_btcom_send_BALL(uint8_t act, int16_t x, int16_t y) {
	char string[10];
  
	/* Construct the data */
	*((uint16_t *) string) = msgId++;
	string[2] = TEAM_ID;	/* src */
	string[3] = gTeamMateId;	/* dst */
	string[4] = MSG_BALL;
	string[5] = act;	/* DROP or PICKUP */
  memcpy(string + 6, &x, sizeof(int16_t));
  memcpy(string + 8, &y, sizeof(int16_t));
	//string[6] = x;
	//string[7] = 0x00;
	//string[8] = y;
	//string[9] = 0x00;

	/* Send the string to server */
	return mod_btcom_send_to_server(string, 10);
}


/**
 * Send POSITION
 */
int mod_btcom_send_POSITION(int x, int y) {
	char string[9];
  
  int16_t x_little_endian = (int16_t)(x);
  int16_t y_little_endian = (int16_t)(y);
	/* Construct the data */
	*((uint16_t *) string) = msgId++;
	string[2] = TEAM_ID;	/* src */
	string[3] = 0xFF;	/* dst */
	string[4] = MSG_POSITION;
  string[5] = x_little_endian;
  memcpy(string + 5, &x_little_endian, sizeof(int16_t));
  //string[5] = x;              // <<<<<<<<<< TODO Little endian
  //string[6] = 0x00;
  memcpy(string + 7, &y_little_endian, sizeof(int16_t));
  //string[7] = y;
  //string[8] = 0x00;

	/* Send the string to server */
	return mod_btcom_send_to_server(string, 9);
}

/**
 * Send NEXT message whenever finishing my turn
 */
int mod_btcom_send_NEXT(uint8_t dst) {
  printf(" [BT] Sending NEXT message to robot %d\n", dst);
	char string[5];

	/* Construct the data */
	*((uint16_t *) string) = msgId++;
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
		fprintf(stderr, " [BT] Error in receiving data from server\n");
		printf(" [BT] Error code: %d\n", ret);
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

	printf(" [BT] Received %d bytes from server.\n", ret);

	if (ret > 0) {
		*actionType = (uint8_t) string[4];
		dst = (unsigned char) string[3];
	} else {
		fprintf(stderr, " [BT] Error in receiving data from server\n");
		printf(" [BT] Error code: %d\n", ret);
		return -3;
	}

	/* Only take care messages sent to us */
	if (dst != TEAM_ID) {
		printf(" [BT] Received a message, but not for us. dst = %d. Skip!\n", dst);
		return -1;
	}

	switch (*actionType) {
		case MSG_ACK:
			break;	/* no additional info needed */
		case MSG_NEXT:
      memcpy(&ret, string, sizeof(int16_t));
      printf(" [BT] Next received - %d to be ACKed", ret);
			break;	/* no additional info needed */
		case MSG_START:
      *arg1 = (uint8_t ) string[5];
      *arg2 = (int16_t ) string[6];
      *arg3 = (int16_t ) string[7];
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
      memcpy(&ret, string, sizeof(int16_t));
			*arg1 = (uint8_t ) string[5];
			*arg2 = (int16_t ) string[6];
			*arg3 = (int16_t ) string[8];
			break;
		default:
			printf(" [BT] Invalid type of message.\n");
			ret = -2;	
			break;
	}
  
	return ret;
}

void *__mod_btcom_wait_messages(void* arg) {
	uint8_t actionType;
	uint8_t arg1;
	int16_t arg2, arg3;
	int ret;
  
  pthread_mutex_init(&bt_mutex, NULL);
  pthread_cond_init(&cv_next, NULL);
  
	while (1) {
		/* Loop to get message from server */
		ret = mod_btcom_get_message(&actionType, &arg1, &arg2, &arg3);

		//printf("ret=%d\n", ret);
    pthread_mutex_lock(&bt_mutex);
    printf(" [BT] Getting msg from server\n");
		
    if (ret >= 0) {
			switch (actionType) {
				case MSG_NEXT:
					printf(" [BT] Got the NEXT message\n");
					if (gMyState == WAITING){
						printf(" [BT] Okay. The finisher can start right now!\n");
						gMyState = READY;
            pthread_cond_signal(&cv_next);
            mod_btcom_send_ACK(gTeamMateId, ret, ACK_OK);/*TODO*/
					}
          else {
						printf(" [BT] I'm not a finisher or I'm running. Skip.\n");
					}
					break;
				case MSG_START:
          gMyRole = (unsigned char) arg1;
          gMySide = (unsigned char) arg2;
          gTeamMateId = (unsigned char) arg3;
          gGameState = GAME_STARTED;

          //printf("I already started. Skip.\n");
					break;
				case MSG_STOP:
					printf(" [BT] Got the STOP message.\n");
					gMyState = STOPPED;
          gGameState = GAME_STOPPED;
          pthread_cond_signal(&cv_next);
					printf(" [BT] I'm done!\n");
          //return 0; /* Exit */
					break;
				case MSG_KICK:
					printf(" [BT] Got the KICK message.\n");
					if (arg1 == TEAM_ID) {
						printf(" [BT] Damn, we got kicked!\n");
						gMyState = KICKED;
            gGameState = GAME_KICKED;
            pthread_cond_signal(&cv_next);
						//return 0; /* Exit */
					} else {
						printf(" [BT] Robot no.%d is out of game\n", arg1);
					}
					break;
				case MSG_POSITION:
					printf(" [BT] Got the POSITION message\n");
					printf(" [BT] You sent to a wrong address, man: %d!\n", arg1);
					break;
				case MSG_BALL:
					printf(" [BT] Got the BALL message.\n");
          mod_btcom_send_ACK(gTeamMateId, ret, ACK_OK);/*TODO*/
					if (arg1 == DROP) {
						printf(" [BT] Someone dropped a ball at location x = %d, y = %d\n", arg2, arg3);
					} else {
						printf(" [BT] Someone picked up the ball at location x = %d, y = %d\n", arg2, arg3);
					}
					/* Send ackowledgement*/
          //mod_btcom_send_ACK(gTeamMateId, 0, ACK_OK);/*TODO*/
					break;
        case ACK_OK:
          printf(" [BT] ACK received. Thanks, mate!\n");
          break;
				default:
					printf(" [ERROR] Incorrect type of message received: %d\n", actionType);
					break;
			}
		} else {
			printf(" [ERROR] Got a problem when receiving the message. RET = %d", ret);
			break;
		}
    pthread_mutex_unlock(&bt_mutex);
		sleep(1);
	}

	
	return NULL;
}

void *__mod_btcom_send_location(void* arg) {
	int16_t ret, x, y;

	x = 21; /*TODO: update the real values here*/
	y = 22; /*TODO:*/
  //printf("Welcome from send location thread\n");
	/* Periodically send the location */
  while (1) {
    //if ( (gMyState != STOPPED) && (gMyState != KICKED) && (gMyState != NOTSTARTED) ){
    //printf("mystate = %d", gMyState );
    if (gMyState == RUNNING) {
      x = (int16_t)ceilf(robot_position.x);
      y = (int16_t)ceilf(robot_position.y);
    
			printf(" [BT] Sending location: X = %d, Y = %d\n", x, y);
			ret = mod_btcom_send_POSITION(x, y);

      if (ret < 0) break;
		}
    sleep(2);
	}

	return NULL;
}
