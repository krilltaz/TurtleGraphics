/* FILE: listoperations.c
 * AUTHOR: Kyle Notani | 19149918
 * UNIT: UCP COMP1000
 * PURPOSE: Operations on creation, manipulation, deletion and validation of
 *          generic linked list data structure.
 * OTHER: The operations are focused on a singly-linked, singly-ended
 *        Linked List.
 *        '-1' evaluates to true, '0' evaluates to false.
 * SELF-CITE: The following functions have been submitted for 
 *            Worksheet 7: Structs as practical work on date 19/10/18,
 *            time: 13:46
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"
#include "listoperations.h"
#include "structset.h"


/* NAME: constructList()
 * PURPOSE: Constructs an empty generic linked list.
 * HOW IT WORKS: Allocates a LinkedList struct in heap memory giving 
 *               pointing the head at nothing yet.
 * RELATIONS:
 *    main() - Used to construct the core generic linked list to store
 *             all commands (in a command struct) as the value of each
 *             list node.
 * IMPORTS:
 *    none
 * EXPORTS:
 *    list - a pointer to the allocated LinkedList struct on the heap.
 */

LinkedList* constructList()
{
   /* Allocate a LinkedList struct */
   LinkedList* list = ( LinkedList* )malloc( sizeof( LinkedList ) );
   
   /* If list points to memory for allocated struct, point list head at null */
   if( list != NULL )
   {
      list->head = NULL;
   }

   return list;
}


/* NAME: insertFirst()
 * PURPOSE: Inserts a given value into a given list at the start.
 * HOW IT WORKS: Allocates a new List Node struct in heap memory.
 *               Gives the list node an associated value to be pointed to.
 * RELATIONS:
 *    none
 * IMPORTS:
 *    list - A given list to insert a new node at the start.
 *    value - A pointer to any value to be stored (pointed by node's value) 
 *            within the list.
 * EXPORTS:
 *    none
 */

void insertFirst( LinkedList* list, void* value )
{
   /* Allocate a new node to be inserted */
   LinkedListNode* node = ( LinkedListNode* )malloc( sizeof( LinkedListNode ) );

   /* Give node data */
   node->data = value;

   /* Point new node to the already first node in the list */
   node->next = list->head;

   /* Point the head of list to the new node */
   list->head = node;
}  




/* NAME: insertLast()
 * PURPOSE: Inserts a given value into a given list at the end. Used 
 *          particularly to maintain the natural ordering of read in commands 
 *          from a file in the same way.
 * HOW IT WORKS: Allocates a new List Node struct in heap memory.
 *               Gives the list node an associated value to be pointed to.
 * RELATIONS:
 *    storeCommand() - Used by storeCommand() to store a validated command 
 *                     within a command struct at the end of the list.
 * IMPORTS:
 *    list - A given list to insert a new node at the end.
 *    value - A pointer to any value to be stored (pointed by node's value) 
 *            within the list.
 * EXPORTS:
 *    none
 */

void insertLast( LinkedList* list, void* value )
{
   /* Allocate a new node to be inserted */
   LinkedListNode* node = ( LinkedListNode* )malloc( sizeof( LinkedListNode ) );
   /* Maintain a temporary current pointer pointing to the list's head node */
   LinkedListNode* current = list->head;   

   /* Give new node passed in value */
   node->data = value;
   node->next = NULL;

   /* If there exists no nodes in the list */
   if ( current == NULL )
   {
      list->head = node;
   }
   /* While there exists a next node, loop until the end to be inserted last */
   else
   {
      while( current->next != NULL )
      {
         current = current->next;
      }

      current->next = node;
   }
}




/* NAME: isEmpty()
 * PURPOSE: Checks if a given list is empty before carrying out any list 
 *          operations which other functions use.
 * HOW IT WORKS: Checks if or if not the list head points to any node and 
 *               returns the condition.
 * RELATIONS:
 *    draw() - Checks if the commands were never stored within the list before 
 *             commencing drawing.
 * IMPORTS:
 *    list - A given list to check if empty.
 * EXPORTS:
 *    isEmpty - Boolean evaluating if the list is empty (FALSE) or is not empty.
 */

int isEmpty( LinkedList* list )
{
   int isEmpty = 0;

   /* If no node is pointed by the head, list is empty */
   if( list->head == NULL )
   {
      isEmpty = -1;
   }
   
   return isEmpty;
}
 
 
/* NAME: freeList()
 * PURPOSE: Deallocates the list stored on heap memory along with any nodes 
 *          that contain values.
 *          Also makes sure every allocated command is no longer stored on 
 *          heap memory.
 *          Specifically, TurtleGraphics stores Command structs as node values 
 *          so freeing it aswell must be accomplished.
 * HOW IT WORKS: While a node exists in the list, first free a commands 
 *               associated name and value. Free the command itself afterwards, 
 *               then follow on to free each node itself.
 *               Once all nodes are deallocated, the list node itself will be 
 *               freed.
 * RELATIONS:
 *    main() - Deallocates the constructing list in main() after complete use.
 * IMPORTS:
 *    list - A given list to deallocate.
 * EXPORTS:
 *    none
 */

void freeList( LinkedList* list )
{
   LinkedListNode* node;
   LinkedListNode* nextNode;

   Command* cmd;

   node = list->head;
   
   /* Loop through each node */
   while( node != NULL )
   {
      nextNode = node->next;
      cmd = ( Command* )( node->data );
      /* Free command data */
      free( cmd->name );
      free( cmd->value );
      /* Free command struct */
      free( cmd );
      /* Free list node */
      free( node );

      node = nextNode;
   }
   /* Free entire list */
   free( list );
}


