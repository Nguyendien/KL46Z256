#include "MKL46Z4.h"                    // Device header

#include "led.h"
int main(void){
	InitLED();
	init_SysTick_interrupt();
	while(1){
		BlinkLED1();
	//	SysTick_Handle();
	//	Delay();
		}
}
		