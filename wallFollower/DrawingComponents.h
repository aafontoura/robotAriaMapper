#pragma once
#include <vector>
#include "ObjectDrawer.h"
#include "RobotDrawComponent.h"
#include "OccupationMDrawComponent.h"

enum {
	ROBOT_COMPONENT,
	OCCUPATION_M_COMPONENT
};

class DrawingComponents
{
public:
	DrawingComponents();
	~DrawingComponents();

	void drawObjects();

	RobotDrawComponent *getRobot();
	OccupationMDrawComponent *getOccupationMatrix();


private:
	std::vector<ObjectDrawer*> drawingList;
	void fillDrawingList();
};

