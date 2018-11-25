/* FILE: draw.h
 * AUTHOR: Kyle Notani | 19149918
 * UNIT: UCP COMP1000
 * PURPOSE: Header file associated with draw.c
 */

#ifndef DRAW_H
   #define DRAW_H

   #include "linkedlist.h"
   #include "structset.h"
   
   /* Boolean Conditions */
   #define FALSE 0
   #define TRUE !FALSE

   
   /* Handles the deciding operation for what command function to call based
    * on list contents writing the draw process into a graphics.log file.
    */
   void draw( LinkedList* list );
   
   
   /* Commences the draw command. Draw a line on the terminal based on current 
    * angle and distance.
    * Uses trigonometetry to maintain coordinate locations on the terminal
    * 2D space to draw from start to finish. Each draw maintains the current x
    * and y values at the current state assuring following commands continue 
    * along where the cursor is located.
    */
 
   void drawLine( Command* cmd, GraphicsState* current, double* prevX, double* prevY );  
   
   /* Commences the move command. Moves the cursor based on current angle and 
    * distance.
    * Uses trigonometetry to maintain coordinate locations on the terminal
    * 2D space to move from start to finish. Each move maintains the current x
    * and y values at the current state assuring following commands continue along
    * where the cursor is located.
    */
   void move( Command* cmd, GraphicsState* current, double* prevX, double* prevY );
   
   
   /* Rotates the angle based on rotate command ensuring the rotation is within 
    * 360 degrees.
    */
   void rotate( Command* cmd, GraphicsState* current );
   
   
   /* Sets the foreground colour of the terminal. */
   void changeFgColour( Command* cmd, GraphicsState* current );
   
   
   /* Sets the background colour of the terminal. */
   void changeBgColour( Command* cmd, GraphicsState* current );
   
   
   /* Sets the pattern (character) to be drawn with on the terminal. */
   void setPattern( Command* cmd, GraphicsState* current );

   
   /* Allows line() in effects.c to plot a simple character onto the screen. */
   void plotPoint( void* plotData );

#endif
