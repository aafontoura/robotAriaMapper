#include "DrawingComponents.h"


DrawingComponents::DrawingComponents()
{
	fillDrawingList();
}


DrawingComponents::~DrawingComponents()
{
}

void DrawingComponents::drawObjects()
{
	drawingList[0]->drawObject();
}


void DrawingComponents::fillDrawingList()
{
	RobotDrawComponent* Robot = new RobotDrawComponent(0, 0);

	drawingList.push_back(dynamic_cast<ObjectDrawer*>(Robot));

}
RobotDrawComponent* DrawingComponents::getRobot()
{
	return static_cast<RobotDrawComponent*>(drawingList[ROBOT_COMPONENT]);
}
