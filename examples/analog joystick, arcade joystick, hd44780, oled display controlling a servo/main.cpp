// ==========================================================================
//
// File      : main.cpp
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
#include "hwlib.hpp"

#include <array>
#include "lightMenu.hpp"
#include "hd44780Menu.hpp"
#include "oledmenu.hpp"
#include "joystickMenuController.hpp"
#include "arcadeJoystickController.hpp"
#include "servoControl.hpp"

int main(int argc, char **argv)
{
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;	

	//	 testing screen 20x4
	auto d1rs = hwlib::target::pin_out(hwlib::target::pins::d12);
	auto d1e = hwlib::target::pin_out(hwlib::target::pins::d11);
	auto d1dpin4 = hwlib::target::pin_out(hwlib::target::pins::d5);
	auto d1dpin5 = hwlib::target::pin_out(hwlib::target::pins::d4);
	auto d1dpin6 = hwlib::target::pin_out(hwlib::target::pins::d3); 
	auto d1dpin7 = hwlib::target::pin_out(hwlib::target::pins::d2);

	auto d1dataPins = hwlib::port_out_from_pins(d1dpin4, d1dpin5, d1dpin6, d1dpin7);
	auto display20x4 = hwlib::hd44780(d1rs, d1e, d1dataPins, 4, 20);
	// testing screen 16x2
	auto d2rs = hwlib::target::pin_out(hwlib::target::pins::d31);
	auto d2e = hwlib::target::pin_out(hwlib::target::pins::d33);  
	auto d2dpin4 = hwlib::target::pin_out(hwlib::target::pins::d53);
	auto d2dpin5 = hwlib::target::pin_out(hwlib::target::pins::d51);
	auto d2dpin6 = hwlib::target::pin_out(hwlib::target::pins::d49);
	auto d2dpin7 = hwlib::target::pin_out(hwlib::target::pins::d47);

	auto d2dataPins = hwlib::port_out_from_pins(d2dpin4, d2dpin5, d2dpin6, d2dpin7);
	auto display16x2 = hwlib::hd44780(d2rs, d2e, d2dataPins, 4, 20);
	//testing screen oled
	auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
	auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
   
	auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
   
	auto displayOled = hwlib::glcd_oled( i2c_bus, 0x3c );  
	// servo pin
	auto servoPin = hwlib::target::pin_out(hwlib::target::pins::d45);
	hwlib::wait_ms(500);

	const int maxMenuItemsPerMenu = 5;
	const int maxMenus = 3;
//	menuitem name

	hwlib::string<20> servoControlMenuString;
	servoControlMenuString.clear() << "Servo control"; 

	hwlib::string<30> servoPos0;
	servoPos0.clear() << "Set servo 0%";

	hwlib::string<30> servoPos25;
	servoPos25.clear() << "Set servo 25%"; 

	hwlib::string<30> servoPos50;
	servoPos50.clear() << "Set servo 50%";
	
	hwlib::string<30> servoPos75;
	servoPos75.clear() << "Set servo 75%";
	
	hwlib::string<30> servoPos100;
	servoPos100.clear() << "Set servo 100%";
	
	
	servoControl servoPos0MenuItem(servoPos0, 0, servoPin);
	servoControl servoPos25MenuItem(servoPos25, 25, servoPin);
	servoControl servoPos50MenuItem(servoPos50, 50, servoPin);
	servoControl servoPos75MenuItem(servoPos75, 75, servoPin);
	servoControl servoPos100MenuItem(servoPos100, 100, servoPin);
	
	std::array<lightMenu::menuItem*, maxMenuItemsPerMenu> mainMenuArray = {};
	
	std::array<lightMenu::menuItem*, maxMenuItemsPerMenu> servoControlMenuArray = {&servoPos0MenuItem, &servoPos25MenuItem, &servoPos50MenuItem, &servoPos75MenuItem, &servoPos100MenuItem};

	lightMenu::menu<maxMenuItemsPerMenu> mainMenu(mainMenuArray);
	lightMenu::menu<maxMenuItemsPerMenu> servoControlMenu(servoControlMenuArray, &mainMenu);
	
	std::array<lightMenu::menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&mainMenu, &servoControlMenu};
	lightMenu::baseMenu<maxMenus, maxMenuItemsPerMenu> demoBaseMenu(menuArrayTest);
	auto hd4478020x4 = hd44780Menu<maxMenus, maxMenuItemsPerMenu>(demoBaseMenu, display20x4, 4, 20);
	auto hd4478016x2 = hd44780Menu<maxMenus, maxMenuItemsPerMenu>(demoBaseMenu, display16x2, 2, 16);
	auto oled = oledMenu<maxMenus, maxMenuItemsPerMenu>(demoBaseMenu, displayOled, 5);
	
	auto click = hwlib::target::pin_in(hwlib::target::pins::d10);
	auto xaxis = hwlib::target::pin_adc(hwlib::target::ad_pins::a1);
	auto yaxis = hwlib::target::pin_adc(hwlib::target::ad_pins::a0);
	auto joystickcontroller = joystickMenuController<maxMenus, maxMenuItemsPerMenu>(demoBaseMenu, click, xaxis, yaxis);

	auto arcJoyPinUp = hwlib::target::pin_in(hwlib::target::pins::d35);
	auto arcJoyPinDown = hwlib::target::pin_in(hwlib::target::pins::d37);
	auto arcJoyPinLeft = hwlib::target::pin_in(hwlib::target::pins::d39);
	auto arcJoyPinRight = hwlib::target::pin_in(hwlib::target::pins::d41);
	auto arcJoy = arcadeJoystickController<maxMenus, maxMenuItemsPerMenu>(demoBaseMenu, arcJoyPinUp, arcJoyPinDown, arcJoyPinLeft, arcJoyPinRight);
	
	lightMenu::menuItemMenuLink<maxMenus,maxMenuItemsPerMenu> servoControlMenuItem(servoControlMenuString, servoControlMenu, demoBaseMenu);
	mainMenu.addMenuItem(&servoControlMenuItem);
	
	joystickcontroller.flush();
	hd4478020x4.draw();
	hd4478016x2.draw();
	oled.draw();
	for(;;){
		if(joystickcontroller.read() || arcJoy.read()){
			hd4478020x4.draw();
			hd4478016x2.draw();
			oled.draw();
			hwlib::wait_ms(50);
		}

	}
}
