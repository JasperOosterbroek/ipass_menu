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
	
	menu<t>(){}

	menu<t>(const std::array<menuItem*, t> & menuItems):
		menuItemArray( menuItems)
	{}
	
	menu<t>(menu<t> *parentMenu){
		baseMenuPosition = parentMenu->getBaseMenuPosition();
	}
	
	menu<t>(const std::array<menuItem*, t> & menuItems, menu<t> *parentMenu):
		menuItemArray( menuItems )
		{
		baseMenuPosition = parentMenu->getBaseMenuPosition();
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
		return baseMenuPosition;
	}
	
	unsigned int getMenuItemArraySize(){
		unsigned int count = 0;
		for(unsigned int i = 0; i <= menuItemArray.max_size() -1; i++ ){
			if(menuItemArray[i] != NULL){
				count++;
			}
		}
		return count;
	}
	
	void addMenuItem(menuItem* item){
		for(unsigned int i = 0; i <= menuItemArray.max_size()-1; i++ ){
			if(menuItemArray[i] == NULL){
				menuItemArray[i] = item;
				break;
			}
		}
	}
	
};

#endif // MENU_HPP
