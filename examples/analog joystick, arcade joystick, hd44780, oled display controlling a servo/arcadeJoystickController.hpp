#ifndef ARCADEJOYSTICKCONTROLLER_HPP
#define ARCADEJOYSTICKCONTROLLER_HPP
#include "hwlib.hpp"
#include "lightMenu.hpp"

template<int t, int u>
class arcadeJoystickController : public lightMenu::controlMenu<t, u>
{
	hwlib::target::pin_in pinUp;
	hwlib::target::pin_in pinDown;
	hwlib::target::pin_in pinLeft;
	hwlib::target::pin_in pinRight;

public:
	arcadeJoystickController(lightMenu::baseMenu<t, u> & baseMenu, hwlib::target::pin_in & pinUp, hwlib::target::pin_in & pinDown, hwlib::target::pin_in & pinLeft, hwlib::target::pin_in & pinRight):
		lightMenu::controlMenu<t, u> (baseMenu),
		pinUp( pinUp ),
		pinDown( pinDown ),
		pinLeft( pinLeft ),
		pinRight( pinRight )
	{};
	bool read(){
		if(pinUp.get() == 0){
			lightMenu::controlMenu<t, u>::cursorUp();
			return true;
		}else if(pinDown.get() == 0){
			lightMenu::controlMenu<t, u>::cursorDown();
			return true;
		}else if(pinLeft.get() == 0){
			lightMenu::controlMenu<t,u>::previousMenu();
			return true;
		}else if(pinRight.get() == 0){
			lightMenu::controlMenu<t, u>::select();
			return true;
		}else{
			return false;
		}
	}
};

#endif // ARCADEJOYSTICKCONTROLLER_HPP
