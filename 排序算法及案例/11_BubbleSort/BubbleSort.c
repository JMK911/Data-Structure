#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int *a,int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

//初始版本
void BubbleSort(int n,int *a){
    for (int j = 1; j < n ;++j){               //外循环控制交换的末尾距离
        for (int i = 0; i < n - j; ++i)        //内循环负责不断比较相邻节点，将最大的节点放至末尾
        {
            if (a[i] > a[i + 1])
            {
                swap(&a[i], &a[i + 1]);
            }
        }
    }
}
//改进版本
void BubbleSort1(int n,int* a){
    bool swapped;
    int last = n - 1;
    do{
        swapped = false;
        for (int i = 0; i < last;++i){          //last控制遍历的重点
            if(a[i]>a[i+1]){                    //不断从下标0开始，将该节点和右边的节点进行比较，将较大的节点换到右边
                swap(&a[i], &a[i + 1]);
                swapped = true;                 //交换过就将swapped置为true
            }
        }
        last--;
    } while (swapped);              //当该轮循环没有发生交换时，说明数组已经按从小到大排序了，不需要再进行后面的操作，退出循环
}
void input(int n,int *a){
    for (int i = 0; i < n;++i){
        scanf("%d",& a[i]);
    }
}
void output(int n,int *a){
    printf("排序后的数组为：");
    for (int i = 0; i < n;++i){
        printf("%d ", a[i]);
    }
    printf("\n");
}
int main(){
    int n;
    printf("请输入数组的尺寸：\n");
    scanf("%d", &n);
    printf("请输入%d个数组元素：\n",n);
    int *a = (int *)malloc(sizeof(int) * n);
    input(n, a);
    BubbleSort1(n, a);
    output(n, a);
    return 0;
}