#include <string>
#include "Aria.h"
#include "OpenGLComponent.h"
#include "ClassRobo.h"
#include <iostream>       // std::cout
#include <thread>         // std::thread

PioneerRobot* robot;
int** occupationMatrixT;
DrawingComponents* dComponents;


class later
{
public:
	template <class callable, class... arguments>
	later(int after, bool async, callable&& f, arguments&&... args)
	{
		std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));

		if (async)
		{
			std::thread([after, task]() {
				std::this_thread::sleep_for(std::chrono::milliseconds(after));
				task();
			}).detach();
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(after));
			task();
		}
	}

};
later* timer;

int getFrontDist(int *s)
{
	int i = 99999;
	i = s[2] < i ? s[2] : i;
	i = s[3] < i ? s[3] : i;
	i = s[4] < i ? s[4] : i;

	return i;
}

#define RUN_STRAIGHT 3
#define RUN_PARALLEL 1
#define TURN_LEFT 2
#define TURN_RIGHT 4
#define RUN_STRAIGHT_FOR_PARALELL 5
#define INIT_STATE 0
#define STRAIGHT_DIST_LIMIT 900
#define TURN_ANGLE 90.0

bool turnRight()
{
	static bool isInProcess = false;

	if (!isInProcess)
	{
		robot->robot.setDeltaHeading(TURN_ANGLE);
		robot->Move(50, -50);
		isInProcess = true;
	}
	else
	{
		std::cout << robot->robot.getHeadingDoneDiff() << " " << std::endl;
		if (robot->robot.isHeadingDone())
		{
			robot->robot.stop();
			isInProcess = false;
		}
	}
	return isInProcess;
}

bool turnLeft()
{
	static bool isInProcess = false;
	
	if (!isInProcess)
	{
		robot->robot.setDeltaHeading(-TURN_ANGLE);
		robot->Move(-50, 50);
		isInProcess = true;
	}
	else
	{
		std::cout << robot->robot.getHeadingDoneDiff() << " " << std::endl;
		if (robot->robot.isHeadingDone())
		{
			robot->robot.stop();
			isInProcess = false;
		}
	}
	return isInProcess;
}

int keepDistRightWall(int* s, int* diff, int* diff2)
{
	static int left = 150, right = 150;

	if (getFrontDist(s) < STRAIGHT_DIST_LIMIT)
		return 2;

	if (s[7] < 2000)
	{
		if ((diff[7] < 0))
		{
			if (diff2[7] < 0)
			{
				left += 1;
				right -= 1;
			}
			else if (diff2[7] > 0)
			{
				left -= 5;
				right += 5;
			}
			else
			{
				left -= 1;
				right += 1;
			}
		}
		else if (diff[7] > 0)
		{
			if (diff2[7] < 0)
			{
				left += 1;
				right -= 1;
			}
			else if (diff2[7] > 0)
			{
				left += 5;
				right -= 5;
			}
			else
			{
				left += 1;
				right -= 1;
			}
		}

		std::cout << left << " " << right << std::endl;
		robot->Move(left, right);

		return 1;
	}
	else
	{
		if ((s[7] < 5000) || (diff[7]>1000))
		{
			return 3;
		}
		else
			/* no action can be done. Distance from the wall unknown */
			return 0;
	}

}

