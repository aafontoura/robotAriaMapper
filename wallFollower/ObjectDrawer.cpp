#include "ObjectDrawer.h"


ObjectDrawer::ObjectDrawer()
{
}


ObjectDrawer::~ObjectDrawer()
{
}

/* Draw Strings */
void ObjectDrawer::renderBitmapString(float x, float y, float z, char *string) {

	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
	}
}

void ObjectDrawer::drawRectangle(float left, float right, float up, float down, bool filled)
{
	glBegin(GL_QUADS);
	glVertex3f(left, down, 0);
	glVertex3f(left, up, 0);
	glVertex3f(right, up, 0);
	glVertex3f(right, down, 0);
	glEnd();
}

void ObjectDrawer::drawSquare(float x, float y, float sideSize)
{
	drawRectangle(x - sideSize / 2, x + sideSize / 2, y + sideSize / 2, y - sideSize / 2);
}

void ObjectDrawer::drawLine(float p1X, float p1Y, float p2X, float p2Y, float width = 1.0)
{
	glBegin(GL_LINES);
	glVertex3f(p1X, p1Y, 0);
	glVertex3f(p2X, p2Y, 0);
	glEnd();
}



/* Draw a circle centered in cx,cy with radius r. */
/* The circunference is drawed using line segments. the number
/* of segments used for drawing the circle is num_segments. */
void ObjectDrawer::drawCircle(float cx, float cy, float r, int num_segments)
{
	float theta = 2 * 3.1415926 / float(num_segments);
	float c = cosf(theta);//precalculate the sine and cosine
	float s = sinf(theta);
	float t;

	float x = r;//we start at angle = 0 
	float y = 0;

	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);//output vertex 

		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
	glEnd();
}



float ObjectDrawer::getXDisplay(float xInput_m)
{	
	return xInput_m*0.5 + 0.5/ 2;
}

float ObjectDrawer::getYDisplay(float yInput_m)
{
	return yInput_m*0.5 + 0.5 / 2;
}

float ObjectDrawer::getXMeter(float xInput_disp)
{
	return ((xInput_disp - 0.5 / 2) / 0.5);
}

float ObjectDrawer::getYMeter(float yInput_disp)
{
	return ((yInput_disp - 0.5 / 2) / 0.5);
}