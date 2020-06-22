/*
 * Servers.c
 *
 *  Created on: 2020Äê4ÔÂ26ÈÕ
 *      Author: WangXiang
 */
#include "Servers.h"
#include <stdio.h>
#include "UserConfig.h"
#include <stddef.h>

//struct Device_control
//{
//	char USB_buffer[10];//机箱号、模式、地址高、地址低、功能
//	char status;//Whether to complete the update
//} USB_control;

char begin_status = 0;				//variable for UART
char end_status = 0;
int i = 0;
extern DeviceControl DeviceControlMessage;

/* *********************************************
 * name:Get_USB_Message
 * function: USB receive control messages
 * variable:USB message of control messages
 * time:2020.6.17
 * Author: ZRH
 * *********************************************/
void Get_USB_Message(uint8_t buffer[200])
{
	if (USB_RxRead(buffer, 10) > 0)
	{
		DeviceControlMessage.DeviceNumber = buffer[2];
		DeviceControlMessage.ControlMode = buffer[3];
		DeviceControlMessage.addh = buffer[4];
		DeviceControlMessage.addl = buffer[5];
		DeviceControlMessage.function = buffer[6];
		DeviceControlMessage.status = 0x01;
//		USB_printf("%s",buffer);
	}
}

/* *********************************************
 * name:Control_485_device
 * function: After receiving the USB message, control the 485 device
 * variable:\
  * time:2020.6.17
 * Author: ZRH
 * *********************************************/
void Control_485_device()
{
	if (DeviceControlMessage.DeviceNumber == 0x01)
	{

	}
}

/* *********************************************
 * name:USART1_IRQHandler
 * function: USB device Send and receive messages
 * variable��\
 * time:2020.6.9
 * Author: ZRH
 * *********************************************/
//void USART1_IRQHandler(void)
//{
//	char x = USART_ReceiveData(USART1);
//
//	if (x == 0x55)
//	{
//		begin_status++;
////		USB_control.USB_buffer[0] = x;
//	} else if (x != 0x55 && begin_status == 1) //begin_status==2 means complete receive message
//	{
//		begin_status = 0;
////		USB_control.USB_buffer[0] = 0x00;
//	}
//	if (x == 0x0D)								//消息以0D,0A结尾
//	{
//		end_status++;
//	} else if (x != 0x0A && end_status == 1)
//	{
//		end_status = 0;
//	}else if (x == 0x0A && end_status == 1)
//	{
//		end_status++;
//	}
//
//	if (USB_control.status == 0 && begin_status > 1)
//	{
//		USB_control.USB_buffer[i]=x;
//		i++;
//		if(end_status>1)
//		{
//			i=0;//variable init
//			end_status = 0;
//			begin_status = 0;
//			USB_control.status = 1;//buffer init
//		}
//	}
//}
void USART1_IRQHandler(void)
{
	char x = USART_ReceiveData(USART1);
	if (x == 0x55)
	{
		begin_status++;
	} else if (x != 0x55 && begin_status == 1) //begin_status==2 means complete receive message
	{
		begin_status = 0;
	}
	if (begin_status > 1)
	{
		USB_printf("%c", 0x01);
		begin_status = 0;
	}
}
/* *********************************************
 * name:USART2_IRQHandler
 * function: 485 device Send and receive messages
 * variable:\
 * time:2020.6.9
 * Author: ZRH
 * *********************************************/
void USART2_IRQHandler(void)
{
	char x = USART_ReceiveData(USART2);
	if (x == 0x55)
	{
		begin_status++;
	} else if (x != 0x55 && begin_status == 1) //begin_status==2 means complete receive message
	{
		begin_status = 0;
	}
	if (begin_status > 1)
	{
		USB_printf("%c", 0x01);
		begin_status = 0;
	}
}

void USART3_IRQHandler(void)
{
	char x = USART_ReceiveData(USART3);
	if (x == 0x55)
	{
		begin_status++;
	} else if (x != 0x55 && begin_status == 1) //begin_status==2 means complete receive message
	{
		begin_status = 0;
	}
	if (begin_status > 1)
	{
		USB_printf("%c", 0x01);
		begin_status = 0;
	}
}

/* *********************************************
 * name:Control_light_device
 * function: Control light switch
 * variable: addh:Address high
 * 			 addl:Address low
 * 			 mode:Light switch mode
 * 			 uart:UART number
 * time:2020.6.1
 * Author: ZRH
 * *********************************************/
void Control_light_device(char addh, char addl, char mode, char uart)
{
	IWDG_Feed();
	char Cumulative_sum = 0x55 + 0x55 + 0x08 + 0x01 + 0x30 + 0x41 + 0x01 + addh + addl + mode;
	digitalWriteA(GPIO_Pin_1, HIGH);
	digitalWriteA(GPIO_Pin_8, HIGH);
	digitalWriteC(GPIO_Pin_4, HIGH);
	delay_us(1500);
	if (uart == 0x01)
	{
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x55);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x55);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x08);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x01);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x30);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x41);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x01);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, addh);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, addl);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, mode);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, Cumulative_sum);
	} else if (uart == 0x02)
	{
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x55);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x55);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x08);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x01);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x30);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x41);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x01);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, addh);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, addl);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, mode);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, Cumulative_sum);
	} else if (uart == 0x03)
	{
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x55);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x55);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x08);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x01);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x30);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x41);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x01);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, addh);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, addl);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, mode);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, Cumulative_sum);
	}

	delay_us(1500);
	digitalWriteA(GPIO_Pin_1, LOW);
	digitalWriteA(GPIO_Pin_8, LOW);
	digitalWriteC(GPIO_Pin_4, LOW);
}

