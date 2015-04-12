#include "RobotMap.h"


CRobotMap::CRobotMap()
{
}


CRobotMap::~CRobotMap()
{
}

bool CRobotMap::SetCellWalked(int iX, int iY, bool bWalked)
{
	if (iX < MATRIX_X_SIZE && iY < MATRIX_Y_SIZE)
	{
		Map[iX][iY].bWalkedOver = bWalked;
		return true;
	}
	else
		return false;
}

bool CRobotMap::SetCone(Position stPos, int iAlpha, int iRange)
{
	return true;
}

Index CRobotMap::PositionToIndex(Position stPosition)
{
	Index Result;
	Result.iX = -1;
	Result.iY = -1;
	int tempX = stPosition.fX_m / (float)SIZE_CELL_M + 1;
	int tempY = (stPosition.fX_m / SIZE_CELL_M);

	if ((tempX < MATRIX_X_SIZE) || (tempY< MATRIX_Y_SIZE))
	{
		Result.iX = tempX;
		Result.iY = tempY;
	}
	return Result;
}