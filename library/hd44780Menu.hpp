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
