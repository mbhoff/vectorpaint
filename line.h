/*************************************************************************//**
 * @file 
 *****************************************************************************/

/** 
 *  @class Line
 *  @brief This class is derived from the Shape class. It adds an endpoint and
 *  replaces the virtual functions as well.
 *
 *
 *  @author Mark
 *  @author Other team member
 */



#include <iostream>

#ifndef _Line_H
#define _Line_H_

#include "shape.h"

class Line : public Shape
{
    private:
    	///Float for the endpoint x
        float endX;
        
        ///Float for the endpoint y
        float endY;

    public:
    	///Line constructor
        Line( float x = 0.0, float y = 0.0, ColorType c = ColorType( 0 ), float cx = 0.0, float cy = 0.0, float Xend = 0.0, float Yend = 0.0);
        
        ///Line destructor
        ~Line( );
        
        ///Change object's position by x and y
        void moveTo( float x, float y );
        
        ///Checks if the line contains the input point
        bool contains( float x, float y);
        
        ///Draw the line
        void draw( ) const;
};

#endif

