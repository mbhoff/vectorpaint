/*************************************************************************//**
 * @file 
 *****************************************************************************/

/** 
 *  @class Rectangle
 *  @brief This is the derived class for rectangles. It inherits functions and
 *  data from Shape and adds additional data and functionality. Based on code
 *  provided by Dr. Weiss.
 *
 *
 *  @author Mark
 *  @author Other team member
 */

// guard against multiple inclusions
#ifndef _Rectangle_H_
#define _Rectangle_H_

#include "shape.h"

// Rectangle class interface
class Rectangle : public Shape
{
    protected:
    	///Float for the width of the rectangle
        float width;
        
        ///Float for the height of the rectangle
        float height;

    public:
    	///Rectangle Constructor
        Rectangle( float x = 0.0, float y = 0.0, ColorType c = ColorType( 0 ), 
        	float cx = 0.0, float cy = 0.0, float w = 1.0, float h = 1.0 );
        	
        ///Rectangle Destructor
        ~Rectangle( );
        
        ///Move object
        void moveTo( float x, float y );
        
        ///Check if the shape contains the input point
        bool contains( float x, float y);
        
        ///Draw function
        virtual void draw( ) const;
};

#endif
