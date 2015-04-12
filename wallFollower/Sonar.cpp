#include "Sonar.h"


CSonar::CSonar()
{
	//TODO set offset no construtor
	SonarOffsetPosition = {0.0,0.0};
	RelativeAngle = 0.0;
	SonarCone = {10, 0, 300};
}


CSonar::~CSonar()
{
}
