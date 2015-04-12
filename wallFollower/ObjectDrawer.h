#pragma once

#include <GL/glut.h>
#include <math.h>



class ObjectDrawer
{
public:
	ObjectDrawer();
	~ObjectDrawer();

	virtual void drawObject()=0;
protected:
	void drawCircle(float cx, float cy, float r, int num_segments);
	void drawLine(float p1X, float p1Y, float p2X, float p2Y, float width);
	void drawSquare(float x, float y, float sideSize);
	void drawRectangle(float left, float right, float up, float down, bool filled );
	void renderBitmapString(float x, float y, float z, char *string);

	/* Opengl coordinates Conversion Methods */
	float getXDisplay(float xInput_m);
	float getYDisplay(float yInput_m);
	float getXMeter(float xInput_disp);
	float getYMeter(float yInput_disp);


};

