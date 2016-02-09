/*************************************************************************//**
 * @file 
 *****************************************************************************/
 
// include files
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <GL/freeglut.h>
#include "globals.h"
#include "callbacks.h"
#include "graphics.h"
#include "shape.h"
#include "rectangle.h"
#include "filledRectangle.h"
#include "ellipse.h"
#include "line.h"
#include "filledEllipse.h"
#include "globalVector.h"

using namespace std;
/******************************************************************************/
/*                          OpenGL callback functions                         */
/******************************************************************************/




/**************************************************************************//** 
 * @author Mark, Other team member
 * 
 * @par Description: Callback function that tells OpenGL how to redraw window.
 * First, the display is cleared. Then, the function steps through the vector
 * and calls the draw function for each shape. After drawing the shapes, the
 * function calls another function to draw the toolbar. This ensures that no
 * shapes will draw over the toolbar. Based on code provided by Dr. Weiss.
 *****************************************************************************/
// callback function that tells OpenGL how to redraw window
void display( void )
{
    // clear the display
    glClear( GL_COLOR_BUFFER_BIT );
    
    //Draw each shape
    for (int i = 0; i < shapes.size(); i++)
    {
    	shapes[i]->draw();	 
    }
    
    //Draw the toolbar
    drawToolbar();
    glFlush();
}

/**************************************************************************//** 
 * @author Dr. Weiss
 * 
 * @par Description: Callback function that tells OpenGL how to resize window. 
 * Note that this is called when the window is first created.
 * 
 * 
 * @param[in]      w - the width to resize to
 * @param[in]      h - the height to resize to
 * 
 * 
 *****************************************************************************/
// callback function that tells OpenGL how to resize window
// note that this is called when the window is first created
void reshape( int w, int h )
{
    // store new window dimensions globally
    ScreenWidth = w;
    ScreenHeight = h;

    // how to project 3-D scene onto 2-D
    glMatrixMode( GL_PROJECTION );		// use an orthographic projection
    glLoadIdentity();				// initialize transformation matrix
    gluOrtho2D( 0.0, w, 0.0, h );		// make OpenGL coordinates
    glViewport( 0, 0, w, h );			// the same as the screen coordinates
}


/**************************************************************************//** 
 * @author Mark, Other team member
 * 
 * @par Description: Callback function that tells OpenGL how to handle 
 * keystrokes. The escape or q key exit the program after deallocating the
 * memory of the shapes. The d key deletes the last shape in the vector, 
 * which is also the one drawn on top. The c key clears and deallocates all
 * shapes. Any other key will redraw the display. Based on code provided by
 * Dr. Weiss
 * 
 * 
 * @param[in]      key - tells which key was pressed
 * @param[in]      x - input mouse x
 * @param[in]      y - input mouse y
 * 
 * 
 *****************************************************************************/
// callback function that tells OpenGL how to handle keystrokes
void keyboard( unsigned char key, int x, int y )
{
	Shape *temp;
    // correct for upside-down screen coordinates
    y = ScreenHeight - y;
    switch ( key )
    {
        // Escape or q quits program
	case 'q':
	case EscapeKey:
		for (auto x : shapes)
			delete x;
	    exit( 0 );
	    break;
	//The d key deletes the top shape
	case 'd':
	{
		if (!shapes.empty())
		{
		temp = shapes.back();
		shapes.pop_back();
		delete temp;
		}
		glutPostRedisplay();
		break;
	}
	//The c key removes all shapes and deallocates the memory
	case 'c':
	{
		for (auto x : shapes)
		{
			delete x;
		}
		shapes.clear();
		glutPostRedisplay();
	}
        // anything else redraws window
	default:
	    glutPostRedisplay();
	    break;
    }
}

/**************************************************************************//** 
 * @author Mark, Other team member
 * 
 * @par Description: Callback function for mouse button click events. This
 * function draws shapes or selects tools and colors with the left click and
 * selects and moves shapes and selects colors with the right click. Global
 * variables are used to track the mouse locations between click and release. 
 * Upon release of the left click, the function will make and draw a shape only
 * if the user has already selected a tool and the colors and is clicking on
 * the drawing space. The toolbarSelection function allows the program to
 * check if the toolbar is being selected and select the appropriate tools or
 * colors. If the right button is clicked, the function calls a different
 * but similar toolbar function to select the fill color. If the right mouse is
 * clicked over the drawing area, the selectShape function will determine the 
 * closest shape that contains the clicked point and will select and move it
 * accordingly. Based on code provided by Dr. Weiss.
 * 
 * 
 * @param[in]      button - tells which button was pressed
 * @param[in]      state - tells if button is down or up
 * @param[in]      x - input mouse x
 * @param[in]      y - input mouse y
 * 
 * 
 *****************************************************************************/
