/* Testing Binary Tree implementation */
#include <stdio.h>
#include <stdlib.h>

#include "bitree.h"

void print_tree(BiTree *t);
void print_node(BiTreeNode *n, int level);

typedef struct AstNode_ {
    char *type;
    char *value;
} AstNode;

/* Testing the following methods and macros:
    Methods:
      - bitree_init()
      - bitree_destroy()
      - bitree_insert_left()
      - bitree_insert_right()
      - bitree_remove_left()
      - bitree_remove_right()
      - bitree_merge()
    Macros:
      - bitee_size()
      - bitree_root()
      - bitree_is_eob()
      - bitree_is_leaf()
      - bitree_data()
      - bitree_left()
      - bitree_right()
*/
int main()
{
    /* Let's make a parse tree for an expression like a=b+3; */
    
    /* Allocate size for a binary tree and initialize */
    BiTree *tree = malloc(sizeof(*tree));
    if(tree == NULL)
        return -1;
    bitree_init(tree, NULL);

    /* Create the relevant nodes */
    AstNode n0 = {"BINOP", "="};
    AstNode n1 = {"IDENT", "a"};
    AstNode n2 = {"BINOP", "+"};
    AstNode n3 = {"IDENT", "b"};
    AstNode n4 = {"INT", "3"};

    /* Add the root node (pass NULL as the node parameter)  */
    bitree_insert_left(tree, NULL, (void *)&n0);

    /* Add the rest of the nodes */
    bitree_insert_left(tree, bitree_root(tree), (void *)&n1);
    bitree_insert_right(tree, bitree_root(tree), (void *)&n2);
    bitree_insert_left(tree, bitree_right(bitree_root(tree)), (void *)&n3);
    bitree_insert_right(tree, bitree_right(bitree_root(tree)), (void *)&n4);

    /* Print out the tree */
    printf("---- Parse Tree ----\n");
    printf("Expression:  a = b + 3;\n");
    print_tree(tree);
    printf("\n");

    /* Create another expression parse tree (c="hello";) */
    AstNode n5 = {"BINOP", "="};
    AstNode n6 = {"IDENT", "c"};
    AstNode n7 = {"STRING", "\"hello\""};
    BiTree *tree2 = malloc(sizeof(*tree2));
    if(tree2 == NULL)
        return -1;
    bitree_init(tree2, NULL);
    bitree_insert_left(tree2, NULL, (void *)&n5);
    bitree_insert_left(tree2, bitree_root(tree2), (void *)&n6);
    bitree_insert_right(tree2, bitree_root(tree2), (void *)&n7);
    
    /* Allocate an expr_list tree which will hold the merge of the two expressions */
    AstNode n8 = {"EXPR_LIST", "a = b + 3, c = \"hello\";"};
    BiTree *expr_list_tree = malloc(sizeof(*expr_list_tree));
    if(expr_list_tree == NULL)
        return -1;

    /* Merge the trees (NOTE: Cannot use tree or tree2 anymore) */
    bitree_merge(expr_list_tree, tree, tree2, (void *)&n8);

    /* Print out the merge */
    printf("---- Parse Tree (Merged) ----\n");
    printf("Expression: a = b + 3, c = \"hello\";\n");
    print_tree(expr_list_tree);
    printf("\n");

    /* Remove some nodes -- Doesnt really make sense for this example but good to test out */
    bitree_remove_left(expr_list_tree, bitree_left(bitree_root(expr_list_tree)));
    bitree_remove_right(expr_list_tree, bitree_root(expr_list_tree));
    printf("---- Removed Nodes ----\n");
    printf("Removed: a\n");
    printf("Removed: c = \"hello\"\n");
    print_tree(expr_list_tree);
    printf("\n");

    /* Destroy the tree */
    bitree_destroy(expr_list_tree);

    return 0;
}

/* Function to print out the tree 
    Tree will get printed out as follows:
    
    ROOT
        LEFT
        RIGHT
*/
void print_tree(BiTree *tree)
{
    printf("Size: %d\n", bitree_size(tree));
    print_node(bitree_root(tree), 0);
}

/* Recursive function to print each node */
void print_node(BiTreeNode *n, int level)
{
    /* If the node is the end of the branch (i.e., NULL), dont print anything */
    if(bitree_is_eob(n))
        return;
    
    /* Print spaces for a pretty-print */
    for(int i = 0; i < level; i++)
        printf("  ");
 
    /* Print out the contents of the node */
    AstNode *ast_node = (AstNode *)bitree_data(n);
    printf("(%s, %s)\n", ast_node->type, ast_node->value);
    
    /* Print out the left and right children */
    print_node(bitree_left(n), level + 1);
    print_node(bitree_right(n), level + 1);

}


