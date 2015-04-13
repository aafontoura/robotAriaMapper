#include "RobotMap.h"


CRobotMap::CRobotMap()
{
}


CRobotMap::~CRobotMap()
{
}

bool CRobotMap::SetCellWalked(Position stPos, bool bWalked)
{
	Index tempIndex = PositionToIndex(stPos);
	if (tempIndex.iX < MATRIX_X_SIZE && tempIndex.iY < MATRIX_Y_SIZE)
	{
		Map[tempIndex.iX][tempIndex.iY].bWalkedOver = bWalked;
		return true;
	}
	else
		return false;
}

bool CRobotMap::SetCone(Position stPos, Cone stCone)
{
	Position fMinPos, fMaxPos;
	Index iMinIndex, iMaxIndex;

	fMinPos.fX_m = stPos.fX_m - stCone.fRange_m;
	fMinPos.fY_m = stPos.fY_m - stCone.fRange_m;
	fMaxPos.fX_m = stPos.fX_m + stCone.fRange_m;
	fMaxPos.fY_m = stPos.fY_m + stCone.fRange_m;

	iMinIndex = PositionToIndex(fMinPos);
	iMaxIndex = PositionToIndex(fMaxPos);

	//Check if it is -1

	for (int y = iMinIndex.iY; y <= iMaxIndex.iY; y++)
	{
		for (int x = iMinIndex.iX; x <= iMaxIndex.iX; x++)
		{
			Index tempIndex;
			Position tempPosition;
			tempIndex.iX = x;
			tempIndex.iY = y;
			tempPosition = IndexToPosition(tempIndex);
			float CO = tempPosition.fX_m - stPos.fX_m;
			float CA = tempPosition.fY_m - stPos.fY_m;
			float H = sqrt((CO * CO) + (CA * CA));
			float RelativeAngle = (atan2(CO , CA) * 360) / (2 * 3.1415); //TODO fix constants

			if (RelativeAngle > (stCone.fAzimuth_deg - stCone.fViewAngle_deg / 2) &&
				RelativeAngle < (stCone.fAzimuth_deg + stCone.fViewAngle_deg / 2)) /*&&
				(H < stCone.fRange_m))*/
			{
				Map[x][y].bSonarViewed = true;
			}
		}
	}

	return true;
}

Index CRobotMap::PositionToIndex(Position stPosition)
{
	Index Result;
	Result.iX = -1;
	Result.iY = -1;
	int tempX = floor((int)stPosition.fX_m / SIZE_CELL_M);
	int tempY = floor((int)stPosition.fX_m / SIZE_CELL_M);

	if ((tempX < MATRIX_X_SIZE) || (tempY< MATRIX_Y_SIZE))
	{
		Result.iX = tempX;
		Result.iY = tempY;
	}
	return Result;
}

Position CRobotMap::IndexToPosition(Index stIndex)
{
	Position Result;
	Result.fX_m = (float)(stIndex.iX * SIZE_CELL_M) - SIZE_CELL_M/2;
	Result.fY_m = (float)(stIndex.iY * SIZE_CELL_M) - SIZE_CELL_M/2;
	return Result;
}




