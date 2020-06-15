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
int main(void)
{



	DBGMCU_Config(DBGMCU_IWDG_STOP, ENABLE); //DEBUG时看门狗关闭
	nvic_init();

	USB_Port_Set(0);
	delay_us(200000);
	USB_Port_Set(1);
	USB_Config();
    USB_printf("Devices PID:8520 Init OK!\r\n");

	int count = 0,len=0;
	while (1)
	{
		uint8_t buf[200] = {0};

		len = USB_RxRead(buf, sizeof(buf));
		if(len>0)
		{
			count++;
			USB_printf("PID:8520 Count=%d - Recvive Data:%s\r\n",count,buf);
		}

	}
}

