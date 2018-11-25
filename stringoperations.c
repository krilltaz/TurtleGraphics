/* 
 * FILE: stringoperations.c
 * AUTHOR: Kyle Notani | 19149918
 * UNIT: UCP COMP1000
 * PURPOSE: Perform operation(s) specifically to string modifications.
 *          Mainly utilised by other larger functions to assist on string 
 *          identification and validity.
 * OTHER: -1 Evaluates to true, 0 Evaluates to false.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stringoperations.h"


/* NAME: stringUpperCase()
 * PURPOSE:    Converts a string to upper case. Allows for appropriate string 
 *             comparisons which check for validity.
 * HOW IT WORKS:  Checks each character to see if its corresponding numerical value
 *                is within the range of any lower case letters.
 *                Any character representing a lower case value will be converted
 *                to its upper case correspondent.
 * RELATIONS:  
 *    validateCommandName() - To identify if a command text within a line read
 *                            in from a file matches a correct command name.
 *    draw() - Identify which TurtleGraphics command operation to commence
 *             during drawing stage.
 * IMPORTS:
 *    string   A string to be converted to all upper case.
 * EXPORTS:
 *    none
 *
 * SELF-CITE: The following function stringUpperCase() has been submitted for
 *            Worksheet 4: Arrays and String as practical work on date 19/09/18,
 *            time: 15:52
 */

void stringUpperCase( char* string )
{
   int ii;
   /* Length of string */
   int length = strlen( string );

   /* Loop through each character */
   for ( ii = 0; ii < length; ii++ )
   {
      if ( 97 <= string[ii] && string[ii] <= 122 )
      {
         string[ii] -= 32;
      }
   }
}




/* NAME: stringIsCtrl()
 * PURPOSE: Used to check if each character within a string is a control 
 *          character,returning a value to check.
 *          Mainly used to check for lines in a file that contain blank lines of
 *          non-printable characters and assures command parameters are validated
 *          correctly.
 * HOW IT WORKS: Loops through each character within a string and checks if all
 *               characters are control characters by using iscntrl() and includes
 *               blank whitespace as a check to ignore any whitespace characters.
 *               If all ctrl characters found matches the length of the string
 *               then the string entirely has control characters.
 * RELATIONS:
 *    main() - Used in main to first check if a line contains all control 
 *             characters to indicate blank lines.
 *    validator.c parameter functions - Used to check if a other parameters 
 *                                      after tokenising are just blank lines, 
 *                                      only treating printable characters as 
 *                                      valid parameters checks.
 * IMPORTS:
 *    string   A string to be converted to all upper case.
 * EXPORTS:
 *    none
 */
         
int stringIsCtrl( char* string )
{
   int ii;
   int isCtrl = 0;
   int ctrlCount = 0;
   /* Length of string */
   int length = strlen( string );

   /* Loop through each character */
   for ( ii = 0; ii < length; ii++ )
   {
      if ( iscntrl( string[ii] ) || ( string[ii] == ' ') )
      {
         ctrlCount++;
      }
   }

   /* If all control characters exist in the string then evaluate to true */
   if ( ctrlCount == length )
   {
      isCtrl = -1;
   }
   
   return isCtrl;
}
