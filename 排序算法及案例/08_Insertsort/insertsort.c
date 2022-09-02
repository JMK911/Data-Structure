#include <stdio.h>
#include <stdlib.h>

int a[1010];

void Input(int n, int *a) {
    for(int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
}

void Output(int n, int *a) {
    printf("排序后的数组为：");
    for(int i = 0; i < n; ++i) {
        if(i)
            printf(" ");
        printf("%d", a[i]);
    }
    puts("");
}

void InsertSort(int n, int *a) {       
    int i, j; 
    for(i = 1; i < n; ++i) {        //外循环控制末尾位置
        int x = a[i];                  
        for(j = i-1; j >= 0; --j) {  //内循环从末尾位置向前寻找比末尾位置大的数  
            if(x <= a[j]) {          
                a[j+1] = a[j];       //只要比末尾位置的数大，就将该数后移，该数的位置空出  
            }else
                break;              //只要找到比末尾位置的数小的数，就停止   
        }
        a[j+1] = x;                 //退出循环时，a[j]<x，所以此时的空位应该是j+1，在空位插入末尾位置的数  
    }                               //注意，末尾位置是从小到大，每一次外循环开始，都意味着末尾位置之前的数组都已经升序排列。
} 

int main() {
    int n;
    printf("请输入数组的尺寸：\n");
    while(scanf("%d", &n) != EOF) {
        printf("请输入%d个数组元素：\n",n);
        Input(n, a);
        InsertSort(n, a);
        Output(n, a);
        printf("可以再次排序新的数组,");
        system("pause");
        printf("请输入数组的尺寸：\n");
    }
    return 0;
} 

