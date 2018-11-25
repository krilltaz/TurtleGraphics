/* FILE: structset.h
 * AUTHOR: Kyle Notani | 19149918
 * UNIT: UCP COMP1000
 * PURPOSE: Header file associated with storing series of data grouped
 *          into a struct to easily pass around for core drawing operations.
 */

#ifndef STRUCTSET_H
   #define STRUCTSET_H
   
   /* Stores crucial data to maintain current state of graphics during drawing */
   typedef struct
   {
      /* Current Coordinates */
      double x;
      double y;
      /* Current Angle */
      double angle;
      /* Current Foreground Colour */
      int fgColour;
      /* Current Background Colour */
      int bgColour;
      /* Current Pattern */
      char pattern;
   } GraphicsState;

   /* Stores data of commands from command file input */
   typedef struct
   {
      /* Command Name */
      char* name;
      /* Associated Value */
      char* value;
   } Command;

#endif
