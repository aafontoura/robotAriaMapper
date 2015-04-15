#pragma once
#include "ObjectDrawer.h"
#include "ConeDrawComponent.h"

#define NUM_OF_CONES 8

typedef struct {
	float x;
	float y;
} positionType;

class RobotDrawComponent :
	public ObjectDrawer
{
public:
	RobotDrawComponent(int x, int y);
	RobotDrawComponent();
	void drawObject();
	~RobotDrawComponent();

	void setPosition(float x, float y);
	void setAngle(float azAngle);
	
	ConeDrawComponent* cones[NUM_OF_CONES];
	
private:
	float orientationAngle;
	positionType rPos;
	
};


