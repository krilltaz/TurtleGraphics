/* 
 * FILE: readinput.c
 * AUTHOR: Kyle Notani | 19149918
 * UNIT: UCP COMP1000
 * PURPOSE: Read formatted commands from file and store into linked list
 *          while assuring that each command matches the specified format.
 * FILE FORMATS: Any text based file.
 * COMMAND ARGUMENTS: A single filename containing commands to draw.
 * OTHER: '-1' evaluates to true, '0' evaluates to false. See readinput.h.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readinput.h"
#include "validators.h"
#include "listoperations.h"
#include "linkedlist.h"
#include "structset.h"
#include "draw.h"
#include "stringoperations.h"

/* 
 * NAME: main()
 * PURPOSE: Entry point to the program. Reads in a series of commands top to bottom 
 *          from an input file while validating its viability to perform various 
 *          draw operations on the terminal.
 * HOW IT WORKS: - Uses fgets() for each line (excludes blank lines) in the file 
 *                 until the file has ended.
 *               - Each line containing any text will be validated with various 
 *                 validators.c functions depending on the command identified.
 *               - If a single validation function returns false then the file is
 *                 marked as invalid and any errors will be printed out to identify
 *                 what and where the problem occured in the file.
 *               - An invalid file indicates that drawing may not commence
 *                 until all errors are fixed.
 *               - Each validated command operation in the file will be stored
 *                 using storeCommand().
 * RELATIONS:
 *    constructList() - Allocates an empty linked list.
 *    validateCommandName() - Validates the name of a command giving
 *                            parameters as exports to pointers to other validator 
 *                            functions.
 *    storeCommand() - Stores a command (name and value) into the constructed 
 *                     linked list.
 *    freeList() - Free the list including any list nodes and its associated values.
 *
 * IMPORTS: 
 *    argc  The number of command-line arguments.
 *    argv  An array of pointers to chars where each represents the argument
 *          string (argument vector).
 *
 * EXPORTS:
 *          Exit status condition provided to the OS.
 */

