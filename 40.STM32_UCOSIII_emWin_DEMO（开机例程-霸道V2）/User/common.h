#ifndef __COMMON_H_
#define __COMMON_H_

#include  <stdint.h>
#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>
/**************************************************************************************
*
*       Defines
*
***************************************************************************************
*/
//#define USE_EXRAMDATA

#ifdef  USE_EXRAMDATA
#define EXDATAADD					(0x680C0000-EXRAMDATA_SIZE)
#endif

#define COMDATA_SIZE			0x1000	//4096B
#define EXRAMDATA_SIZE		0x1000	//4096B

#define CODEADD						(uint16_t *)(0x680C0000)
/*********************************************************************
*
*       data
*
**********************************************************************
*/
extern uint8_t comdata[COMDATA_SIZE];

#ifdef USE_EXRAMDATA
extern uint8_t exramdata[EXRAMDATA_SIZE] __attribute__((at(EXDATAADD)))
#endif

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
void com_data2null(uint8_t *data,uint32_t length);

void com_gbk2utf8(const char *src, char *str);
void com_utf82gbk(const char *src, char *str);
void com_createdir(const char *dir);
#endif //end of __COMMON_H_
