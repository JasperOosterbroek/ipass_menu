// ==========================================================================
//
// File      : hd44780Menu.hpp
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
#ifndef HD44780MENU_HPP
#define HD44780MENU_HPP
#include "hwlib.hpp"
#include "lightMenu.hpp"

template <int t, int u>
class hd44780Menu : public lightMenu::displayMenu<t, u>
{
private:
	hwlib::hd44780 & display;
	int lines;
	int columns;
public:
	hd44780Menu<t, u>(lightMenu::baseMenu<t, u> & baseMenu, hwlib::hd44780 & display, uint_fast8_t lines, uint_fast8_t columns):
		lightMenu::displayMenu<t, u>(baseMenu),
		display(display),
		lines( lines ),
		columns( columns )
	{}
	
	void draw() override{
		display.clear();
		display << '\r';
		for(unsigned int i = lightMenu::displayMenu<t,u>::baseMenuRef.getCurrentCursorPos(); i < lines + lightMenu::displayMenu<t,u>::baseMenuRef.getCurrentCursorPos(); i++){
			
			if( i == lightMenu::displayMenu<t,u>::baseMenuRef.getCurrentCursorPos()){
				display << char(62);
			}else{
				display << " ";
			}
			if(i < lightMenu::displayMenu<t,u>::baseMenuRef.getCurrentMenuSize()){
				display << lightMenu::displayMenu<t,u>::baseMenuRef.getCurrentMenu()->getMenuItemByIndex(i)->getName();
			}
			display << '\n';
		}
	}
	
	void clear() override{
		display.clear();
	}
};

#endif // HD44780MENU_HPP
