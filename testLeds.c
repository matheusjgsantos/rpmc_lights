
#include <stdlib.h>
#include <stdio.h>
#include "PiGpio.h"

void main(void){
	gpioInit();
	gpioUpdateLeds();
	gpioShutdown();
}
