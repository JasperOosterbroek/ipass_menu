#ifndef JOYSTICKMENUCONTROLLER_HPP
#define JOYSTICKMENUCONTROLLER_HPP
#include "hwlib.hpp"
#include "controlMenu.hpp"
#include "baseMenu.hpp"

template<int t, int u>
class joystickMenuController : public controlMenu<t, u>
{
private:
	hwlib::target::pin_in selectPin;
	hwlib::target::pin_adc xAxisPin;
	hwlib::target::pin_adc yAxisPin;

public:
	joystickMenuController(baseMenu<t, u> & baseMenu, hwlib::target::pin_in & selectPin, hwlib::target::pin_adc xAxisPin, hwlib::target::pin_adc yAxisPin):
	controlMenu<t, u> (baseMenu),
	selectPin( selectPin ),
	xAxisPin( xAxisPin ),
	yAxisPin( yAxisPin)
	{}
	// "read joystick input"
	void flush(){
		xAxisPin.get();
		yAxisPin.get();
	}
	bool read(){
		if(selectPin.get() == 0){
			controlMenu<t, u>::select();
			return true;
		}
		int tempXAxis = xAxisPin.get();
		int tempYAxis = yAxisPin.get();
		// checkcenter
		if(!((tempXAxis < 2800 && tempXAxis > 3200) && (tempYAxis < 2800 && tempYAxis > 3200)) ){
			//check left && right
			if(tempXAxis > 3500){
				controlMenu<t,u>::previousMenu();
				return true;
			}else if(tempXAxis < 500){
				controlMenu<t, u>::select();
				return true;
			}
			//check up && down
			else if(tempYAxis > 3500){
				controlMenu<t,u>::cursorUp();
				return true;
			}else if(tempYAxis < 500){
				controlMenu<t,u>::cursorDown();
				return true;
			}else{
				return false;
			}
			return false;
		}
		return false;
	}
	//  might not be neccesery because of just running the draw function
	void back(std::function<void()> f){
		f();
	}
	
	void backToMenu(){
		
	}
};

#endif // JOYSTICKMENUCONTROLLER_HPP
