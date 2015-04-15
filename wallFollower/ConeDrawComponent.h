#pragma once
#include "ObjectDrawer.h"
class ConeDrawComponent :
	public ObjectDrawer
{
public:
	ConeDrawComponent(float alfaIn, float bearingIn, float distanceIn, float xIn, float yIn);
	~ConeDrawComponent();

	virtual void drawObject();

	void setPosition(float xIn,float yIn, float bearingIn);
	void setPosition(float xIn, float yIn);
	void setBearing(float bearingIn);
	void setDistance(float distanceIn);

private:
	float alfa;
	float bearing;
	float distance;
	float x;
	float y;
};

