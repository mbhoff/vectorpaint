/*************************************************************************//**
 * @file 
 *****************************************************************************/

/** 
 *  @class Shape
 *  @brief This is the base class for all derived shapes. It includes member
 *  functions as well as virtual functions which will be overloaded. Based on
 *  code provided by Dr. Weiss.
 *
 *
 *  @author Mark
 *  @author Other team member
 */



// guard against multiple inclusions
#ifndef _Shape_H_
#define _Shape_H_

// include files
#include <iostream>
using namespace std;

/// ColorType enumerated type for the border and fill colors
enum ColorType
{
    BLACK, RED, GREEN, BLUE, MAGENTA, CYAN, YELLOW, WHITE
};


class Shape
{
    protected:                    
        ///Float for the x location of the shape
        float locX;
        
        ///Float for the y location of the shape
        float locY;
        
        ///Border color of the shape
        ColorType color;
        
        ///Float for the center x of the shape
        float centerX;
        
        ///Float for the center y of the shape
        float centerY;
        
        
    public:                       
        ///Shape constructor
        Shape( float x = 0.0, float y = 0.0, ColorType c = ColorType( 0 ), 
        	float centerX = 0.0, float centerY = 0.0);

        ///Shape destructor
        virtual ~Shape( );

        ///Move the object to the input x and y
        virtual void moveTo( float x, float y );
        
        ///Checks if the shape contains the input point
        virtual bool contains( float x, float y);
        
        ///Find the distance between the shape's center and the input point
        int distance(float x, float y);

        ///Draw method
        virtual void draw() const = 0;

};

#endif
