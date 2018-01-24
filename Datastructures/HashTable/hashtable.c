#include "hashtable.h"

typedef struct node{
    unsigned long key;
    Node*         next;
    int           data;
}Node;

typedef struct table{
    Node**   node_table;
    unsigned long size;
}Table;

Table*
hash_create(void)
{
    int i; 
    
    Table* table = (Table*) malloc(sizeof(Table));
    if(table == NULL)
        return NULL;

    table->size = TABLE_SIZE;

    table->node_table = (Node**) malloc(sizeof(Node*) * table->size);
    if(table->node_table == NULL){
        free(table);
        return NULL;
    }

    for(i = 0; i < table->size; i++)
        table->node_table[i] = NULL;

    return table;
}

unsigned long
hash_hash(int size, int data)
{
    return data % size;
}

int
hash_add(Table* table, int data)
{
    return 0;
}

Node*
hash_lookup(Table* table, int data)
{
    unsigned hash;
    Node     *_node;

    hash = hash_hash(table->size,data);
    for(_node = table->node_table[hash]; _node != NULL; _node = _node->next)
        if(_node->data == data)
            return _node;

    return NULL;
}


