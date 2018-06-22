#include "hwlib.hpp"

#include <array>
#include <functional>
#include "menu.hpp"
#include "menuItem.hpp"
#include "baseMenu.hpp"
#include "hd44780Menu.hpp"
#include "joystickMenuController.hpp"


class testclass : public menuItem{
private:
	
public:

	testclass(hwlib::string<0> & name):
	menuItem(name)
	{}
	
	void run(){
		hwlib::cout << "werkt het?";
	}
};

class testclass2 : public menuItem{
private:
	hwlib::hd44780 & display;
public:

	testclass2(hwlib::string<0> & name, hwlib::hd44780 & display):
	menuItem(name),
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
	menuNameTest1.clear() << "spullen";  //6

	hwlib::string<30> menuNameTest2;
	menuNameTest2.clear() << "aardappels"; //10

	hwlib::string<30> menuNameTest3;
	menuNameTest3.clear() << "bananensap"; //10

	hwlib::string<30> menuNameTest4;
	menuNameTest4.clear() << "frituurpan"; //10
	
	hwlib::string<30> menuNameTest5;
	menuNameTest4.clear() << "appelsientje"; //10
	
	hwlib::string<30> menuNameTest6;
	menuNameTest4.clear() << "krakatoa"; //10
//	construct menuitem

	testclass testMenuItem1(menuNameTest1);
	testclass2 testMenuItem2(menuNameTest2, display);
	testclass testMenuItem3(menuNameTest3);
	testclass testMenuItem4(menuNameTest4);
	
	testclass testMenuItem5(menuNameTest5);
	testclass testMenuItem6(menuNameTest6);

	std::array<menuItem*, maxMenuItemsPerMenu> menuItemArrayTest = {&testMenuItem1, &testMenuItem2, &testMenuItem3, &testMenuItem4};
	
	std::array<menuItem*, maxMenuItemsPerMenu> menuItemArrayTest2 = {&testMenuItem4, &testMenuItem3, &testMenuItem2, &testMenuItem1};

	menu<maxMenuItemsPerMenu> testmenu(menuItemArrayTest);
	menu<maxMenuItemsPerMenu> testmenu2(menuItemArrayTest2, &testmenu);
	
	std::array<menu<maxMenuItemsPerMenu>*, maxMenus>menuArrayTest = {&testmenu, &testmenu2};
	
	baseMenu<maxMenus, maxMenuItemsPerMenu> baseMenuTest(menuArrayTest);
	
	auto hd44780 = hd44780Menu<2, maxMenuItemsPerMenu>(baseMenuTest, display, lines, columns);
	
	auto click = hwlib::target::pin_in(hwlib::target::pins::d10);
	auto xaxis = hwlib::target::pin_adc(hwlib::target::ad_pins::a1);
	auto yaxis = hwlib::target::pin_adc(hwlib::target::ad_pins::a0);
	auto joystickcontroller = joystickMenuController<2, maxMenuItemsPerMenu>(baseMenuTest, click, xaxis, yaxis);
	
	hd44780.draw();
	hwlib::wait_ms(1000);
	joystickcontroller.flush();
	
	
//	testmenu.getMenuItemByIndex(0)->setFunction();
//	testmenu.getMenuItemByIndex(1)->setFunction();
//	testmenu.getMenuItemByIndex(2).setFunction();
//	testmenu.getMenuItemByIndex(3).setFunction();

	for(;;){
		if(joystickcontroller.read()){
			hd44780.draw();
			hwlib::wait_ms(250);
		}
	}
}
