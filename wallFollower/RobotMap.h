#pragma once
#include "Types.h" 
#include "math.h"


#define MATRIX_X_SIZE	500
#define MATRIX_Y_SIZE	500
#define SIZE_CELL_M 0.1

class CRobotMap
{
public:
	Mapcell Map[MATRIX_X_SIZE][MATRIX_Y_SIZE];

	bool SetCellWalked(Position stPos, bool bWalked);
	bool SetCone(Position stPos, float fRobotAngle, Cone stCone);
	Index PositionToIndex(Position stPosition);
	Position IndexToPosition(Index stIndex);

	CRobotMap();
	~CRobotMap();
};

