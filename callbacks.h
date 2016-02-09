/**
 *	@file
 */
// OpenGL callback function prototypes

// guard against multiple inclusions
#ifndef _Callbacks_H_
#define _Callbacks_H_

//Functions created by Mark, other team member
void makeShape();
void drawToolbar();
bool toolbarSelection(void);
bool toolbarSelectionR(void);
void selectShape();

//Functions created by Dr. Weiss and modified by Mark and other team member
void display( void );
void reshape( int w, int h );
void keyboard( unsigned char key, int x, int y );
void mouseclick( int button, int state, int x, int y );

#endif
