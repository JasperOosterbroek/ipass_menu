#ifndef MENUITEM_HPP
#define MENUITEM_HPP
#include "hwlib.hpp"
// t = string length
class menuItem{
	
private:
	hwlib::string<0> & name;
	//pointer
public:
	
	menuItem(hwlib::string<0> & name):
	name( name )
	{};
	hwlib::string<0> getName(){
		return name;
	}
};

#endif // MENUITEM_HPP
