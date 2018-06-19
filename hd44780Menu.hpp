#ifndef HD44780MENU_HPP
#define HD44780MENU_HPP
#include "hwlib.hpp"
#include "DisplayMenu.hpp"

template <int t, int u>
class hd44780Menu : public DisplayMenu<t, u>
{
private:
	hwlib::hd44780 & display;
	int lines;
	int columns;
public:
	hd44780Menu<t, u>(baseMenu<t, u> & baseMenu, hwlib::hd44780 & display, uint_fast8_t lines, uint_fast8_t columns):
		DisplayMenu<t, u>(baseMenu),
		display(display),
		lines( lines ),
		columns( columns )
	{}
	void draw() override{
		display.clear();
//		hwlib::cout << "draw " << DisplayMenu<t,u>::baseMenuRef.getCurrentCursorPos() << '\n';
//		hwlib::wait_ms(50);
		display << '\r';
		for(unsigned int i = DisplayMenu<t,u>::baseMenuRef.getCurrentCursorPos(); i < lines + DisplayMenu<t,u>::baseMenuRef.getCurrentCursorPos(); i++){
//			hwlib::cout << "i - " << i << '\n';
			if( i == DisplayMenu<t,u>::baseMenuRef.getCurrentCursorPos()){
				display << char(62);
			}else{
				display << " ";
			}
			if(i <= DisplayMenu<t,u>::baseMenuRef.getMaxHeight()){
				display << DisplayMenu<t,u>::baseMenuRef.getCurrentMenu().getMenuItemByIndex(i).getName();
			}
			display << '\n';
		}
//		hwlib::wait_ms(5000);
	}
	
	void clear() override{
		display.clear();
	}
};

#endif // HD44780MENU_HPP
