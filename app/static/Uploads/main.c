#include<stdio.h>
#include<math.h>
#include<stdlib.h>
typedef struct polynode                                       //�������ʽ�ṹ��
{
    int coef;                                                 //ϵ��
    int exp;                                                  //ָ��
    struct polynode *link;
}polynode;
typedef polynode *polypointer;                                //�������ṹ��λ��ָ��
polypointer attach(int c,int e,polypointer d);                //������ĩ�������½ڵ�
polypointer read(int n);                                      //���������ʽ������ȡ����ʽ�ڵ㲢��������
void disPlay(polypointer p);                                  //���ָ������
polypointer padd(polypointer a,polypointer b);                //��������ʽ���
polypointer order(polypointer a);                             //��������
int main()
{
    int n1,n2;
    polypointer a = NULL;
    polypointer b = NULL;
    polypointer d = NULL;
    printf("���������ʽa������:");
    scanf("%d",&n1);
    a = read(n1);
    printf("���������ʽb������:");
    scanf("%d",&n2);
    b = read(n2);
    d = padd(a,b);
    d = order(d);
    printf("����ʽaΪ:");
    disPlay(a);
    printf("\n");
    printf("����ʽbΪ:");
    disPlay(b);
    printf("\n");
    printf("����ʽa��b�ĺ���:");
    disPlay(d);
    return 0;
}

polypointer attach(int c,int e,polypointer d)
/*�����������ݴ����ڵ㣬��������ָ������ĩβ������ָ��Ϊԭ����ĩβ*/
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
/*����Ԥ������Ķ���ʽ��������ȡ��������ֵ��������attach()��������������*/
{
    int n1,n2,i;
    polypointer d = (polynode *)malloc(sizeof(polynode));
    polypointer head = d;
    for(i=1;i<=n;i++)
    {
        printf("�������%d���ϵ����ָ��(��3x^14������3 14):",i);
        scanf("%d %d",&n1,&n2);
        attach(n1,n2,d);
        d = d->link;
    }
    return head;
}

void disPlay(polypointer p)
/*��ʾ����ʽ�����������������������ʽģ����ѧ��ʽ*/
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
/*��������ʽ��ͣ������¶���ʽ����ͷָ��*/
{
    polypointer p,q,c,d;
    int x;
    p = a->link;
    q = b->link;
    c = (polynode *)malloc(sizeof(polynode));
    d = c;
    while((p!=NULL)&&(q!=NULL))               //��������ʽ��δ����ĩβ
    {
        if(p->exp==q->exp)                    //����ͬ�׵���ʽ��ӣ���Ӻ���Ϊһ������ʽ��ӵ�������
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
        else if(p->exp>q->exp)                //p��qС���������ӵ�����������ƶ�ָ��
        {
            d = attach(p->coef,p->exp,d);
            p = p->link;
            continue;
        }
        else if(p->exp<q->exp)                //q��pС���������ӵ�����������ƶ�ָ��
        {
            d = attach(q->coef,q->exp,d);
            q = q->link;
            continue;
        }
    }
    while(p!=NULL)                            //��p���Ƚϳ�����ʣ���޷��ϲ��ĵ���ʽȫ�����
    {
        d = attach(p->coef,p->exp,d);
        p = p->link;
    }
    while(q!=NULL)                            //��q���Ƚϳ�����ʣ���޷��ϲ��ĵ���ʽȫ�����
    {
        d = attach(q->coef,q->exp,d);
        q = q->link;
    }
    d->link = NULL;
    return c;
}

polypointer order(polypointer a)
/*ð�����򷨶������������*/
{
    polypointer p,q,temp1,temp2;
    if(a==NULL)
    {
        printf("Empty List!\n");
        return a;
    }
    for(q=a;q->link!=NULL;q=q->link)//�ӵ�һ��Ԫ�ؿ�ʼ��
    {
        for(p=q;p->link!=NULL;p=p->link)
            /*��һ��ѭ����ӦԪ�����Ѱ�ң�ÿ�ҵ���һ��Ԫ�ر�ǰһ��С�����н�����
            ֱ����������Ԫ��������ٽ�����һ��Ѱ�ң���һ������Ԫ�ز���Ѱ��
            ��ʱqһ����p֮ǰ*/
        {
            if(p->link->exp>q->link->exp)
            {
                if(q->link==p)//������Ԫ���м�ֻ���һ��Ԫ��ʱ
                {
                    temp1=p->link;
                    p->link=p->link->link;
                    temp1->link=q->link;
                    q->link=temp1;
                    p=temp1;
                }
                else //������Ԫ��֮�䲻ֹ���һ��Ԫ��ʱ
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

