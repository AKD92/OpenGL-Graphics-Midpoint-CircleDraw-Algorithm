

/************************************************************************************
	Midpoint CircleDraw Algorithm Implementation C file
	Floating Point Version
	Author:             Ashis Kumar Das
	ID:                 11301002
	Email:              akd.bracu@gmail.com
*************************************************************************************/


#include <stdio.h>
#include <GL\gl.h>
#include <GL\glu.h>

#define FLOAT_DIFF_VALUE 0.001




/************************************************************************************
*
*   Function Prototypes and Variable Definitions
*
*************************************************************************************/



static void mygl_drawCirclePoint(float x, float y);

static void mygl_drawCirclePointOrigin(float x0, float y0, float x, float y);

void mygl_midpointCircleDraw(float x0, float y0, float radius);

void mygl_midpointCircleDraw_1(float x0, float y0, float radius);

void mygl_midpointCircleDraw_2(float x0, float y0, float radius);

//void mygl_midpointCircleDrawSOrder(float radius);





/************************************************************************************
*
*   Implementation of Midpoint CircleDraw Algorithm
*	Floating Point Version
*
*************************************************************************************/



static void mygl_drawCirclePoint(float x, float y) {

	glVertex2f(x, y);
	glVertex2f(y, x);
	glVertex2f(y, -1.0 * x);
	glVertex2f(x, -1.0 * y);
	glVertex2f(-1.0 * x, -1.0 * y);
	glVertex2f(-1.0 * y, -1.0 * x);
	glVertex2f(-1.0 * y, x);
	glVertex2f(-1.0 * x, y);

	return;
}


static void mygl_drawCirclePointOrigin(float x0, float y0, float x, float y) {
	
	glVertex2f(x0 + x, y0 + y);
	glVertex2f(x0 + y, y0 + x);
	glVertex2f(x0 + y, y0 + -1.0 * x);
	glVertex2f(x0 + x, y0 + -1.0 * y);
	glVertex2f(x0 + -1.0 * x, y0 + -1.0 * y);
	glVertex2f(x0 + -1.0 * y, y0 + -1.0 * x);
	glVertex2f(x0 + -1.0 * y, y0 + x);
	glVertex2f(x0 + -1.0 * x, y0 + y);
	
	return;
}


void mygl_midpointCircleDraw(float x0, float y0, float radius) {
	
//	mygl_midpointCircleDraw_1(x0, y0, radius);
	mygl_midpointCircleDraw_2(x0, y0, radius);
//	mygl_midpointCircleDrawSOrder(x0, y0, radius);
	
	return;
}


void mygl_midpointCircleDraw_1(float x0, float y0, float radius) {

	float x, y, d;

	x = 0.0;
	y = radius;
	d = 5.0  - 4.0 * radius;
	mygl_drawCirclePointOrigin(x0, y0, x, y);       /* Using 8-way symmetry */

	while (x < y) {
		if (d < 0) {
			d = d + (2.0 * x + 3.0 * FLOAT_DIFF_VALUE) * 4.0;
			x = x + FLOAT_DIFF_VALUE;
		}
		else {
			d = d + (2.0*x - 2.0*y + 5.0 * FLOAT_DIFF_VALUE) * 4.0;
			x = x + FLOAT_DIFF_VALUE;
			y = y - FLOAT_DIFF_VALUE;
		}
//		mygl_drawCirclePoint(x, y);
		mygl_drawCirclePointOrigin(x0, y0, x, y);
	}

	return;
}



void mygl_midpointCircleDraw_2(float x0, float y0, float radius) {
	
	float x, y, d;
	
	x = radius;
	y = 0;
	d = 5.0 - 4.0 * radius;
	mygl_drawCirclePointOrigin(x0, y0, x, y);       /* Using 8-way symmetry */
	
	while (y < x) {
		if (d < 0) {
			d = d + (2.0 * y + 3.0 * FLOAT_DIFF_VALUE) * 4.0;
			y = y + FLOAT_DIFF_VALUE;
		}
		else {
			d = d + (2.0*y - 2.0*x + 5.0 * FLOAT_DIFF_VALUE) * 4.0;
			x = x - FLOAT_DIFF_VALUE;
			y = y + FLOAT_DIFF_VALUE;
		}
//		mygl_drawCirclePoint(x, y);
		mygl_drawCirclePointOrigin(x0, y0, x, y);
	}
	
	return;
}


void mygl_midpointCircleDrawSOrder(float radius) {
	
	float x, y, d, dE, dSE;
	
	x = 0.0;
	y = radius;
	d = 1.0 - radius;
	dE = 3.0;
	dSE = -2.0 * radius + 5.0;
	mygl_drawCirclePoint(x, y);                     /* Using 8-way symmetry */
	
	while (y > x) {
		if (d < 0.0) {
			d += dE;
			dE += 2.0;
			dSE += 2.0;
		}
		else {
			d += dSE;
			dE += 2.0;
			dSE += 4.0;
			y-= FLOAT_DIFF_VALUE;
		}
		x+=FLOAT_DIFF_VALUE;
		mygl_drawCirclePoint(x, y);
	}
	
	return;
}
