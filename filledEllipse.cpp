/**************************************************************************//** 
 * @file
 *****************************************************************************/


// include files
#include <iostream>
using namespace std;

#include "filledEllipse.h"
#include "graphics.h"
#include "globals.h"

// Ellipse class implementation

// constructor instantiates centerX and centerY
filledEllipse::filledEllipse( float x, float y, ColorType c, float cx, float cy, float r, float rY, ColorType d ) : Ellipse(x, y, c, cx, cy, r, rY ), fillColor(d)
{
    centerX = locX;
    centerY = locY;
}

// destructor
filledEllipse::~filledEllipse( )
{
}

// draw function draws an ellipse on top of a filled ellipse
void filledEllipse::draw( ) const
{
	DrawFilledEllipse(radiusX, radiusY, locX, locY, colors[fillColor]);
    	DrawEllipse(radiusX, radiusY, locX, locY, colors[color]);
}

