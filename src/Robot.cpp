#include "WPILib.h"
#include <string>

using namespace std;
class Robot: public IterativeRobot {
private:
	enum steps {
		forward, turnLeft, turnRight, stop
	} driving;
	bool stopped;
	Gyro *spinny;
	CANTalon *right, *left;
	Robot::steps whatToDo[10];
	Timer *timing;
	int stepper;

	void RobotInit() {
		timing = new Timer;
		right = new CANTalon(5);
		left = new CANTalon(3);
		spinny->Calibrate();
	}

	void AutonomousInit() {
		stopped = false;
		timing->Start();
		stepper = 0;
		whatToDo[0] = (forward);
		whatToDo[1] = (turnLeft);
		whatToDo[2] = (turnRight);
		whatToDo[3] = (turnRight);
		whatToDo[4] = (turnRight);
		whatToDo[5] = (turnLeft);
		whatToDo[6] = (turnLeft);
		whatToDo[7] = (turnLeft);
		whatToDo[8] = (turnRight);
		whatToDo[9] = (stop);
	}

	void AutonomousPeriodic() {
		driving = whatToDo[stepper];
		if (!stopped)
			switch (driving) {
			case forward:
				left->Set(-.6);
				right->Set(.6);
				if (timing->Get() > 1) {
					stepper++;
					timing->Reset();
				}
				break;
			case stop:
				left->Set(0);
				right->Set(0);
				stopped = true;
				break;
			case turnLeft:
				left->Set(.6);
				right->Set(-.6);
				if (spinny->GetAngle() < -90) {
					spinny->Reset();
					stepper++;
					timing->Reset();
				}
				break;
			case turnRight:
				left->Set(-.6);
				right->Set(.6);
				if (spinny->GetAngle() > 90) {
					spinny->Reset();
					stepper++;
					timing->Reset();

					break;
				}
			}
	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {

	}

	void TestPeriodic() {

	}
};

START_ROBOT_CLASS(Robot)
