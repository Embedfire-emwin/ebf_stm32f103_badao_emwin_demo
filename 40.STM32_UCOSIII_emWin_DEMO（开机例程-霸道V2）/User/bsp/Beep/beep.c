/*
******************************************************************************
* @file    bsp_led.c
* @author  野火
* @version V1.0
* @date    2015-xx-xx
* @brief   led应用函数接口
******************************************************************************
* @attention
*
* 实验平台:野火 iSO STM32 开发板 
* 论坛    :http://www.firebbs.cn
* 淘宝    :https://fire-stm32.taobao.com
*
******************************************************************************
*/
#include "..\User\bsp\Beep\beep.h" 

void Beep_Init ( void )
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	
	/*开启GPIOB和GPIOF的外设时钟*/
	macBEEP_GPIO_APBxClock_FUN  ( macBEEP_GPIO_CLK, ENABLE ); 

	/*选择要控制的GPIOG引脚*/															   
	GPIO_InitStructure.GPIO_Pin = macBEEP_PIN;	

	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*调用库函数，初始化GPIOG6*/
	GPIO_Init ( macBEEP_PORT, & GPIO_InitStructure );

	/* 关闭*/
	macBEEP_OFF ();
}
/*********************************************END OF FILE**********************/
