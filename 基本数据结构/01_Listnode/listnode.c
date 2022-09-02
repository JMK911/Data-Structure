#include <stdio.h>
#include <stdlib.h>

struct listnode{
    int data;
    struct listnode *next;
};

//创建单个节点
struct listnode *listcreatenode(int data)
{
    struct listnode *node=(struct listnode *)malloc(sizeof(struct listnode));
    node->data=data;
    node->next=NULL;
    return node;
}

//头插法创建链表
struct listnode *listnodecreatebyhead(int n,int *a)
{
    struct listnode *head=NULL,*vtx;
    while(n--)
    {
        vtx=listcreatenode(a[n]);
        vtx->next = head;
        head = vtx;
    }
    return head;
}

void listprint(struct listnode *head)
{
    struct listnode *vtx=head;
    while(vtx)
    {
        printf("%d->",vtx->data);
        vtx = vtx->next;
    }
    printf("NULL");
}

//在位置n(n>=0)处插入值为data的节点
struct listnode *listnodeinput(int i,int data,struct listnode *head,int n)
{
    struct listnode *pre=head,*vtx,*aft;
    if(i==0){
        vtx=listcreatenode(data);
        vtx->next = head;
        head = vtx;
        return head;
    }
    int j=0;
    while(pre&&j<i-1)
    {
        pre=pre->next;
        ++j;
    }
    if(!pre)
    {
        return NULL;
    }

    vtx=listcreatenode(data);
    aft=pre->next;
    pre->next=vtx;
    vtx->next=aft;
    return head;
}

//删除位置n(n>=0)处的节点
struct listnode *listnodedel(struct listnode *head,int n)
{
    int i=0;
    struct listnode *pre=head, *now;
    if(n==0)
    {
        now = head;
        head = head->next;
        free(now);
        return head;
    }
    if(head==NULL)
    {
        return NULL;
    }
    while(pre&&i<n-1)
    {
        pre = pre->next;
        ++i;
    }
    now = pre->next;
    pre->next = now->next;
    free(now);
    return head;
}

//测试程序
int main(){
    int a[5]={0,1,2,3,4};
    int i,data;
    struct listnode *head=listnodecreatebyhead(5,a);
    listprint(head);
    printf("\n");
    printf("\n请输入插入链表的位置(从0开始)和数值: \n");
    scanf("%d%d",&i,&data);
    head=listnodeinput(i,data,head,5);
    listprint(head);
    printf("\n请输入删除链表的位置(从0开始): \n");
    scanf("%d",&i);
    head=listnodedel(head,i);
    listprint(head);
    return 0;
}