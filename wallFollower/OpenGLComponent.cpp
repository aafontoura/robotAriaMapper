#include "OpenGLComponent.h"


using namespace std;



#define X_MOUSE_MOTION_FACTOR 7.0
#define Y_MOUSE_MOTION_FACTOR 5.0

#define PIXEL_SIZE 0.5

/* ------------------------------------------------------------------*/
/*
/*						GLOBAL VARIABLES
/*
/* ------------------------------------------------------------------*/
DrawingComponents *objectsComponents;

float angle = 0.0f;




/* Camera position */
float xA = 4.0f;
float yA = 2.0f;
float zA = 10.0f;

bool keyStates[256]; // Create an array of boolean values of length 256 (0-255)  

int xOrigin = -1;
int yOrigin = -1;
bool bMooveMap = false;



float getX(int x)
{
	return x*PIXEL_SIZE + PIXEL_SIZE / 2;
}

float getPoint(int x)
{
	return x*PIXEL_SIZE + PIXEL_SIZE / 2;
}

int getInvPoint(float x)
{
	return (int)((x - PIXEL_SIZE / 2) / PIXEL_SIZE);
}


/* ------------------------------------------------------------------*/

OpenGLComponent::OpenGLComponent()
{

}


OpenGLComponent::~OpenGLComponent()
{
}


void OpenGLComponent::setMapData(CRobotMap* Map)
{
	objectsComponents->getOccupationMatrix()->setRobotMap(Map);
}
void OpenGLComponent::setRobotPos(float x, float y, float angle)
{
	objectsComponents->getRobot()->setPosition(x, y);
	objectsComponents->getRobot()->setAngle(angle);
}

void OpenGLComponent::changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void OpenGLComponent::keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = true; // Set the state of the current key to pressed  
}


void OpenGLComponent::keyUp(unsigned char key, int x, int y) {
	keyStates[key] = false; // Set the state of the current key to not pressed  
}


/* Handles keys press */
void OpenGLComponent::processSpecialKeys(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:
		yA += 0.1f;
		break;
	case GLUT_KEY_DOWN:
		yA -= 0.1f;
		break;
	case GLUT_KEY_RIGHT:
		xA += 0.1f;
		break;
	case GLUT_KEY_LEFT:
		xA -= 0.1f;
		break;
	case GLUT_KEY_PAGE_UP:
		//globalScale += 10;
		//realScale = globalScale*SCALE_FACTOR_IN_10Z;//0.5878;

		//yA+=0.5f;
		zA += 0.1f;
		break;
	case GLUT_KEY_PAGE_DOWN:
		/*globalScale -= 10;
		realScale = globalScale*SCALE_FACTOR_IN_10Z;*/
		//yA+=150.0f/globalScale;//0.3f;

		zA -= 0.1f;
		break;

	case GLUT_KEY_F1:
		break;
	case GLUT_KEY_F2:
		break;
	case GLUT_KEY_F3:
		break;


	case GLUT_KEY_F4:
		break;
	case GLUT_KEY_F5:
		break;
	case GLUT_KEY_F6:
		break;
	case GLUT_KEY_F7:
		break;
	case GLUT_KEY_F8:
		break;
	case GLUT_KEY_F9:
		break;
	case GLUT_KEY_F10:
		break;
	case GLUT_KEY_F11:
		break;
	case GLUT_KEY_F12:
		break;

	}
}


void processKeys()
{
	if (keyStates['+'])
	{
	}
	if (keyStates['-'])
	{
	}
}



void OpenGLComponent::mouseButtonHandler(int button, int state, int x, int y)
{
	//std::cout << "button - " << x << " - " << y << " - " << button << " - " << state << std::endl;
	switch (button)
	{
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			xOrigin = x;
			yOrigin = y;
			bMooveMap = true;
		}
		else
		{
			xOrigin = -1;
			yOrigin = -1;
			bMooveMap = false;
		}
		break;
	case 3:
		if (state == GLUT_DOWN)
		{
			zA += 0.2f;
			/*globalScale += 20;
			realScale = globalScale*SCALE_FACTOR_IN_10Z;*/
		}
		break;
	case 4:
		if (state == GLUT_DOWN)
		{
			zA -= 0.2f;
			/*globalScale -= 10;
			realScale = globalScale*SCALE_FACTOR_IN_10Z;*/
		}

		break;
	default:
		break;
	}
}

void OpenGLComponent::mouseMotionHandler(int x, int y)
{
	//std::cout << "motion - " << x << " - " << y << std::endl;
	if (bMooveMap)
	{
		xA -= ((float)(x - xOrigin)*2.0*X_MOUSE_MOTION_FACTOR) / (float)1024;
		yA += ((float)(y - yOrigin)*2.0*Y_MOUSE_MOTION_FACTOR) / (float)WINDOW_SIZE_HEIGHT;
		xOrigin = x;
		yOrigin = y;
	}
}


void OpenGLComponent::renderScene() {
	


	glViewport(0, 0, 1024, 1024);
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt(xA, yA, zA,//10.0f,
		xA, yA, 0.0f,
		0.0f, 1.0f, 0.0f
		);


	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	/* Handles keys pressed */
	processKeys();


	objectsComponents->drawObjects();

	


	glutSwapBuffers();



}



void OpenGLComponent::setDrawingComponents(DrawingComponents *dComponents)
{
	objectsComponents = dComponents;
}

