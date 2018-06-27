// ==========================================================================
//
// File      : arcadeJoystickController.hpp
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
#ifndef ARCADEJOYSTICKCONTROLLER_HPP
#define ARCADEJOYSTICKCONTROLLER_HPP
#include "hwlib.hpp"
#include "lightMenu.hpp"

template<int t, int u>
class arcadeJoystickController : public lightMenu::controlMenu<t, u>
{
	hwlib::target::pin_in pinUp;
	hwlib::target::pin_in pinDown;
	hwlib::target::pin_in pinLeft;
	hwlib::target::pin_in pinRight;

public:
	arcadeJoystickController(lightMenu::baseMenu<t, u> & baseMenu, hwlib::target::pin_in & pinUp, hwlib::target::pin_in & pinDown, hwlib::target::pin_in & pinLeft, hwlib::target::pin_in & pinRight):
		lightMenu::controlMenu<t, u> (baseMenu),
		pinUp( pinUp ),
		pinDown( pinDown ),
		pinLeft( pinLeft ),
		pinRight( pinRight )
	{};
	bool read(){
		if(pinUp.get() == 0){
			lightMenu::controlMenu<t, u>::cursorUp();
			return true;
		}else if(pinDown.get() == 0){
			lightMenu::controlMenu<t, u>::cursorDown();
			return true;
		}else if(pinLeft.get() == 0){
			lightMenu::controlMenu<t,u>::previousMenu();
			return true;
		}else if(pinRight.get() == 0){
			lightMenu::controlMenu<t, u>::select();
			return true;
		}else{
			return false;
		}
	}
};

#endif // ARCADEJOYSTICKCONTROLLER_HPP
