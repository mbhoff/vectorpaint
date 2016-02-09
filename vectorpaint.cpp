/*************************************************************************//**
 * @file 
 *
 * @mainpage Vector Paint
 * 
 * @author Mark, Other team member
 * 
 * @section program_section Program Information 
 * 
 * @details This program is a simple paint program implementing OpenGL and
 * using class inheritance. When initialized, this program starts by creating a
 * window and drawing a toolbar. When the user clicks on a tool, it is 
 * selected, and once they select two colors with the left and right clicks
 * then they can start drawing. Within the callbacks file, there are a series
 * of procedures that occur during mouseclicks and keyboard presses.
 *
 * When the user draws a shape, a new shape object is added to the end of a
 * vector. Depending on the tool type selected, the shape will be a different
 * derived class from the shape object. The display function clears the display
 * and redraws the toolbar and all of the objects in the vector. Deleting an
 * object or clearing objects with the 'd' or 'c' keys will remove the items 
 * from the vector and redraw. 
 *
 * For the user to move an object, they need to right-click on it and drag the
 * mouse. The program checks all of the objects to see which ones contain the
 * clicked point, and selects the one with the closest center. Selecting an
 * object puts it at the end of the list, making it drawn last and on top of
 * the others, as well as making it the first one to be removed with 'd'. 
 *
 * Certain functions are available for each shape from the base class, such 
 * as the distance formula, while other functions need to be virtual and 
 * replaced for specific implementatino in each derived class. The rectangle 
 * and ellipse classes both have different functions for drawing and for
 * checking for a shape within its boundaries. The Filled- classes for each of
 * these shapes are able to inherit and use these special functions. 
 *
 * The program ends when the user presses 'q', 'escape' or exits the window 
 * through other means. In the case of 'q' and 'escape', the program is able
 * to properly deallocate the memory from the dynamically created shape
 * objects. 
 *
 *
 * @section compile_section Compiling and Usage 
 *
 * @par Compiling Instructions: 
 *	simply compile with makefile provided by typing "make" 
 *	or compile on the terminal with the following 
 *      g++ -o vectorpaint *.cpp -lglut -lGLU -lGL -lm -std=c++11 
 *	optionally disable flags 
 *	-Wno-unused-variable -Wno-return-type 
 *	-Wno-sign-compare -Wno-reorder 
 * 
 * @par Usage: 
   @verbatim  
   c:\> ./vectorpaint
   d:\> c:\bin\./vectorpaint
   @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 * 
 * @bug none
 * 
 * @todo none
 * 
 * @par Modifications and Development Timeline: 
   @verbatim 
   Date          Modification 
   ------------  -------------------------------------------------------------- 
   Sep 20, 2015  Toolbar and window drawn
   Sep 21, 2015  Can draw all shapes
   Sep 23, 2015  Draws all colors and can select tool
   Sep 24, 2015  Started Doxygen
   Sep 24, 2015  Finished Doxygen
   @endverbatim
 *
 *****************************************************************************/



using namespace std;

#include <cstdlib>
#include <iostream>
#include <GL/freeglut.h>
#include "graphics.h"
#include "callbacks.h"
#include "globals.h"


void initOpenGL( void );

/**************************************************************************//** 
 * @author Mark, Other team member
 * 
 * @par Description: The main function calls OpenGL initializer functions and 
 * then enters the main loop until the program ends. Based on code provided by
 * Dr. Weiss.
 * 
 *****************************************************************************/
int main( int argc, char *argv[] )
{
    // perform various OpenGL initializations
    glutInit( &argc, argv );
    initOpenGL();
    glutMainLoop();
    
    return 0;
}

/**************************************************************************//** 
 * @author Dr. Weiss
 * 
 * @par Description: Various commands to initialize OpenGL and GLUT.
 * 
 * 
 *****************************************************************************/
// various commands to initialize OpenGL and GLUT
void initOpenGL( void )
{
	// 32-bit graphics and single buffering
    glutInitDisplayMode( GLUT_RGBA | GLUT_SINGLE );	

    glutInitWindowSize( ScreenWidth, ScreenHeight );	// initial window size
    glutInitWindowPosition( 100, 50 );			// initial window  position
    glutCreateWindow( "Vector Paint" );			// window title

    glClearColor( 0.0, 0.0, 0.0, 0.0 );			// use black for glClear command

    // callback routines
    glutDisplayFunc( display );				// how to redisplay window
    glutReshapeFunc( reshape );				// how to resize window
    glutKeyboardFunc( keyboard );			// how to handle key presses
    glutMouseFunc( mouseclick );			// how to handle mouse events
}
 
