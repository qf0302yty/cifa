#include<stdio.h>
#include<math.h>
#include<stdlib.h>
typedef struct polynode                                       //定义多项式结构体
{
    int coef;                                                 //系数
    int exp;                                                  //指数
    struct polynode *link;
}polynode;
typedef polynode *polypointer;                                //重命名结构体位置指针
polypointer attach(int c,int e,polypointer d);                //在链表末段链接新节点
polypointer read(int n);                                      //按输入多项式项数读取多项式节点并创建链表
void disPlay(polypointer p);                                  //输出指定链表
polypointer padd(polypointer a,polypointer b);                //两个多项式求和
polypointer order(polypointer a);                             //链表排序
int main()
{
    int n1,n2;
    polypointer a = NULL;
    polypointer b = NULL;
    polypointer d = NULL;
    printf("请输入多项式a的项数:");
    scanf("%d",&n1);
    a = read(n1);
    printf("请输入多项式b的项数:");
    scanf("%d",&n2);
    b = read(n2);
    d = padd(a,b);
    d = order(d);
    printf("多项式a为:");
    disPlay(a);
    printf("\n");
    printf("多项式b为:");
    disPlay(b);
    printf("\n");
    printf("多项式a与b的和是:");
    disPlay(d);
    return 0;
}

polypointer attach(int c,int e,polypointer d)
/*根据输入数据创建节点，并链接在指定链表末尾，输入指针为原链表末尾*/
{
    polypointer x;
    x = (polynode *)malloc(sizeof(polynode));
    x->coef = c;
    x->exp = e;
    x->link = NULL;
    d->link = x;
    return x;
}

polypointer read(int n)
/*根据预先输入的多项式项数，读取键盘输入值，并调用attach()函数，创建链表*/
{
    int n1,n2,i;
    polypointer d = (polynode *)malloc(sizeof(polynode));
    polypointer head = d;
    for(i=1;i<=n;i++)
    {
        printf("请输入第%d项的系数与指数(如3x^14请输入3 14):",i);
        scanf("%d %d",&n1,&n2);
        attach(n1,n2,d);
        d = d->link;
    }
    return head;
}

void disPlay(polypointer p)
/*显示多项式，即遍历链表后输出，输出形式模仿数学格式*/
{
    p = p->link;
    while(p->link!=NULL)
    {
        if(p->exp==0)
        {
            printf("%d",p->coef);
            printf("+");
        }
        else
        {
            printf("%dx^%d",p->coef,p->exp);
            printf("+");
        }
        p = p->link;
    }
    if(p->exp==0)
    {
        printf("%d",p->coef);
    }
    else
    {
        printf("%dx^%d",p->coef,p->exp);
    }
}

polypointer padd(polypointer a,polypointer b)
/*两个多项式求和，返回新多项式链表头指针*/
{
    polypointer p,q,c,d;
    int x;
    p = a->link;
    q = b->link;
    c = (polynode *)malloc(sizeof(polynode));
    d = c;
    while((p!=NULL)&&(q!=NULL))               //两个多项式都未到达末尾
    {
        if(p->exp==q->exp)                    //两个同阶单项式相加，相加后作为一个单项式添加到新链表
        {
            x = p->coef + q->coef;
            if(x)
            {
                d = attach(x,p->exp,d);
            }
            p = p->link;
            q = q->link;
            continue;
        }
        else if(p->exp>q->exp)                //p大q小，将大的添加到新链表并向后移动指针
        {
            d = attach(p->coef,p->exp,d);
            p = p->link;
            continue;
        }
        else if(p->exp<q->exp)                //q大p小，将大的添加到新链表并向后移动指针
        {
            d = attach(q->coef,q->exp,d);
            q = q->link;
            continue;
        }
    }
    while(p!=NULL)                            //若p长度较长，将剩下无法合并的单项式全部添加
    {
        d = attach(p->coef,p->exp,d);
        p = p->link;
    }
    while(q!=NULL)                            //若q长度较长，将剩下无法合并的单项式全部添加
    {
        d = attach(q->coef,q->exp,d);
        q = q->link;
    }
    d->link = NULL;
    return c;
}

polypointer order(polypointer a)
/*冒泡排序法对链表进行排序*/
{
    polypointer p,q,temp1,temp2;
    if(a==NULL)
    {
        printf("Empty List!\n");
        return a;
    }
    for(q=a;q->link!=NULL;q=q->link)//从第一个元素开始找
    {
        for(p=q;p->link!=NULL;p=p->link)
            /*从一层循环对应元素向后寻找，每找到后一个元素比前一个小都进行交换，
            直到本轮最大的元素在最后。再进行下一轮寻找，上一轮最大的元素不予寻找
            此时q一定在p之前*/
        {
            if(p->link->exp>q->link->exp)
            {
                if(q->link==p)//当两个元素中间只间隔一个元素时
                {
                    temp1=p->link;
                    p->link=p->link->link;
                    temp1->link=q->link;
                    q->link=temp1;
                    p=temp1;
                }
                else //当两个元素之间不止间隔一个元素时
                {
                    temp1=p->link;
                    temp2=q->link;
                    p->link=temp1->link;
                    q->link=temp2->link;
                    temp1->link=q->link;
                    q->link=temp1;
                    temp2->link=p->link;
                    p->link=temp2;
                }
            }
        }
    }
    return a;
}

