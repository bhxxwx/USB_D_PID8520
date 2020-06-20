/*	USB虚拟串口设备
 *
 * 	PID: 8520
 *
 * 	南京 - 独立2台设备
 *
 * 	Author:王翔
 * 	20200615
 */
/*include*/
#include "stm32f10x.h"
#include <stdio.h>
#include <stddef.h>

#include "UserConfig.h"//用户库调用

uint16_t res_count;
DeviceControl DeviceControlMessage;  //USB control message

int main(void)
{
	DBGMCU_Config(DBGMCU_IWDG_STOP, ENABLE); //DEBUG时看门狗关闭
	nvic_init();
	USB_Port_Set(0);
	delay_us(200000);
	USB_Port_Set(1);
	USB_Config();
//	USB_printf("Devices PID:8520 Init OK!\r\n");
	usart_1_init(9600);
	usart_2_init(9600, 2);
	usart_3_init(9600, 3);
	IWDG_INIT(IWDG_Prescaler_64, 1563); //2.5S watch dog
//	delay_us(500000);
//	int count = 0, len = 0;
	while (1)
	{
		uint8_t buf[200] = { 0 };
		Get_USB_Message(buf);
		IWDG_Feed();
		if (DeviceControlMessage.status == 1)
		{
			if (DeviceControlMessage.DeviceNumber == 0x01)         			//Villa Level 1 or Booth(设备1口，使用串口2)
			{
				switch (DeviceControlMessage.ControlMode)
				{
					case 0x00:
						Control_Scenes_device(DeviceControlMessage.function, 0x02);					//0x01为1号串口
						break;          //Scene mode, serial port 1
					case 0x01:
						Control_light_device(DeviceControlMessage.addh, DeviceControlMessage.addl,
						        DeviceControlMessage.function, 0x02);
						break;          //Light mode, serial port 1
					case 0x03:
						Control_Curtain_device(DeviceControlMessage.addh, DeviceControlMessage.addl,
						        DeviceControlMessage.function, 0x02);
						break;          //Curtain mode, serial port 1
					case 0x04:
						Control_Music_device(DeviceControlMessage.addh, DeviceControlMessage.addl,
						        DeviceControlMessage.function, 0x02);
						break;          //Music mode, serial port 1
				}
			} else if (DeviceControlMessage.DeviceNumber == 0x02) //Villa Level 2 or single-apartment(设备2口，使用串口3)
			{
				switch (DeviceControlMessage.ControlMode)
				{
					case 0x00:
						Control_Scenes_device(DeviceControlMessage.function, 0x03);
						break;          //Scene mode, serial port 2
					case 0x01:
						Control_light_device(DeviceControlMessage.addh, DeviceControlMessage.addl,
						        DeviceControlMessage.function, 0x03);
						break;          //Light mode, serial port 2
					case 0x03:
						Control_Curtain_device(DeviceControlMessage.addh, DeviceControlMessage.addl,
						        DeviceControlMessage.function, 0x03);
						break;          //Curtain mode, serial port 2
					case 0x04:
						Control_Music_device(DeviceControlMessage.addh, DeviceControlMessage.addl,
						        DeviceControlMessage.function, 0x03);
						break;          //Music mode, serial port 2
				}
			} else if (DeviceControlMessage.DeviceNumber == 0x03)					//Villa Level 3(设备3口，使用串口1)
			{
				switch (DeviceControlMessage.ControlMode)
				{
					case 0x00:
						Control_Scenes_device(DeviceControlMessage.function, 0x01);
						break;          //Scene mode, serial port 3
					case 0x01:
						Control_light_device(DeviceControlMessage.addh, DeviceControlMessage.addl,
						        DeviceControlMessage.function, 0x01);
						break;          //Light mode, serial port 3
					case 0x03:
						Control_Curtain_device(DeviceControlMessage.addh, DeviceControlMessage.addl,
						        DeviceControlMessage.function, 0x01);
						break;          //Curtain mode, serial port 3
					case 0x04:
						Control_Music_device(DeviceControlMessage.addh, DeviceControlMessage.addl,
						        DeviceControlMessage.function, 0x01);
						break;          //Music mode, serial port 3
				}
			} else if (DeviceControlMessage.DeviceNumber == 0x04)							//Booth(设备1口，使用串口2)
			{
				switch (DeviceControlMessage.ControlMode)
				{
					case 0x00:
						Control_Scenes_device(DeviceControlMessage.function, 0x02);
						break;          //Scene mode, serial port 1
					case 0x01:
						Control_light_device(DeviceControlMessage.addh, DeviceControlMessage.addl,
						        DeviceControlMessage.function, 0x02);
						break;          //Light mode, serial port 1
					case 0x03:
						Control_Curtain_device(DeviceControlMessage.addh, DeviceControlMessage.addl,
						        DeviceControlMessage.function, 0x02);
						break;			//Curtain mode, serial port 1
					case 0x04:
						Control_Music_device(DeviceControlMessage.addh, DeviceControlMessage.addl,
						        DeviceControlMessage.function, 0x02);
						break;			//Music mode, serial port 1
				}
			} else if (DeviceControlMessage.DeviceNumber == 0x05)				//single-apartment(设备3口，使用串口1)
			{
				switch (DeviceControlMessage.ControlMode)
				{
					case 0x00:
						Control_Scenes_device(DeviceControlMessage.function, 0x01);
						break;          //Scene mode, serial port 2
					case 0x01:
						Control_light_device(DeviceControlMessage.addh, DeviceControlMessage.addl,
						        DeviceControlMessage.function, 0x01);
						break;          //Light mode, serial port 2
					case 0x03:
						Control_Curtain_device(DeviceControlMessage.addh, DeviceControlMessage.addl,
						        DeviceControlMessage.function, 0x01);
						break;			//Curtain mode, serial port 2
					case 0x04:
						Control_Music_device(DeviceControlMessage.addh, DeviceControlMessage.addl,
						        DeviceControlMessage.function, 0x01);
						break;			//Music mode, serial port 2
				}
			}
			DeviceControlMessage.status = 0x00;					//Mark bit cleared
		}

//		len = USB_RxRead(buf, sizeof(buf));
//		if(len>0)
//		{
//			count++;
//			USB_printf("PID:8520 Count=%d - Recvive Data:%s\r\n",count,buf);
//		}

	}
}

