/* FILE: linkedlist.h
 * AUTHOR: Kyle Notani | 19149918
 * UNIT: UCP COMP1000
 * PURPOSE: Header file associated list operations
 *          across a generic linked list.
 */

#ifndef LINKEDLIST_H
   #define LINKEDLIST_H
   
   /* Struct Declaration for a Generic Linked List Node
    * Properties: Singly-Linked 
    */
   typedef struct LinkedListNode
   {
      void* data;
      struct LinkedListNode* next;
   } LinkedListNode;

   /* Struct Declaration for a Generic Linked List 
    * Properties: Singly-Ended
    */
   typedef struct
   {
      LinkedListNode* head;
   } LinkedList;

#endif
