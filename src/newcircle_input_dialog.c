

/************************************************************************************
	NewCircle Input Dialog Box implementation C file
	Author:             Ashis Kumar Das
	ID:                 11301002
	Email:              akd.bracu@gmail.com
*************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list.h>
#include <iup.h>




/************************************************************************************
*
*   Function Prototypes and Variable Definitions
*
*************************************************************************************/


struct CircleData_ {
	
	float x0;
	float y0;
	float radius;
	float r;
	float g;
	float b;
};

typedef struct CircleData_ CircleData;


char strX[15];                          /* Buffers for storing last user-typed values */
char strY[15];
char strR[15];
char strRed[10];
char strGreen[10];
char strBlue[10];

Ihandle *createCircleInputDialog(void);     /* Dialog creation function */

int create_cb(Ihandle *btn);                /* Callback for btnCreate Draw Circle */

int cancel_cb(Ihandle *btn);                /* Callback for btnCancel */

int txtgetfocus_cb(Ihandle *txt);           /* Callback for editable text boxes */





/************************************************************************************
*
*   Implementation of NewCircle Input Dialog Box
*
*************************************************************************************/


Ihandle *createCircleInputDialog(void) {
	
	Ihandle *dialog;
	Ihandle *lblX, *lblY, *lblR;
	Ihandle *txtX, *txtY, *txtR;
	Ihandle *lblRed, *lblGreen, *lblBlue;
	Ihandle *txtRed, *txtGreen, *txtBlue;
	Ihandle *lblHbar1, *lblHbar2;
	Ihandle *btnCreate, *btnCancel;
	Ihandle *colHbox;
	Ihandle *gridBox, *bottomHbox, *mainVbox;
	char *fRange, *zRange;

	fRange = "-1.0:1.0";                        	/* Float range for Circle Origin */
	zRange = "0.0:1.0";
	
	lblX = IupLabel("X origin (-1.0 <-> 1.0)");
	lblY = IupLabel("Y origin (-1.0 <-> 1.0)");
	lblR = IupLabel("Radius (0.0 <-> 1.0)");
	
	txtX = IupText(0);
	IupSetAttribute(txtX, "ALIGNMENT", "ACENTER");
	IupSetAttribute(txtX, "MASKFLOAT", fRange);
	IupSetAttribute(txtX, "FONTSIZE", "10");
	IupSetAttribute(txtX, "NOHIDESEL", "NO");
	IupSetAttribute(txtX, "VALUE", strX);
	IupSetCallback(txtX, "GETFOCUS_CB", (Icallback) txtgetfocus_cb);
	IupSetHandle("txtX", txtX);
	
	txtY = IupText(0);
	IupSetAttribute(txtY, "ALIGNMENT", "ACENTER");
	IupSetAttribute(txtY, "MASKFLOAT", fRange);
	IupSetAttribute(txtY, "FONTSIZE", "10");
	IupSetAttribute(txtY, "NOHIDESEL", "NO");
	IupSetAttribute(txtY, "VALUE", strY);
	IupSetCallback(txtY, "GETFOCUS_CB", (Icallback) txtgetfocus_cb);
	IupSetHandle("txtY", txtY);
	
	txtR = IupText(0);
	IupSetAttribute(txtR, "ALIGNMENT", "ACENTER");
	IupSetAttribute(txtR, "MASKFLOAT", "0.0:2.0");
	IupSetAttribute(txtR, "FONTSIZE", "10");
	IupSetAttribute(txtR, "NOHIDESEL", "NO");
	IupSetAttribute(txtR, "VALUE", strR);
	IupSetCallback(txtR, "GETFOCUS_CB", (Icallback) txtgetfocus_cb);
	IupSetHandle("txtR", txtR);
	
	gridBox = IupGridBox(lblX, txtX, lblY, txtY, lblR, txtR, 0);
	IupSetAttribute(gridBox, "ORIENTATION", "HORIZONTAL");
	IupSetAttribute(gridBox, "NUMDIV", "2");
	IupSetAttribute(gridBox, "EXPAND", "YES");
	IupSetAttribute(gridBox, "EXPANDCHILDREN", "YES");
	IupSetAttribute(gridBox, "EXPANDWEIGHT", "1.5");
	IupSetAttribute(gridBox, "NGAPLIN", "10");
	IupSetAttribute(gridBox, "SIZECOL", "1");
	IupSetAttribute(gridBox, "HOMOGENEOUSCOL", "YES");
	IupSetAttribute(gridBox, "HOMOGENEOUSLIN", "YES");
	
	lblHbar1 = IupLabel(0);
	IupSetAttribute(lblHbar1, "SEPARATOR", "HORIZONTAL");
	IupSetAttribute(lblHbar1, "EXPAND", "HORIZONTAL");
	
	lblHbar2 = IupLabel(0);
	IupSetAttribute(lblHbar2, "SEPARATOR", "HORIZONTAL");
	IupSetAttribute(lblHbar2, "EXPAND", "HORIZONTAL");
	
	lblRed = IupLabel("Red :");
	IupSetAttribute(lblRed, "EXPAND", "VERTICAL");
	
	lblGreen = IupLabel("Green :");
	IupSetAttribute(lblGreen, "EXPAND", "VERTICAL");
	
	lblBlue = IupLabel("Blue :");
	IupSetAttribute(lblBlue, "EXPAND", "VERTICAL");

	txtRed = IupText(0);
	IupSetAttribute(txtRed, "ALIGNMENT", "ACENTER");
	IupSetAttribute(txtRed, "MASKFLOAT", zRange);
	IupSetAttribute(txtRed, "FONTSIZE", "10");
	IupSetAttribute(txtRed, "NOHIDESEL", "NO");
	IupSetAttribute(txtRed, "EXPAND", "YES");
	IupSetAttribute(txtRed, "VISIBLECOLUMNS", "1");
	IupSetAttribute(txtRed, "VALUE", strRed);
	IupSetCallback(txtRed, "GETFOCUS_CB", (Icallback) txtgetfocus_cb);
	IupSetHandle("txtRed", txtRed);
	
	txtGreen = IupText(0);
	IupSetAttribute(txtGreen, "ALIGNMENT", "ACENTER");
	IupSetAttribute(txtGreen, "MASKFLOAT", zRange);
	IupSetAttribute(txtGreen, "FONTSIZE", "10");
	IupSetAttribute(txtGreen, "NOHIDESEL", "NO");
	IupSetAttribute(txtGreen, "EXPAND", "YES");
	IupSetAttribute(txtGreen, "VISIBLECOLUMNS", "1");
	IupSetAttribute(txtGreen, "VALUE", strGreen);
	IupSetCallback(txtGreen, "GETFOCUS_CB", (Icallback) txtgetfocus_cb);
	IupSetHandle("txtGreen", txtGreen);
	
	txtBlue = IupText(0);
	IupSetAttribute(txtBlue, "ALIGNMENT", "ACENTER");
	IupSetAttribute(txtBlue, "MASKFLOAT", zRange);
	IupSetAttribute(txtBlue, "FONTSIZE", "10");
	IupSetAttribute(txtBlue, "NOHIDESEL", "NO");
	IupSetAttribute(txtBlue, "EXPAND", "YES");
	IupSetAttribute(txtBlue, "VISIBLECOLUMNS", "1");
	IupSetAttribute(txtBlue, "VALUE", strBlue);
	IupSetCallback(txtBlue, "GETFOCUS_CB", (Icallback) txtgetfocus_cb);
	IupSetHandle("txtBlue", txtBlue);
	
	colHbox = IupHbox(lblRed, txtRed, lblGreen, txtGreen,
								lblBlue, txtBlue, 0);
	IupSetAttribute(colHbox, "EXPAND", "YES");
	IupSetAttribute(colHbox, "NGAP", "10");
	IupSetAttribute(colHbox, "NORMALIZESIZE", "VERTICAL");
	IupSetAttribute(colHbox, "EXPANDWEIGHT", "0.5");
	
	btnCreate = IupButton("Draw Circle", 0);
	IupSetAttribute(btnCreate, "RASTERSIZE", "100x30");
	IupSetCallback(btnCreate, "ACTION", (Icallback) create_cb);
	IupSetHandle("NewCircleWindow\btnCreate", btnCreate);
	
	btnCancel = IupButton("Cancel", 0);
	IupSetAttribute(btnCancel, "RASTERSIZE", "80x30");
	IupSetCallback(btnCancel, "ACTION", (Icallback) cancel_cb);
	IupSetHandle("NewCircleWindow\btnCancel", btnCancel);
	
	bottomHbox = IupHbox(IupFill(), btnCreate, btnCancel, 0);
	IupSetAttribute(bottomHbox, "NGAP", "7");
	IupSetAttribute(bottomHbox, "EXPAND", "HORIZONTAL");
	
	mainVbox = IupVbox(gridBox, lblHbar1, colHbox, lblHbar2, bottomHbox, 0);
	IupSetAttribute(mainVbox, "NGAP", "10");
	IupSetAttribute(mainVbox, "NMARGIN", "10x10");
	
	dialog = IupDialog(mainVbox);
	IupSetAttribute(dialog, "TITLE", "Enter Circle Properties");
	IupSetAttribute(dialog, "SHRINK", "YES");
	IupSetAttribute(dialog, "DIALOGFRAME", "YES");
	IupSetAttribute(dialog, "PARENTDIALOG", "MidpointCircleDrawWindow");
	IupSetAttribute(dialog, "DEFAULTENTER", "NewCircleWindow\btnCreate");
	IupSetAttribute(dialog, "DEFAULTESC", "NewCircleWindow\btnCancel");
	
	IupSetHandle("NewCircleWindow", dialog);
	
	return dialog;
}



