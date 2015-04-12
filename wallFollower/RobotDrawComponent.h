#pragma once
#include "ObjectDrawer.h"

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
	


private:
	positionType rPos;
};


