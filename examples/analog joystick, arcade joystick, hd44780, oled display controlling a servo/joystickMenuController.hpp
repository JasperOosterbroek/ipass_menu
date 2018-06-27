// ==========================================================================
//
// File      : joystickMenuController.hpp
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
#ifndef JOYSTICKMENUCONTROLLER_HPP
#define JOYSTICKMENUCONTROLLER_HPP
#include "hwlib.hpp"
#include "lightMenu.hpp"

template<int t, int u>
class joystickMenuController : public lightMenu::controlMenu<t, u>
{
private:
	hwlib::target::pin_in selectPin;
	hwlib::target::pin_adc xAxisPin;
	hwlib::target::pin_adc yAxisPin;

public:
	joystickMenuController(lightMenu::baseMenu<t, u> & baseMenu, hwlib::target::pin_in & selectPin, hwlib::target::pin_adc xAxisPin, hwlib::target::pin_adc yAxisPin):
	lightMenu::controlMenu<t, u> (baseMenu),
	selectPin( selectPin ),
	xAxisPin( xAxisPin ),
	yAxisPin( yAxisPin)
	{}
	// "read joystick input"
	void flush(){
		xAxisPin.get();
		yAxisPin.get();
	}
	bool read(){
		if(selectPin.get() == 0){
			lightMenu::controlMenu<t, u>::select();
			return true;
		}
		int tempXAxis = xAxisPin.get();
		int tempYAxis = yAxisPin.get();
		// checkcenter
		if(!((tempXAxis < 2800 && tempXAxis > 3200) && (tempYAxis < 2800 && tempYAxis > 3200)) ){
			//check left && right
			if(tempXAxis > 3500){
				lightMenu::controlMenu<t,u>::previousMenu();
				return true;
			}else if(tempXAxis < 500){
				lightMenu::controlMenu<t, u>::select();
				return true;
			}
			//check up && down
			else if(tempYAxis > 3500){
				lightMenu::controlMenu<t,u>::cursorUp();
				return true;
			}else if(tempYAxis < 500){
				lightMenu::controlMenu<t,u>::cursorDown();
				return true;
			}else{
				return false;
			}
			return false;
		}
		return false;
	}
	
};

#endif // JOYSTICKMENUCONTROLLER_HPP
