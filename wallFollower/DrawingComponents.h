#pragma once
#include <vector>
#include "ObjectDrawer.h"
#include "RobotDrawComponent.h"

enum {
	ROBOT_COMPONENT
};

class DrawingComponents
{
public:
	DrawingComponents();
	~DrawingComponents();

	void drawObjects();

	RobotDrawComponent *getRobot();


private:
	std::vector<ObjectDrawer*> drawingList;
	void fillDrawingList();
};

