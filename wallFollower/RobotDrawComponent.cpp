#include "RobotDrawComponent.h"



RobotDrawComponent::RobotDrawComponent()
{
}

RobotDrawComponent::RobotDrawComponent(int x, int y)
{

}

void RobotDrawComponent::drawObject()
{
	glColor4f(1.0, 0.0, 0.0, 0.8f);
	drawCircle(getXDisplay(rPos.x), getYDisplay(rPos.y), 0.1, 10);
}

void RobotDrawComponent::setPosition(float x, float y)
{
	rPos.x = x/100;
	rPos.y = y/100;
}


RobotDrawComponent::~RobotDrawComponent()
{
}
