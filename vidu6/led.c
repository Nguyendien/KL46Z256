
#include "MKL46Z4.h"
#include "led.h"
void InitLED(void)
	{ 
//This function enables the red LED on the FRDM-KL46Z development board
//Note, each chapter from the Reference Manual is a structure, while each register is a member of that structure, so we address them by Chapter -> Register
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; //This enables the clock to PORTD
    PORTD->PCR[5] = PORT_PCR_MUX(1u); //This sets the Mux control of PTD5 to 001, or GPIO
    PTD->PDDR |= (1u<<5); //This sets PTD5 as an output.  There are no masks defined for each pin so we have to do it by hand and just comment well.
}
  
void BlinkLED1(void)
	{
		//This method turns the LED off, then back on using two separate commands.
    uint32_t i = 0; //Create a loop variable
     
    PTD->PSOR = (1u<<5); //Set PTD5 = 1, turns LED OFF (Cathode connected to PTD5)
    //for(i=0; i < 5000000; i++){}; //Burn some time
    Delay(500);
		PTD->PCOR = (1u<<5); //Clear PTD5 = 0, turns LED ON
    //for(i=0; i < 5000000; i++){}; //Burn some time
		Delay(500);
	}
int32_t volatile msTicks = 0; 
void init_SysTick_interrupt()
	{ 
		SysTick ->LOAD = SystemCoreClock /1000;// systemcoreClock =48MHz ~ 1s/1000=1ms
		SysTick ->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk |SysTick_CTRL_ENABLE_Msk;
	}
	void SysTick_Handler(void){// dieu khien ngat
		msTicks++;
	}
void Delay (uint32_t TICK) {
		while (msTicks < TICK);// wait 500ms
		msTicks = 0;// reset counter
	}