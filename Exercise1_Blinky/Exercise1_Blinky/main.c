#include "LED.h"                    // Device header
void Delay(void);
int main(void){
    InitLED(); //Initialize LED for use
    while(1){//Main loop
        BlinkLED1(); //I prefer the third method.  All the command does is toggle the LED, which is exactly what we want to do.  All of the above methods will work.
	//	Delay();
		} //End main loop
} //End main