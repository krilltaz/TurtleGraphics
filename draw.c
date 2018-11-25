/* 
 * FILE: draw.c
 * AUTHOR: Kyle Notani | 19149918
 * UNIT: UCP COMP1000
 * PURPOSE: Draw a series of validated commands from a linked list
 *          onto the terminal based on regular, simple and debug modes while
 *          while writing each coordinate based draw or move into a logfile.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "draw.h"
#include "effects.h"
#include "linkedlist.h"
#include "listoperations.h"
#include "structset.h"
#include "stringoperations.h"
#include "conversions.h"

/*
 * NAME: draw()
 * PURPOSE: Handles the deciding operation for what command function to call 
 *    based on list contents writing the draw process into a graphics.log file.
 *          
 * HOW IT WORKS:
 *    - Constructs a GraphicsState struct which indicates the current
 *      state of the applied commands performed during command grabbing.
 *    - The current graphics state starts with default setting for each
 *      command.
 *    - Loop through each node from the list containing the stored commands
 *      as a List node containing Command structs as a value to identify
 *      the command name.
 *    - Each identifiable command name will call it's corresponding command
 *      function operation.
 *    - Any draw or move commands will simply be appended to a graphics.log
 *      file for debugging purposes.
 *
 * RELATIONS:
 *    main() - Calling function for drawing operation to commence.
 *    stringUpperCase() - Used to allow case-insensitive comparisons to ensure
 *                        each command is identified correctly to perform its
 *                        operation.
 * IMPORTS:
 *    list - The linked list with any read in valid commands.
 * EXPORTS:
 *    none
 *
 */

void draw(LinkedList* list)
{
   /* Initially open logfile */
   FILE* log = fopen("graphics.log", "a");

   /* Current state of Graphics maintained during command operations */
   GraphicsState* current = (GraphicsState*)malloc( sizeof(GraphicsState) );
   
   /* Command struct contained within each list node in the list */
   Command* cmd = NULL;

   /* Point a temporary current list node to the head of the list */
   LinkedListNode* currentNode = list->head;

   /* Temp coordinate variables */
   double prevX = 0.0;
   double prevY = 0.0;

   /* Initial Read is set to TRUE */
   int initialRead = -1;

   /* Default Position */
   current->x = 0.0;
   current->y = 0.0;

   /* Default Angle */
   current->angle = 0.0;
   
   /* Default Colours */
   #ifndef SIMPLE
   current->fgColour = 7;
   current->bgColour = 0;
   /* Simple Mode Colours */
   #else
   current->fgColour = 0;
   current->bgColour = 7;
   #endif

   /* Default Pattern */
   current->pattern = '+';

   if(log == NULL)
   {
      perror("Error: log file can't be updated\n");
   }
   else
   {
      fprintf(log, "---\n");
   }

   /* Check if the list is empty */
   if(isEmpty(list) != FALSE)
   {
      printf("Error: No commands to perform drawing\n");
      printf("       Check if file contains any commands\n");
      free(current);
      current = NULL;
      fclose(log);
   }
   else
   {
      /* Initially blank the terminal before drawing */
      clearScreen();

      /* Default simple mode colours overriding any colour changes */
      #ifdef SIMPLE
      setFgColour(current->fgColour);
      setBgColour(current->bgColour);
      #endif

      /* Iterate through the list and run the commands */
      /* Use a do while loop to assure that a single command by itself 
       * can be read */
      do
      {
         /* Only iterate if a single command is already done */
         if ((currentNode->next != NULL) && (initialRead == FALSE))
         {
            currentNode = currentNode->next;
         }

         /* Grab command from list */
         cmd = (Command*)currentNode->data;
         stringUpperCase(cmd->name);

         /* Draw */
         if(strcmp(cmd->name, "DRAW") == 0)
         {
            drawLine(cmd, current, &prevX, &prevY);

            /* Append to logfile */
            fprintf(log, "DRAW (%7.3f,%7.3f)-(%7.3f,%7.3f)\n", prevX, prevY, current->x, current->y);
            #ifdef DEBUG
            fprintf(stderr, "DRAW (%7.3f,%7.3f)-(%7.3f,%7.3f)\n", prevX, prevY, current->x, current->y);
            #endif
         }
         /* Move */
         else if(strcmp(cmd->name, "MOVE") == 0)
         {
            move(cmd, current, &prevX, &prevY);
            
            /* Append to logfile */
            fprintf(log, "MOVE (%7.3f,%7.3f)-(%7.3f,%7.3f)\n", prevX, prevY, current->x, current->y);
            #ifdef DEBUG
            fprintf(stderr, "MOVE (%7.3f,%7.3f)-(%7.3f,%7.3f)\n", prevX, prevY, current->x, current->y);
            #endif
         }
         /* Rotate */
         else if (strcmp(cmd->name, "ROTATE") == 0)
         {
            rotate(cmd, current);
         }
         /* Change Foreground Colour */
         else if (strcmp(cmd->name, "FG") == 0)
         {
            changeFgColour(cmd, current);
         }
         /* Change Background Colour */
         else if(strcmp(cmd->name, "BG") == 0)
         {
            changeBgColour(cmd, current);
         }
         /* Change Pattern */
         else if(strcmp(cmd->name, "PATTERN") == 0)
         {
            setPattern(cmd, current);
         }

         if (initialRead != FALSE)
         {
            initialRead = FALSE;
         }

      /* We will increment the current pointer after command reading only if
       * there exists a next pointer
       */
      } while(currentNode->next != NULL);
   
      /* Point cursor to the bottom of terminal after command operations */
      penDown();
      fclose(log);

      free(current);
      current = NULL;
   }
}





