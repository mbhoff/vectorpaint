/**************************************************************************//** 
 * @file
 *****************************************************************************/
#include <iostream>
using namespace std;

#include "filledRectangle.h"
#include "graphics.h"
#include "shape.h"
#include "globals.h"

// Rectangle class implementation

// constructor sets instantiates centerX and centerY
filledRectangle::filledRectangle( float x, float y, ColorType c, float cx, float cy, float w, float h, ColorType d ) :
    Rectangle( x, y, c, cx, cy, w, h ), fillColor(d)
{
	centerX = locX + width / 2;
	centerY = locY + height / 2;
}

// destructor
filledRectangle::~filledRectangle( )
{
}

// draws rectangle on top of filled rectangle
void filledRectangle::draw( ) const
{
    DrawFilledRectangle(locX, locY, locX + width, locY + height, colors[fillColor] );
    DrawRectangle(locX, locY, locX + width, locY + height, colors[color]);
}
