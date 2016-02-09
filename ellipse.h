/**
 *  @file
 *	@class Ellipse
 *	@brief This is the derived class Ellipse, which inherits functions,
 * 	and data from the parent class Shape. This class is based on code
 *	written by Dr. Weiss.
 *
 *
 *	@author Mark
 *	@author Other team member
 */

// guard against multiple inclusions
#ifndef _Ellipse_H_
#define _Ellipse_H_

#include "shape.h"
// Ellipse class interface
class Ellipse : public Shape
{
    protected:
	///float for the y radius of the Ellipse 
	float radiusY;
	///float for the x radius of the Ellipse
        float radiusX;

    public:
	///Ellipse constructor
        Ellipse( float x = 0.0, float y = 0.0,
		ColorType c = ColorType( 0 ),
		float cx = 0.0, float cy = 0.0,
		float r = 1.0, float rY = 1.0 );
	///Ellipse destructor
        ~Ellipse( );
        
    ///MoveTo function moves x and y of Ellipse
        void moveTo( float x, float y );

	///contains compares mouse coordinates to Ellipse coordinates
        bool contains(float x, float y);

	///draw function draws the shape
        virtual void draw( ) const;
};

#endif
