/*
 * Servers.h
 *
 *  Created on: 2020��4��26��
 *      Author: WangXiang
 */

#ifndef SERVERS_H_
#define SERVERS_H_

void Get_USB_Message(unsigned char* buffer);
void Control_light_device(char addh, char addl, char mode, char uart);
void Control_Scenes_device(char scence_num, char uart);
void Control_Curtain_device(char addh, char addl, char mode,char uart);
void Control_Music_device(char addh, char addl, char mode, char uart);


#endif /* SERVERS_H_ */
