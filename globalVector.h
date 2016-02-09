/**
 *	@file
 *	@brief This is the header file for the global vectors.
 *
 *
 *	@author Mark
 *	@author Other team member
 */


#ifndef _GlobalsV_H_
#define _GlobalsV_H_

#include <vector>
#include "shape.h"

///this vector holds the shapes
extern vector<Shape*>shapes;

///this float stores the tooltype value
extern float toolType;

///stores the fill color
extern ColorType fillColor;

///stores the border color
extern ColorType border;

#endif
