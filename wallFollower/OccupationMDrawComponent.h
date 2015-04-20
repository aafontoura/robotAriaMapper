#pragma once
#include "ObjectDrawer.h"
#include "RobotMap.h"

enum {
	OCCUPATION_ONLY_MODE,
	PROBABILITY_MODE,
	ROBOT_PATH_MODE
} ;


class OccupationMDrawComponent :
	public ObjectDrawer
{
public:
	OccupationMDrawComponent();
	~OccupationMDrawComponent();
	void drawObject();
	void setRobotMap(CRobotMap* newRobotMap);
protected:
	CRobotMap* robotMap;
	int mapMode;
	
};

