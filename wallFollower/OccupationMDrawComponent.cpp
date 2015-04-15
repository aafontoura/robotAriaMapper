#include "OccupationMDrawComponent.h"


OccupationMDrawComponent::OccupationMDrawComponent()
{
}


OccupationMDrawComponent::~OccupationMDrawComponent()
{
}


void OccupationMDrawComponent::drawObject()
{
	glColor4f(1.0, 1.0, 1.0, 0.8f);
	drawLine(-500, 0, 500, 0,1.0);
	drawLine(0, -500, 0, 500, 1.0);


	for (int i = 0; i < MATRIX_X_SIZE; i++)
		for (int j = 0; j< MATRIX_Y_SIZE; j++)
		{
			Position posXY = robotMap->IndexToPosition({ i, j });

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			//if (testMatrix[i][j] == 1)
			if (robotMap->Map[i][j].bSonarViewed == true)
			{
				glColor4f(1.0, 1.0, 1.0, 0.8f);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				drawRectangle(getXDisplay(posXY.fX_m) - SIZE_CELL_M / 2, getXDisplay(posXY.fX_m) + SIZE_CELL_M / 2, getYDisplay(posXY.fY_m) + SIZE_CELL_M / 2, getYDisplay(posXY.fY_m) - SIZE_CELL_M);
			}
			else
				glColor4f(1.0, 1.0, 1.0, 0.8f);

			

		}

}


void OccupationMDrawComponent::setRobotMap(CRobotMap* newRobotMap)
{
	robotMap = newRobotMap;

}