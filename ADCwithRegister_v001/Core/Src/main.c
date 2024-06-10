#include "string.h"
#include "main.h"

uint8_t adc_value;


void RCC_Config()
{
	RCC->CR |= 0x10000; 			  // HSEON enable
	while(!(RCC->CR & 0x20000));      // HSEON Ready Flag wait
	RCC->CR |= 0x80000;				  // CSS enable
	RCC->PLLCFGR |= 0x400000; 		  // PLL e HSE sectik
	RCC->PLLCFGR |= 0x000004; 		  // PLL M = 4
	RCC->PLLCFGR |= 0x005A00; 		  // PLL N=168
	RCC->PLLCFGR |= 0x000000; 		  // PLL P=2
	RCC->CFGR |= 0x000000; 		 	  // AHB Prescaler = 1
	RCC->CFGR |= 0x080000; 		  	  // APB2 Prescaler = 2
	RCC->CFGR |= 0x001400; 		  	  // APB1 Presclaer = 4
	RCC->CIR |= 0x00080000;			  // HSERDY Flag Clear
	RCC->CIR |= 0x00800000;			  // CSS Flag Clear

}

void GPIO_Config()
{
	RCC->AHB1ENR |= 0x01;             // GPIOA port clock enable
	GPIOA->MODER |= 0x03;			  // analog pin selected pin 0
	GPIOA->OSPEEDR |= 0x03;			  // output selected high speed
	//GPIOA->PUPDR |= 0x02;			  // GPIOA selected pull-down

}


void ADC_Config()
{
	RCC->APB2ENR |= 0x100;			                  // ADC1 Clock enable
	ADC1->CR1 |= 0x2000000;			                  // ADC resolution choose 8 bit
	ADC1->CR2 |= ADC_CR2_ADON << 0x01;				  // Enable ADC (ADON = 1)
	ADC1->SMPR2 |= 0x02;			                  // ADC Sample 28 cycles
	ADC->CCR |= 0x10000;							  // Div 4

}

uint8_t Read_ADC()
{
	uint8_t value;
	ADC1->CR2 |= ADC_CR2_ADON << 0x01;				  // Enable ADC (ADON = 1)

	ADC1->CR2 |= 0x40000000;
	while(ADC1->SR & 0x0002);

	value = ADC1->DR ;

	return value;

}

int main(void)
{

  RCC_Config();
  GPIO_Config();
  ADC_Config();


  while (1)
  {

	  adc_value = Read_ADC();
  }

}
