#pragma once
#include "ObjectDrawer.h"
#include "ConeDrawComponent.h"
#include "Types.h"

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

	void setCone(struct Cone coneAttributes, int coneIndex);
	void setConeDistance(float range, int coneIndex);

	void initializeCone(Cone attributes, int index);
	
	ConeDrawComponent* cones[NUM_OF_CONES];
	
private:
	float orientationAngle;
	positionType rPos;
	
};


