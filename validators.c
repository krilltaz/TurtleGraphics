/*
 * FILE: validators.c
 * AUTHOR: Kyle Notani | 19149918
 * UNIT: UCP COMP1000
 * PURPOSE: Validate each read in command operation from the file
 *          by checking the command's name, it's corresponding required parameter 
 *          count, data type and value range.
 * OTHER: This file contains functions that assist readinput.c to achieve it's 
 *        purpose.
 *        '-1' evaluates to true, '0' evaluates to false.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "validators.h"
#include "stringoperations.h"


/*
 * NAME: validateCommandName()
 * PURPOSE: Verifies if a command name is valid and return if a command name 
 *          is found or not found. Provides the main function assistance
 *          to continue validating other command fields. 
 *          
 * HOW IT WORKS: - Uses strtok() to tokenise the command contained in the line
 *                 string to grab the command name.
 *               - Modify the string to uppercase to check if it matches each of
 *                 the valid commands viable for use.
 *               - Each identified command points all function pointers to another
 *                 validation function to further test if the command is viable.
 * RELATIONS:
 *    main() - Calling function for command validation.
 *    stringUpperCase() - Used to treat each command name to be case
 *                        insensitive and provide comparison with expected
 *                        uppercase command names. A command name with mixed casing
 *                        is allowed.
 * IMPORTS:
 *    tempLine - The line string to check if a command name is valid.
 *    validateDataType - Function pointer to point to a matched command's data type
 *                       validation.
 *    validateParam - Function pointer to point to a matched command's parameters
 *                    validation.
 *    validateRange - Function pointer to point to a matched command's value range
 *                    validation.
 * EXPORTS:
 *    isValid - A boolean evaluating to '0' (FALSE) if a command name is invalid 
 *              or '-1' (TRUE) if command name is valid.
 *
 */

int validateCommandName( char* tempLine, CmdDataFunc* validateDataType, CmdParamFunc* validateParam, CmdRangeFunc* validateRange )
{
   int isValid = 0;

   char* command = NULL;

   /* Get expected command name */
   command = strtok( tempLine, " " );
   stringUpperCase( command );

   /* Check if a command name matches */
   if ( strcmp( command, "DRAW" ) == 0 )
   {
      isValid = -1;
      *validateDataType = &validateReal;
      *validateParam = &validateParameters;
      *validateRange = &validateDrawRange;
   }
   else if ( strcmp( command, "MOVE" ) == 0 )
   {
      isValid = -1;
      *validateDataType = &validateReal;
      *validateParam = &validateParameters;
      *validateRange = &validateMoveRange;
   }
   else if ( strcmp( command, "ROTATE" ) == 0 )
   {
      isValid = -1;
      *validateDataType = &validateReal;
      *validateParam = &validateParameters;
      *validateRange = &validateRotateRange;
   }
   else if ( strcmp( command, "FG" ) == 0 )
   {
      isValid = -1;
      *validateDataType = &validateInt;
      *validateParam = &validateParameters;
      *validateRange = &validateFgRange;
   }
   else if ( strcmp ( command, "BG" ) == 0 )
   {
      isValid = -1;
      *validateDataType = &validateInt;
      *validateParam = &validateParameters;
      *validateRange = &validateBgRange;
   }
   else if ( strcmp ( command, "PATTERN" ) == 0 )
   {
      isValid = -1;
      *validateDataType = &validateChar;
      *validateParam = &validatePatternParameters;
      *validateRange = &validatePatternRange;
   }

   return isValid;
}




/*
 * NAME: validateReal()
 * PURPOSE: Validates if a command value is of a real data type.
 * HOW IT WORKS: - Tokenises the line string containing the command operation 
 *                 to grab the value as a string.
 *               - Convert the string value to a real by using strtod() as well
 *                 as passing a string to identify errors during conversion.
 *               - If error string contains a new line character or a null
 *                 terminator the datatype is correct.
 *               - Compare errorString to strValue to assure that strtod() that 
 *                 conversion went correctly. strtod() stores the original 
 *                 string in errorPtr if conversion was not successful.
 * RELATIONS: 
 *    main() - To evaluate the datatype validation condition for a command in a line.
 *           - Has the 'errorString' and 'strValue' passed by reference to also be utilised
 *             with other validation functions.
 *    validateCommandName() - Points to this function depending on command operation.
 * IMPORTS:
 *    errorString - A pointer to a string passed by reference from main() containing
 *                  the errorString from strtod().
 *    strValue - A pointer to a string passed by reference from main() to be used
 *               in other validation functions dealing with the command value only.
 * EXPORTS:
 *    isValid - A boolean evaluating to '0' (FALSE) if a command name is invalid
 *              or '-1' (TRUE) if command name is valid.
 *
 */

