#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct NODE                                         //定义链表结构体
{
    int num;
    struct NODE *next;
    struct NODE *pre;
}NODE;
typedef NODE *LIST;                                         //重定义链表头指针
typedef NODE *POSITION;                                     //重定义链表位置指针
void writerandom(char fileName[100]);
NODE *readFile(NODE *head,char filename[100]);              //读取文件，建立链表
NODE *appendNode(NODE *head,int s);                         //建立链表的具体操作
void dispList(NODE *head);                                  //显示链表元素
NODE *findpivot(NODE *p,NODE *q);
void swap(NODE *p,NODE *q);
int isBehind(NODE *p,NODE *q);
NODE *partion(NODE *head,NODE *a,NODE *b,NODE *pi);
NODE *bubbleSort(NODE *head);
int quicksort(NODE *head,NODE *a,NODE * b,NODE *k1);
int main()
{
    LIST head = NULL;
    POSITION end = NULL;
    int i;
    char s[100] = "data.txt";
    writerandom(s);
    clock_t start,finish;
    double duration;
    head = readFile(head,s);
    if(head==NULL)
    {
        printf("Empty List!");
    }
    else
    {
        printf("排序前的链表是:\n");
        dispList(head);
        start = clock();
        head = bubbleSort(head);
        finish = clock();
        printf("冒泡排序后的链表是:\n");
        dispList(head);
        duration = (double)(finish-start)/CLOCKS_PER_SEC;
        printf("冒泡排序所用的时间是%fseconds\n",duration);
        head = NULL;
        head = readFile(head,s);
        end = head;
        while(end->next!=NULL)
        {
            end = end->next;
        }
        start = clock();
        i = quicksort(head,head,end,end);
        finish = clock();
        printf("快速排序后的链表是:\n");
        dispList(head);
        duration = (double)(finish-start)/CLOCKS_PER_SEC;
        printf("快速排序所用的时间是%lfseconds\n",duration);
    }
    return 0;
}

NODE *appendNode(NODE *head,int s)
{
    POSITION p = NULL;
    POSITION pr = head;
    p = (NODE *)malloc(sizeof(NODE));
    if(head == NULL)
    {
        head = p;
        p->pre = NULL;
        p->next = NULL;
    }
    else
    {
        while(pr->next!=NULL)
        {
            pr = pr->next;
        }
        pr->next = p;
        p->pre = pr;
    }
    p->num = s;
    p->next = NULL;
    return head;
}
void writerandom(char fileName[100])
{
    FILE *fp;
    int i,x;
    fp = fopen(fileName,"w+");
    srand((int)time(NULL));
    for(i=0;i<20;i++)
    {
        x = rand()%1000;
        fprintf(fp,"%d ",x);
    }
    fclose(fp);
}

NODE *readFile(NODE *head,char fileName[100])
{
    FILE *fp;
    int c[10] = {0};
    int rs = 0;
    int i,j;
    char ch;
    int bit = 0;
    fp = fopen(fileName,"r");
    while((ch=fgetc(fp))!=EOF)
    {
        /*读取字符元素，不为空格则存于一个整形数组中，
        直到读取到空格，则此数值读取结束，将整形数组中的元素
        转换成对应整型数值（通过乘十），再将该数组及标记变量bit清零*/
        if(ch!=' ')
        {
            c[bit]=(int)ch-48;//转换ASICII成整形
            bit++;
        }
        else
        {
            for(i=0;i<bit;i++)
            {
                for(j=0;j<bit-i-1;j++)
                {
                    c[i] = c[i]*10;
                }
                rs+=c[i];
            }
            head = appendNode(head,rs);
            rs = 0;
            bit = 0;
            for(i=0;i<10;i++)
            {
                c[i]=0;
            }
        }
    }
    for(i=0;i<bit;i++)
    {
        for(j=0;j<bit-i-1;j++)
        {
            c[i] = c[i]*10;
        }
        rs+=c[i];
    }
    head = appendNode(head,rs);
    rs = 0;
    bit = 0;
    for(i=0;i<10;i++)
    {
        c[i]=0;
    }
    fclose(fp);
    return head;
}

void dispList(NODE *head)
{
    /*从链表头部开始遍历结点，显示每个结构体中的num值，再将位置指针恢复头部*/
    POSITION p = head;
    if(head==NULL)
    {
        printf("Empty List!\n");
    }
    while(p!=NULL)
    {
        printf("%d",p->num);
        putchar(' ');
        p = p->next;
    }
    printf("\n");
    p = head;
}

NODE *findpivot(NODE *p,NODE *q)
{
    int firstkey;
    POSITION k;
    firstkey = p->num;
    if(p==q)
    {
        return NULL;
    }
    else
    {
        for(k=p->next;k!=q;p=p->next)
        {
            if(k->num>firstkey)
            {
                return k;
            }
            if(k->num<=firstkey)
            {
                return p;
            }
        }
        return k;
    }

}

void swap(NODE *p,NODE *q)
{
    int temp;
    temp = p->num;
    p->num = q->num;
    q->num = temp;
    return;
}

int isBehind(NODE *p,NODE *q)
{
    POSITION a = p;
    POSITION b = q;
    while(a!=NULL)
    {
        if(a==b)
        {
            return 1;
        }
        a = a->next;
    }
    return 0;
}

NODE *partion(NODE *head,NODE *a,NODE *b,NODE *pi)
{
    POSITION p,q;
    int pif = pi->num;
    int i;
    p = a;
    q = b;
    i = isBehind(p,q);
    while(i)
    {
        while(p->num<pif)
        {
            p = p->next;
        }
        while(q->num>pif)
        {
            q = q->pre;
        }
        if(p!=q&&p->num==q->num&&p->num==pif&&p->next!=q)
        {
            q = q->pre;
        }
        swap(p,q);
        i = isBehind(p,q);
        if(p==q)
        {
            return p;
        }
        if(p!=q&&p->num==q->num&&p->num==pif&&p->next==q)
        {
            return p;
        }
    }
    return p;
}

NODE *bubbleSort(NODE *head)
/*冒泡排序法对链表进行排序*/
{
    POSITION p,q,h;
    if(head==NULL)
    {
        printf("Empty List!\n");
        return head;
    }
    h = (NODE *)malloc(sizeof(NODE));
    h->next = head;
    h->num = 0;
    for(q=h;q->next!=NULL;q=q->next)//从第一个元素开始找
    {
        for(p=q;p->next!=NULL;p=p->next)
        {
            if(p->next->num<q->next->num)
            {
                swap(p->next,q->next);
            }
        }
    }
    return h->next;
}

int quicksort(NODE *head,NODE *a,NODE *b,NODE *k1)
{
    POSITION pi,k;
    int rs;
    pi = findpivot(a,b);
    if(pi!=NULL)
    {
        k = partion(head,a,b,pi);
        if(k==k1)
        {
            return 1;
        }
        if(k->pre!=NULL)
        {
            rs = quicksort(head,a,k->pre,k);
            if(rs==0)
            {
               rs = quicksort(head,k,b,k);
            }
            if(rs==1)
            {
                rs = quicksort(head,k->next,b,k);
            }
        }
    }
    return 0;
}
