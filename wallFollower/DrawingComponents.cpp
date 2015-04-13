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
	drawingList[1]->drawObject();
}


void DrawingComponents::fillDrawingList()
{
	RobotDrawComponent* Robot = new RobotDrawComponent(0, 0);
	OccupationMDrawComponent* OccupationMatrix = new OccupationMDrawComponent();


	drawingList.push_back(dynamic_cast<ObjectDrawer*>(Robot));
	drawingList.push_back(dynamic_cast<OccupationMDrawComponent*>(OccupationMatrix));

}
RobotDrawComponent* DrawingComponents::getRobot()
{
	return static_cast<RobotDrawComponent*>(drawingList[ROBOT_COMPONENT]);
}


OccupationMDrawComponent* DrawingComponents::getOccupationMatrix()
{
	return static_cast<OccupationMDrawComponent*>(drawingList[OCCUPATION_M_COMPONENT]);
}

