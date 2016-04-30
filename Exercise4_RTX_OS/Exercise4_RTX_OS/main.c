/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "LED.h" // Initialize and set GPIO Port 
/* 
* main: initialize and start the system */ 
int main (void) 
{ 
osKernelInitialize (); // Initialize CMSIS-RTOS 
// initialize peripherals here 
LED_Initialize (); // Initialize LEDs 
// create 'thread' functions that start executing, 
// example: tid_name = osThreadCreate (osThread(name), NULL); 
Init_BlinkyThread (); // Start Blinky thread 
osKernelStart (); // Start thread execution 
while (1); 
}

