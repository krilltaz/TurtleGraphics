/* FILE: listoperations.h
 * AUTHOR: Kyle Notani | 19149918
 * UNIT: UCP COMP1000
 * PURPOSE: Header file associated with listoperations.c
 */

#ifndef LISTOPERATIONS_H
   #define LISTOPERATIONS_H
   
   #include "linkedlist.h"

   /* Constructs an empty generic linked list. */
   LinkedList* constructList();
   
   /* Inserts a given value into a given list at the start. */
   void insertFirst( LinkedList* list, void* value );

   /* Inserts a given value into a given list at the end. Used particularly to
    * maintain the natural ordering of read in commands from a file in the same
    * way.
    */
   void insertLast( LinkedList*, void* value );
   
   
   /* Checks if a given list is empty before carrying out any list operations
    * which other functions use.
    */
   int isEmpty( LinkedList* list );

   
   /* Deallocates the list stored on heap memory along with any nodes that 
    * contain values.
    * Also makes sure every allocated command is no longer stored on heap memory.
    */ 
   void freeList( LinkedList* list );

#endif
