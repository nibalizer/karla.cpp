//Spencer Krum
//CS161 Assignment #3
//March 10, 2010
//DBAD Licencse 
//Using OpenGL(glut) for graphics
//gl is for openGl functions, GLU for openGL utility, and GLUT for openGL Utility Toolkit

#include <iostream>
#include <stdlib.h>
#include <string>

#include <GL/glut.h>

using namespace std;
/*
typedef struct _color {
	float r;
	float g;
	float b;
} kolor;

kolor corners[4] = {{0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}};

enum CORNERS = {topleft, topright, bottomright, bottomleft};
*/
float _xangle = 30.0f;			//through what angle are we rotating our figurine? --autually no
float _yangle = 30.0f;			//through what angle are we rotating our figurine? --autually no
float _scale = 0.1f;			//by what factor do we scale our figurine?	--actually no
float _xtranslate = 0.0f;		//move the object around in x , change every value to glvertex3f by this
float _ytranslate = 0.0f;		//move the object around in y
float _ztranslate = 0.0f;		//move the object around in z

const int RGB = 3;
const int VERTICIES = 4;
float _theColor[VERTICIES][RGB] = {	{0.85f, 0.00f, 0.00f}, 	//multidimensional array of floats to hold the RGB values for the verticies 
					{0.00f, 1.00f, 0.00f},
					{0.00f, 0.00f, 0.00f},
					{0.25f, 0.25f, 0.25f}};
int verticie = 0;
int color = 0;


bool growing = true;			//getting bigger or not
bool changingSize = true;		//changing Size or not

int xsign = -1;				//sets direction of rotation about x
int ysign = -1;				//sets direction of rotation about y



void handleKeypress (unsigned char key, int x, int y)
{
	//function to deal with keyboard input, x and y are mouse positions (for later?)
	switch (key) {
		case 27: 				//27 is ascii for escape key
			exit(0); 			//its nice to let people quit if they want to
			break; 				//not really necessary, but we all love continuity 
		case 44: 				//44 is ascii for comma , which is lowercase for left carrot < which we will be using to rotate our figurine left
			ysign = -1;			//sets direction of rotation about x axis
			break;
		case 46: 				//46 is ascii for period . which is lowercase for right carrot >  which we will be using to rotate our figurine right
			ysign = 1;			//sets direction of rotation about x axis
			break;
		case 109:				//109 is ascii for m
			xsign = -1;			//sets direction of rotation about y axis
			break;
		case 110:				//110 is ascii for n
			xsign = 1;			//sets direction of rotation about y axis
			break;
		case 111:				// 111 is ascii for o, lets the user pause the spinning for a second.
			ysign = 0;
			xsign = 0;
			break;
		case 114:				//114 is ascii for o
			_xangle = 0.0f;
			_yangle = 0.0f;
			changingSize = false;
			_ytranslate = 0.0f;
			_xtranslate = 0.0f;
			_ztranslate = 0.0f;
			break;
		case 99:				//99 is ascii for c
			changingSize = !changingSize;	//toggle the grow/shrink behavior
			break;
			
			
		case 119:				//119 is ascii for w
			_ytranslate += -0.5;		//move up .5 units
			break;
		case 115:				//115 is ascii for s
			_ytranslate += 0.5;		//move down .5 units
			break;
		case 97:				//97 is ascii for a
			_xtranslate += -0.5;		//move left .5 units
			break;
		case 100:				//100 is ascii for d
			_xtranslate += 0.5;		//move right .5 units
			break;
		case 122:				//122 is ascii for z
			_ztranslate += 0.5;		//move back half a unit
			break;
		case 120:				//120 is ascii for x
			_ztranslate += -0.5;		//move up half a unit
			break;
		case 102:				//102 is ascii for f
			
			if (verticie == 3){
			verticie = 0;
			}
			else{
			verticie += 1;
			}
		case 103: 				//103 is ascii for g
			if (color == 2){
			color = 0;
			}
			else {
			color += 1;
			}
		case 116: 				//116 is ascii for t
			if (_theColor[verticie][color] < 1.0f){		//color values are between 1 and zero
			_theColor[verticie][color] += 0.25f;		//set the color
			}
			break; 				
		case 121:				//116 is ascii for y
			if (_theColor[verticie][color] > 0.0f){		//color values are between 1 and zero
			_theColor[verticie][color] -= 0.25f;		//set the color
			}
			break;

	}
}

//OpenGl goodness, initalzing 3d, layering, colors
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}