void handleSensors()
{
	int s[8];
	static int sOld[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	static int diff[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int diff2[8];
	static int count = 0;
	
	static int state = 0;
	robot->getAllSonar(s);

	for (int i = 0; i < 8; i++)
	{
		diff2[i] = diff[i] - (s[i] - sOld[i]);
		diff[i] = s[i] - sOld[i];
	}

	std::cout << state << " ";
	for (int i = 0; i < 8; i++)
		std::cout << s[i] << " ";

	std::cout << std::endl;

	
	switch (state)
	{
	case INIT_STATE:
	case RUN_STRAIGHT:
		robot->Move(150, 150);
		if (getFrontDist(s) < STRAIGHT_DIST_LIMIT)
			state = TURN_LEFT;

		if (s[7] < 4000)
			state = RUN_PARALLEL;
		break;
	case RUN_PARALLEL:
		switch (keepDistRightWall(s, diff, diff2))
		{
		case 0:
			state = RUN_STRAIGHT;
			break;
		case 2:
			state = TURN_LEFT;
			break;
		case 3:
			state = TURN_RIGHT;
		default:
			break;
		}
		break;
	case TURN_LEFT:
		if (turnLeft())
			state = RUN_PARALLEL;
		break;
	case TURN_RIGHT:
		if (turnRight())
		{
			state = RUN_STRAIGHT_FOR_PARALELL;
			count = 0;
		}
		break;
	case RUN_STRAIGHT_FOR_PARALELL:		
		robot->Move(150, 150);
		if (count++ > 2)
			state = RUN_PARALLEL;
		break;

	}

	/*if (getFrontDist(s) > 2000)
		robot->Move(50, -50);
	else if (getFrontDist(s) > 1000)
	{*/

	
	/*}
	else
		robot->Move(-50, 50);*/
	
	OpenGLComponent::setRobotPos(robot->getXPos(), robot->getYPos());
	std::cout << robot->getXPos()<<"-" << robot->getYPos() <<  std::endl;

	memcpy(sOld, s, sizeof(int) * 8);
	timer = new later(1000, false, &handleSensors);

	/*char  st[10];
	itoa(s[0], st, 10);
	s1->Text = gcnew String(st);

	itoa(s[1], st, 10);
	s2->Text = gcnew String(st);

	itoa(s[2], st, 10);
	s3->Text = gcnew String(st);

	itoa(s[3], st, 10);
	s4->Text = gcnew String(st);

	itoa(s[4], st, 10);
	s5->Text = gcnew String(st);

	itoa(s[5], st, 10);
	s6->Text = gcnew String(st);

	itoa(s[6], st, 10);
	s7->Text = gcnew String(st);

	itoa(s[7], st, 10);
	s8->Text = gcnew String(st);

	itoa(robo->getXPos(), st, 10);
	lx->Text = gcnew String(st);

	itoa(robo->getYPos(), st, 10);
	ly->Text = gcnew String(st);

	itoa(robo->getAngBase(), st, 10);
	lfi->Text = gcnew String(st);*/
}

void loopRobot()
{
	
}

void openGLThread()
{
	int argc;
	char** argv = NULL;

	// init GLUT and create window
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);//1024,768);
	glutCreateWindow("Robot Grid");

	// register callbacks
	glutDisplayFunc(OpenGLComponent::renderScene);

	glutReshapeFunc(OpenGLComponent::changeSize);
	glutIdleFunc(OpenGLComponent::renderScene);
	glutSpecialFunc(OpenGLComponent::processSpecialKeys);
	glutMotionFunc(OpenGLComponent::mouseMotionHandler);
	glutMouseFunc(OpenGLComponent::mouseButtonHandler);
	glutKeyboardFunc(OpenGLComponent::keyPressed); // Tell GLUT to use the method "keyPressed" for key presses  
	glutKeyboardUpFunc(OpenGLComponent::keyUp); // Tell GLUT to use the method "keyUp" for key up events

	occupationMatrixT = (int**)malloc(sizeof(int)*MATRIX_X_SIZE);
	for (int i = 0; i < MATRIX_X_SIZE;i++)
		occupationMatrixT[i] = (int*)malloc(sizeof(int)*MATRIX_X_SIZE);

	dComponents = new DrawingComponents();
	OpenGLComponent::setDrawingComponents(dComponents);// (int**)(robot->occupationMatrix));

	OpenGLComponent::setOccupationMatrix((int**)occupationMatrixT);// (int**)(robot->occupationMatrix));

	OpenGLComponent::getMapData(&robot->stMap);

	// enter GLUT event processing cycle
	glutMainLoop();
}

int main(int argc, char** argv)
{	
	int status;

	robot = new PioneerRobot(ConexaoSimulacao, "", &status);
	std::thread t1(openGLThread);// , t2(handleSensors);   // run both functions at once




	
	timer = new later(1000, false, &handleSensors);
	
	// Final synchronisation:
	// All running threads must be either joined or detached
	t1.join();

}