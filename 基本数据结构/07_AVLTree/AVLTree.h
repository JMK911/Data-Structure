#ifndef _AVLTREE_H
#define _AVLTREE_H

typedef struct KeyValue{
    int key;
    int data;
} KeyValue;

typedef KeyValue DataType;

typedef struct TreeNode{
    DataType data;
    int height;
    struct TreeNode *left, *right;
} TreeNode;

int CompareData(DataType a, DataType b);

TreeNode *AVLRemove(TreeNode *T, DataType dt);

int max(int a, int b);

TreeNode *AVLCreateNode(DataType dt);

int AVLGetHeight(TreeNode *node);

void AVLCalcHeight(TreeNode *node);

int AVLGetBalanceFactor(TreeNode *node);

TreeNode *RRotate(TreeNode *T);

TreeNode *LRotate(TreeNode *T);

TreeNode *AVLTreeLL(TreeNode *T);

TreeNode *AVLTreeRR(TreeNode *T);

TreeNode *AVLTreeLR(TreeNode *T);

TreeNode *AVLTreeRL(TreeNode *T);

TreeNode *AVLBalance(TreeNode *T);

TreeNode *AVLGetMin(TreeNode *T);

TreeNode *AVLGetMax(TreeNode *T);

TreeNode *AVLInsert(TreeNode *T, DataType dt);

bool *AVLFind(TreeNode *T, DataType dt);

TreeNode *AVLRemoveRoot(TreeNode *T);

TreeNode *AVLRemove(TreeNode *T, DataType dt);

void AVLDestroy(TreeNode *T);

void AVLprint(TreeNode *T);

void visit(DataType a);

#endif
