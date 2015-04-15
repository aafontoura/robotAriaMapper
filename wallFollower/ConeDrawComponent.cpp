#include "ConeDrawComponent.h"


ConeDrawComponent::ConeDrawComponent(float alfaIn, float bearingIn, float distanceIn, float xIn, float yIn)
{
	alfa = alfaIn;
	bearing = bearingIn;
	distance = distanceIn;	
	x = xIn;
	y = yIn;
}


ConeDrawComponent::~ConeDrawComponent()
{
}


void ConeDrawComponent::drawObject()
{
	glColor4f(0.0, 0.0, 0.5, 0.4f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	
	gluPartialDisk(gluNewQuadric(), 0, getXDisplay(distance), 100, 10, bearing + 90 - alfa/2, alfa);
}


void ConeDrawComponent::setPosition(float xIn, float yIn, float bearingIn)
{
	bearing = bearingIn;
	x = xIn;
	y = yIn;
}

void ConeDrawComponent::setPosition(float xIn, float yIn)
{
	x = xIn;
	y = yIn;
}

void ConeDrawComponent::setBearing(float bearingIn)
{
	bearing = bearingIn;
}

void ConeDrawComponent::setDistance(float distanceIn)
{

	distance = distanceIn;

}

void ConeDrawComponent::setAlfa(float alfaIn)
{
	alfa = alfaIn;
}

void ConeDrawComponent::setRange(float rangeIn)
{
	range = rangeIn;
}