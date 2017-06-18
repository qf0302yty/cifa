#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct NODE                                         //��������ṹ��
{
    int num;
    struct NODE *next;
    struct NODE *pre;
}NODE;
typedef NODE *LIST;                                         //�ض�������ͷָ��
typedef NODE *POSITION;                                     //�ض�������λ��ָ��
void writerandom(char fileName[100]);
NODE *readFile(NODE *head,char filename[100]);              //��ȡ�ļ�����������
NODE *appendNode(NODE *head,int s);                         //��������ľ������
void dispList(NODE *head);                                  //��ʾ����Ԫ��
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
        printf("����ǰ��������:\n");
        dispList(head);
        start = clock();
        head = bubbleSort(head);
        finish = clock();
        printf("ð��������������:\n");
        dispList(head);
        duration = (double)(finish-start)/CLOCKS_PER_SEC;
        printf("ð���������õ�ʱ����%fseconds\n",duration);
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
        printf("����������������:\n");
        dispList(head);
        duration = (double)(finish-start)/CLOCKS_PER_SEC;
        printf("�����������õ�ʱ����%lfseconds\n",duration);
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
        /*��ȡ�ַ�Ԫ�أ���Ϊ�ո������һ�����������У�
        ֱ����ȡ���ո������ֵ��ȡ�����������������е�Ԫ��
        ת���ɶ�Ӧ������ֵ��ͨ����ʮ�����ٽ������鼰��Ǳ���bit����*/
        if(ch!=' ')
        {
            c[bit]=(int)ch-48;//ת��ASICII������
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
    /*������ͷ����ʼ������㣬��ʾÿ���ṹ���е�numֵ���ٽ�λ��ָ��ָ�ͷ��*/
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
/*ð�����򷨶������������*/
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
    for(q=h;q->next!=NULL;q=q->next)//�ӵ�һ��Ԫ�ؿ�ʼ��
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