void mouseclick( int button, int state, int x, int y )
{
    // correct for upside-down screen coordinates
    y = ScreenHeight - y;
    // handle mouse click events
    switch ( button )
    {
	case GLUT_LEFT_BUTTON:				// left button: should create objects
	    if ( state == GLUT_DOWN )			// press
		{
			x_click = x;
			y_click = y;
		}
	    else if ( state == GLUT_UP )		// release
		{
			x_release = x;
			y_release = y;
			//Only makes a shape if mouse is not over the toolbar and the tool 
			//and colors are selected
			if (!toolbarSelection() && toolType != -1 && 
				border != ColorType(-1) && fillColor != ColorType(-1))
			{
				makeShape();
				shapes[shapes.size() - 1]->draw();
			}
		}
	    break;

	case GLUT_RIGHT_BUTTON:				// right button: should move objects
	    if ( state == GLUT_DOWN )			// press
		{
			y_r_click = y;
			x_r_click = x;
		}
	    else if ( state == GLUT_UP )		// release
		{	
			x_r_release = x;
			y_r_release = y;
			//If the toolbar is not selected, and tool and colors are chosen,
			//call the selectShape function
			if (!toolbarSelectionR() && toolType != -1 && 
				border != ColorType(-1) && fillColor != ColorType(-1))
			{
				selectShape();
				glutPostRedisplay();
			}
		}
	    break;
    }
}

/**************************************************************************//** 
 * @author Mark, Other team member
 * 
 * @par Description: This function creates a new shape based on what tool type
 * is selected. Each different tool type has different calculations either in 
 * this function or the shape constructors that allow it to initialize with the
 * proper data. Each shape is pushed to the end of the vector as a new object.
 * 
 * 
 * 
 *****************************************************************************/
void makeShape()
{
	float height, width, min_x = ScreenWidth, min_y = ScreenHeight;
	//Do not continue if the toolType has not been selected
	if (toolType == -1)
		return;
	else if (toolType == 0)//Line
	{
		shapes.push_back(new Line(x_click, y_click, border, 0, 0, x_release,
			 y_release));
	}
	else if (toolType == 1 || toolType == 2 )	//Rectangle
	{
		//Compute the min x and y so the rectangle is always drawn from
		//lower left corner to upper right corner
		if (x_release < min_x)
			min_x = x_release;
		if (x_click < min_x)
			min_x = x_click;
		if (y_click < min_y)
			min_y = y_click;
		if (y_release < min_y)
			min_y = y_release;
		width = abs(x_click - x_release);
		height = abs(y_click - y_release);
		//Create a filled rectangle
		if (toolType == 2)
			shapes.push_back(new filledRectangle(min_x, min_y, border, 0, 0,
			width, height, fillColor ));
		//Create an unfilled rectangle
		else
			shapes.push_back(new Rectangle(min_x, min_y, border, 0, 0,
			width, height));
		
	}
	else if (toolType == 3 || toolType == 4)	//Ellipse
	{
		//Create an unfilled ellipse
		//The math for the center point and radii are included in the
		//new object initialization
		if (toolType == 3)
			shapes.push_back(new Ellipse((x_click + x_release)/2, 
				(y_click + y_release) / 2, border, 0, 0, 
				abs( x_click - x_release)/2, abs(y_click - y_release) / 2));
		//Create a filled ellipse
		else
			shapes.push_back(new filledEllipse((x_click + x_release)/2, 
				(y_click + y_release) / 2, border, 0, 0, 
				abs( x_click - x_release)/2, abs(y_click - y_release) / 2, 
				fillColor));
	}
}

/**************************************************************************//** 
 * @author Mark, Other team member
 * 
 * @par Description: This function redraws the toolbar after the screen has
 * been cleared. Each square for colors and tools is designed to be 40 x 40
 * pixels and will start drawing from the top left corner. Instead of scaling
 * the toolbar to match the window size, we chose this method so that the 
 * selections would always be a consistent size.
 * 
 * 
 *
 * 
 *****************************************************************************/
