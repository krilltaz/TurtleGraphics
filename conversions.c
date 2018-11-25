/* FILE: conversions.c
 * AUTHOR: Kyle Notani | 19149918
 * UNIT: UCP COMP1000
 * PURPOSE: Used to perform a series of miscellaneous conversions for
 *          assisting the drawing process for TurtleGraphics.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "conversions.h"

 
/* NAME: defineCoordinates()
 * PURPOSE:    Converts angles and distances to (x, y) coordinates for commands
 *             that require coordinates to perform drawing on a 2D space.
 *             We must define a set of end x and y coordinates for these commands 
 *             to have a destination to point at to plot.
 * HOW IT WORKS:  Uses the cos() and sin() functions from the math.h library
 *                applying trigonometry to identify x and y coordinates.
 *
 * RELATIONS:  
 *    drawLine() - Called by drawLine() to identify (x, y) coordinates to perform
 *                 line drawing based on distance.
 *    move() - Called by move() to identify (x, y) coordinates to move the cursor
 *             to the coordinates.
 * IMPORTS:
 *    x0   Starting x coordinate.
 *    y0   Starting y coordinate.
 *    x1   Ending x coordinate.
 *    y1   Ending y coordinate.
 *    angle    The current angle to identify the direction to where coordinates 
 *             will lead to.
 *    distance    The distance from the starting coordinates(x0, y0) to the 
 *                ending coordinates (x1, y1).
 * EXPORTS:
 *    none
 */

void defineCoordinates( double* x0, double* y0, double* x1, double* y1, double* angle, double* distance )
{
   double radianCos = cos( RADIAN( *angle ) );
   double radianSin = sin( RADIAN( *angle ) );

   /* Set x1 and y1 coordinates */
   *x1 = ( ( *distance * radianCos ) + *x0 );
   *y1 = ( *y0 - ( *distance * radianSin ) );
}


/* NAME: round()
 * PURPOSE: Rounds the series of real-values coordinates to nearest integer 
 *          values.
 * HOW IT WORKS: Gets the floor of a real value x and adds 0.5 to round it to 
 *               the closes integer value.
 *               eg) 2.51 + 0.5 = 3.01
 *                   floor of 3.01 = 3 which is 2.51 rounded to nearest integer 
 *                   value.
 * RELATIONS:
 *    line() - Used by line to draw coordinates based on x and y starting and 
 *             finishing coordinates, rounded to nearest integer values.
 * IMPORTS:
 *    x  Any real value
 * EXPORTS:
 *    rounded  x rounded to nearest integer.
 */

int round( double x )
{
   int rounded;
   rounded = floor( x + 0.5 );

   return rounded;
}



/* NAME: defineAngle()
 * PURPOSE: Defines an angle within 360 degrees.
 * HOW IT WORKS: Mods the current angle passed in by 360 to ensure it's within 
 *               360 degrees
 * RELATIONS:
 *    rotate() - Used by rotate to define a given angle each time a command 
 *               requests a rotate.
 * IMPORTS:
 *    inAngle  - Current angle after a rotate command.
 *
 * EXPORTS:
 *    the angle ensured within 360 degrees.
 */
 
double defineAngle( double inAngle )
{
   return fmod( ( fmod( inAngle, 360 ) + 360 ), 360 );
}