/*
 * NAME: drawLine()
 * PURPOSE: Commences the draw command. Draw a line on the terminal based on 
 *          current angle and distance.
 *          Uses trigonometetry to maintain coordinate locations on the terminal
 *          2D space to draw from start to finish. Each draw maintains the 
 *          current x and y values at the current state assuring following 
 *          commands continue along where the cursor is located.
 *
 * HOW IT WORKS: - Grabs the distance (using atof()) from the passed in command 
 *                 and reducing its value by one to prevent double printing to 
 *                 the terminal.
 *               - Store the current x and y value to previous values.
 *               - Call defineCoordinates (uses trigonometry to identify the 
 *                 coordinates from distance-1 and current angle).
 *               - Move cursor by one as a final move to prevent double 
 *                 printing.
 * RELATIONS:
 *    draw() - Calling function to draw line. (Passes in current state of 
 *             graphics and command data from list.)
 *    defineCoordinates() - Used to define coordinates (x, y) with trigonometry 
 *                          to identify the coordinates from distance-1 and 
 *                          current angle as well as the start move to complete 
 *                          a single line draw.
 *    line() - Calls line() passing rounded x and y start and finish coordinates,
 *             the plot function as well as the current pattern to draw a line() 
 *             output to the terminal.
 *    plotPoint - pointer to a function passed for line to simple print a 
 *                given character (pattern) on screen.
 * IMPORTS:
 *    cmd - Command data to grab distance value to draw.
 *    current - Graphics state data to identify current angle and current x 
 *              and y coordinates.
 *    prevX/prevY - Coordinates passed as a pointer to ensure logfile prints 
 *                  correct start and finishing coordinates done from the 
 *                  calling function draw().
 * EXPORTS:
 *    none
 *
 */


void drawLine( Command* cmd, GraphicsState* current, double* prevX, double* prevY )
{

   /* Distance to draw line */
   double distance = 0.0;
   
   /* Coordinates to start drawing from distance-1 */
   double endDrawX = 0.0;
   double endDrawY = 0.0;
   
   /* Cursor move distance */
   double finalMove = 1.0;

   distance = atof( cmd->value );
   distance -= 1;

   /* Set prev temp values to current x and y coordinates */
   *prevX = ( current->x );
   *prevY = ( current->y );

   /* Define coordinates to distance-1 and current angle */
   defineCoordinates( prevX, prevY, &endDrawX, &endDrawY, &( current->angle ), &distance );

   /* Draw line */
   line( round( *prevX ), round( *prevY ), round( endDrawX ), round( endDrawY ), &plotPoint, &( current->pattern ) );

   /* End at correct coordinates */
   endDrawX = ( double )round( endDrawX );
   endDrawY = ( double )round( endDrawY );

   /* Move cursor along by one */
   defineCoordinates( &endDrawX, &endDrawY, &( current->x ), &( current->y ), &( current->angle ), &finalMove );
}





/*
 * NAME: move()
 * PURPOSE: Commences the move command. Moves the cursor based on current angle 
 *          and distance.
 *          Uses trigonometetry to maintain coordinate locations on the terminal
 *          2D space to move from start to finish. Each move maintains the 
 *          current x and y values at the current state assuring following 
 *          commands continue along where the cursor is located.
 *
 * HOW IT WORKS: - Grabs the distance (using atof()) from the passed in command.
 *               - Store the current x and y value to previous values.
 *               - Call defineCoordinates to move (uses trigonometry to identify 
 *                 the coordinates from distance and current angle).
 * RELATIONS:
 *    draw() - Calling function to move cursor. (Passes in current state of 
 *             graphics and command data from list.)
 *    defineCoordinates() - Used to define coordinates (x, y) with trigonometry
 *                          to identify the coordinates from distance and 
 *                          current angle.
 * IMPORTS:
 *    cmd - Command data to grab distance value to draw.
 *    current - Graphics state data to identify current angle and current x 
 *              and y coordinates.
 *    prevX/prevY - Coordinates passed as a pointer to ensure logfile prints 
 *                  correct start and finishing coordinates done from the 
 *                  calling function draw().
 * EXPORTS:
 *    none
 *
 */

