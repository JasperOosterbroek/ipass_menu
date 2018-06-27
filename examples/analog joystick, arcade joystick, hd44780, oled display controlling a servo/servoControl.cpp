#include "servoControl.hpp"

void servoControl::run(){
	goToPos(servoPos);
}
	
void servoControl::goToPos(int pos){

	if(pos > 120 || pos < 0){
		return;
	}
	int pulseWidth = ((pos*2170)/180);
		for(int i = 0; i<20; i++){
			pwmPin.set(1);
			hwlib::wait_us(pulseWidth);
			pwmPin.set(0);
			hwlib::wait_ms(20);
		}

}