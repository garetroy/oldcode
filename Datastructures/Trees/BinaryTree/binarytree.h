/*
    Garett Roberts
    mygarett@gmail.com

    Purpose:
        Binary Trees are more effiecent for memory, only allocating what it needs
        Good for orginizing data

    Complexity:
        Time:  O(n)
        Space: O(n)
*/

#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <stdlib.h>
#include <stdio.h>

/*
    Contains:
        Left and Right nodes (BST_Tree *)
        Data (int)
*/
typedef struct bst_tree BST_Tree;

/*
    Returns:
        BST_TREE* if successful
        NULL      if unsuccessful

    Allocates space for a BST_Tree, loads the data, sets left and right nodes to NULL.
*/
BST_Tree* bst_create(int data);

/*
    Returns:
        1 if successful
       -1 if unsuccessful

    Recursivly finds a place to put the data, sorted on value of the data ( >= on right, < on left), upon finding the spot
    adds the data by using bst_create.
*/
int bst_add(BST_Tree* root, int data);

/*
    Returns:
        1 if data found in tree
        0 if data not found in tree

    Traverses through the tree, trying to find matching data. (Recursivly) 
*/
int bst_get(BST_Tree* root, int data);

/*
    Returns:
        void
    
    Traverses through the left side of the tree first, printing out the data in order. (Recursivly)
*/
void bst_print(BST_Tree* root);

/*
    Returns:
        BST_Tree* if successful
        NULL      if unsucessful

    Recursivly traverses through the tree to find the minimum
*/
BST_Tree* bst_min(BST_Tree* root);

/*
    Returns:
        BST_Tree* if successful
        NULL      if unsucessful

    Recursivly traverses through the tree to find the max
*/
BST_Tree* bst_max(BST_Tree* root);

/*
    Returns:
        NULL       if successful
        BST_Tree * if unsuccessful

    Recursivly traverses through the tree, finding the node it wants to delete, then handles accordingly dependant
    on the desired node's left and right branches.
*/
BST_Tree* bst_remove(BST_Tree* root, int data);

/*
    Returns:
        void

    Recursivly traverses through the tree and deletes the nodes with post-order
*/
void bst_destroy(BST_Tree* root);

#endif
