#pragma once
#include "Types.h" 


#define MATRIX_X_SIZE	100
#define MATRIX_Y_SIZE	100

class CRobotMap
{
public:
	Mapcell Map[MATRIX_X_SIZE][MATRIX_Y_SIZE];

	bool SetCellWalked(int iX, int iY, bool bWalked);
	bool SetCone(int iX, int iY, int iAlpha, int iRange);


	CRobotMap();
	~CRobotMap();
};

