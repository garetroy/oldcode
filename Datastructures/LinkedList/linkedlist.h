/*
    Garett Roberts
    mygarett@gmail.com
    
    Purpose:
        LinkedLists are practical for things like optical disks

    Complexity:
        Time:  O(n) for access and search, O(1) for insertion and Deletion
        Space: O(n)
*/

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <stdio.h>
#include <stdlib.h>

/*
    Contains:
        LL* next
        int data
*/
typedef struct linkedlist LL;

/*
    Returns:
        NULL if unsuccessful
        LL*  if successful
    
    Creates a linkedlist node
*/
LL* linkedlist_create(int data);

/*
    Returns:
        -1 if unsucessful;
         0 if successful;

    Adds linkedlist node at the end of root given
*/
int linkedlist_add(LL* root, int data);

/*
    Returns:
        0 if not found
        1 if found

    Attempts to find the item in the linkedlist
*/
int linkedlist_get(LL* root, int data);

/*
    Returns:
        void
    
    Prints out the linkedlist
*/
void linkedlist_print(LL* root);

/*
    Returns:
        -1 if unsuccessful;
         1 if successful;

    Removes an item from the linked list
*/
int linkedlist_remove(LL* root, int data);

/*
    Returns:
        void

    Destroys linkedlist
*/
void linkedlist_destroy(LL* root);

#endif
