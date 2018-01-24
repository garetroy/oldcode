#include "linkedlist.h"

int
main()
{
    int i    = 0;
    LL* root = linkedlist_create(10);

    for(;i<10;i++){
        linkedlist_add(root,i);
    }
    
    if(linkedlist_get(root,5) == 1){
        fprintf(stdout,"here");
    }

    linkedlist_remove(root,5);

    if(linkedlist_get(root,5) == 0)
        fprintf(stdout,"works");

    linkedlist_destroy(root);

    return 0;
}