int main( int argc, char* argv[] )
{

   /* pointer to the input file containing commands */
   FILE* input = NULL;

   /* the number of bytes from the start of file */
   long fileDistance = 0;

   /* string (array of chars) of length maximum buffer size for each line read */
   char line[BUFFER_LENGTH];
   
   /* a copied alternative for the original line for use in validators.c functions */
   char* tempLine = NULL;

   /* the command value as a string */
   char* strValue = NULL;

   /* error pointer required for strtoX() functions */
   char* errorString = NULL;

   /* data structure to store commands */
   LinkedList* list = NULL;

   /* used for easy error identification in file printed to the terminal 
    * for invalid commands, data types, parameters and ranges */
   int lineNo = 0;
   int cmdsRead = 0;

   /* to identify invalid files */
   int isInvalid = FALSE;

   /* validator values to verify each line */
   int foundCommand = FALSE;
   int correctParameters = FALSE;
   int correctDataType = FALSE;
   int correctRange = FALSE;

   /* pointers to validators.c functions to validate each command */
   CmdParamFunc validateParameters;
   CmdDataFunc validateDataType;
   CmdRangeFunc validateRange; 


   /* If argument count is invalid, do not proceed with file operations */
   if ( argc != MAX_ARG )
   {
      printf( "Error: argument count %d is not valid\n", argc );
      printf( "       enter filename along execution\n" );
   }
   else
   {
      input = fopen( argv[1], "r" );
      list = constructList();      

      /* Output error if input file can't open */
      if ( input == NULL )
      {
         perror( "Error: file could not be opened\n" );
         printf( "       check if file exists\n" );
         freeList(list);
      }

      /* Output error if list can't be constructed */
      else if ( list == NULL )
      {
         printf( "Error: could not construct list data structure\n" );
      }
      else
      {
         /* Check if input file is empty */
         fseek( input, 0, SEEK_SET );
         fseek( input, 0, SEEK_END );
         fileDistance = ftell( input );

         if ( fileDistance <= MIN_FILE_DATA )
         {
            printf( "Error: file contains no data\n" );
         }
         else  
         {
            rewind( input );

            /* Grab each line */
            while ( fgets( line, BUFFER_LENGTH, input ) != NULL )
            {
               lineNo++;

               /* Make another copy of the line for validation */
               tempLine = ( char* )malloc( BUFFER_LENGTH * sizeof(char) );
               strcpy( tempLine, line );

               /* Skip any line just containing control characters (non-printable) */
               if ( stringIsCtrl( line ) == FALSE )
               {
                  /* Identify the validation operations to commence 
                   * (pointers to functions) if the command name is found */
                  foundCommand = validateCommandName( tempLine, &validateDataType, &validateParameters, &validateRange );      

                  if ( foundCommand == FALSE )
                  {
                     isInvalid = -1;
                     printf( "Error: Line %d. command unidentified\n", lineNo);
                     printf( "       check if value exists and/or name is spelt correctly\n");
                  }
                  else
                  {
                     /* Check datatype of value */
                     correctDataType = ( *validateDataType )( &errorString, &strValue );

                     /* Check parameter count */
                     correctParameters = ( *validateParameters )( &strValue, &errorString );

                     if ( correctParameters == FALSE )
                     {
                        isInvalid = -1;
                        printf( "       Line %d. incorrect number of parameters for command\n\n", lineNo);
                     }
                     if ( correctDataType == FALSE )
                     {
                        isInvalid = -1;
                        printf( "       Line %d. incorrect data type for command\n\n", lineNo);
                     }
                     if ( ( correctParameters != FALSE ) && (correctDataType != FALSE ) )
                     {
                        /* Check value range */
                        correctRange = ( *validateRange )( &strValue );
                        if ( correctRange == FALSE )
                        {
                           isInvalid = -1;
                           printf( "       Line %d. incorrect range for command\n\n", lineNo );
                        }
                        else
                        {
                           /* Increment the no of commands read/found */
                           cmdsRead++;
                           /* Insert the command into the linked list */
                           storeCommand( line, list );
                        }
                     }
                  }
               }
               free( tempLine );
               tempLine = NULL;
            }
            			
            /* Inform that the end of file is reached after each line is read */
            if ( fgets( line, BUFFER_LENGTH, input ) == NULL )
            {
               printf( "---------------------REPORT---------------------\n" );
               printf( "End of file reached\n" );
               printf( "%d command(s) valid\n", cmdsRead );
               if ( isInvalid != FALSE )
               {
                  printf( "Fix any listed errors to draw\n" );
               }
               printf( "------------------------------------------------\n" );
            }

            /* Start drawing if file was valid */
            if ( isInvalid == FALSE )
            {
               draw( list );
            }
      
            /* Output an error if an error was identified during reading */
            if ( ferror( input ) )
            {
               perror( "Error occured during reading\n" );
            }
         }

         freeList( list );
         list = NULL;

         fclose( input );
      }
   }
   return 0;
}

/*
 * NAME: storeCommand()
 * PURPOSE: Stores a valid command to be grouped into a Command struct 
 *          with its name and value into a linked list in reverse order.
 * HOW IT WORKS: - Allocate memory for a command struct as well as
 *                 the name and value.
 *               - Tokenise the string using strtok() to isolate the
 *                 validated command name and value to be inserted in the
 *                 command struct.
 *               - Insert the struct into a list using insertLast()
 * RELATIONS:
 *    insertLast() - Inserts a new node with the associated value into the 
 *                   end of the list
 * IMPORTS:
 *    line - String that contains the validated command operation
 *    list - The linked list to insert the command
 *
 * EXPORTS:
 *    none
 */

void storeCommand( char* line, LinkedList* list )
{
   Command* cmd = NULL;

   char* cmdName = NULL;
   char* cmdValue = NULL;

   /* Allocate a command struct in heap memory */
   cmd = ( Command* )malloc( sizeof( Command ) );
   cmd->name = ( char* )malloc( MAX_CMD_NAME * sizeof( char ) );
   cmd->value = ( char* )malloc( MAX_DIGITS * sizeof( char ) );

   /* Grab each validated command name and corresponding value */
   cmdName = strtok( line, " " );
   cmdValue = strtok( NULL, " " );

   /* Store file contents into a single command struct */
   strcpy( cmd->name, cmdName );
   strcpy( cmd->value, cmdValue );

   /* Pass in the command data to the list to be inserted in reverse order */
   insertLast( list, cmd );
}
