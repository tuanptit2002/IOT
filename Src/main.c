
#include<stdio.h>
#include<stdint.h>
#include <stm32f401re.h>
#include <stm32f401re_rcc.h>
#include<stm32f401re_gpio.h>
#include<led.h>
#include<button.h>
#include <buzzer.h>



//define logic GPIO pin

#define GPIO_PIN_SET 1
#define GPIO_PIN_RESET 0
#define GPIO_PIN_LOW 0
#define GPIO_PIN_HIGHT 1


// define GPIO pin
#define LED_GPIO_PORT GPIOA
#define LED_GPIO_PIN GPIO_Pin_5
#define LED_PIN5  5
#define LEDControl_SetClock RCC_AHB1Periph_GPIOA

#define BUTTON_GPIO_PORT  GPIOC
#define BUTTON_GPIO_PIN   GPIO_Pin_13
#define BUTTON_PIN13    13
#define BUTTONControl_SetClock RCC_AHB1Periph_GPIOC



static
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(LEDControl_SetClock, ENABLE);
//	RCC_AHB1PeriphClockCmd(LEDControl_SetClock, ENABLE);
	GPIO_InitStructure.GPIO_Pin  = LED_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed  =  GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);
}

static
void Button2_Init(void){
	GPIO_InitTypeDef GPIO_InitStucture;

	RCC_AHB1PeriphClockCmd(BUTTONControl_SetClock, ENABLE);
	GPIO_InitStucture.GPIO_Pin =  BUTTON_GPIO_PIN;
	GPIO_InitStucture.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStucture.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStucture);
}

static
void LedControl_SetStatus(GPIO_TypeDef *GPIOx, uint8_t GPIO_PIN, uint8_t Status)
{
	if(Status  == GPIO_PIN_SET){
		GPIOx -> BSRRL |= 1 << GPIO_PIN;
	}
	if(Status  == GPIO_PIN_RESET){
		GPIOx -> BSRRH |= 1 << GPIO_PIN;
	}
}

static
uint8_t ButtonRead_Status(GPIO_TypeDef *GPIOx, uint32_t GPIO_PIN)
{
	uint32_t Read_Pin;

	Read_Pin  = (GPIOx -> IDR) >> GPIO_PIN;
	Read_Pin  = Read_Pin & 0x01;

	return Read_Pin;
}

void mainInit(){
	SystemCoreClockUpdate();
	LED_Init();
	Button2_Init();
}
void Delay(__IO uint32_t nCount) {
    while(nCount--) {
    }
}
int main(void)
{
   mainInit();
   uint8_t led_status = GPIO_PIN_RESET;
	while(1){
				if(ButtonRead_Status(BUTTON_GPIO_PORT, BUTTON_PIN13) == 0){
					Delay(3000);
					if(ButtonRead_Status(BUTTON_GPIO_PORT, BUTTON_PIN13) == 0){
						led_status  = !led_status;
						LedControl_SetStatus(LED_GPIO_PORT, LED_PIN5, led_status);
					}
					 Delay(300000);
				}
	}
}
