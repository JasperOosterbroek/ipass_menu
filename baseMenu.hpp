#ifndef BASEMENU_HPP
#define BASEMENU_HPP
#include <array>
#include "menu.hpp"

// t = basemenu array size
// u = menuItemsize
// v = menuarraysize
template<int t, int u> class baseMenu {
private:
	std::array<menu<u>*, t> & menus;
	unsigned int maxHeight;
	unsigned int maxWidth;
	std::array<unsigned int, 2> curpos = {0,0};
public:
	baseMenu<t,u>(std::array<menu<u>*, t> & menus):
		menus (menus),
		maxHeight(u - 1),
		maxWidth(t - 1)
	{
		for(unsigned int i = 0; i < menus.size(); i++){
			menus[i]->setBaseMenuPosition(i);
		}
	}
	menu<u>& getMenuByIndex(int index){
		return menus[index];
	}
	
	menu<u>* getCurrentMenu(){
		return menus[curpos[0]];
	}
	
	unsigned int getCurrentCursorPos(){
		return curpos[1];
	}
	void setCursorHeigth(unsigned int i){
		if(maxHeight >= i){
			curpos[1] = i;
		}
	}
	unsigned int getMaxHeight(){
		return maxHeight;
	}
	
	void cursorUp(){
		if(curpos[1] > 0){
			curpos[1]--;
		}
	}
	
	void cursorDown(){
		if(curpos[1] < maxHeight){
			curpos[1]++;
		}
	}
	
	void select(){
		getCurrentMenu()->getMenuItemByIndex(curpos[1]).run();
	}
	
	void setMenu(menu<u> & setMenu){
		curpos[0] = setMenu.getBaseMenuPosition();
	}
	
	void previousMenu(){
		curpos[0] = getCurrentMenu()->getParentMenu()->getBaseMenuPosition();
	}
	
	
};

	
#endif // BASEMENU_HPP
