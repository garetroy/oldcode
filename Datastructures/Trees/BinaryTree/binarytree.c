#include "binarytree.h"

typedef struct bst_tree{
    int       data;
    BST_Tree* left;
    BST_Tree* right;

}BST_Tree;

BST_Tree*
bst_create(int data)
{
    BST_Tree* root = (BST_Tree *) malloc(sizeof(BST_Tree));
    if(root == NULL)
        return NULL;
    
    root->data  = data;
    root->left  = NULL;
    root->right = NULL;
    
    return root;
}

int
bst_add(BST_Tree* root, int data)
{
    if(root == NULL)
        return -1;

    if(data < root->data){
        if(root->left == NULL){
            root->left = bst_create(data);
            return 1;
        } else { 
            return bst_add(root->left,data);
        }
    } else if(data >= root->data) {
        if(root->right == NULL){
            root->right = bst_create(data);
            return 1;
        } else {
            return bst_add(root->right,data);
        }
    }

    return -1;
}

int
bst_get(BST_Tree* root, int data)
{
    if(root == NULL)
        return 0;
    
    if(root->data == data){
        return 1; 
    } else if(root->left != NULL && root->left->data < data) {
        return bst_get(root->left,data);
    } else if(root->right != NULL && root->right->data > data) {
        return bst_get(root->right,data);
    }
    
    return 0;
}

void
bst_print(BST_Tree* root)
{
    if(root == NULL)
        return;
    
    if(root->left != NULL)
        bst_print(root->left);

    fprintf(stdout,"%d,",root->data);
    
    if(root->right != NULL)
        bst_print(root->right);
    
    return;
}

BST_Tree*
bst_min(BST_Tree* root)
{
    if(root == NULL)
        return NULL;
    
    if(root->left != NULL)
        return bst_min(root->left);

    return root;
}

BST_Tree*
bst_max(BST_Tree* root)
{
    if(root == NULL)
        return NULL;
    
    if(root->right != NULL)
        return bst_min(root->right);

    return root;
}

BST_Tree*
bst_remove(BST_Tree* root, int data)
{
    if(root == NULL)
        return NULL;

    if(data < root->data){
        root->left = bst_remove(root->left,data);
    } else if(data > root->data) {
        root->right = bst_remove(root->right,data);
    } else if(root->left == NULL && root->right == NULL) {
        root = NULL;
        free(root);
        return root;
    } else if(root->left == NULL) {
        BST_Tree* newroot = root;
        root = root->right;
        free(newroot);
        return newroot;
    } else if(root->right == NULL) {
        BST_Tree* newroot = root;
        root = root->left;
        free(newroot);
        return newroot;
    } else {
        BST_Tree* minroot = bst_min(root->right);
        root->data = minroot->data;
        root->right = bst_remove(root->right,minroot->data); 
    }
    return root;
}

void
bst_destroy(BST_Tree* root)
{
    if(root == NULL)
        return;
    
    bst_destroy(root->left);
    bst_destroy(root->right);

    free(root);

    return;
}
