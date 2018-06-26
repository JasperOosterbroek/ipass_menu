// ==========================================================================
//
// File      : main.cpp
// Part of   : C++ light menu, easy to use menu library
// Author    : Jasper Oosterbroek
// Github    : https://github.com/JasperOosterbroek/light-menu
// Copyright : jasper.oosterbroek@student.hu.nl 2018
//
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "hwlib.hpp"
#include "lightMenu.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
//temp class to test menuItem
class tempTestMenuItem : public lightMenu::menuItem{
public:
	tempTestMenuItem(hwlib::string<0> name):
	lightMenu::menuItem(name)
	{}
	
	void run(){
		
	}
};


 /***********************
 *  baseMenu Testcases  *
 ***********************/
//baseMenu getMenuByIndex
TEST_CASE("baseMenu getMenuByIndex"){
	const int maxMenus = 1;
	const int maxMenuItemsPerMenu = 1;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	std::array<lightMenu::menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&testmenu};
	lightMenu::baseMenu<maxMenus, maxMenuItemsPerMenu> baseMenuTest(menuArrayTest);
	REQUIRE(&testmenu == baseMenuTest.getMenuByIndex(0));
}
//baseMenu getCurrentMenu
TEST_CASE("baseMenu getCurrentMenu"){
	const int maxMenus = 1;
	const int maxMenuItemsPerMenu = 1;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	std::array<lightMenu::menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&testmenu};
	lightMenu::baseMenu<maxMenus, maxMenuItemsPerMenu> baseMenuTest(menuArrayTest);
	REQUIRE(&testmenu == baseMenuTest.getCurrentMenu());
}
//baseMenu getCurrentCursorPos
TEST_CASE("baseMenu getCurrentCursorPos"){
	const int maxMenus = 1;
	const int maxMenuItemsPerMenu = 1;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	std::array<lightMenu::menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&testmenu};
	lightMenu::baseMenu<maxMenus, maxMenuItemsPerMenu> baseMenuTest(menuArrayTest);
	REQUIRE(baseMenuTest.getCurrentCursorPos() == 0);
}
//baseMenu setCursorPos
TEST_CASE("baseMenu setCursorPos"){
	const int maxMenus = 1;
	const int maxMenuItemsPerMenu = 1;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	std::array<lightMenu::menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&testmenu};
	lightMenu::baseMenu<maxMenus, maxMenuItemsPerMenu> baseMenuTest(menuArrayTest);
	hwlib::string<20> testString = "Test string";
	auto testMenuItem = tempTestMenuItem(testString);
	testmenu.addMenuItem(&testMenuItem);
	baseMenuTest.setCursorPos(1);
	REQUIRE(baseMenuTest.getCurrentCursorPos() == 1);
}
//baseMenu getCurrentMenuSize
TEST_CASE("baseMenu getCurrentMenuSize"){
	const int maxMenus = 1;
	const int maxMenuItemsPerMenu = 1;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	std::array<lightMenu::menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&testmenu};
	lightMenu::baseMenu<maxMenus, maxMenuItemsPerMenu> baseMenuTest(menuArrayTest);
	hwlib::string<20> testString = "Test string";
	auto testMenuItem = tempTestMenuItem(testString);
	testmenu.addMenuItem(&testMenuItem);
	REQUIRE(baseMenuTest.getCurrentMenuSize() == 1);
}
//baseMenu cursorUp
TEST_CASE("baseMenu cursorUp"){
	const int maxMenus = 1;
	const int maxMenuItemsPerMenu = 2;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	std::array<lightMenu::menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&testmenu};
	lightMenu::baseMenu<maxMenus, maxMenuItemsPerMenu> baseMenuTest(menuArrayTest);
	baseMenuTest.setCursorPos(1);
	baseMenuTest.cursorUp();
	REQUIRE(baseMenuTest.getCurrentCursorPos() == 0);
}
//baseMenu cursorDown
TEST_CASE("baseMenu cursorDown"){
	const int maxMenus = 1;
	const int maxMenuItemsPerMenu = 2;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	std::array<lightMenu::menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&testmenu};
	lightMenu::baseMenu<maxMenus, maxMenuItemsPerMenu> baseMenuTest(menuArrayTest);
	baseMenuTest.cursorDown();
	REQUIRE(baseMenuTest.getCurrentCursorPos() == 1);
}
//baseMenu setMenu using menu
TEST_CASE("baseMenu setMenu using menu"){
	const int maxMenus = 1;
	const int maxMenuItemsPerMenu = 1;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	std::array<lightMenu::menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&testmenu};
	lightMenu::baseMenu<maxMenus, maxMenuItemsPerMenu> baseMenuTest(menuArrayTest);
	baseMenuTest.setMenu(&testmenu);
	REQUIRE(&testmenu == baseMenuTest.getCurrentMenu());
}
//baseMenu setMenu using int
TEST_CASE("baseMenu setMenu using int"){
	const int maxMenus = 1;
	const int maxMenuItemsPerMenu = 1;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	std::array<lightMenu::menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&testmenu};
	lightMenu::baseMenu<maxMenus, maxMenuItemsPerMenu> baseMenuTest(menuArrayTest);
	baseMenuTest.setMenu(int(0));
	REQUIRE(&testmenu == baseMenuTest.getCurrentMenu());
}
//baseMenu previousMenu without cursorpos
TEST_CASE("baseMenu previousMenu without cursorpos"){
	const int maxMenus = 2;
	const int maxMenuItemsPerMenu = 1;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	lightMenu::menu<maxMenuItemsPerMenu> testmenuTwo(&testmenu);
	std::array<lightMenu::menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&testmenu, &testmenuTwo};
	lightMenu::baseMenu<maxMenus, maxMenuItemsPerMenu> baseMenuTest(menuArrayTest);
	baseMenuTest.setMenu(&testmenuTwo);
	baseMenuTest.previousMenu();
	REQUIRE(baseMenuTest.getCurrentMenu() == &testmenu);
}

