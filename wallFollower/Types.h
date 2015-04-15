#ifndef TYPES_H
#define TYPES_H

#define MATRIX_X_SIZE	200
#define MATRIX_Y_SIZE	200
#define SIZE_CELL_M 0.1

struct Cone
{
	float fViewAngle_deg;
	float fAzimuth_deg;
	float fRange_m;

};

struct Position
{
	float fX_m;
	float fY_m;
};

struct Mapcell
{
	bool bWalkedOver;
	bool bSonarViewed;
	bool bLaserViewed;
};

struct Distance
{
	int Value_m;
	float fError;
};

struct Index
{
	int iX;
	int iY;
};


#endif