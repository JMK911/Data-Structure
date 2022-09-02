#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include "AVLTree.h"

//测试案例
int main(){
    int i;
    DataType dt;
    int a[10] = {0, 4, 3, 1, 2, 5, 9, 6, 7, 8};
    TreeNode *T=NULL;
    for (i = 0; i < 10;++i)
    {
        dt.key = a[i];
        dt.data = 0;
        T=AVLInsert(T, dt);
    }
    AVLprint(T);//此处使用中序遍历验证树是否按照从小到大排序。
    printf("\n");
    dt.key = 5;
    dt.data = 0;
    TreeNode *Tnew = AVLRemove(T, dt);//测试remove
    AVLprint(Tnew);
    return 0;
}
