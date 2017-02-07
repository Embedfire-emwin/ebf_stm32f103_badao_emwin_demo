/**
  ******************************************************************************
  * @file    main.c
  * @author  秉火
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   emWin基础例程主函数
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 iSO STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
	
#include "stm32f10x.h"

#include "GUI.h"

#include "..\User\usart\bsp_usart1.h"
#include "..\User\SysTick\bsp_SysTick.h"
#include "..\User\led\bsp_led.h"
#include "..\User\lcd\bsp_xpt2046_lcd.h"
#include "..\User\ExSRAM\bsp_fsmc_sram.h"
#include "..\User\lcd\bsp_ili9341_lcd.h"
#include "GUIDEMO.h"

/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{	
	FSMC_SRAM_Init();
	
	/* LED 端口初始化 */
	LED_GPIO_Config();	
  
  USART1_Config();
	
	XPT2046_Init();
	
	/* 初始化定时器 */
	SysTick_Init();
	
	/*CRC和emWin没有关系，只是他们为了库的保护而做的，这样STemWin的库只能用在ST的芯片上面，别的芯片是无法使用的。 */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
	
	/* 初始化GUI */
	GUI_Init(); 
	
	GUI_Delay(100);
	LCD_BK_EN;//开液晶屏背光
	
	while(1)
	{
		GUIDEMO_Main();
	}

}


/*********************************************END OF FILE**********************/
