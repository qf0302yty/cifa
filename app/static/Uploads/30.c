#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#define MAX_VERTEX_NUM 20
int visited[MAX_VERTEX_NUM];
int news[MAX_VERTEX_NUM];
int stack = 0;
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode* next;
}ArcNode;
typedef ArcNode* APOSITION;
typedef struct Vnode
{
    int data;
    ArcNode *firstarc;
}Vnode;
typedef Vnode* VPOSITION;
typedef struct
{
    VPOSITION vertices[MAX_VERTEX_NUM];
    int vexnum;
}ALGraph;
typedef ALGraph* GPOSITION;
GPOSITION NewGraph();
void DFS(GPOSITION g);
void TreesEdges(GPOSITION g);
int NextAdjVex(GPOSITION g,int v);
int main()
{
    GPOSITION g = NULL;
    g = NewGraph();
    printf("图建立完成\n");
    printf("图的深度优先遍历是:");
    DFS(g);
    printf("\n");
    printf("图中所含树边有:");
    TreesEdges(g);
    return 0;
}

GPOSITION NewGraph()
{
    GPOSITION g = NULL;
    APOSITION a = NULL;
    APOSITION ar = NULL;
    g = (GPOSITION)malloc(sizeof(ALGraph));
    int n,i,j;
    char s[MAX_VERTEX_NUM*2] = {0};
    printf("请输入节点个数:");
    scanf("%d",&n);
    g->vexnum = n;
    printf("请输入邻接表:\n");
    for(i=0;i<n;i++)
    {
        g->vertices[i] = (VPOSITION)malloc(sizeof(Vnode));
        g->vertices[i]->data = i+1;
        g->vertices[i]->firstarc = NULL;
        fflush(stdin);
        gets(s);
        fflush(stdin);
        if(((int)s[0]-48)==i)
        {
            for(j=1;j<strlen(s);j++)
            {
                if(s[j]!=' ')
                {
                    a = (APOSITION)malloc(sizeof(ArcNode));
                    a->adjvex = (int)s[j]-48;
                    a->next = NULL;
                    if(g->vertices[i]->firstarc==NULL)
                    {
                        g->vertices[i]->firstarc = a;

                    }
                    else
                    {
                        ar = g->vertices[i]->firstarc;
                        while(ar->next!=NULL)
                        {
                            ar = ar->next;
                        }
                        ar->next = a;
                    }

                }
            }
        }
        memset(s,0,MAX_VERTEX_NUM);
    }
    return g;
}

int NextAdjVex(GPOSITION g,int v)
{
    APOSITION a;
    a = g->vertices[v]->firstarc;
    while(a!=NULL&&visited[a->adjvex]==1)
    {
        a = a->next;
    }
    if(a==NULL)
    {
        return -1;
    }
    else
    {
        return a->adjvex;
    }
}

void DFS(GPOSITION g)
{
    int i,v,w;
    APOSITION a = NULL;
    for(i=0;i<MAX_VERTEX_NUM;i++)
    {
        visited[i]=0;
        news[i]=-1;
    }
    if(visited[0]==0)
    {
        printf("%d ",g->vertices[0]->data);
        visited[0]=1;
        news[stack] = 0;
        stack++;
    }
    while(stack!=0)
    {
        v = news[stack-1];
        a = g->vertices[v]->firstarc;
        if(a!=NULL&&visited[a->adjvex]==0)
        {
            printf("%d ",a->adjvex+1);
            visited[a->adjvex]=1;
            news[stack] = a->adjvex;
            stack++;
        }
        else if(a!=NULL&&visited[a->adjvex]==1)
        {
            w = NextAdjVex(g,v);
            if(w == -1)
            {
                news[stack]=-1;
                stack--;
            }
            else
            {
                printf("%d ",w+1);
                visited[w]=1;
                news[stack]=w;
                stack++;
            }
        }
        else
        {
            news[stack]=-1;
            stack--;
        }
    }
}

void TreesEdges(GPOSITION g)
{
    int i,v,w;
    APOSITION a = NULL;
    for(i=0;i<MAX_VERTEX_NUM;i++)
    {
        visited[i]=0;
        news[i]=-1;
    }
    if(visited[0]==0)
    {
        visited[0]=1;
        news[stack] = 0;
        stack++;
    }
    while(stack!=0)
    {
        v = news[stack-1];
        a = g->vertices[v]->firstarc;
        if(a!=NULL&&visited[a->adjvex]==0)
        {
            printf("(%d,%d) ",v+1,a->adjvex+1);
            visited[a->adjvex]=1;
            news[stack] = a->adjvex;
            stack++;
        }
        else if(a!=NULL&&visited[a->adjvex]==1)
        {
            w = NextAdjVex(g,v);
            if(w == -1)
            {
                news[stack]=-1;
                stack--;
            }
            else
            {
                printf("(%d,%d) ",v+1,w+1);
                visited[w]=1;
                news[stack]=w;
                stack++;
            }
        }
        else
        {
            news[stack]=-1;
            stack--;
        }
    }
}
