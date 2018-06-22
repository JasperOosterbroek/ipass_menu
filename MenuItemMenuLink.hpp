#ifndef MENUITEMMENULINK_HPP
#define MENUITEMMENULINK_HPP
#include "hwlib.hpp"
#include "baseMenu.hpp" 
#include "menu.hpp"
#include "menuItem.hpp"

template <int t, int u>
class MenuItemMenuLink : public menuItem
{
private: 
	menu<u> & menulink;
	baseMenu<t,u> & baseMenuRef;
public:
	MenuItemMenuLink(hwlib::string<0> & name, menu<u> & menulink, baseMenu<t, u> & baseMenuRef):
	menuItem(name),
	menulink(menulink),
	baseMenuRef(baseMenuRef)
	{};
	void run(){
//		unsigned int menuPos = menulink.getBaseMenuPosition();
		baseMenuRef.setMenu(menulink);
		baseMenuRef.setCursorHeigth(0);
	}

};

#endif // MENUITEMMENULINK_HPP
