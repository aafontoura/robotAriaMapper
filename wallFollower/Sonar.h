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
	~CSonar();


	//Accessors
	inline void SetCone(Cone stCone)	{ stCone = SonarCone; };
	inline Cone GetCone()	{ return SonarCone; };
	inline Position GetOffsetPosition()	{ return SonarOffsetPosition; };
	inline void SetMeasure(int iMeasure)	{ stMeasure.Value_m; };
	inline int GetMeasure()	{ return stMeasure.Value_m; };


};

