#include "MKL46Z4.h"                    // Device header
#include <stdbool.h>
#define BUSCLOCK_HZ (13.98 * 1000000)
#define BUSCLOCK_PERIOD_SEC ( 1/ BUSCLOCK_HZ)
#define EXPECT_TIMER1_MS (1000)
#define GREEN_LED_PIN (1<<5)
#define RED_LED_PIN (1 << 29)

void InitLED(void)
	{ 
//This function enables the red LED on the FRDM-KL46Z development board
//Note, each chapter from the Reference Manual is a structure, while each register is a member of that structure, so we address them by Chapter -> Register
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; //This enables the clock to PORTD
   PORTD->PCR[5] = PORT_PCR_MUX(1u); //This sets the Mux control of PTD5 to 001, or GPIO
  PTD->PDDR |= (1u<<5); //This sets PTD5 as an output.  There are no masks defined for each pin so we have to do it by hand and just comment well.
		SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
		PORTE ->PCR[29] = PORT_PCR_MUX(1u);
		PTE ->PDDR |= (1u<<29);
	}
void LED1(void)
{
	//This method turns the LED off, then back on using two separate commands.
    uint32_t i = 0; //Create a loop variable
     
    PTD->PSOR = (1u<<5); //Set PTD5 = 1, turns LED OFF (Cathode connected to PTD5)
	
  for(i=0; i < 1100000; i++){}; //Burn some time
    PTD->PCOR = (1u<<5); //Clear PTD5 = 0, turns LED ON
    for(i=0; i < 1100000; i++){}; //Burn some time
}
void LED2(void)
{
	 uint32_t i = 0;
		PTE->PSOR = (1u<<29); 
    for(i=0; i < 5000000; i++){};
		PTE->PCOR = (1u<<29); 
    for(i=0; i < 5000000; i++){};	
			
}
void PIT_enable(uint32_t ldval)
{
		SIM -> SCGC6 |= SIM_SCGC6_PIT_MASK;//enable PIT clock gate
		PIT -> MCR = ~PIT_MCR_MDIS_MASK; //PIT ->MCR = 0x00U;PIT_MCR: MDIS=0,FRZ=0 : Enable device clock// ~PIT_MCR_MDIS_MASK
		PIT -> 
		PIT ->CHANNEL[0].TCTRL = 0X00U;/* PIT_TCTRL0: CHN=0,TIE=0,TEN=0 : Clear control
register*/
		PIT ->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;/* PIT_TFLG0: TIF=1: Clear timer flag register */
		PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(ldval); /* PIT_LDVAL0: TSV=0xD1B6: Set up load register */
		NVIC_SetPriority(22, 2); /* Set priority for PIT IRQ22 */
		NVIC_EnableIRQ(22); /* Enable IRQ for PIT IRQ22 */
	/* PIT_TCTRL0: CHN=0,TIE=1,TEN=1 */
		PIT->CHANNEL[0].TCTRL = (PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK); /* Set up control register */
}
void PIT_IRQHandler()
{
PIT->CHANNEL[0].TFLG |= 1; // Clear timer interrupt flag
FPTE->PTOR |= GREEN_LED_PIN; //Control LEDs for debugging
PIT->CHANNEL[0].TFLG |= 1; 
FPTE->PTOR |= RED_LED_PIN;
}
