<<<<<<< HEAD
#include "time_exti.h"

void_func_point TIM_func[8]={null_func, null_func, null_func, null_func, null_func, null_func, null_func, null_func};

void TimerSet_NVIC(u8 TimerNum,u32 time_us,void_func_point f,u8 NVIC_IRQ_CPP, u8 NVIC_IRQ_CSP)
{
	u32 arr,psc;
	
	TIM_TypeDef* TIMx;
	u32 RCC_APBxPeriph_TIMx;
	u8 TIMx_IRQn;
	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	if(TimerNum > TIMER8)return;
	
	TIM_func[TimerNum] = f;
	
	time_us*=72;
	if(time_us < 72*30)
	{
		arr=10;
		psc=time_us/arr;
	}
	else if(time_us < 65535*1000)
	{
		arr=time_us/1000;
		psc=time_us/arr;
	}
	else
	{
		arr=time_us/20000;
		psc=time_us/arr;
	}
	
	switch(TimerNum)
	{
		case TIMER1:
			TIMx = TIM1;
			RCC_APBxPeriph_TIMx = RCC_APB2Periph_TIM1;
			TIMx_IRQn = TIM1_UP_IRQn;
			break;
		
		case TIMER2:
			TIMx = TIM2;
			RCC_APBxPeriph_TIMx = RCC_APB1Periph_TIM2;
			TIMx_IRQn = TIM2_IRQn;
			break;
		
		case TIMER3:
			TIMx = TIM3;
			RCC_APBxPeriph_TIMx = RCC_APB1Periph_TIM3;
			TIMx_IRQn = TIM3_IRQn;
			break;
		
		case TIMER4:
			TIMx = TIM4;
			RCC_APBxPeriph_TIMx = RCC_APB1Periph_TIM4;
			TIMx_IRQn = TIM4_IRQn;
			break;
	}
	
	if(TIMx == TIM1 || TIMx == TIM8)
	{
		RCC_APB2PeriphClockCmd(RCC_APBxPeriph_TIMx, ENABLE);
	}
	else 
	{
		RCC_APB1PeriphClockCmd(RCC_APBxPeriph_TIMx, ENABLE); //时钟使能
	}

	TIM_DeInit(TIMx);
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseStructure.TIM_Period = arr-1; 		//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc-1; 	//设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 	//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	/**********************************设置中断优先级************************************/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); //设置NVIC中断分组1
	NVIC_InitStructure.NVIC_IRQChannel = TIMx_IRQn;  //TIM中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQ_CPP;  //先占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQ_CSP;  //从优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	TIM_ClearFlag(TIMx, TIM_FLAG_Update); 
	TIM_ITConfig(TIMx, TIM_IT_Update ,ENABLE);	//使能TIM中断
}

void TimerSet(u8 TimerNum,u32 time_us,void_func_point f)
{
	TimerSet_NVIC(TimerNum, time_us, f, 0, 3);
}

/*****************************定时中断函数*********************************************/
void TIM1_UP_IRQHandler(void)   //TIM1中断
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) 		//检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_func[TIMER1]();
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  	//清除TIMx的中断待处理位:TIM 中断源		
	}
}

void TIM2_IRQHandler(void)   //TIM2中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 		//检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_func[TIMER2]();
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  	//清除TIMx的中断待处理位:TIM 中断源		
	}
}

void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		TIM_func[TIMER3]();
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

void TIM4_IRQHandler(void)   //TIM4中断
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		TIM_func[TIMER4]();
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}








=======
#include "time_exti.h"
#include "Arduino.h"

void_func_point TIM_func[8]={null_func, null_func, null_func, null_func, null_func, null_func, null_func, null_func};

void TimerSet(u8 TimerNum,u32 us,void_func_point f)
{
	u8 NVIC_IRQ_CPP=0,NVIC_IRQ_CSP=3;
	u32 arr,psc;
	
	TIM_TypeDef* TIMx;
	u32 RCC_APBxPeriph_TIMx;
	u8 TIMx_IRQn;
	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	if(TimerNum > TIMER8)return;
	
	TIM_func[TimerNum] = f;
	
	us*=72;
	if(us<65535*1000)
	{
		arr=us/1000;
		psc=us/arr;
	}
	else
	{
		arr=us/20000;
		psc=us/arr;
	}
	
	switch(TimerNum)
	{
		case TIMER1:
			TIMx = TIM1;
			RCC_APBxPeriph_TIMx = RCC_APB2Periph_TIM1;
			TIMx_IRQn = TIM1_UP_IRQn;
			break;
		
		case TIMER2:
			TIMx = TIM2;
			RCC_APBxPeriph_TIMx = RCC_APB1Periph_TIM2;
			TIMx_IRQn = TIM2_IRQn;
			break;
		
		case TIMER3:
			TIMx = TIM3;
			RCC_APBxPeriph_TIMx = RCC_APB1Periph_TIM3;
			TIMx_IRQn = TIM3_IRQn;
			break;
		
		case TIMER4:
			TIMx = TIM4;
			RCC_APBxPeriph_TIMx = RCC_APB1Periph_TIM4;
			TIMx_IRQn = TIM4_IRQn;
			break;
	}
	
	if(TIMx == TIM1 || TIMx == TIM8)
	{
		RCC_APB2PeriphClockCmd(RCC_APBxPeriph_TIMx, ENABLE);
	}
	else 
	{
		RCC_APB1PeriphClockCmd(RCC_APBxPeriph_TIMx, ENABLE); //时钟使能
	}

	TIM_DeInit(TIMx);
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseStructure.TIM_Period = arr-1; 		//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc-1; 	//设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 	//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	/**********************************设置中断优先级************************************/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); //设置NVIC中断分组1
	NVIC_InitStructure.NVIC_IRQChannel = TIMx_IRQn;  //TIM中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQ_CPP;  //先占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQ_CSP;  //从优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
	TIM_ClearFlag(TIMx, TIM_FLAG_Update); 
	TIM_ITConfig(TIMx, TIM_IT_Update ,ENABLE);	//使能TIM中断
}

/*****************************定时中断函数*********************************************/
void TIM1_UP_IRQHandler(void)   //TIM1中断
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) 		//检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_func[TIMER1]();
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  	//清除TIMx的中断待处理位:TIM 中断源		
	}
}

void TIM2_IRQHandler(void)   //TIM2中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 		//检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_func[TIMER2]();
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  	//清除TIMx的中断待处理位:TIM 中断源		
	}
}

void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		TIM_func[TIMER3]();
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

void TIM4_IRQHandler(void)   //TIM4中断
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		TIM_func[TIMER4]();
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}








>>>>>>> 301cbab54594d1de84f6a7e456407b3a84e8d255
