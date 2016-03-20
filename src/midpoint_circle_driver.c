

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iup.h>
#include <iupgl.h>
#include <list.h>



struct CircleData_ {

	float x0;
	float y0;
	float radius;
	float r;
	float g;
	float b;
};

typedef struct CircleData_ CircleData;


int cdlg_x, cdlg_y;                     /* Stores screen position of new circle dialog */

List circleList;
CircleData *data;






int main(void);

/*	GUI Toolkit related functions	*/

Ihandle * createMainWindow(void);

Ihandle *createCircleInputDialog(void);

int repaint_cb(Ihandle *canvas);

int newCircle_cb(Ihandle *btn);

int clearCanvas_cb(Ihandle *btn);

int exit_cb(Ihandle *btn);



/*	OpenGL related functions	*/

/* Function prototype for drawing circles */
void mygl_midpointCircleDraw(float x0, float y0, float radius);





Ihandle * createMainWindow(void) {                  /* Function for creating Main Window */

	const char *winTitle;
	Ihandle *bottomHbox, *mainVbox;
	Ihandle *lblTitle, *glCanvas, *btnNewCircle, *btnClose;
	Ihandle *btnClearCanvas;
	Ihandle *dialog;

	winTitle = "Graphics Homework 04\nImplementation of Midpoint CircleDraw Algorithm";
	lblTitle = IupLabel(winTitle);
	IupSetAttribute(lblTitle, "EXPAND", "HORIZONTAL");
	IupSetAttribute(lblTitle, "ALIGNMENT", "ALEFT:ACENTER");
	IupSetAttribute(lblTitle, "FONTSIZE", "10");

	glCanvas = IupGLCanvas(0);                      	/* Create our OpenGL canvas */
	IupSetAttribute(glCanvas, "EXPAND", "YES");
	IupSetAttribute(glCanvas, "BORDER", "NO");
	IupSetAttribute(glCanvas, "CANFOCUS", "NO");
	IupSetCallback(glCanvas, "ACTION", (Icallback) repaint_cb);
	IupSetHandle("GLCanvas", glCanvas);
	
	btnNewCircle = IupButton("Draw New Circle", 0);
	IupSetAttribute(btnNewCircle, "RASTERSIZE", "110x33");
	IupSetCallback(btnNewCircle, "ACTION", (Icallback) newCircle_cb);
	
	btnClearCanvas = IupButton("Clear Canvas", 0);
	IupSetAttribute(btnClearCanvas, "RASTERSIZE", "90x33");
	IupSetCallback(btnClearCanvas, "ACTION", (Icallback) clearCanvas_cb);

	btnClose = IupButton("Close", 0);               	/* Create a close button */
	IupSetAttribute(btnClose, "RASTERSIZE", "80x33");
	IupSetCallback(btnClose, "ACTION", (Icallback) exit_cb);
	IupSetHandle("btnClose", btnClose);

	bottomHbox = IupHbox(btnNewCircle, btnClearCanvas, IupFill(), btnClose, 0);
	IupSetAttribute(bottomHbox, "EXPAND", "HORIZONTAL");
	IupSetAttribute(bottomHbox, "NMARGIN", "0x5");
	IupSetAttribute(bottomHbox, "NGAP", "5");

	mainVbox = IupVbox(lblTitle, glCanvas, bottomHbox, 0);
	IupSetAttribute(mainVbox, "NMARGIN", "10x10");
	IupSetAttribute(mainVbox, "NGAP", "10");

	dialog = IupDialog(mainVbox);                   /* Create the dialog window */
	IupSetAttribute(dialog, "TITLE", "OpenGL Lab");
	IupSetAttribute(dialog, "RASTERSIZE", "425x550");
	IupSetAttribute(dialog, "SHRINK", "YES");
	IupSetAttribute(dialog, "DEFAULTESC", "btnClose");
	IupSetAttribute(dialog, "DEFAULTENTER", "btnClose");
	
	IupSetHandle("MidpointCircleDrawWindow", dialog);

	return dialog;
}


