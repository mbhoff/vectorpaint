/**
 *	@file
 *  @author Dr. Weiss
 */

/*
                    ***** graphics.h *****

OpenGL graphics program, illustrating use of GLUT and callback functions.

Author: Dr. Weiss
Class:  CSC300 Data Structures
Date:   Fall 2015

Modifications:
*/

// useful graphics function prototypes

// guard against multiple inclusions
#ifndef _Graphics_H_
#define _Graphics_H_

///Initialize OpenGL
void initOpenGL( void );

///Draws a line between two points
void DrawLine( float x1, float y1, float x2, float y2, const float color[] );

///Draws an unfilled rectangle
void DrawRectangle( float x1, float y1, float x2, float y2, const float color[] );

///Draws a filled rectangle
void DrawFilledRectangle( float x1, float y1, float x2, float y2, const float color[] );

///Draws an unfilled ellipse
void DrawEllipse( float xRadius, float yRadius, int x, int y, const float color[] );

///Draws a filled ellipse
void DrawFilledEllipse( float xRadius, float yRadius, int x, int y, const float color[] );

///Draws a text string at a given location
void DrawTextString( char *string, int x, int y, const float color[] );

#endif
