/**
  ******************************************************************************
  * @file    GUIDEMO_Fatfs.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����ļ�ϵͳ
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "stm32f10x.h"
#include "..\User\usart\bsp_usart1.h"
#include "..\User\lcd\bsp_ili9341_lcd.h"
#include "ff.h"
#include "GUI.h"

FIL fnew;													/* file objects */
FATFS fs;													/* Work area (file system object) for logical drives */
FRESULT res; 
UINT br, bw;            					/* File R/W count */
BYTE buffer[4096]={0};       		  /* file copy buffer */
BYTE textFileBuffer[] = "Welcome to use Wildfire F103 stm32 Development Board,\
this is a demo about enWin && Flash FatFS.\n\
today is a good day";

//Ҫ���ԵĴ��̺ţ�0Ϊspi��1Ϊsd��
char disk_num[] = "0:";



void Fatfs_MainTask(void)
{
		char Str_temp[100];
	
	  /* ������ʾ�ļ����ݵĴ��ڴ�С */ 
		GUI_RECT file_content;
	
		GUI_SetFont(GUI_FONT_8X16);
	
		file_content.x0 = 5;
		file_content.y0 =GUI_GetFontSizeY() * 7;
		file_content.x1 = LCD_GetXSize()-5;
		file_content.y1 = LCD_GetYSize()-5;
	
		/* ����Ļˢ�ϱ�����ɫ */
		GUI_Clear();	
	  
		GUI_DispStringAt ("f_mount...",5,GUI_GetFontSizeY()*1);
		
		GUI_Delay(500);		
		LCD_BK_EN;//��Һ��������		
		
		/* Register work area for each volume (Always succeeds regardless of disk status) */
		res = f_mount(&fs,disk_num,1);	
		
		if(res == FR_NO_FILESYSTEM)
		{
			/* ����ǰ����ɫ��������ɫ��*/
			GUI_SetColor(GUI_RED);

			GUI_DispStringAt ("File System not found on disk !",5,GUI_GetFontSizeY()*3);
			while(1);
		}
		else if	(res != FR_OK)
		{
			/* ����ǰ����ɫ��������ɫ��*/
			GUI_SetColor(GUI_RED);
			
			sprintf(Str_temp,"File System err:%d !",res);

			GUI_DispStringAt (Str_temp,5,GUI_GetFontSizeY()*3);
			while(1);
		}

		/* function disk_initialize() has been called in f_open */
		
	  GUI_DispStringAt ("f_open :newfile.txt ...",5,GUI_GetFontSizeY()*2);
	
		//ƴ���ļ�·��
		sprintf(Str_temp,"%snewfile.txt",disk_num);
		/* Create new file on the drive  */
		res = f_open(&fnew, Str_temp, FA_CREATE_ALWAYS | FA_WRITE );
 
		if ( res == FR_OK )
		{
			res = f_write(&fnew, textFileBuffer, sizeof(textFileBuffer), &bw);
			f_close(&fnew);      
		}
		else
		{
			/* ����ǰ����ɫ��������ɫ��*/
			GUI_SetColor(GUI_RED);
			
			sprintf(Str_temp,"File System err:%d !",res);

			GUI_DispStringAt (Str_temp,5,GUI_GetFontSizeY()*5);
			while(1);
		}

		GUI_DispStringAt ("f_read :newfile.txt ...",5,GUI_GetFontSizeY()*3);
		
		res = f_open(&fnew, Str_temp, FA_OPEN_EXISTING | FA_READ); 	 
		res = f_read(&fnew, buffer, sizeof(buffer), &br); 

		printf("\r\n %s ", buffer);
		
		GUI_DispStringAt ("file content:",5,GUI_GetFontSizeY()*5);
		
		/* ����ǰ����ɫ��������ɫ��*/
		GUI_SetColor(GUI_RED);
		
		/* �������� */
		GUI_SetFont(GUI_FONT_COMIC18B_ASCII);
		
		/* ��ʾ�ı�����Ļ�� */
		GUI_DispStringInRectWrap((const char *)buffer,&file_content,GUI_TA_LEFT,GUI_WRAPMODE_WORD) ;
		
		/* Close open files */
		f_close(&fnew);	                                      
		 
    /* Unregister work area prior to discard it */
		f_mount(NULL,disk_num,1);	
		
		while(1);
}

/*********************************************END OF FILE**********************/
	  