void move( Command* cmd, GraphicsState* current, double* prevX, double* prevY )
{
   /* Distance to move cursor to */
   double distance = 0.0;

   distance = atof( cmd->value );
   *prevX = current->x;
   *prevY = current->y;

   /* Perform the move */
   defineCoordinates( prevX, prevY, &( current->x ), &( current->y ), &( current->angle ), &distance );
}



/*
 * NAME: rotate()
 * PURPOSE: Rotates the angle based on rotate command ensuring the rotation is 
 *          within 360 degrees.
 * HOW IT WORKS: - Grabs the rotate value (using atof()) from the passed in 
 *                 command.
 *               - Calls defineAngle to mod the angle by 360 to keep it within 
 *                 360 degree range.
 * RELATIONS:
 *    draw() - Calling function to rotate angle. (Passes in current state of 
 *             graphics and command data from list.)
 *    defineAngle() - Used to mod a given value by 360.
 * IMPORTS:
 *    cmd - Command data to grab angle value to rotate.
 *    current - Graphics state data to set current angle.
 * EXPORTS:
 *    none
 *
 */

void rotate( Command* cmd, GraphicsState* current )
{
   current->angle += atof( cmd->value );
   /* Mod by 360 */
   current->angle = defineAngle( current->angle );
}




/*
 * NAME: changeFgColour()
 * PURPOSE: Sets the foreground colour of the terminal.
 * HOW IT WORKS: - Grabs the foreground colour value from the command struct 
 *                 using atoi() to store the validated command in the current 
 *                 graphics state.
 *               - Calls setFgColour to the command value grabbed.
 * RELATIONS:
 *    draw() - Calling function to set foreground colour. 
 *            (passes in current state of graphics and command data  from list.)
 *    setFgColour - function within effects.c file to set the foreground colour 
 *                  of the terminal.
 * IMPORTS:
 *    cmd - Command data to grab foreground colour to set.
 *    current - Graphics state data to set foreground colour.
 * EXPORTS:
 *    none
 *
 */

void changeFgColour( Command* cmd, GraphicsState* current )
{
   #ifndef SIMPLE
   current->fgColour = atoi( cmd->value );
   setFgColour( current->fgColour );
   #endif
}




/*
 * NAME: changeBgColour()
 * PURPOSE: Sets the background colour of the terminal.
 * HOW IT WORKS: - Grabs the background colour value from the command struct 
 *                 using atoi() to store the validated command in the current 
 *                 graphics state.
 *               - Calls setBgColour to the command value grabbed.
 * RELATIONS:
 *    draw() - Calling function to set background colour.
 *            (passes in current state of graphics and command data  from list.)
 *    setBgColour - function within effects.c file to set the background colour 
 *                  of the terminal.
 * IMPORTS:
 *    cmd - Command data to grab background colour to set.
 *    current - Graphics state data to set background colour.
 * EXPORTS:
 *    none
 *
 */

void changeBgColour( Command* cmd, GraphicsState* current )
{
   #ifndef SIMPLE
   current->bgColour = atoi( cmd->value );
   setBgColour( current->bgColour );
   #endif
}




/*
 * NAME: setPattern()
 * PURPOSE: Sets the pattern (character) to be drawn with on the terminal.
 * HOW IT WORKS: - Grabs the pattern value from the command struct by simply 
 *                 grabbing the first char within the validated value string.
 *               - Sets the current pattern to the character value.
 * RELATIONS:
 *    draw() - Calling function to set pattern.
 *            (passes in current state of graphics and command data from list.)
 *    line() - line() requires a current pattern to be printed onto the 
 *             terminal output.
 * IMPORTS:
 *    cmd - Command data to grab pattern to set.
 *    current - Graphics state data to set pattern.
 * EXPORTS:
 *    none
 */

void setPattern( Command* cmd, GraphicsState* current )
{
   current->pattern = ( cmd->value )[0];
}
  



/*
 * NAME: plotPoint()
 * PURPOSE: Allows line() in effects.c to plot a simple character onto the screen.
 * HOW IT WORKS: - Takes plot data (void* to remain generic) to be typecasted 
 *                 to a pointer to a character, printing the character out to 
 *                 the terminal.
 * RELATIONS:
 *    drawLine() - Passes pointer to this function to line().
 *    line() - line() requires a current pattern data to be printed onto the 
 *             terminal output.
 * IMPORTS:
 *    plotData - void pointer to plot data to be typecasted to a character and 
 *               printed out.
 * EXPORTS:
 *    none
 */ 
 
void plotPoint( void* plotData )
{
   char* ptr = ( char* )plotData;
   char pattern = *ptr;
   /* Print single pattern on screen */
   printf( "%c", pattern );
}
                
