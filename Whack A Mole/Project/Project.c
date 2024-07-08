#include "stm32f407xx.h"

void interrupt(void);
void configurepushButton(void);
void configureDport(void);
void configureAport(void);
void sevensegment(int check);
void EXTI0_IRQHandler(void);
 
void interrupt(void)
{
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  SYSCFG->EXTICR[0] &= ~ ((uint32_t)0x000f);
  EXTI->FTSR &= ~((uint32_t)1);  
  EXTI->IMR |= 1;
  EXTI->RTSR |= 1;  
  NVIC_EnableIRQ (EXTI0_IRQn);  
  NVIC_SetPriority(EXTI0_IRQn, 1);
}
void configurepushButton(void)
{
  RCC->AHB1ENR  |= (1<<0);
	GPIOA->MODER &= ~(uint32_t)(3<<0);

}
static int number =0;
void sevensegment(int check)
{
	int temp;
	GPIOD->ODR&=~((uint32_t)(0xff));
	if(check==0)
	{
		temp=number%10;
		GPIOA->MODER &=~((uint32_t)(1<<1));
		GPIOA->MODER |=(1<<2);
  }
	else
	{
		temp=number/10;
		GPIOA->MODER &=~((uint32_t)(1<<2));
		GPIOA->MODER |=(1<<1);
  }

	if(temp==0)
	{
	   GPIOD->ODR|=(uint32_t)0x3f; 
	}
	else if(temp==1)
  {
	   GPIOD->ODR|=(uint32_t)0x6;
	}
	else if(temp==2)
	{
		GPIOD->ODR|=(uint32_t)0x5b; 
	}
	else if(temp==3)
  {
		GPIOD->ODR|=(uint32_t)0x4f;
	}
   else if(temp==4)
	{
		GPIOD->ODR|=(uint32_t)0x66;
	}
	else if(temp==5)
  {
		GPIOD->ODR|=(uint32_t)0x6d; 
	}
	else if(temp==6)
  {
		GPIOD->ODR|=(uint32_t)0x7d; 
	}
	else if(temp==7)
  {	
		GPIOD->ODR|=(uint32_t)0x7; 
	}
	else if(temp==8)
  {
		GPIOD->ODR|=(uint32_t)0x7f; 
	}
	else  if(temp==9)
  { 
		GPIOD->ODR|=(uint32_t)0x6f;
	}
}

void configureDport(void)
{
	RCC->AHB1ENR  |= (1<<3);
	GPIOD->MODER &= ~((uint32_t)(0x3fff));
	GPIOD->MODER |= (1<<0);
	GPIOD->MODER |= (1<<2);
	GPIOD->MODER |= (1<<4);
	GPIOD->MODER |= (1<<6);
	GPIOD->MODER |= (1<<8);
	GPIOD->MODER |= (1<<10);
	GPIOD->MODER |= (1<<12);
	GPIOD->ODR &= ~((uint32_t)(0x7f));
}

void configureAport(void)
{
		GPIOA->MODER &=~((uint32_t)(0x3c));
		GPIOA->MODER |= (1<<2);
		GPIOA->MODER |= (1<<4);
		GPIOA->ODR &=~((uint32_t)(0x60));
}

int main(void)
{
		configureDport();
		configureAport();
		configurepushButton();
		interrupt();
	while(1)
	{
		sevensegment(0);
		sevensegment(1);
	}
}

void EXTI0_IRQHandler(void)
{
	if (EXTI->PR & (1<<0))
	{
			number++;
		if(number>99)
		{
			number=0;
		}
			EXTI->PR |= (1<<0);
	}
}