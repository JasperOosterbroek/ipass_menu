// ==========================================================================
//
// File      : main.hpp
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
#include <functional>
#include "lightMenu.hpp"
#include "hd44780Menu.hpp"
#include "joystickMenuController.hpp"

class testclass : public lightMenu::menuItem{
private:
	
public:

	testclass(hwlib::string<0> name):
	lightMenu::menuItem(name)
	{}
	
	void run(){
		hwlib::cout << "werkt het?";
	}
};
	
class testclass2 : public lightMenu::menuItem{
private:
	hwlib::hd44780 & display;
public:

	testclass2(hwlib::string<0> name, hwlib::hd44780 & display):
	lightMenu::menuItem(name),
	display( display )
	{}
	void test(){
		display << '\n';
		display << "dit werkt ook!";
	}
	void run(){
		hwlib::cout << "het werkt!";
		display.clear();
		display << '\r';
		display << "het werkt!";
		test();
		for(;;){
			
		}
	}
};

int main(int argc, char **argv)
{
	// kill the watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;	

	//	 testing screen
	auto rs = hwlib::target::pin_out(hwlib::target::pins::d12);
	auto e = hwlib::target::pin_out(hwlib::target::pins::d11);
	auto dpin4 = hwlib::target::pin_out(hwlib::target::pins::d5);
	auto dpin5 = hwlib::target::pin_out(hwlib::target::pins::d4);
	auto dpin6 = hwlib::target::pin_out(hwlib::target::pins::d3);
	auto dpin7 = hwlib::target::pin_out(hwlib::target::pins::d2);

	uint_fast8_t lines = 4;
	uint_fast8_t columns = 20;

	auto dataPins = hwlib::port_out_from_pins(dpin4, dpin5, dpin6, dpin7);

	auto display = hwlib::hd44780(rs, e, dataPins, lines, columns);
	hwlib::wait_ms(500);

	const int maxMenuItemsPerMenu = 4;
	const int maxMenus = 2;
//	menuitem name

	hwlib::string<20> menuNameTest1;
	menuNameTest1.clear() << "test 1";

	hwlib::string<30> menuNameTest2;
	menuNameTest2.clear() << "test 2";

	hwlib::string<30> menuNameTest3;
	menuNameTest3.clear() << "test 3";

	hwlib::string<30> menuNameTest4;
	menuNameTest4.clear() << "test 4";
	
	hwlib::string<30> menuNameTest5;
	menuNameTest4.clear() << "test 5";
	
	hwlib::string<30> menuNameTest6;
	menuNameTest4.clear() << "test 6";

	testclass testMenuItem1(menuNameTest1);
	testclass2 testMenuItem2(menuNameTest2, display);
	
	testclass testMenuItem4(menuNameTest4);
	
	testclass testMenuItem5(menuNameTest5);
	testclass testMenuItem6(menuNameTest6);

	std::array<lightMenu::menuItem*, maxMenuItemsPerMenu> menuItemArrayTest = {&testMenuItem1};
	
	std::array<lightMenu::menuItem*, maxMenuItemsPerMenu> menuItemArrayTest2 = {&testMenuItem4, &testMenuItem2};

	lightMenu::menu<maxMenuItemsPerMenu> testmenu(menuItemArrayTest);
	lightMenu::menu<maxMenuItemsPerMenu> testmenu2(menuItemArrayTest2, &testmenu);
	
	std::array<lightMenu::menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&testmenu};
	lightMenu::baseMenu<maxMenus, maxMenuItemsPerMenu> baseMenuTest(menuArrayTest);
	auto hd44780 = hd44780Menu<2, maxMenuItemsPerMenu>(baseMenuTest, display, lines, columns);
	
	auto click = hwlib::target::pin_in(hwlib::target::pins::d10);
	auto xaxis = hwlib::target::pin_adc(hwlib::target::ad_pins::a1);
	auto yaxis = hwlib::target::pin_adc(hwlib::target::ad_pins::a0);
	auto joystickcontroller = joystickMenuController<2, maxMenuItemsPerMenu>(baseMenuTest, click, xaxis, yaxis);

	lightMenu::menuItemMenuLink<maxMenus,maxMenuItemsPerMenu> testMenuItem3(menuNameTest3, testmenu2, baseMenuTest);

	testmenu.addMenuItem(&testMenuItem1);

	testmenu.addMenuItem(&testMenuItem3);
	baseMenuTest.addMenu(&testmenu2);
	baseMenuTest.addMenu(&testmenu2);

	hd44780.draw();
	hwlib::string<20> replacestring = "test"; 
	testMenuItem1.setName(replacestring);
	joystickcontroller.flush();
	hd44780.draw();
	for(;;){
		if(joystickcontroller.read()){
			hd44780.draw();
			hwlib::wait_ms(250);
		}
	}
}
