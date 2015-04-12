#pragma once
#include "Types.h" 
#include "math.h"


#define MATRIX_X_SIZE	100
#define MATRIX_Y_SIZE	100
#define SIZE_CELL_M 0.5

class CRobotMap
{
public:
	Mapcell Map[MATRIX_X_SIZE][MATRIX_Y_SIZE];

	bool SetCellWalked(int iX, int iY, bool bWalked);
	bool SetCone(Position stPos, int iAlpha, int iRange);
	Index PositionToIndex(Position stPosition);



	

	CRobotMap();
	~CRobotMap();
};

