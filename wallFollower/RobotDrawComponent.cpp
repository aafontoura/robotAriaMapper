#include "RobotDrawComponent.h"


RobotDrawComponent::RobotDrawComponent()
{
	orientationAngle = 20;
}

RobotDrawComponent::RobotDrawComponent(int x, int y)
{
	rPos.x = x / 100;
	rPos.y = y / 100;
	orientationAngle = 00;

	for (int i = 0; i < NUM_OF_CONES; i++)
		cones[i] = new ConeDrawComponent(30, i * 180 / 7 - 15 - 75, 5, 0, 0);

}

void RobotDrawComponent::drawObject()
{
	//drawCircle(getXDisplay(rPos.x), getYDisplay(rPos.y), 0.1, 10);	

	//GLUquadric* test = gluNewQuadric();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslatef(getXDisplay(rPos.x), getYDisplay(rPos.y), 0.0f);

	for (int i = 0; i < NUM_OF_CONES; i++)
		cones[i]->drawObject();


	glColor4f(1.0, 0.0, 0.0, 0.8f);
	gluPartialDisk(gluNewQuadric(), 0, 0.25, 100, 10, -orientationAngle+100, 340);

	
	glTranslatef(-getXDisplay(rPos.x), -getYDisplay(rPos.y), 0.0f);
}

void RobotDrawComponent::setPosition(float x, float y)
{
	rPos.x = x/100;
	rPos.y = y/100;

	for (int i = 0; i < NUM_OF_CONES; i++)
		cones[i]->setPosition(x, y);
}

void RobotDrawComponent::setAngle(float azAngle)
{
	orientationAngle = azAngle;
	for (int i = 0; i < NUM_OF_CONES; i++)
		cones[i]->setBearing(-azAngle + i * 180 / 7 - 15 - 75);

}


RobotDrawComponent::~RobotDrawComponent()
{
}
