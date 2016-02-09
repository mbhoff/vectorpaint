/**
 *  @file
 *	@class filledEllipse
 *	@brief This is the derived class filledEllipse, which inherits functions,
 * 	and data from the parent classes Shape and Ellipse. This class is based on code
 *	written by Dr. Weiss.
 *
 *
 *	@author Mark
 *	@author Other team member
 */


// guard against multiple inclusions
#ifndef _filledEllipse_H_
#define _filledEllipse_H_

#include "shape.h"
#include "ellipse.h"

// filledEllipse class interface
class filledEllipse : public Ellipse
{
    private:
	/// fill color
        ColorType fillColor;

    public:
	///constructor instantiates the x and y values to 0
        filledEllipse( float x = 0.0, float y = 0.0, ColorType c = ColorType(0), float cx = 0.0, float cy = 0.0, float r = 0.0, float rY = 0.0, ColorType fillColor = ColorType(0) );
	
	///destructor        
	~filledEllipse( );
        
        
        /// draws filledEllipse
        void draw( ) const;
};

#endif
