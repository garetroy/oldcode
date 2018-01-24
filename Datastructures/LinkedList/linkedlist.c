#include "linkedlist.h"

typedef struct linkedlist{
    LL  *next;
    int data;
}LL;

LL*
linkedlist_create(int data)
{
   LL* node = (LL*) malloc(sizeof(LL));
   if(node == NULL)
        return NULL;
    
    node->data = data;
    node->next = NULL;
    
    return node;
} 

int
linkedlist_add(LL* root, int data)
{
    LL* newnode = linkedlist_create(data);
    if(newnode == NULL)
        return -1;
    
    LL* current = root;

    while(current->next != NULL){
        current = current->next;
    }
    
    current->next = newnode;

    return 0;
}

int
linkedlist_get(LL* root, int data)
{
    if(root == NULL)
        return 0;

    LL* current = root;

    while(current != NULL){

        if(current->data == data)
            return 1;
        
        current = current->next;
    }

    return 0;
}

void
linkedlist_print(LL* root)
{
    if(root == NULL)
        return;

    LL* current = root;
    
    while(current != NULL){
        fprintf(stdout,"%d",current->data);
    }

    fprintf(stdout,"\n");
    
    return;
}

int
linkedlist_remove(LL* root, int data)
{
    if(root == NULL)
        return -1;
    
    LL* current = root;

    while(current != NULL){
        if(current->data == data){
            current = NULL;
            free(current);
            return 1;
        }
        current = current->next;
    }
    
    return -1;
}

void
linkedlist_destroy(LL* root)
{
    if(root == NULL)
        return;
    
    LL* current = root;
    LL* previous;

    while(current->next != NULL){
        previous = current;
        current = current->next;
        previous = NULL;
        free(previous);
    }
    
    free(current);

    return;
}
