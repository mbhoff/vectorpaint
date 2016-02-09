
/** 
 *  @file
 *  @brief This file contains global variables for various functions, as well
 *  as the colors and colors array that can be indexed by a ColorType enum. 
 *  The click and release variables hold data that can be used between
 *  functions.
 *
 *
 *  @author Mark
 *  @author Other team member
 *  @author Dr. Weiss
 */


#ifndef _Globals_H_
#define _Globals_H_



///Define Escape keypress
const int EscapeKey = 27;




// colors

///Black
const float Black[]	= { 0.0, 0.0, 0.0 };

///Red
const float Red[]	= { 1.0, 0.0, 0.0 };

///Green
const float Green[]	= { 0.0, 1.0, 0.0 };

///Blue
const float Blue[]	= { 0.0, 0.0, 1.0 };

///Magenta
const float Magenta[]	= { 1.0, 0.0, 1.0 };

///Cyan
const float Cyan[]	= { 0.0, 1.0, 1.0 };

///Yellow
const float Yellow[]	= { 1.0, 1.0, 0.0 };

///White
const float White[]	= { 1.0, 1.0, 1.0 };

///Colors array for converting from ColorType to floats for draw functions
extern const float colors[8][3];




// global vars

///Screen width
extern int ScreenWidth;

///Screen Height
extern int ScreenHeight;

///Left mouse click x
static int x_click;

///Left mouse click y
static int y_click;

///Left mouse release x
static int x_release;

///Left mouse release y
static int y_release;

///Right mouse click x
static int x_r_click;

///Right mouse click y
static int y_r_click;

///Right mouse relase x
static int x_r_release;

///Right mouse release y
static int y_r_release;

#endif
