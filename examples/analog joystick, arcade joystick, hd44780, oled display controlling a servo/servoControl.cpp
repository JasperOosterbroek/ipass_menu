// ==========================================================================
//
// File      : servoControl.cpp
// Part of   : C++ light menu, easy to use menu library
// Author    : Jasper Oosterbroek
// Github    : https://github.com/JasperOosterbroek/light-menu
// Copyright : jasper.oosterbroek@student.hu.nl 2018
//
//
//Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
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