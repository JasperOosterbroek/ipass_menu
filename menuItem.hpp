#ifndef MENUITEM_HPP
#define MENUITEM_HPP
#include "hwlib.hpp"
#include <functional>
// t = string length

class menuItem{
	
private:
	hwlib::string<0> & name;
	//pointer
		std::function<void()> f;
public:
	
	menuItem(hwlib::string<0> & name, std::function<void()> f):
	name( name ),
	f( f )
	{};
	hwlib::string<0> getName(){
		return name;
	}
	void run(){
		f();
	}

};

#endif // MENUITEM_HPP
