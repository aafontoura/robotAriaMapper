#pragma once
#include "ObjectDrawer.h"
#include "RobotMap.h"


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
	
};

