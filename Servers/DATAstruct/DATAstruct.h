/*
 * DATAstruct.h
 *
 *  Created on: 2020年6月2日
 *      Author: wxujs
 */

#ifndef DATASTRUCT_DATASTRUCT_H_
#define DATASTRUCT_DATASTRUCT_H_

/*
 * USB解析后的控制消息
 * 机箱号、模式、地址高、地址低、功能
 */
typedef struct
{
	char DeviceNumber;
	char ControlMode;
	char addh;
	char addl;
	char function;
	char status;  //Whether the message is refreshed
} DeviceControl;


#endif /* DATASTRUCT_DATASTRUCT_H_ */
