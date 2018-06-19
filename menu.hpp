#ifndef MENU_HPP
#define MENU_HPP
#include <array>
#include "menuItem.hpp"
// t = menuItemsize
template<int t> class menu
{
private:
	std::array<menuItem, t> menuItemArray;
	menu<t> *parentMenu;
	int cursorPos = 0;
	int size;
public:

	menu<t>(const std::array<menuItem, t> & menuItems):
		menuItemArray( menuItems)
		
	{
		size = menuItems.size();
		}
	
	menu<t>(const std::array<menuItem, t> & menuItems, const menu<t> & parentMenu):
		parentMenu( parentMenu ),
		menuItemArray( menuItems )
		{
			size = menuItems.size();
		}
		
	menuItem& getMenuItemByIndex(int index){
		return menuItemArray[index];
	}
};

#endif // MENU_HPP
