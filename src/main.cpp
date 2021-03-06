#include <iostream>
#include <cstdio>
#include "MyRioCar.h"
#include "MyRioHelper.h"
#include "AccelerometerHelper.h"
#include "RemoteControl/RemoteControl.h"

using namespace std;

int main() {
	try {
	printf("Testing control\n");

	MyRioCar Car;

	 /* Normally, the main function runs a long running or infinite loop.
	 * Keep the program running for 60 seconds so that the PWM output can be
	 * observed using an external instrument.
	 */

	float a = 45;
	Car.start();

	RemoteControl rc(Car);
	rc.startServer(1337);

	cout << "Power off then power on the speed regulator" << endl;
	time_t currentTime;
	time_t finalTime;
	time_t startTime;
	time(&startTime);
	time(&currentTime);
	finalTime = currentTime + 30;
	time_t nextInvert = currentTime + 1;
	using namespace std;

	while (currentTime < finalTime) {
		if (currentTime >= nextInvert) {
			std::cout << "current time: " << currentTime - startTime << "\n";
			//cout << "a: " << a << endl;
			//Car.Control.Speed.setSpeed(a+=0.1);
			Car.Control.Direction.setAngle(a = -a);


			nextInvert = currentTime + 1;
		}
		time(&currentTime);
	}

	rc.stop();
	cout << "end " << endl;
	} catch(const char* e){
		cout << e << endl;
	}
	return 0;
}

