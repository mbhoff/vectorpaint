/**************************************************************************//** 
 * @file
 *****************************************************************************/

// include files
#include <iostream>
using namespace std;

#include "ellipse.h"
#include "graphics.h"
#include "globals.h"
#include <cmath>

// Ellipse class implementation

// constructor
Ellipse::Ellipse( float x, float y, ColorType c, float cx, float cy, float r, float rY ) : Shape(x, y, c, cx, cy), radiusX( r ), radiusY( rY )
{
    centerX = locX;
    centerY = locY;
}

// destructor
Ellipse::~Ellipse( )
{
}

// draws the ellipse
void Ellipse::draw( ) const
{
    DrawEllipse(radiusX, radiusY, locX, locY, colors[color]);
}

//comparse mouse coordinates and ellipse area
bool Ellipse::contains(float x, float y)
{
	float op1, op2;
	op1 = pow(x - locX, 2) / pow(radiusX, 2);
	op2 = pow(y - locY, 2) / pow(radiusY, 2);
	return (op1 + op2 <= 1);
}

//moves the ellipse to dragged mouse position
void Ellipse::moveTo( float x, float y )
{
	locX += x;
	locY += y;
	centerX =locX;
	centerY =locY;
}