void drawToolbar()
{
	int width = 40, height = 40;
	int i = 0;
	
	//Fill Squares for Tools and Colors
	DrawFilledRectangle(0, ScreenHeight, 80, ScreenHeight - 120, Black);
	DrawFilledRectangle(0, ScreenHeight - 3 * 40, 40, ScreenHeight - 4 * 40,
		 White);
	DrawFilledRectangle(0, ScreenHeight - 4 * 40, 40, ScreenHeight - 5 * 40,
		 Black);
	DrawFilledRectangle(0, ScreenHeight - 5 * 40, 40, ScreenHeight - 6 * 40, 
		Red);
	DrawFilledRectangle(0, ScreenHeight - 6 * 40, 40, ScreenHeight - 7 * 40, 
		Green);
	DrawFilledRectangle(40, ScreenHeight - 3 * 40, 80, ScreenHeight - 4 * 40,
		 Blue);
	DrawFilledRectangle(40, ScreenHeight - 4 * 40, 80, ScreenHeight - 5 * 40, 
		Magenta);
	DrawFilledRectangle(40, ScreenHeight - 5 * 40, 80, ScreenHeight - 6 * 40, 
		Cyan);
	DrawFilledRectangle(40, ScreenHeight - 6 * 40, 80, ScreenHeight - 7 * 40, 
		Yellow);
	
	//Draw Borders for Tools and Colors
	for (i = 0; i < 7; i++)
	{
		DrawRectangle(0, ScreenHeight - i * 40, 40, ScreenHeight - (i+1)*40, 
			White);
		DrawRectangle(40, ScreenHeight - i * 40, 80, ScreenHeight - (i+1)*40,
			White);
	}
	
	//Draw Tools in their squares
	DrawRectangle (8, ScreenHeight - 40 - 8, 40 - 8, ScreenHeight - 80 + 8, 
		Red);
	DrawFilledRectangle (40 + 8, ScreenHeight - 40 - 8, 80 - 8, 
		ScreenHeight - 80 + 8, Red);
	DrawRectangle (40 + 8, ScreenHeight - 40 - 8, 80 - 8, 
		ScreenHeight - 80 + 8, Yellow);
	DrawEllipse(12, 12, 20, ScreenHeight - 100, Red);
	DrawFilledEllipse(12, 12, 60, ScreenHeight - 100, Red);
	DrawEllipse(12, 12, 60, ScreenHeight - 100, Yellow);
	DrawLine(48, ScreenHeight - 32, 72, ScreenHeight - 8, Yellow);
	
	//Draw current tool
	if (toolType == 0)
		DrawLine(8, ScreenHeight - 32, 32, ScreenHeight - 8, colors[border]);
	if (toolType == 1)
		DrawRectangle(8, ScreenHeight - 32, 32, ScreenHeight - 8, 
			colors[border]);
	if (toolType == 2)
	{
		DrawFilledRectangle( 8, ScreenHeight - 32, 32, ScreenHeight - 8, 
			colors[fillColor]);
		DrawRectangle(8, ScreenHeight - 32, 32, ScreenHeight - 8, 
			colors[border]);
	}
	if (toolType == 3)
		DrawEllipse(12, 12, 20, ScreenHeight - 20, colors[border]);
	if (toolType == 4)
	{
		DrawFilledEllipse(12, 12, 20, ScreenHeight - 20, colors[fillColor]);
		DrawEllipse(12, 12, 20, ScreenHeight - 20, colors[border]);
	}
}


/**************************************************************************//** 
 * @author Mark, Other team member
 * 
 * @par Description: This function checks the left mouse click to see if the 
 * toolbar was selected. Clicking anywhere else would allow the user to draw.
 * When selecting within the toolbar, the regions set up for the tools and 
 * colors are defined and will set the corresponding tool or color when it is
 * clicked. This function also calls the redisplay because the selected tool
 * will now need to change in the toolbar to reflect what the user will be 
 * using to draw.
 * 
 * 
 * @returns true - the user clicked on the toolbar
 * @returns false - the user clicked outside of the toolbar
 * 
 *****************************************************************************/
