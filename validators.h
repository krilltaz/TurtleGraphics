/* FILE: validators.h
 * AUTHOR: Kyle Notani | 19149918
 * UNIT: UCP COMP1000
 * PURPOSE: Header file associated with validators.c
 */

#ifndef VALIDATORS_H
   #define VALIDATORS_H

   /* Pointers to Function Typedef */
   /* Points to parameter validator functions */
   typedef int ( *CmdParamFunc )( char**, char** );
   
   /* Points to datatype validator functions */
   typedef int ( *CmdDataFunc )( char**, char** );
   
   /* Points to value range validator functions */
   typedef int ( *CmdRangeFunc )( char** );
   
   
   /* Verifies if a command name is valid and return if a command name 
    * is found or not found. Provides the main function assistance
    * to continue validating other command fields.
    */
   int validateCommandName( char* tempLine, CmdDataFunc* validateDataType, CmdParamFunc* validateParameters, CmdRangeFunc* validateRange );

   /* Validates if a command value is of a real data type. */
   int validateReal( char** errorString, char** strValue );
   
   /* Validates if a command value is of an integer data type. */
   int validateInt( char** errorString, char** strValue );
   
   /* Validates if a command value is of a printable char type. */
   int validateChar( char** errorString, char** strValue );

   /* Validates if the number of command parameters is only of a single value. */
   int validateParameters( char** strValue, char** errorString );
   
   /* Validates if the number of command parameters is of a single character
    * for a pattern command.
    */
   int validatePatternParameters( char** strValue, char** errorString );

   /* To validate the range of a distance to be no bigger than terminal
    * maximum width.
    */
   int validateDrawRange( char** strValue );
   
   /* To validate the range of a distance to be no bigger than terminal
    * maximum width.
    */
   int validateMoveRange( char** strValue );
   
   /* Placeholder function in the case of a rotate range to be assigned
    * in the future.
    */
   int validateRotateRange( char** strValue );
   
   /* To validate the range of foreground colour to be between 0 to 15
    * colours.
    */
   int validateFgRange( char** strValue );
   
   /* To validate the range of background colour to be between 0 to 7
    * colours.
    */
   int validateBgRange( char** strValue );
   
   /* Validates the range of pattern printable characters */
   int validatePatternRange ( char** strValue );
   
#endif
