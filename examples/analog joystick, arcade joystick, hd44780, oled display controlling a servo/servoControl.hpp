#ifndef SERVOCONTROL_HPP
#define SERVOCONTROL_HPP
#include "lightMenu.hpp"
#include "hwlib.hpp"

class servoControl : public lightMenu::menuItem{
private:
	hwlib::target::pin_out & pwmPin;
	int servoPos;
public:
	servoControl(hwlib::string<0> name, int servoPos, hwlib::target::pin_out & pwmPin):
	lightMenu::menuItem(name),
	pwmPin(pwmPin),
	servoPos(servoPos)
	{}
	
	void run();
	void goToPos(int pos);
	
};
#endif // SERVOCONTROL_HPP
