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

	bool isInsideSector(Position origin, float R1, float R2, float ang1_deg, float ang2_deg, Position testpoint, float *rDist_m, float *rAngle_deg); // Tests if the point[pX, pY] is inside the sector defined
	float UpdateBayesFilter(float P_sn_H, float P_H_sn_Minus1, float P_sn_notH, float P_notH_sn_Minus1); // updates the probability of occupied or empty according to Bayes theorem

	CRobotMap();
	~CRobotMap();
};

