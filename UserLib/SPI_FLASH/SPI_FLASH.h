/*
 * SPI_FLASH.h
 *
 *  Created on: 2020年5月22日
 *      Author: WangXiang
 */

#ifndef SPI_FLASH_SPI_FLASH_H_
#define SPI_FLASH_SPI_FLASH_H_
#include "UserConfig.h"
#include <stdarg.h>

#define Page1 0x0
#define Page2 0x200
#define Page3 0x400
#define Page4 0x600
#define Page5 0x800


#define CS_HIGH digitalWriteA(GPIO_Pin_4, HIGH)
#define CS_LOW digitalWriteA(GPIO_Pin_4, LOW)

extern int SPI_printf(uint32_t page, const char *fmt, ...);

void SPI_INIT();
void SPI_write(u8 TxData);
void SPI_writeStr(uint32_t page, char *str);

void WREN();
void ERDI();

void ts_itoa(char **buf, unsigned int d, int base);
int ts_formatstring(char *buf, const char *fmt, va_list va);
int ts_formatlength(const char *fmt, va_list va);

#endif /* SPI_FLASH_SPI_FLASH_H_ */
