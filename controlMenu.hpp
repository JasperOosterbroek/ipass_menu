#ifndef CONTROLMENU_HPP
#define CONTROLMENU_HPP
#include "hwlib.hpp"
#include "baseMenu.hpp"

template<int t, int u>
class controlMenu
{
protected:
	baseMenu<t, u> & baseMenuRef;
public:
	controlMenu<t, u>(baseMenu<t, u> & baseMenuRef):
	baseMenuRef(baseMenuRef)
	{}

protected:
	void cursorUp(){
		baseMenuRef.cursorUp();
	}

	void cursorDown(){
		baseMenuRef.cursorDown();
	}

	void select(){
		baseMenuRef.select();
	}

	virtual void backToMenu() = 0;
	
	void previousMenu(){
		baseMenuRef.previousMenu();
	}
	
};

#endif // CONTROLMENU_HPP