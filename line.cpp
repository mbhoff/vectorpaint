/*************************************************************************//**
 * @file 
 *****************************************************************************/

#include <iostream>
using namespace std;

#include "line.h"
#include "graphics.h"
#include "globals.h"
#include <cmath>

// Line class implementation

// constructor
Line::Line( float x, float y, ColorType c, float cx, float cy, float Xend, float Yend ) : Shape(x, y, c, cx, cy), endX(Xend), endY(Yend)
{
	cx = (endX+x)/2;
	cy = (endY+y)/2;
}

// destructor
Line::~Line( )
{
}

// must override pure virtual Shape::draw() method to instantiate class
void Line::draw( ) const
{
    DrawLine(locX, locY, endX, endY, colors[color]);
}

//Checks for containment of the input point
bool Line::contains( float x, float y)
{
	//Creates a slope between endpoints
	float slope = (endY - locY) / (endX - locX);
	
	//Checks if the selection is within the shapes boundaries
	if (x >= locX && x <= endX && y >= locY && y <= endY)
		{
		//Checks if the selected point is actually where the line should be
		if ((x - locX) * slope == (y - locY))
			return true;
		}
	return false;

}

//Change the line by the amount input for x and y
void Line::moveTo( float x, float y )
{
	locX += x;
	locY += y;
	centerX = (endX+x)/2;
	centerY = (endY+y)/2;
}


