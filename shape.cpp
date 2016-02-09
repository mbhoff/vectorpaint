/*************************************************************************//**
 * @file 
 *****************************************************************************/

// include files
#include <iostream>
using namespace std;
#include <cmath>
#include "shape.h"

// Shape class implementation

// constructor
Shape::Shape( float x, float y, ColorType c, float cx, float cy ) : locX( x ), locY( y ), color( c ), centerX(cx), centerY(cy)
{}

// destructor
Shape::~Shape( )
{
}
        
//Distance to x, y
int Shape::distance(float x, float y)
{
	int d = 0;
	d += pow((x - centerX) / 2, 2);
	d += pow((y - centerY) / 2, 2);
	d = sqrt(d);
	return d;
}

//Contains
bool Shape::contains( float x, float y)
{}
// move object
void Shape::moveTo( float x, float y )
{
    locX = x;
    locY = y;
}