bool toolbarSelection(void)
{
	//Return if clicked over drawing space
	if (x_click >= 80 || y_click < ScreenHeight - 280)
		return false;
		
	//Select Tool within toolbar
	if (x_click < 80 || y_click > ScreenHeight -280)
	{
		//Left column
		if (x_click >= 0 && x_click <= 40)
		{
			if (y_click <= ScreenHeight - 40 && y_click >= ScreenHeight - 80)
				toolType = 1;	//Rectangle
			else if (y_click <= ScreenHeight - 80 && 
				y_click >= ScreenHeight - 120)
				toolType = 3;	//Ellipse
			else if (y_click <= ScreenHeight - 120 && 
				y_click >= ScreenHeight - 160)
				border = WHITE;	//White
			else if (y_click <= ScreenHeight - 160 && 
				y_click >= ScreenHeight - 200)
				border = BLACK;	//Black
			else if (y_click <= ScreenHeight - 200 && 
				y_click >= ScreenHeight - 240)
				border = RED;	//Red
			else if (y_click <= ScreenHeight - 240 && 
				y_click >= ScreenHeight - 280)
				border = GREEN;	//Green
		}
		//Right column
		if (x_click >= 40 && x_click <= 80)
		{
			if (y_click <= ScreenHeight && y_click >= ScreenHeight - 40)
				toolType = 0;	//Line	
			else if (y_click <= ScreenHeight - 40 && 
				y_click >= ScreenHeight - 80)
				toolType = 2;	//Filled Rectangle
			else if (y_click <= ScreenHeight - 80 && 
				y_click >= ScreenHeight - 120)
				toolType = 4;	//Filled Ellipse
			else if (y_click <= ScreenHeight - 120 && 
				y_click >= ScreenHeight - 160)
				border = BLUE;	//Blue
			else if (y_click <= ScreenHeight - 160 && 
				y_click >= ScreenHeight - 200)
				border = MAGENTA;//Magenta
			else if (y_click <= ScreenHeight - 200 && 
				y_click >= ScreenHeight - 240)
				border = CYAN;	//Cyan
			else if (y_click <= ScreenHeight - 240 && 
				y_click >= ScreenHeight - 280)
				border = YELLOW;//Yellow
		}
	
	}
	glutPostRedisplay();
	return true;
}

/**************************************************************************//** 
 * @author Mark, Other team member
 * 
 * @par Description: Similar to the left-click selection, this function checks
 * for right-click selection. It is a different function because the user
 * selects the fill color instead of the border color. This function has
 * regions for each color laid out based on the toolbar layout and will check
 * which one contains the mouse click, unless the click was out of the bounds
 * of the toolbar. 
 * 
 * 
 * 
 * @returns true - the user clicked on the toolbar
 * @returns false - the user clicked outside of the toolbar
 * 
 *****************************************************************************/
bool toolbarSelectionR(void)
{
	//Return if clicked over drawing space
	if (x_r_click >= 80 || y_r_click < ScreenHeight - 280)
		return false;
		
	//Select Tool within toolbar
	if (x_r_click < 80 || y_r_click > ScreenHeight -280)
	{
		//Left column
		if (x_r_click >= 0 && x_r_click <= 40)
		{
			if (y_r_click <= ScreenHeight - 120 && 
				y_r_click >= ScreenHeight - 160)
				fillColor = WHITE;	//White
			else if (y_r_click <= ScreenHeight - 160 && 
				y_r_click >= ScreenHeight - 200)
				fillColor = BLACK;	//Black
			else if (y_r_click <= ScreenHeight - 200 && 
				y_r_click >= ScreenHeight - 240)
				fillColor = RED;	//Red
			else if (y_r_click <= ScreenHeight - 240 && 
				y_r_click >= ScreenHeight - 280)
				fillColor = GREEN;	//Green
		}
		//Right column
		if (x_r_click >= 40 && x_r_click <= 80)
		{
			if (y_r_click <= ScreenHeight - 120 && 
				y_r_click >= ScreenHeight - 160)
				fillColor = BLUE;	//Blue
			else if (y_r_click <= ScreenHeight - 160 && 
				y_r_click >= ScreenHeight - 200)
				fillColor = MAGENTA;//Magenta
			else if (y_r_click <= ScreenHeight - 200 && 
				y_r_click >= ScreenHeight - 240)
				fillColor = CYAN;	//Cyan
			else if (y_r_click <= ScreenHeight - 240 && 
				y_r_click >= ScreenHeight - 280)
				fillColor = YELLOW;//Yellow
		}
	
	}
	glutPostRedisplay();
	return true;
	
}


/**************************************************************************//** 
 * @author Mark, Other team member
 * 
 * @par Description: This function determines which shape the user was trying 
 * to select. First, this function checks which shape's center was the closest
 * to the click by stepping through the vector and calling the distance
 * function.  
 *****************************************************************************/
void selectShape()
{
	int distance;
	int leastDistance = shapes[0]->distance(x_r_click, y_r_click);
	int index;
	
	//Check for closest shape to the click
	for (int i = 0; i < shapes.size(); i++)
	{
		distance = shapes[i]->distance(x_r_click, y_r_click);
		if (distance < leastDistance)
		{
			distance = leastDistance;
			index = i;
		}

	}
	
	//If the closest shape contains the click, the function will push the
	//shape to the end of the vector and then delete it from the vector.
	//Note that this does not deallocate the shape from memory
	if (shapes[index]->contains(x_r_click, y_r_click))
	{
		shapes.push_back(shapes[index]);
		shapes.erase(shapes.begin()+index);
		
		//Move the shape by the difference in the click and release
		shapes.back()->moveTo(x_r_release - x_r_click, 
			y_r_release - y_r_click);
	}	
}