/* *********************************************
 * name:Control_Scenes_device
 * function: Control light switch
 * variable:scence_num:Scene number
 * 			uart:UART number
 * time:2020.6.1
 * Author: ZRH
 * *********************************************/
void Control_Scenes_device(char scence_num, char uart)
{
	IWDG_Feed();
	char Cumulative_sum = 0x55 + 0x55 + 0x06 + 0x01 + 0x30 + 0x40 + 0x00 + scence_num;
	digitalWriteA(GPIO_Pin_1, HIGH);
	digitalWriteA(GPIO_Pin_8, HIGH);
	digitalWriteC(GPIO_Pin_4, HIGH);
	delay_us(1500);

	if (uart == 0x01)
	{
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x55);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x55);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x06);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x01);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x30);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x40);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x00);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, scence_num);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, Cumulative_sum);
	} else if (uart == 0x02)
	{
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x55);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x55);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x06);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x01);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x30);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x40);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x00);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, scence_num);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, Cumulative_sum);
	} else if (uart == 0x03)
	{
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x55);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x55);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x06);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x01);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x30);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x40);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x00);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, scence_num);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, Cumulative_sum);
	}

	delay_us(1500);
	digitalWriteA(GPIO_Pin_1, LOW);
	digitalWriteA(GPIO_Pin_8, LOW);
	digitalWriteC(GPIO_Pin_4, LOW);
}
/* *********************************************
 * name:Control_Curtain_device
 * function: Control music mode
 * variable��addh:Address high
 * 			 addl:Address low
 * 			 mode:Music switch mode
 * 			 uart:UART number
 * time:2020.6.1
 * Author: ZRH
 * *********************************************/
void Control_Curtain_device(char addh, char addl, char mode, char uart)
{
	IWDG_Feed();
	char Cumulative_sum = 0x55 + 0x55 + 0x08 + 0x01 + 0x30 + 0x43 + 0x03 + addh + addl + mode;
	digitalWriteA(GPIO_Pin_1, HIGH);
	digitalWriteA(GPIO_Pin_8, HIGH);
	digitalWriteC(GPIO_Pin_4, HIGH);
	delay_us(1500);

	if (uart == 0x01)
	{
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x55);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x55);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x08);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x01);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x30);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x43);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x03);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, addh);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, addl);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, mode);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, Cumulative_sum);
	} else if (uart == 0x02)
	{
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x55);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x55);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x08);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x01);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x30);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x43);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x03);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, addh);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, addl);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, mode);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, Cumulative_sum);
	} else if (uart == 0x03)
	{
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x55);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x55);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x08);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x01);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x30);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x43);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x03);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, addh);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, addl);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, mode);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, Cumulative_sum);
	}

	delay_us(1500);
	digitalWriteA(GPIO_Pin_1, LOW);
	digitalWriteA(GPIO_Pin_8, LOW);
	digitalWriteC(GPIO_Pin_4, LOW);
}
/* *********************************************
 * name:Control_Music_device
 * function: Control music mode
 * variable��addh:Address high
 * 			 addl:Address low
 * 			 mode:Music switch mode
 * 			 uart:UART number
 * time:2020.6.1
 * Author: ZRH
 * *********************************************/
void Control_Music_device(char addh, char addl, char mode, char uart)
{
	IWDG_Feed();
	char Cumulative_sum = 0x55 + 0x55 + 0x08 + 0x01 + 0x30 + 0x44 + 0x04 + addh + addl + mode;
	digitalWriteA(GPIO_Pin_1, HIGH);
	digitalWriteA(GPIO_Pin_8, HIGH);
	digitalWriteC(GPIO_Pin_4, HIGH);
	delay_us(1500);

	if (uart == 0x01)
	{
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x55);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x55);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x08);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x01);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x30);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x44);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, 0x04);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, addh);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, addl);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, mode);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART1, Cumulative_sum);
	} else if (uart == 0x02)
	{
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x55);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x55);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x08);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x01);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x30);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x44);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, 0x04);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, addh);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, addl);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, mode);
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART2, Cumulative_sum);
	} else if (uart == 0x03)
	{
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x55);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x55);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x08);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x01);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x30);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x44);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, 0x04);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, addh);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, addl);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, mode);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			;
		USART_SendData(USART3, Cumulative_sum);
	}

	delay_us(1500);
	digitalWriteA(GPIO_Pin_1, LOW);
	digitalWriteA(GPIO_Pin_8, LOW);
	digitalWriteC(GPIO_Pin_4, LOW);
}