int validateReal( char** errorString, char** strValue )
{
   int isValid = 0;
   double realValue = 0.0;   

   /* Set the strValue to expected value within same line string */
   *strValue = strtok( NULL, " " );

   if ( *strValue != NULL )
   {
      realValue = strtod( *strValue, errorString );

      /* Evaluate errorString thorougly testing all conversion cases */
      if ( ( (**errorString == '\n') || (**errorString == '\0') ) && ( ( strlen(*strValue) != strlen(*errorString) ) && ( strcmp( *strValue, *errorString ) != 0 ) ) )
      {
         isValid = -1;
      }
      else
      {
         printf( "Error: real data type expected\n" );
      }
   }
   
   return isValid;
}




/* NAME: validateInt()
 * PURPOSE: Validates if a command value is of an integer data type.
 * HOW IT WORKS: - Tokenises the line string containing the command operation
 *                 to grab the value as a string.
 *               - Convert the string value to an integer by using strtol() as
 *                 well as passing a string to identify errors during conversion.
 *               - If error string contains a new line character or a null
 *                 terminator, the datatype is correct.
 *               - Compare errorString to strValue to assure that strtol()
 *                 conversion went correctly. strtol() stores the original
 *                 string in errorPtr if conversion was not successful.
 * RELATIONS:
 *    main() - To evaluate the datatype validation condition for a command in a
 *             line.
 *           - Has the errorString and strValue passed by reference to also be
 *             utilised with other validation functions.
 *    validateCommandName() - Points to this function depending on command operation.
 * IMPORTS:
 *    errorString - A pointer to a string passed by reference from main()
 *                  containing the errorString from strtol().
 *    strValue - A pointer to a string passed by reference from main() to be used
 *               in other validation functions dealing with the command value only.
 * EXPORTS:
 *    isValid - A boolean evaluating to '0' (FALSE) if a command name is invalid
 *              or '-1' (TRUE) if command name is valid.
 *
 */

int validateInt( char** errorString, char** strValue )
{
   int isValid = 0;
   int intValue = 0;

   /* Set the strValue to the expected value after command name on same line */
   *strValue = strtok( NULL, " " );

   if ( *strValue != NULL ) 
   {
      intValue = strtol( *strValue, errorString, 10 );

      /* Evaluate errorString after conversion */
      if( ( (**errorString == '\n') || (**errorString == '\0') ) && ( (strlen(*strValue) != strlen(*errorString) ) && ( strcmp( *strValue, *errorString ) != 0 ) ) )
      {
         isValid = -1;
      }
      else
      {
         printf( "Error: integer data type expected\n" );
      }
   }

   return isValid;
}



/* NAME: validateChar()
 * PURPOSE: Validates if a command value is of a printable char type.
 * HOW IT WORKS: - Grabs the character of from strValue and uses
 *                 isprint() to test if it's a printable character.
 * RELATIONS:
 *    main() - To evaluate the datatype validation condition for a command in a line.
 *    validateCommandName() - A pattern command specifically points to this function 
 *                            to evaluate datatype.
 * IMPORTS:
 *    errorString - A pointer to a string passed by reference from main() containing
 *                  the errorString. *Included as a parameter to match the CmdDataFunc
 *                  function pointer typedef signature.
 *    strValue - A pointer to a string passed by reference from main() to be used
 *               in other validation functions dealing with the command value only.
 * EXPORTS:
 *    isValid - A boolean evaluating to '0' (FALSE) if a command name is invalid
 *              or '-1' (TRUE) if command name is valid.
 *
 */

int validateChar( char** errorString, char** strValue )
{
   int isValid = 0;
   
   char pattern;
 
   /* Set the strValue to the expected value after command name on the same line */
   *strValue = strtok( NULL, " " );

   pattern = **strValue;

   /* Check if pattern is a printable character */
   if( isprint( pattern ) != 0 )
   {
      isValid = -1;
   }
   else
   {
      printf( "Error: character data type expected\n" );
   }
   
   return isValid;
}



