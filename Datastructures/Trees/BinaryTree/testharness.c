#include <stdio.h>
#include "binarytree.h"

int
main()
{
    BST_Tree* tree = bst_create(100);
    int i          = 0;

    for(; i < 100; i++){
        bst_add(tree,i);
    }
    bst_print(tree);
    
    bst_remove(tree, 99);
    if(!bst_get(tree,99))
        fprintf(stdout,"It's not in there\n");
    bst_print(tree);
   
    bst_destroy(tree); 
    return 0;
}
