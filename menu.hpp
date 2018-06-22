#ifndef MENU_HPP
#define MENU_HPP
#include <array>
#include "menuItem.hpp"
// t = menuItemsize
template<int t> class menu
{
private:
	std::array<menuItem*, t> menuItemArray;
	unsigned int parenMenuPosition = 0;
	unsigned int baseMenuPosition = 0;
public:

	menu<t>(const std::array<menuItem*, t> & menuItems):
		menuItemArray( menuItems)
		
	{}
	
	menu<t>(const std::array<menuItem*, t> & menuItems, menu<t> *parentMenu):
		menuItemArray( menuItems )
		{
		baseMenuPosition = parentMenu->getBaseMenuPosition();
		hwlib::cout << baseMenuPosition;
		}
		
	menuItem* getMenuItemByIndex(int index){
		return menuItemArray[index];
	}
	
	unsigned int getParentMenuPosition(){
		return parenMenuPosition;
	}
	
	void setBaseMenuPosition(unsigned int i){
		baseMenuPosition = i;
	}
	
	unsigned int getBaseMenuPosition(){
		hwlib::cout << baseMenuPosition;
		return baseMenuPosition;
	}
};

#endif // MENU_HPP
