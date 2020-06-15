/*
 * Servers.h
 *
 *  Created on: 2020年4月26日
 *      Author: WangXiang
 */

#ifndef SERVERS_H_
#define SERVERS_H_
#include "UserConfig.h"
#include "DATAstruct/DATAstruct.h"





bool iscontants(char *str, char *cmd);
void send_cmd(char *str);
bool check_receives(uint8_t cmd_number, char *cmd);
void BC28_RESET();
void BC28_Init();
void pack_to_aliyun();

void writeUTC(char *time, char *data);
void writeL(char *lan, char *data);
void clearStr(char *str, uint8_t i);

void anaGPS();

uint8_t get_pack_currentPack(CanRxMsg CANRX);

#endif /* SERVERS_H_ */
