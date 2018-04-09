#ifndef MQTT_H_INCLUDED

#define MQTT_H_INCLUDED



#include <string.h>

#include <stdint.h>


uint8_t mqtt_message[127];

void mqtt_connect_message(void) {

	mqtt_message[0] = 0x10;                      // MQTT Message Type CONNECT

	mqtt_message[1] = 0x12;   // Remaining length of the message



	mqtt_message[2] =0x00;                       // Protocol Name Length MSB

	mqtt_message[3] =0x04;                       // Protocol Name Length LSB

	mqtt_message[4] = 0x4D;                      // ASCII Code for M

	mqtt_message[5] = 0x51;                      // ASCII Code for Q

	mqtt_message[6] = 0x54;                      // ASCII Code for T

	mqtt_message[7] = 0x54;                     // ASCII Code for T

	mqtt_message[8] = 0x04;                     // ASCII Code for d

	mqtt_message[9] = 0x02;                     // ASCII Code for p

	mqtt_message[10] = 0x00;                      // KA MSB

	mqtt_message[11] = 0x3C;                      // KA LSB

	mqtt_message[12] = 0x00;                      // CIDLEN MSB

	mqtt_message[13] = 0x06;                     //CIDLEN LSB
	mqtt_message[14]=0x41;
	mqtt_message[15]=0x42;
	mqtt_message[16]=0x43;
	mqtt_message[17]=0x44;
	mqtt_message[18]=0x45;
	mqtt_message[19]=0x45;
                   // Client ID length MSB
     // Client ID length LSB
	// Client ID
}

void mqtt_publish_message(void) {
	mqtt_message[0] = 0x30;                                  // MQTT Message Type CONNECT
	mqtt_message[1] =0x13 ;   // Remaining length
	mqtt_message[2] = 0x00;                                   // MQTT Message Type CONNECT
	mqtt_message[3] = 0x08;                        // tplen msb
	mqtt_message[4]=0x76;
	mqtt_message[5]=0x61;
	mqtt_message[6]=0x6C;
	mqtt_message[7]=0x65;
	mqtt_message[8]=0x74;
	mqtt_message[9]=0x72;
	mqtt_message[10]=0x6F;
	mqtt_message[11]=0x6E;
	mqtt_message[12]=0x68;
	mqtt_message[13]=0x65;
	mqtt_message[14]=0x6C;
	mqtt_message[15]=0x6C;
	mqtt_message[16]=0x6F;
	mqtt_message[17]=0x72;
	mqtt_message[18]=0x61;
	mqtt_message[19]=0x76;
	mqtt_message[20]=0x69;
}
void mqtt_disconnect_message(uint8_t * mqtt_message) {
	mqtt_message[0] = 0xE0; // msgtype = connect
	mqtt_message[1] = 0x00; // length of message (?)
}







#endif // MQTT_H_INCLUDED