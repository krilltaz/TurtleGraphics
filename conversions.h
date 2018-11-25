/* FILE: conversions.h
 * AUTHOR: Kyle Notani | 19149918
 * UNIT: UCP COMP1000
 * PURPOSE: Header file associated with conversions.c
 */

#ifndef CONVERSIONS_H
   #define CONVERSIONS_H   
   
   /* The value of PI */
   #define PI 3.141592653589793238462643383279502

   /* Macro defintion conversion from degrees to radians */
   #define RADIAN(d) ( ( d ) * ( PI / 180 ) )

   /* Converts angles and distances to (x, y) coordinates for commands
    * that require coordinates to perform drawing on a 2D space.
    */
   void defineCoordinates( double* x0, double* y0, double* x1, double* y1, double* angle, double* distance );
   
   /* Rounds the series of real-values coordinates to nearest 
    * integer values.
    */
   int round( double x );

   /* Defines an angle within 360 degrees. */
   double defineAngle( double angle );

#endif