/* NAME: validateParameters()
 * PURPOSE: Validates if the number of command parameters is only of a single value.
 * HOW IT WORKS: - Tokenises the original line string to check if any string
 *                 is passed to otherParameters.
 *               - if errorString contains either a new line character or null
 *                 terminator then strtoX() functions previously done would have
 *                 only converted the value and nothing else.
 *               - Further checks if no string is pointed by otherParameters then the parameters
 *                 are valid.
 *               - If the otherParameters contains a string then further check
 *                 if the string contains entirely control characters in
 *                 stringIsCtrl() which can evaluate the parameter count to be valid.
 *               - Otherwise the parameters cound are not valid.
 * RELATIONS:
 *   main() - To evaluate the parameter count validation condition for a command in
 *            a line.
 *          - Uses the strValue to point to the string of the value.
 *
 *   validateCommandName() - Points to this function depending on command operation. 
 * IMPORTS:
 *    strValue - A pointer to a string passed by reference from main() to be used in
 *               other validation functions dealing with the command value only.
 *    errorString - A pointer to a string passed by reference from main() containing
 *                  the errorString from stroX() functions.
 * EXPORTS:
 *    isValid - A boolean evaluating to '0' (FALSE) if a command name is invalid or
 *              '-1' (TRUE) if command name is valid.
 */

int validateParameters( char** strValue, char** errorString )
{
   int isValid = 0;

   char* otherParameters = NULL;

   /* Check if any values exist after previously tokenised data value */
   otherParameters = strtok( NULL, " " );
   
   /* Check if errorString converted the numeric datatype correctly */
   if( ( **errorString == '\n' ) || ( **errorString == '\0' ) )
   {
      /* If otherParameters don't exist then evaluate to true */
      if ( otherParameters == NULL )
      {
         isValid = -1;
      }
      /* If otherParameters consist of non printable characters then parameters
       * are valid */
      else if ( stringIsCtrl( otherParameters ) == -1 )
      {
         isValid = -1;
      }
      else
      {
         printf( "Error: expected one parameter value\n" );
      }
   }
   
   return isValid;
}




/* NAME: validatePatternParameters()
 * PURPOSE: Validates if the number of command parameters is of a single character
 *          for a pattern command.
 * HOW IT WORKS: - Tokenises the original line string value to check if any string
 *                 is passed to otherParameters.
 *               - Also checks if the value of the pattern command is only
 *                 of a single character value by using strlen()
 * RELATIONS:
 *    main() - To evaluate the parameter cound validation condition for a command in
 *             a line.
 *    validateCommandName() - Points to this function for pattern commands.
 * IMPORTS:
 *    strValue - A pointer to a string passed by 
 * EXPORTS:
 *    isValid - A boolean evaluating to '0' (FALSE) if a command name is invalid
 *              or '-1' (TRUE) if command name is valid.
 */

int validatePatternParameters( char** strValue, char** errorString )
{
   int isValid = 0;

   char* otherParameters = NULL;

   otherParameters = strtok( NULL, " " );
   
   /* Checks if the length of the string is two (character + new line) */
   /* Checks if there are any tokenised values after a space */
   if ( ( strlen( *strValue ) == 2) && ( otherParameters == NULL ) )
   {
      isValid = -1;
   }
   else
   {
      printf( "Error: expected one parameter value\n" );
   }

   return isValid;
}





/* NAME: validateDrawRange()
 * PURPOSE: To validate the range of a distance to be no bigger than terminal
 *          maximum width.
 * HOW IT WORKS:
 *          - Converts the already validated datatype value to a real using
 *            atof().
 *          - Checks if distance is between 0 and 80 inclusive.
 * RELATIONS:
 *    main() - To evaluate the range of an already validated datatype for a command.
 *    validateCommandName() - Points to this function on draw commands.
 * IMPORTS:
 *    strValue - A pointer to a string passed by reference from main() to be used in
 *               other validation functions dealing with the command value only.
 * EXPORTS:
 *    isValid - A boolean evaluating to '0' (FALSE) if a command name is invalid
 *              or '-1' (TRUE) if command name is valid.
 */

int validateDrawRange( char** strValue )
{
   int isValid = 0;
   
   double distance;
   
   distance = atof( *strValue );
   
   if ( ( 0 <= distance ) && ( distance <= 80 ) )
   {
      isValid = -1;
   }
   else
   {
      printf( "Error: draw distance must be between 0 and 80\n" );
   }

   return isValid;
}




/* NAME: validateMoveRange()
 * PURPOSE: To validate the range of a distance to be no bigger than terminal
 *          maximum width.
 * HOW IT WORKS:
 *          - Converts the already validated datatype value to a real using
 *            atof().
 *          - Checks if distance is between 0 and 80 inclusive.
 * RELATIONS:
 *    main() - To evaluate the range of an already validated datatype for a command.
 *    validateCommandName() - Points to this function on move commands.
 * IMPORTS:
 *    strValue - A pointer to a string passed by reference from main() to be used in
 *               other validation functions dealing with the command value only.
 * EXPORTS:
 *    isValid - A boolean evaluating to '0' (FALSE) if a command name is invalid
 *              or '-1' (TRUE) if command name is valid.
 */   

