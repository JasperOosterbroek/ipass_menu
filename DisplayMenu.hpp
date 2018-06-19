#ifndef DISPLAYMENU_HPP
#define DISPLAYMENU_HPP

#include "baseMenu.hpp"

template<int t, int u>
class displayMenu
{
protected:
	baseMenu<t, u> & baseMenuRef;
public:
	displayMenu<t, u>(baseMenu<t, u> & baseMenuRef):
	baseMenuRef(baseMenuRef)
	{}

	
	virtual void draw() = 0;
	virtual void clear() = 0;
};

#endif // DISPLAYMENU_HPP