//you want to be able to resize the window? Good thing this function is here!
void handleResize(int w, int h){
	glViewport(0, 0, w, h); 			//set the viewport, affine transformation is involved
	glMatrixMode(GL_PROJECTION); 			//applies subsequent matrix opperations to the projection matrix stack, which means very little to me so far, but commented for posterity
	glLoadIdentity(); 				//replaces the current matrix with the identity matrix
	gluPerspective(	45.0,  				//camera angle
			(double)w / (double)h,  	//width to height ratio
			1.0,				//near z clipping coordinate			
			200.0);				//far z clipping coordinate
}

void update (int value){				//the timer/update function, the value is always zero, glut things, hand waving 
	
	_yangle += (2.0f * ysign);			//makes for incremental y rotation in degrees, with direction
	if (_yangle > 360) {				//allows for continuous rotation
		_yangle -= 360;
	}
	_xangle += (2.0f * xsign);			//same for x
	if (_xangle > 360) {
		_xangle -= 360;
	}
	if (_scale > 3.0f){				//grows and shrinks the object incrementally
	growing = false; 
	}
	if (_scale < 0.02f){
	growing = true;
	}
	if (changingSize){				//turn off and on growing
	if (growing) {
	_scale += 0.01f;
	}
	else {
	_scale -= 0.01f;
	}
	}
	
	
	
	glutPostRedisplay(); 				//tell glut the scene has changed
	glutTimerFunc(25, update, 0);			//tell glut to update again in 25 milliseconds, the function asks glut to call itself again in 25 seconds , recursion?

}

//a little function to write text, there is only display one character at a time, which is sort of lame
void bitmapString(	float x, //accepts coordinates, where to put the word
			float y,
			float z,
			char *text) { //*text is a pointer its value is the address of the start of the text to print out
	char *p;
	glRasterPos3f(x, y, z);	 //glutbitmapcharacter will automatically advance this one step per character
	
	for (p = text; *p !='\0'; p++){ // move along the memory 
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *p); //write down the value in the memory
	}
}


//draw the scene!
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clears the last draw, sneak a | in there for ... idunno .. lost a fair ammount of time here on it though ...(the binary OR i mean)
	glMatrixMode(GL_MODELVIEW); 			//switch the mode back to modelview
	glLoadIdentity();				//replaces the current matrix with the identity matrix
	glTranslatef(0.0f, 0.0f, -5.0f);		//move forward 5 units, (move what forward?)
	
	glPushMatrix();					//save what we've done so far
	glTranslatef(_xtranslate, _ytranslate, _ztranslate); 		//move to center of trapezoid
	glRotatef( _yangle, 0.0f, 1.0, 0.0f);		//rotate though _angle about the Y axis	
	glRotatef(_xangle,  1.0f, 0.0f, 0.0f);
	glScalef(_scale, _scale, _scale);		//scale x y and z to _scale 

	glBegin(GL_QUADS);
	
	//Trapezoid
	glColor3f(_theColor[0][0], _theColor[0][1], _theColor[0][2]);
	glVertex3f(-0.7f, -0.5f, 0.0f);
	glColor3f(_theColor[1][0],_theColor[1][1], _theColor[1][2]);	
	glVertex3f(0.7f,-0.5f,0.0f);
	glColor3f(_theColor[2][0], _theColor[3][1], _theColor[2][2]);
	glVertex3f(0.4f, 0.5f, 0.0f);
	glColor3f(_theColor[3][0], _theColor[3][1],_theColor[3][2]);
	glVertex3f(-0.4f, 0.5f, 0.0f);
	
	glEnd();
	
	glPopMatrix();					//undo the move to the center of the trapezoid
	glPushMatrix();					//again, saving state
	
	glColor3f(1.0f, 1.0f, 1.0f);
	char title[] = "Assignment 3 - Spencer Krum";	//output to user
	bitmapString(-2.0f, 1.5f, 0.0f, title);
	char welcome[] = "Welcome! You can exit with the escape key.";
	bitmapString(-2.0f, -1.0f, 0.0f, welcome);
	char line1[] = "Use <,>,m, n, and o to control rotation.";
	bitmapString(-2.0f, -1.25f, 0.0f, line1);
	char line3[] = "Use t,y to change color, f to select a corner, and g to select Red, Blue or Green.";
	bitmapString(-2.0f, -2.00f, 0.0f, line3);
	char line2[] = "Use w,a,s, and d  to move the piece in space.";
	bitmapString(-2.0f, -1.5f, 0.0f, line2);
	char line4[] = "Use r to reset and c to toggle growing/shrinking behavior.";
	bitmapString(-2.0f, -1.75f, 0.0f, line4);
	glutSwapBuffers(); 			//sends the scene off to the screen
}

//the programs main
int main(int argc, char** argv) {  //I did not come up with the double asterisks. I will change this comment if/when i figure out what's goin on 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500); 		//this is self-explanatory 
	glutCreateWindow("Assignment #3");
	initRendering();
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	glutMainLoop();
	return 0; //doesn't return though
}
	


