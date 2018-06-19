#ifndef MENU_HPP
#define MENU_HPP
#include <array>
#include "menuItem.hpp"
// t = menuItemsize
template<int t> class menu
{
private:
	std::array<menuItem, t> menuItemArray;
	menu<t>* parentMenu;
	unsigned int baseMenuPosition = 0;
public:

	menu<t>(const std::array<menuItem, t> & menuItems):
		menuItemArray( menuItems)
		
	{}
	
	menu<t>(const std::array<menuItem, t> & menuItems, menu<t> *parentMenu):
		menuItemArray( menuItems ),
		parentMenu( parentMenu )
		{}
		
	menuItem& getMenuItemByIndex(int index){
		return menuItemArray[index];
	}
	
	menu<t>* getParentMenu(){
		return parentMenu;
	}
	
	void setBaseMenuPosition(unsigned int i){
		baseMenuPosition = i;
	}
	
	unsigned int getBaseMenuPosition(){
		return baseMenuPosition;
	}
};

#endif // MENU_HPP
