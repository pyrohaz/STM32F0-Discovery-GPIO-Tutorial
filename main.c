#include <stm32f0xx_gpio.h>
#include <stm32f0xx_rcc.h>

GPIO_InitTypeDef Gp; //Create GPIO struct


//Define LED pins
#define GreenLED_Pin GPIO_Pin_9
#define BlueLED_Pin GPIO_Pin_8
#define LED_GPIO GPIOC

//Define Push button
#define PushButton_Pin GPIO_Pin_0
#define PushButton_GPIO GPIOA

int main(void)
{
	//Enable clocks to both GPIOA (push button) and GPIOC (output LEDs)
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	Gp.GPIO_Pin = GreenLED_Pin | BlueLED_Pin; //Set pins inside the struct
	Gp.GPIO_Mode = GPIO_Mode_OUT; //Set GPIO pins as output
	Gp.GPIO_OType = GPIO_OType_PP; //Ensure output is push-pull vs open drain
	Gp.GPIO_PuPd = GPIO_PuPd_NOPULL; //No internal pullup resistors required
	Gp.GPIO_Speed = GPIO_Speed_Level_1; //Set GPIO speed to lowest
	GPIO_Init(LED_GPIO, &Gp); //Assign struct to LED_GPIO

	Gp.GPIO_Pin = PushButton_Pin; //Set pins inside the struct
	Gp.GPIO_Mode = GPIO_Mode_IN; //Set GPIO pins as output
	Gp.GPIO_PuPd = GPIO_PuPd_NOPULL; //No pullup required as pullup is external
	GPIO_Init(PushButton_GPIO, &Gp); //Assign struct to LED_GPIO

	uint8_t ButtonRead = 0; //Initialize ButtonRead variable

	while(1) //Infiinte loop!
	{
		//Read button input
		ButtonRead = GPIO_ReadInputDataBit(PushButton_GPIO, PushButton_Pin);

		if(ButtonRead){ //If button is pressed, turn green LED on and blue off
			GPIO_SetBits(LED_GPIO, GreenLED_Pin);
			GPIO_ResetBits(LED_GPIO, BlueLED_Pin);
		}
		else{ //If button isn't pressed, turn green LED off and blue on
			GPIO_ResetBits(LED_GPIO, GreenLED_Pin);
			GPIO_SetBits(LED_GPIO, BlueLED_Pin);
		}
	}
}