int validateMoveRange( char** strValue )
{
   int isValid = 0;

   double distance;

   distance = atof( *strValue );

   if ( ( 0 <= distance ) && ( distance <= 80 ) )
   {
      isValid = -1;
   }
   else
   {
      printf( "Error: move distance must be between 0 and 80\n" );
   }

   return isValid;
}





/* NAME: validateRotateRange()
 * PURPOSE: *The range of a rotate value doesn't have a specific range.
 *          *Used as a placeholder function in the case of a range to be assigned
 *           in the future.
 * HOW IT WORKS:
 *          - Returns the range as being valid.
 * RELATIONS:
 *    main() - To evaluate the range of an already validated datatype for a command.
 *    validateCommandName() - Points to this function on rotate commands.
 * IMPORTS:
 *    strValue - A pointer to a string passed by reference from main() to be used in
 *               other validation functions dealing with the command value only.
 * EXPORTS:
 *    isValid - A boolean evaluating to '0' (FALSE) if a command name is invalid
 *              or '-1' (TRUE) if command name is valid.
 */

int validateRotateRange( char** strValue )
{
   int isValid = -1;

   return isValid;
}




/* NAME: validateFgRange()
 * PURPOSE: To validate the range of foreground colour to be between 0 to 15
 *          colours.
 * HOW IT WORKS:
 *       - Converts the already validated datatype value to an integer using
 *         atoi().
 *       - Checks if fgColour is between 0 and 15 inclusive.
 * RELATIONS:
 *    main() - To evaluate the range of an already validated datatype for a command.
 *    validateCommandName() - Points to this function on fg commands.
 * IMPORTS:
 *    strValue - A pointer to a string passed by reference from main() to be used in
 *               other validation functions dealing with the command value only.
 * EXPORTS:
 *    isValid - A boolean evaluating to '0' (FALSE) if a command name is invalid
 *              or '-1' (TRUE) if command name is valid.
 */

int validateFgRange( char** strValue )
{
   int isValid = 0;

   int fgColour;

   fgColour = atoi( *strValue );  

   if ( ( 0 <= fgColour ) && ( fgColour <= 15 ) )
   {
      isValid = -1;
   }
   else
   {
      printf( "Error: foreground colour must be between 0 and 15\n" );
   }

   return isValid;
}




/* NAME: validateBgRange()
 * PURPOSE: To validate the range of background colour to be between 0 to 7
 *          colours.
 * HOW IT WORKS:
 *          - Converts the already validated datatype value to an integer using
 *            atoi().
 *          - Checks if bgColour is between 0 and 7 inclusive.
 * RELATIONS:
 *    main() - To evaluate the range of an already validated datatype for a command.
 *    validateCommandName() - Points to this function on bg commands.
 * IMPORTS:
 *    strValue - A pointer to a string passed by reference from main() to be used in
 *               other validation functions dealing with the command value only.
 * EXPORTS:
 *    isValid - A boolean evaluating to '0' (FALSE) if a command name is invalid
 *              or '-1' (TRUE) if command name is valid.
 */

int validateBgRange( char** strValue )
{
   int isValid = 0;

   int bgColour;

   bgColour = atoi( *strValue );

   if ( ( 0 <= bgColour ) && ( bgColour <= 7 ) )
   {
      isValid = -1;
   }
   else
   {
      printf( "Error: background colour must be between 0 and 7\n" );
   }

   return isValid;
}




/* NAME: validatePatternRange()
 * PURPOSE: *A pattern shouldn't be assigned a range because the datatype check
 *          function for the pattern commands checks if a pattern is of printable
 *          character.
 *          *Exists for future inclusion of a range of pattern.
 *           eg) Only numeric values in ASCII table.
 * HOW IT WORKS:
 *       - Returns the range as being valid.
 * RELATIONS:
 *    main() - To evaluate the range of an already validated datatype for a command.
 *    validateCommandName() - Points to this function on pattern commands.
 * IMPORTS:
 *    strValue - A pointer to a string passed by reference from main() to be used in
 *               other validation functions dealing with the command value only.
 * EXPORTS:
 *    isValid - A boolean evaluating to '0' (FALSE) if a command name is invalid
 *              or '-1' (TRUE) if command name is valid.
 */

int validatePatternRange( char** strValue )
{
   int isValid = -1;
   
   return isValid;
}


