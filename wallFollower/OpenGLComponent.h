#pragma once
#include <GL/glut.h>
#include <vector>
#include "ClassRobo.h"
#include "RobotDrawComponent.h"
#include "ObjectDrawer.h"
#include "DrawingComponents.h"

#define WINDOW_SIZE_WIDTH 1024
#define WINDOW_SIZE_HEIGHT 1024



class OpenGLComponent
{
public:
	OpenGLComponent();
	~OpenGLComponent();
	static void renderScene();
	static void changeSize(int w, int h);
	static void processSpecialKeys(int key, int x, int y);
	static void mouseButtonHandler(int button, int state, int x, int y);
	static void mouseMotionHandler(int x, int y);
	static void keyPressed(unsigned char key, int x, int y);
	static void keyUp(unsigned char key, int x, int y);
	static void setOccupationMatrix(int** ocupationMatrixInput);
	static void setRobotPos(float x, float y, float angle);

	static void setMapData(CRobotMap* stMap);


	static void setDrawingComponents(DrawingComponents *dComponents);


};

