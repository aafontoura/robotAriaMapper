#pragma once
#include "Types.h" 
#include "math.h"


class CRobotMap
{
public:
	Mapcell Map[MATRIX_X_SIZE][MATRIX_Y_SIZE];

	bool SetCellWalked(Position stPos, bool bWalked);
	bool SetCone(Position stPos, float fRobotAngle, Cone stCone, int distance);
	Index PositionToIndex(Position stPosition);
	Position IndexToPosition(Index stIndex);

	CRobotMap();
	~CRobotMap();
};

