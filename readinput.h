/* FILE: readinput.h
 * AUTHOR: Kyle Notani | 19149918
 * UNIT: UCP COMP1000
 * PURPOSE: Header file associated with readinput.c
 */

#ifndef READINPUT_H
   #define READINPUT_H
   
   #include "linkedlist.h"
   
   /* Maximum number of characters in each line to be stored temporarily */
   #define BUFFER_LENGTH 101
   
   /* Required minimum size in bytes for file to not be empty */
   #define MIN_FILE_DATA 1

   /* Maximum number of arguments for TurtleGraphics to work
    * (includes name of executable file) */
   #define MAX_ARG 2

   /* Maxmimum list of possible command errors to be identified in file 
    * reading */
   #define MAX_ERRORS 3

   /* Max number of characters required to allocate for single command name 
    * string (considers any control characters such as new line + null
    * terminator) */
   #define MAX_CMD_NAME 11

   /* Maximum number of significant digits based on size of max numeric data
    * type on a 64 bit machine (considers any control characters such as
    * new line + null terminator )
    */
   #define MAX_DIGITS 18

   /* Boolean Definitions */
   #define FALSE 0
   #define TRUE !FALSE

   /* Inserts any valid command read in into the linked list */
   void storeCommand( char* line, LinkedList* list );

#endif
