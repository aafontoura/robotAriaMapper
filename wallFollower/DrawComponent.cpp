#include "DrawComponent.h"

using namespace std;



#define X_MOUSE_MOTION_FACTOR 7.0
#define Y_MOUSE_MOTION_FACTOR 5.0

#define PIXEL_SIZE 0.5

/* ------------------------------------------------------------------*/
/*
/*						GLOBAL VARIABLES
/*
/* ------------------------------------------------------------------*/
float angle = 0.0f;

/* Camera position */
float xA = 4.0f;
float yA = 2.0f;
float zA = 10.0f;

bool keyStates[256]; // Create an array of boolean values of length 256 (0-255)  

int xOrigin = -1;
int yOrigin = -1;
bool bMooveMap = false;


positionType robotPos;

int occupationMatrix[MATRIX_X_SIZE][MATRIX_Y_SIZE];
int** testMatrix;

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

DrawComponent::DrawComponent()
{
}


DrawComponent::~DrawComponent()
{
}

void DrawComponent::setOccupationMatrix(int** ocupationMatrixInput)
{
	testMatrix = ocupationMatrixInput;
	//occupationMatrix = ocupationMatrixInput;
}

void DrawComponent::setRobotPos(float x, float y)
{
	robotPos.x = x / 100 + PIXEL_SIZE * 50;
	robotPos.y = y / 100 + PIXEL_SIZE * 50;



	testMatrix[getInvPoint(robotPos.x)][getInvPoint(robotPos.y)] = 1;




}



void DrawComponent::changeSize(int w, int h) {

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

void DrawComponent::keyPressed(unsigned char key, int x, int y) {
	keyStates[key] = true; // Set the state of the current key to pressed  
}


void DrawComponent::keyUp(unsigned char key, int x, int y) {
	keyStates[key] = false; // Set the state of the current key to not pressed  
}


/* Handles keys press */
void DrawComponent::processSpecialKeys(int key, int x, int y) {

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



void DrawComponent::mouseButtonHandler(int button, int state, int x, int y)
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

void DrawComponent::mouseMotionHandler(int x, int y)
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


/* Draw Strings */
void renderBitmapString(float x, float y, float z, char *string) {

	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
	}
}

void drawRectangle(float left, float right, float up, float down, bool filled = 0)
{
	glBegin(GL_QUADS);
	glVertex3f(left, down, 0);
	glVertex3f(left, up, 0);
	glVertex3f(right, up, 0);
	glVertex3f(right, down, 0);
	glEnd();
}

void drawSquare(float x, float y, float sideSize)
{
	drawRectangle(x - sideSize / 2, x + sideSize / 2, y + sideSize / 2, y - sideSize / 2);
}

void drawLine(float p1X, float p1Y, float p2X, float p2Y, float width = 1.0)
{
	glBegin(GL_LINES);
	glVertex3f(p1X, p1Y, 0);
	glVertex3f(p2X, p2Y, 0);
	glEnd();
}



/* Draw a circle centered in cx,cy with radius r. */
/* The circunference is drawed using line segments. the number
/* of segments used for drawing the circle is num_segments. */
void drawCircle(float cx, float cy, float r, int num_segments)
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





void drawOccupationMatrix()
{

	for (int i = 0; i < MATRIX_X_SIZE; i++)
		for (int j = 0; j< MATRIX_Y_SIZE; j++)
		{

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			if (testMatrix[i][j] == 1)
			{
				glColor4f(1.0, 1.0, 1.0, 0.8f);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else
				glColor4f(1.0 , 1.0 , 1.0 , 0.8f);

			drawRectangle(getPoint(i) - PIXEL_SIZE / 2, getPoint(i) + PIXEL_SIZE / 2, getPoint(j) + PIXEL_SIZE / 2, getPoint(j) - PIXEL_SIZE / 2);
			
		}
}

void drawRobot()
{
	glColor4f(1.0, 0.0, 0.0, 0.8f);
	drawCircle(robotPos.x, robotPos.y, PIXEL_SIZE / 5, 10);
}


void DrawComponent::renderScene() {
	


	glViewport(0, 0, 1024, 768);
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
	//processKeys();



	drawOccupationMatrix();
	drawRobot();

	glutSwapBuffers();



}
