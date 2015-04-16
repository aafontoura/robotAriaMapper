#include "RobotMap.h"


CRobotMap::CRobotMap()
{
	cellSize_m = (float) SIZE_CELL_M;
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

bool CRobotMap::SetCone(Position stPos, float fRobotAngle, Cone stCone, int distance)
{
	Position fMinPos, fMaxPos;
	Index iMinIndex, iMaxIndex;

	fRobotAngle = -fRobotAngle;

	/*fMinPos.fX_m = stPos.fX_m - stCone.fRange_m;
	fMinPos.fY_m = stPos.fY_m - stCone.fRange_m;
	fMaxPos.fX_m = stPos.fX_m + stCone.fRange_m;
	fMaxPos.fY_m = stPos.fY_m + stCone.fRange_m;*/

	fMinPos.fX_m = stPos.fX_m - distance;
	fMinPos.fY_m = stPos.fY_m - distance;
	fMaxPos.fX_m = stPos.fX_m + distance;
	fMaxPos.fY_m = stPos.fY_m + distance;

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
			float RelativeAngle = -(atan2(CA,CO) * 180 / 3.1415); //TODO fix constants
			float fBeamAngle_deg = (((int)(fRobotAngle) % 360) + fRobotAngle - ((float)((int)fRobotAngle)) + stCone.fAzimuth_deg); /* precisao corrigida*/

			if (RelativeAngle > (fBeamAngle_deg - stCone.fViewAngle_deg / 2) &&
				RelativeAngle < (fBeamAngle_deg + stCone.fViewAngle_deg / 2) &&
				//(H < stCone.fRange_m))
				(H < distance))
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
	Result.iX = -999999;
	Result.iY = -999999;
	int tempX = (MATRIX_X_SIZE/2)+floor(stPosition.fX_m / SIZE_CELL_M);
	int tempY = (MATRIX_Y_SIZE/2)+floor(stPosition.fX_m / SIZE_CELL_M);

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
	Result.fX_m = (float)((stIndex.iX - (MATRIX_X_SIZE / 2)) * SIZE_CELL_M) - SIZE_CELL_M / 2;
	Result.fY_m = (float)((stIndex.iY - (MATRIX_Y_SIZE / 2)) * SIZE_CELL_M) - SIZE_CELL_M / 2;
	return Result;
}

bool isInsideSector(Position origin, float R1, float R2, float ang1_deg, float ang2_deg, Position testpoint)
{
	return false;
}




