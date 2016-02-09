/**************************************************************************//** 
 * @file
 *****************************************************************************/

#include "globalVector.h"

//instatiates the shape vector
vector<Shape*>shapes;

// initializes the tooltype to -1
float toolType = -1; //-1 = none, 0 = line, 1 = rectangle, 2 = FilledRectangle, 3 = ellipse, 4 = filled Ellipse

//initializes the fill color to -1
ColorType fillColor = ColorType(-1);

//initializes the fill color to -1
ColorType border = ColorType(-1);

