// ==========================================================================
//
// File      : servoControl.hpp
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

#ifndef SERVOCONTROL_HPP
#define SERVOCONTROL_HPP
#include "lightMenu.hpp"
#include "hwlib.hpp"

class servoControl : public lightMenu::menuItem{
private:
	hwlib::target::pin_out & pwmPin;
	int servoPos;
public:
	servoControl(hwlib::string<0> name, int servoPos, hwlib::target::pin_out & pwmPin):
	lightMenu::menuItem(name),
	pwmPin(pwmPin),
	servoPos(servoPos)
	{}
	
	void run();
	void goToPos(int pos);
	
};
#endif // SERVOCONTROL_HPP
