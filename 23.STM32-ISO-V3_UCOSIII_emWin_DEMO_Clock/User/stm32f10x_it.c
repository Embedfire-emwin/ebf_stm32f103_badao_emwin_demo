/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "includes.h"

//Clock
char TimeDisplay=0;
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
	printf("HardFault!!!");
#ifdef SOFTRESET
	Soft_Reset();
#endif
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/* 呼吸灯中断服务函数 */
void TIM3_IRQHandler(void)
{	
	static uint8_t pwm_index = 0;			//用于PWM查表
	static uint8_t period_cnt = 0;		//用于计算周期数
	/* LED亮度等级 PWM表 */
	uint8_t indexWave[] = {1,1,2,2,3,4,6,8,10,14,19,25,33,44,59,80,107,143,191,255,
							255,191,143,107,80,59,44,33,25,19,14,10,8,6,4,3,2,2,1,1};
	CPU_SR_ALLOC();

	CPU_CRITICAL_ENTER();  
	OSIntNestingCtr++;
	CPU_CRITICAL_EXIT();
							
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)	//TIM_IT_Update
 	{			
			period_cnt++;
			if(period_cnt >= 10)										//若输出的周期数大于10，输出下一种脉冲宽的PWM波
			{
				
				TIM3->CCR3 = indexWave[pwm_index];	//根据PWM表修改定时器的比较寄存器值
				pwm_index++;												//标志PWM表的下一个元素
			
				if( pwm_index >=  40)								//若PWM脉冲表已经输出完成一遍，重置PWM查表标志
				{
					pwm_index=0;								
				}
				
				period_cnt=0;												//重置周期计数标志
		}
		TIM_ClearITPendingBit (TIM3, TIM_IT_Update);	//必须要清除中断标志位
	}
	
	/* 在os_core.c文件里定义,如果有更高优先级的任务就绪了,则执行一次任务切换 */
	OSIntExit();
}

/**
  * @brief  This function handles RTC interrupt request.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{
	CPU_SR_ALLOC();

	CPU_CRITICAL_ENTER();  
	OSIntNestingCtr++;
	CPU_CRITICAL_EXIT();
	
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
	{
		/* Clear the RTC Second interrupt */
		RTC_ClearITPendingBit(RTC_IT_SEC);		
		TimeDisplay = 1;
		/* Wait until last write operation on RTC registers has finished */
		RTC_WaitForLastTask();
	}
	
	/* 在os_core.c文件里定义,如果有更高优先级的任务就绪了,则执行一次任务切换 */
	OSIntExit();
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