//baseMenu previousMenu with cursorpos
TEST_CASE("baseMenu previousMenu with cursorpos"){
	const int maxMenus = 2;
	const int maxMenuItemsPerMenu = 1;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	lightMenu::menu<maxMenuItemsPerMenu> testmenuTwo(&testmenu);
	std::array<lightMenu::menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&testmenu, &testmenuTwo};
	lightMenu::baseMenu<maxMenus, maxMenuItemsPerMenu> baseMenuTest(menuArrayTest);
	baseMenuTest.setMenu(&testmenuTwo);
	baseMenuTest.previousMenu(0);
	REQUIRE(baseMenuTest.getCurrentMenu() == &testmenu);
}
//baseMenu addMenu
TEST_CASE("baseMenu addMenu"){
	const int maxMenus = 2;
	const int maxMenuItemsPerMenu = 1;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	lightMenu::menu<maxMenuItemsPerMenu> testmenuTwo(&testmenu);
	std::array<lightMenu::menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&testmenu};
	lightMenu::baseMenu<maxMenus, maxMenuItemsPerMenu> baseMenuTest(menuArrayTest);
	baseMenuTest.addMenu(&testmenuTwo);
	baseMenuTest.setMenu(&testmenuTwo);
	REQUIRE(baseMenuTest.getCurrentMenu() == &testmenuTwo);
}

 /*******************
 *  menu Testcases  *
 *******************/
 
 //menu getMenuItemByIndex
 TEST_CASE("menu getMenuItemByIndex"){
	const int maxMenuItemsPerMenu = 1;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	hwlib::string<20> testString = "Test string";
	auto testMenuItem = tempTestMenuItem(testString);
	testmenu.addMenuItem(&testMenuItem);
	REQUIRE(testmenu.getMenuItemByIndex(0) == &testMenuItem);
 }
 //menu getParentMenuPosition
 TEST_CASE("menu getParentMenuPosition"){
	const int maxMenuItemsPerMenu = 1;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	testmenu.setBaseMenuPosition(22);
	lightMenu::menu<maxMenuItemsPerMenu> testmenuTwo(&testmenu);
	REQUIRE(testmenuTwo.getParentMenuPosition() == 22);
 }
 //menu setBaseMenuPosition
 TEST_CASE("menu setBaseMenuPosition"){
	const int maxMenuItemsPerMenu = 1;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	testmenu.setBaseMenuPosition(1); 
	REQUIRE(testmenu.getBaseMenuPosition() == 1);
 }
 //menu getBaseMenuPosition
 TEST_CASE("menu getBaseMenuPosition"){
	const int maxMenuItemsPerMenu = 1;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	REQUIRE(testmenu.getBaseMenuPosition() == 0);
 }
 //menu getMenuItemArraySize
 TEST_CASE("menu getMenuItemArraySize"){
	const int maxMenuItemsPerMenu = 1;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	hwlib::string<20> testString = "Test string";
	auto testMenuItem = tempTestMenuItem(testString);
	testmenu.addMenuItem(&testMenuItem);
	REQUIRE(testmenu.getMenuItemArraySize() == 1);
 }
 //menu addMenuItem
 TEST_CASE("menu addMenuItem"){
	const int maxMenuItemsPerMenu = 1;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	hwlib::string<20> testString = "Test string";
	auto testMenuItem = tempTestMenuItem(testString);
	testmenu.addMenuItem(&testMenuItem);
	REQUIRE(testmenu.getMenuItemByIndex(0) == &testMenuItem);
 }
 /******************
 *  menu menuItem  *
 ******************/
 
 //menuItem getName
 TEST_CASE("menuItem getName"){
	hwlib::string<20> testString = "Test string";
	auto testMenuItem = tempTestMenuItem(testString);
	REQUIRE(testMenuItem.getName() == testString);
 }
 //menuItem setMenu
 TEST_CASE("menuItem setMenu"){
	hwlib::string<20> testString = "Test string";
	hwlib::string<20> changedTestString = "Changed test string";
	auto testMenuItem = tempTestMenuItem(testString);
	testMenuItem.setName(changedTestString);
	REQUIRE(testMenuItem.getName() == changedTestString);
 }
 
 /********************
 *  menu controller  *
 ********************/
 
 //menu controller previousMenu
 TEST_CASE("menuController previousMenu without cursorpos"){
	const int maxMenus = 2;
	const int maxMenuItemsPerMenu = 1;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	lightMenu::menu<maxMenuItemsPerMenu> testmenuTwo(&testmenu);
	std::array<lightMenu::menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&testmenu, &testmenuTwo};
	lightMenu::baseMenu<maxMenus, maxMenuItemsPerMenu> baseMenuTest(menuArrayTest);
	lightMenu::controlMenu<maxMenus, maxMenuItemsPerMenu> menuController(baseMenuTest);
	baseMenuTest.setMenu(&testmenuTwo);
	menuController.previousMenu();
	REQUIRE(baseMenuTest.getCurrentMenu() == &testmenu);
}

