#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct KeyValue{
    int key;
    int data;
} KeyValue;

typedef KeyValue DataType;

typedef struct TreeNode{
    DataType data;
    int height;//树高
    struct TreeNode *left, *right;
} TreeNode;

int CompareData(DataType a,DataType b)
{
    if(a.key<b.key)
    {
        return -1;
    }else if(a.key>b.key)
    {
        return 1;
    }
    return 0;
}

TreeNode *AVLRemove(TreeNode *T, DataType dt);
bool AVLFind(TreeNode *T, DataType dt);

int max(int a,int b)
{
    return a > b ? a : b;
}

// 创建树节点
TreeNode *AVLCreateNode(DataType dt)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->data = dt;
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

//获取树高
int AVLGetHeight(TreeNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

// 重新计算节点的树高，每次旋转或平衡时用到
void AVLCalcHeight(TreeNode *node)
{
    if(node==NULL)
    {
        return;
    }
    node->height= 1 + max(AVLGetHeight(node->left), AVLGetHeight(node->right));
}

// 获取平衡因子，用以决定树不平衡时的形态LL/LR/RR/RL
int AVLGetBalanceFactor(TreeNode *node)
{
    if(node==NULL)
    {
        return 0;
    }
    return AVLGetHeight(node->left) - AVLGetHeight(node->right);
}

// 当前树的左子树较重，需要对树进行右旋操作，将当前树的根节点T放到T->left的右侧
TreeNode *RRotate(TreeNode *T)
{
    TreeNode *L = T->left;
    T->left = L->right;
    L->right = T;
    AVLCalcHeight(T);//旋转一次，节点的树高发生变化，只有T和L发生了变化
    AVLCalcHeight(L);//虽然L的右子树移动到旋转后的T下，但是树高没有变化
    return L;
}

// 当前树的右子树较重，需要对树进行左旋操作，将当前树的根节点T放到T->right的左侧
TreeNode *LRotate(TreeNode *T)
{
    TreeNode *R = T->right;
    T->right = R->left;
    R->left = T;
    AVLCalcHeight(T);
    AVLCalcHeight(R);
    return R;
}

TreeNode *AVLTreeLL(TreeNode *T)
{
    return RRotate(T);
}

TreeNode *AVLTreeRR(TreeNode *T)
{
    return LRotate(T);
}

TreeNode *AVLTreeLR(TreeNode *T)
{
    T->left = LRotate(T->left);
    return RRotate(T);
}

TreeNode *AVLTreeRL(TreeNode *T)
{
    T->right = RRotate(T->right);
    return LRotate(T);
}

//根据平衡因子进行树形判断，然后进行旋转操作
TreeNode *AVLBalance(TreeNode *T)
{
    int bf = AVLGetBalanceFactor(T);
    if(bf>1)
    {
        if(AVLGetBalanceFactor(T->left)>0)
        {
            T = AVLTreeLL(T);
        }else{
            T = AVLTreeLR(T);
        }
    }
    if(bf<-1)
    {
        if(AVLGetBalanceFactor(T->right)>0)
        {
            T = AVLTreeRL(T);
        }else{
            T = AVLTreeRR(T);
        }
    }
    return T;
}

//根据二叉树的性质，节点root的左子树都小于root,而右子树都大于root
//所以树的最小值必然是左子树的左子树探到底，就算左子树的倒数第二层节点只有右叶子，
//树的最小值也应为倒数第二层那个root,因为右叶子大于root;
TreeNode *AVLGetMin(TreeNode *T)
{
    while(T&&T->left)
    {
        T = T->left;
    }
    return T;
}

TreeNode *AVLGetMax(TreeNode *T)
{
    while(T&&T->right)
    {
        T = T->right;
    }
    return T;
}

//AVL的插入操作，递归调用函数本身，直到满足二叉树性质插入到合适的位置，插入一次平衡一次；
TreeNode *AVLInsert(TreeNode *T,DataType dt)
{
    int cmpResult;
    if(T==NULL)
    {
        T = AVLCreateNode(dt);
        return T;
    }
    if(AVLFind(T,dt))
    {
        return T;
    }
    cmpResult = CompareData(dt, T->data);
    if(cmpResult>0)
    {
        T->right = AVLInsert(T->right, dt);
    }else{
        T->left = AVLInsert(T->left, dt);
    }
    return AVLBalance(T);//注意递归返回时，每一层都要重新平衡。
}

bool AVLFind(TreeNode *T,DataType dt){
    int cmpResult;
    if(T==NULL)
    {
        return false;
    }
    cmpResult = CompareData(dt, T->data);
    if(cmpResult>0)
    {
        return AVLFind(T->right,dt);
    }else if(cmpResult<0)
    {
        return AVLFind(T->left, dt);
    }
    return true;
}

TreeNode *AVLRemoveRoot(TreeNode *T)
{
    TreeNode *retnode;
    if(T==NULL)
    {
        return NULL;
    }
    if(!T->left&&!T->right)//没有左右子树
    {
        free(T);
        return NULL;
    }
    if(T->left&&!T->right)//只有左子树
    {
        retnode = T->left;
        free(T);
        return retnode;
    }else if(T->right&&!T->left)//只有右子树
    {
        retnode = T->right;
        free(T);
        return retnode;
    }

    if(AVLGetHeight(T->left)>AVLGetHeight(T->right))
    {
        T->data = AVLGetMax(T->left)->data;//左子树较重,此处并不是真的删除T节点，而是用左子树的最大值替换T的值
        T->left = AVLRemove(T->left, T->data);//左子树最大值的节点在完成给T赋值操作后就无用了，要被删掉
    }else{
        T->data = AVLGetMin(T->right)->data;//右子树较重
        T->right = AVLRemove(T->right, T->data);//右子树较重则取右子树的最小值，这样放到根节点，才能满足二叉树左子树都小于右子树的性质
    }
    AVLCalcHeight(T);//节点变动，必须重新计算树高
    return T;//返回删除根节点后的树
}

//上一个函数为删除节点输入就是要删除的节点，这一个函数为删除对应数值的节点
//所以需要调用上一个函数，但是当此节点的左右子树都存在时，就涉及到查找树的最大值节点
//替换要删除节点并删除最大值原先节点的情况，有涉及到了查找删除操作，所以两个函数相互调用。
TreeNode *AVLRemove(TreeNode *T,DataType dt)
{
    int cmpResult;
    if(T==NULL)
    {
        return NULL;
    }
    cmpResult = CompareData(dt, T->data);
    if(cmpResult==0)
    {
        return AVLRemoveRoot(T);
    }else if(cmpResult<0)
    {
        T->left = AVLRemove(T->left, dt);
    }else{
        T->right = AVLRemove(T->right, dt);
    }
    return AVLBalance(T);
}

void AVLDestroy(TreeNode *T)
{
    if(T==NULL)
    {
        return;
    }
    AVLDestroy(T->left);
    AVLDestroy(T->right);
    free(T);//后续遍历的删除能够保证根节点是最后删除的
}

//节点数值的打印
void visit(DataType a)
{
    printf("%d ", a.key);
}

//树的打印
void AVLprint(TreeNode *T)
{
    if (T == NULL)
    {
        return;
    }
    AVLprint(T->left);
    visit(T->data);
    AVLprint(T->right);//中序遍历打印二叉树的数值，都是递增排序；
}