//int resize_cb(Ihandle *canvas, int newWidth, int newHeight) {
//
//	IupGLMakeCurrent(canvas);
//
//	glViewport(0, 0, (GLsizei) newWidth, (GLsizei) newHeight);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(0.0, (GLdouble) newWidth/5, 0.0, (GLdouble) newHeight/5);
//
//	return IUP_DEFAULT;
//}


int repaint_cb(Ihandle *canvas) {               /* Callback function for drawing OpenGL canvas */

	register ListElem *elem;
	register CircleData *circle;
	
	if (IupGLIsCurrent(canvas) == 0) {
		IupGLMakeCurrent(canvas);         		/* Redirect all OpenGL commands to this canvas */
		glClearColor(0.0, 0.0, 0.0, 0.0);     	/* Set a clear color (black) */
	}
	
	glClear(GL_COLOR_BUFFER_BIT);               /* Clear the buffer (canvas background) */
	glBegin(GL_POINTS);                         /* Drawing primitive: Points */

		elem = list_head(&circleList);
		while (elem != 0) {
			circle = (CircleData *) list_data(elem);
			glColor3f(circle->r, circle->g, circle->b);
			
			/* Draw a circle through midpoint circle algorithm */
			mygl_midpointCircleDraw(circle->x0, circle->y0, circle->radius);
			elem = list_next(elem);
		}

	glEnd();                                    /* Signal GL for a complete drawing */

	glFlush();                                  /* Flush GL internal buffer */

	return IUP_DEFAULT;
}



int newCircle_cb(Ihandle *btn) {
	
	Ihandle *newCircleDialog;

	newCircleDialog = createCircleInputDialog();   				/* Create the dialog */
	IupSetAttribute(newCircleDialog, "RASTERSIZE", "300x265");
	
	IupPopup(newCircleDialog, cdlg_x, cdlg_y);
	IupGetIntInt(newCircleDialog, "SCREENPOSITION", &cdlg_x, &cdlg_y);
	IupDestroy(newCircleDialog);                            	/* Destroy the dialog */
	
	repaint_cb(IupGetHandle("GLCanvas"));                   	/* Run OpenGL process */
	
	return IUP_DEFAULT;                                     	/* Return to the caller */
}



int clearCanvas_cb(Ihandle *btn) {
	
	void (*destroy) (void *data);
	
	destroy = circleList.destroy;
	
	list_destroy(&circleList);
	list_init(&circleList, destroy);
	repaint_cb(IupGetHandle("GLCanvas"));
	
	return IUP_DEFAULT;
}



int exit_cb(Ihandle *btn) {                     /* Callback function for closing application */

	return IUP_CLOSE;                           /* Closes the whole application */
}







/************************************************************************************
*
*   Main Function (starting point of the program) goes here
*
*************************************************************************************/


int main(void) {                                /* Does not take any cmdline arguments */

	Ihandle *dlg;                               /* Reference to the dialog being created */
//	CircleData *initCircle;

	cdlg_x = IUP_CENTER;
	cdlg_y = IUP_CENTER;
	list_init(&circleList, free);               /* Initialize container for circles */
	
//	initCircle = (CircleData *) malloc(sizeof(CircleData));
//	initCircle->x0 = 0.0f;
//	initCircle->y0 = 0.0f;
//	initCircle->radius = 0.5f;
//	initCircle->r = 1.0;
//	initCircle->g = 1.0;
//	initCircle->b = 0.0;
//	list_ins_next(&circleList, 0, (const void *) initCircle);

	IupOpen(0, 0);                              /* Initialize IUP GUI toolkit */
		IupGLCanvasOpen();                      /* Initialize IUP for OpenGL programming */

		dlg = createMainWindow();               /* Create the dialog in main memory */
		IupShowXY(dlg, IUP_CENTER, IUP_CENTER); /* Show the dialog to screen */

		IupMainLoop();                          /* Start processing events until close */
	IupClose();                                 /* De-allocate resources occupied by IUP */
	
	list_destroy(&circleList);                  /* Erase all data of circles from memory */

	return 0;                                   /* Return to the operating system */
}