//baseMenu previousMenu with cursorpos
TEST_CASE("menuController previousMenu with cursorpos"){
	const int maxMenus = 2;
	const int maxMenuItemsPerMenu = 1;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	lightMenu::menu<maxMenuItemsPerMenu> testmenuTwo(&testmenu);
	std::array<lightMenu::menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&testmenu, &testmenuTwo};
	lightMenu::baseMenu<maxMenus, maxMenuItemsPerMenu> baseMenuTest(menuArrayTest);
	lightMenu::controlMenu<maxMenus, maxMenuItemsPerMenu> menuController(baseMenuTest);
	baseMenuTest.setMenu(&testmenuTwo);
	menuController.previousMenu(0);
	REQUIRE(baseMenuTest.getCurrentMenu() == &testmenu);
}
 //menu controller cursorDown
 TEST_CASE("menuController cursorDown"){
	const int maxMenus = 1;
	const int maxMenuItemsPerMenu = 2;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	std::array<lightMenu::menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&testmenu};
	lightMenu::baseMenu<maxMenus, maxMenuItemsPerMenu> baseMenuTest(menuArrayTest);
	lightMenu::controlMenu<maxMenus, maxMenuItemsPerMenu> menuController(baseMenuTest);
	menuController.cursorDown();
	REQUIRE(baseMenuTest.getCurrentCursorPos() == 1);
}
 //menu controller cursorUp
 TEST_CASE("menuController cursorUp"){
	const int maxMenus = 1;
	const int maxMenuItemsPerMenu = 2;
	lightMenu::menu<maxMenuItemsPerMenu> testmenu;
	std::array<lightMenu::menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&testmenu};
	lightMenu::baseMenu<maxMenus, maxMenuItemsPerMenu> baseMenuTest(menuArrayTest);
	lightMenu::controlMenu<maxMenus, maxMenuItemsPerMenu> menuController(baseMenuTest);
	baseMenuTest.setCursorPos(1);
	menuController.cursorUp();
	REQUIRE(baseMenuTest.getCurrentCursorPos() == 0);
}