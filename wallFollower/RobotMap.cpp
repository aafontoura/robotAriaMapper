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

bool CRobotMap::SetCone(int iX, int iY, int iAlpha, int iRange);