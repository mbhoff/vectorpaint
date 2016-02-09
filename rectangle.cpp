/*************************************************************************//**
 * @file 
 *****************************************************************************/



// include files
#include <iostream>
using namespace std;

#include "rectangle.h"
#include "graphics.h"
#include "shape.h"
#include "globals.h"

// Rectangle class implementation
Rectangle::Rectangle( float x, float y, ColorType c, float cx, float cy, 
	float w, float h ) : Shape( x, y, c, cx, cy ), width( w ), height( h )
{
	centerX = locX + width / 2;
	centerY = locY + height / 2;
}

// destructor
Rectangle::~Rectangle( )
{}

//Change x and y by input values
void Rectangle::moveTo( float x, float y )
{
	locX += x;
	locY += y;
	centerX = locX + width / 2;
	centerY = locY + height / 2;
}
//Draw the shape
void Rectangle::draw( ) const
{
    DrawRectangle(locX, locY, locX + width, locY + height, colors[color] );
}

//Checks if the shape contains the input point
bool Rectangle::contains( float x, float y)
{
	if (x >= locX && x <= locX + width && y >= locY && y <= locY + height)
		return true;
	return false;
}
