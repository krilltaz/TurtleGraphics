/* FILE: stringoperations.h
 * AUTHOR: Kyle Notani | 19149918
 * UNIT: UCP COMP1000
 * PURPOSE: Header file associated with stringoperations.c
 */
 
#ifndef STRINGOPERATIONS_H
   #define STRINGOPERATIONS_H

   /* Converts a given string to all upper case. Allows for appropriate string
    * comparisons which check for validity 
    * */
   void stringUpperCase( char* string );
   
   /* Checks if a given string has only control characters.
    * Mainly used to check for lines in a file that contain blank lines of
    * non-printable characters and assures command parameters are validated
    * correctly */
   int stringIsCtrl( char* string );

#endif
