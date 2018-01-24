/*
    Garett Roberts
    mygarett@gmail.com

    Purpose:
        Extreamly quick when utilizing a key. 
        Chaching frequently.
        Storing relationships between data

    Complexity:
        Time:  O(n)
        Space: O(n)
*/

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 20

/*
    Contains:
        unsigned long key
        Node*         node
        int           data
*/
typedef struct node Node;

/*
    Contains:
        Node**   node_table;
        unsigned long size;
*/
typedef struct table Table;

/*
    Returns:
        NULL   if unsuccessful
        Table* if successful

    Creates a hashtable
*/
Table* hash_create(void);

/*
    Returns:
        unsigned long

    Returns a hash
*/
unsigned long hash_hash(int size, int data);

/*
    Returns:
        1 if successful
       -1 if unsuccessful

    Adds data to the hashtable
*/
int hash_add(Table* table, int data);

/*
    Returns:
        Node* if successful
        NULL  if unsuccessful

    Looks thorugh the hash table to find a node that has matching data
*/
Node* hash_lookup(Table* table, int data);

#endif
