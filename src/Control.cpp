/*
 * Control.cpp
 *
 *  Created on: 9 f�vr. 2016
 *      Author: TinyMan
 */

#include "Control.h"
#include "MyRioHelper.h"
#include <string>
#include <iostream>
using namespace std;

Control::Control() {
	// TODO Auto-generated constructor stub

}

Control::~Control() {
	// TODO Auto-generated destructor stub
}

SpeedControl::SpeedControl() : pwmUsed(MRio.Pwm.A0)
{
	pwmUsed.setFrequency(FREQUENCY_50HZ);
	pwmUsed.setDuty(NEUTRAL_DUTY);
}

void SpeedControl::setSpeed(float speed, bool forward) {
	if(speed < 0 || speed > 1)  throw "Speed should be between 0 and 1";

	float duty = 0;
	if(forward){
		duty = NEUTRAL_DUTY + (MAXDUTYFORWARD - NEUTRAL_DUTY) * speed;
	} else {
		duty = NEUTRAL_DUTY - (NEUTRAL_DUTY - MINDUTYBACKWARD) * speed;
	}
	cout << "setting DUTY for speed " << speed << ": " << duty << endl;
	pwmUsed.setDuty(duty);
}

DirectionControl::DirectionControl() : pwmUsed(MRio.Pwm.A1)
{
	pwmUsed.setFrequency(FREQUENCY_50HZ);
}

void DirectionControl::setAngle(float angle) {
	if(angle < MINANGLE || angle > MAXANGLE) {
		throw "Angle should be between -45 and 45";
	}
	this->angle = angle;
	float duty = MINDUTY + (MAXDUTY - MINDUTY) * ((angle - MINANGLE) / (MAXANGLE - MINANGLE));
	//cout << "setting DUTY for angle " << angle << ": " << duty << endl;
	pwmUsed.setDuty(duty);
}
