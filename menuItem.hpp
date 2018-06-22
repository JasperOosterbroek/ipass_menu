#ifndef MENUITEM_HPP
#define MENUITEM_HPP
#include "hwlib.hpp"
#include <functional>
// t = string length

class menuItem{
	
private:
	hwlib::string<0> & name;
public:
	
	menuItem(hwlib::string<0> & name):
	name( name )
	{}
	
	
	hwlib::string<0> getName(){
		return name;
	}
	
	virtual void run() = 0;

};

#endif // MENUITEM_HPP
