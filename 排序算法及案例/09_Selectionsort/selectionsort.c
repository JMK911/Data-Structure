
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

void Swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void SelectionSort(int n, int *a) {  
    for(int i = 0; i < n - 1; ++i) { //外循环控制起始位置    
        int min = i;                 //min记录最小值的下标
        for(int j = i+1; j < n; ++j) { //内循环寻找起始位置及之后的最小值
            if(a[j] < a[min]) {
                min = j;         //更新最小值
            }
        }
        Swap(&a[i], &a[min]);   //将最小值换到起始位置，然后起始位置后移一位，重复上述操作。   
    }
}

int main() {
    int n;
    printf("请输入数组的尺寸：\n");
    while(scanf("%d", &n) != EOF) {
        printf("请输入%d个数组元素：\n",n);
        Input(n, a);
        SelectionSort(n, a);
        Output(n, a);
        printf("可以再次排序新的数组,");
        system("pause");
        printf("请输入数组的尺寸：\n");
    }
    return 0;
} 

