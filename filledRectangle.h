/**
 *  @file
 *	@class filledRectangle
 *	@brief This is the derived class of Rectangle and Shape. It includes 
 *  a fill color as well and a specialized draw function.
 *
 *
 *	@author Mark
 *	@author Other team member
 */




// guard against multiple inclusions
#ifndef _filledRectangle_H_
#define _filledRectangle_H_

#include "shape.h"
#include "rectangle.h"

// Rectangle class interface
class filledRectangle : public Rectangle
{
    private:
	///This is the fill color for the shape
        ColorType fillColor;

    public:
	///This is the constructor for the filledRectangle
        filledRectangle( float x = 0.0, float y = 0.0,
			ColorType c = ColorType( 0 ),float cx = 0.0,
			float cy = 0.0, float w = 1.0, float h = 1.0,
			ColorType d = ColorType(0) );
	
	///This is the deconstructor for the filledRectangle
        ~filledRectangle( );
        
        ///This is the draw function for the filledRectangle
        void draw( ) const;
};

#endif
