#include "MKL46Z4.h"                    // Device header

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
    for(i=0; i < 5000000; i++){}; //Burn some time
    PTD->PCOR = (1u<<5); //Clear PTD5 = 0, turns LED ON
    for(i=0; i < 5000000; i++){}; //Burn some time
}
	void BlinkLED2(void)
{
	//This method turns the LED off, then back on using PDOR
  //Note the use of |= and &=.  This allows you to change the 5th bit of PDOR without disturbing the other bits.  The other methods do not require this as setting PSOR/PCOR/PTOR = 0 does not change the output.
    uint32_t i = 0; //Create a loop variable
     
    PTD->PDOR |= (1u<<5); //Change PTD5 to 1, turns LED OFF (Cathode connected to PTD5)
    for(i=0; i < 3000000; i++){}; //Burn some time
    PTD->PDOR &= ~((uint32_t)(1u<<5)); //Change PTD5 to 0, turns LED ON.  This line is a bit weird.  First it takes 1u<<5 and typecasts ( http://en.wikipedia.org/wiki/Type_conversion ) it to a 32 bit value.  It then takes the inverse of it, so all bits are 1 except bit 5.  It then logical ands it with the current PDOR, which will retain all values except bit 5 which will be changed to 0.
    for(i=0; i < 3000000; i++){}; //Burn some time
}
void BlinkLED3(void)
{
//This method turns the LED off, then back on using a single command.  It must be run twice in order to blink the LED.
    uint32_t i = 0; //Create a loop variable
     
    PTD->PTOR = (1u<<5); //Toggles PTD5 and the LED
    for(i=0; i < 3000000; i++){}; //Burn some time
}