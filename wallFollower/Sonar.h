#pragma once
#include "Types.h" 



class CSonar
{
private:
	
	Position SonarOffsetPosition;
	float RelativeAngle;
	Cone SonarCone;
	Distance stMeasure;




public:
	
	CSonar();
	CSonar(float alfa, float bearing, float range);
	~CSonar();

	// Added by Fernando
	float Range_m; // the maximum range of a sonar reading
	float beta_deg; // [deg] half of the sensor opening angle
	float MaxOccupied; // the maximum set for P(sn|O)
	float ToleranceRegion1_m; //  [m] this is the tolerance or thickness of region 1
	float InstallAng_deg; // [deg] installation angle respect to robot front


	//Accessors
	inline void SetCone(Cone stCone)	{ SonarCone = stCone ; };
	inline Cone GetCone()	{ return SonarCone; };
	inline Position GetOffsetPosition()	{ return SonarOffsetPosition; };
	inline void SetMeasure(int iMeasure)	{ stMeasure.Value_m = iMeasure; };
	inline int GetMeasure()	{ return stMeasure.Value_m; };


};