int create_cb(Ihandle *btn) {
	
	extern List circleList;
	ListElem *elem;
	CircleData *circle;
	
	Ihandle *txtX, *txtY, *txtR;
	Ihandle *txtRed, *txtGreen, *txtBlue;
	char *valX, *valY, *valR;
	char *valRed, *valGreen, *valBlue;
	
	unsigned int lenX, lenY, lenR;
	unsigned int lenRed, lenGreen, lenBlue;
	
	int retval;
	unsigned int dataAvailable;
	
	txtX = IupGetHandle("txtX");                /* Get handles of the text boxes */
	txtY = IupGetHandle("txtY");
	txtR = IupGetHandle("txtR");
	txtRed = IupGetHandle("txtRed");
	txtGreen = IupGetHandle("txtGreen");
	txtBlue = IupGetHandle("txtBlue");
	
	valX = IupGetAttribute(txtX, "VALUE");      /* Get the values as strings */
	valY = IupGetAttribute(txtY, "VALUE");
	valR = IupGetAttribute(txtR, "VALUE");
	valRed = IupGetAttribute(txtRed, "VALUE");
	valGreen = IupGetAttribute(txtGreen, "VALUE");
	valBlue = IupGetAttribute(txtBlue, "VALUE");
	
	lenX = (unsigned int) strlen(valX);         /* Get the length of each value-string */
	lenY = (unsigned int) strlen(valY);
	lenR = (unsigned int) strlen(valR);
	lenRed = (unsigned int) strlen(valRed);
	lenGreen = (unsigned int) strlen(valGreen);
	lenBlue = (unsigned int) strlen(valBlue);
	
	dataAvailable = (lenX > 0) & (lenY > 0) & (lenR > 0)
					& (lenRed > 0) & (lenGreen > 0) & (lenBlue > 0);
	
	if (dataAvailable == 1) {
		
		strcpy(strX, (const char*) valX);           /* Store values for displaying again */
		strcpy(strY, (const char*) valY);
		strcpy(strR, (const char*) valR);
		strcpy(strRed, (const char*) valRed);
		strcpy(strGreen, (const char*) valGreen);
		strcpy(strBlue, (const char*) valBlue);
		
		circle = (CircleData *) malloc(sizeof(CircleData));
		
		circle->x0 = (float) atof((const char *) strX);     /* Conversion to Float */
		circle->y0 = (float) atof((const char *) strY);
		circle->radius = (float) atof((const char *) strR);
		circle->r = (float) atof((const char *) strRed);
		circle->g = (float) atof((const char *) strGreen);
		circle->b = (float) atof((const char *) strBlue);
		
		elem = list_tail(&circleList);
		list_ins_next(&circleList, elem, (const void *) circle);
		
		retval = IUP_CLOSE;                   	/* Hide + Return control to the caller */
	}                                           /* Caller is responsible for destruction */
												/* of this dialog using IupDestroy() */
	else {
		retval = IUP_DEFAULT;               	/* Stay on the screen */
	}
	
	return retval;
}



int cancel_cb(Ihandle *btn) {
	
	return IUP_CLOSE;                           /* Hides this modal dialog and */
}                                               /* Return control to the caller */
												/* Function of this dialog */


int txtgetfocus_cb(Ihandle *txt) {
	
	unsigned int count;
	
	count = (unsigned int) IupGetInt(txt, "COUNT");
	IupSetfAttribute(txt, "SELECTION", "%d:%d", 1, count + 1);
	IupFlush();
	
	return IUP_DEFAULT;
}
