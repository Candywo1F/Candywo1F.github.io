#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100   // 最大顶点数目

/* ---------------- 邻接表边结点 ---------------- */
typedef struct EdgeNode
{
    int adjVex;                // 邻接点编号
    struct EdgeNode *next;     // 指向下一条边
} EdgeNode;

/* ---------------- 邻接表顶点结点 ---------------- */
typedef struct VexNode
{
    int data;                  // 顶点编号
    EdgeNode *firstEdge;       // 第一条边
} VexNode;

/* ---------------- 图结构体 ---------------- */
typedef struct Graph
{
    int n;                              // 顶点总数
    int matrix[MAXN][MAXN];             // 邻接矩阵
    VexNode adjList[MAXN];              // 邻接表
    int visited[MAXN];                  // 访问标记：0 未访问，1 已访问
} Graph;

/**
 * 初始化图
 * num：顶点个数
 */
void InitGraph(Graph *g, int num)
{
    int i, j;
    g->n = num;

    // 初始化邻接矩阵，全部置 0
    for (i = 0; i < g->n; i++)
    {
        for (j = 0; j < g->n; j++)
        {
            g->matrix[i][j] = 0;
        }
    }

    // 初始化邻接表顶点
    for (i = 0; i < g->n; i++)
    {
        g->adjList[i].data = i;
        g->adjList[i].firstEdge = NULL;
    }

    // 访问标记全部初始化为未访问
    memset(g->visited, 0, sizeof(g->visited));
}

/**
 * 添加无向边 u-v
 */
void AddEdge(Graph *g, int u, int v)
{
    EdgeNode *p1, *p2;

    // 邻接矩阵保存边
    g->matrix[u][v] = 1;
    g->matrix[v][u] = 1;

    // 在 u 的边链表插入 v
    p1 = (EdgeNode *)malloc(sizeof(EdgeNode));
    p1->adjVex = v;
    p1->next = g->adjList[u].firstEdge;
    g->adjList[u].firstEdge = p1;

    // 在 v 的边链表插入 u
    p2 = (EdgeNode *)malloc(sizeof(EdgeNode));
    p2->adjVex = u;
    p2->next = g->adjList[v].firstEdge;
    g->adjList[v].firstEdge = p2;
}

/**
 * 输出所有顶点的度
 */
void PrintDegree(Graph *g)
{
    int i, j, cnt;
    printf("===== 各顶点度数 =====\n");
    for (i = 0; i < g->n; i++)
    {
        cnt = 0;
        for (j = 0; j < g->n; j++)
        {
            if (g->matrix[i][j] == 1)
            {
                cnt++;
            }
        }
        printf("顶点 %d 的度 = %d\n", i, cnt);
    }
}

/**
 * BFS：遍历一个连通分量，保存里面所有顶点
 */
void BfsComponent(Graph *g, int start, int comp[], int *len)
{
    int queue[MAXN];
    int front = 0, rear = 0;
    int u, v;

    queue[rear++] = start;
    g->visited[start] = 1;
    comp[(*len)++] = start;

    while (front < rear)
    {
        u = queue[front++];
        for (v = 0; v < g->n; v++)
        {
            if (g->matrix[u][v] == 1 && g->visited[v] == 0)
            {
                g->visited[v] = 1;
                queue[rear++] = v;
                comp[(*len)++] = v;
            }
        }
    }
}

/**
 * 求连通分量以及数量
 */
void GetConnectComponent(Graph *g)
{
    int i;
    int comp[MAXN];
    int len;
    int num = 0;

    // 重置访问标记
    memset(g->visited, 0, sizeof(g->visited));
    printf("\n===== 连通分量 =====\n");

    for (i = 0; i < g->n; i++)
    {
        if (g->visited[i] == 0)
        {
            num++;
            len = 0;
            BfsComponent(g, i, comp, &len);
            printf("第 %d 组：", num);
            for (int k = 0; k < len; k++)
            {
                printf("%d ", comp[k]);
            }
            printf("\n");
        }
    }
    printf("连通分量总个数：%d\n", num);
}

/**
 * BFS 生成树，输出遍历序列
 */
void BfsTree(Graph *g, int start)
{
    int queue[MAXN];
    int front = 0, rear = 0;
    int u, v;

    memset(g->visited, 0, sizeof(g->visited));
    printf("\n===== BFS 广度优先生成树遍历序列（起点：%d）=====\n", start);

    queue[rear++] = start;
    g->visited[start] = 1;

    while (front < rear)
    {
        u = queue[front++];
        printf("%d ", u);
        for (v = 0; v < g->n; v++)
        {
            if (g->matrix[u][v] == 1 && g->visited[v] == 0)
            {
                g->visited[v] = 1;
                queue[rear++] = v;
            }
        }
    }
    printf("\n");
}

/**
 * 无权图单源最短路径 BFS
 */
void ShortestPath(Graph *g, int start)
{
    int dist[MAXN];
    int queue[MAXN];
    int front = 0, rear = 0;
    int u, v;

    memset(g->visited, 0, sizeof(g->visited));
    // -1 代表不可达
    for (int i = 0; i < g->n; i++)
    {
        dist[i] = -1;
    }

    dist[start] = 0;
    queue[rear++] = start;
    g->visited[start] = 1;

    while (front < rear)
    {
        u = queue[front++];
        for (v = 0; v < g->n; v++)
        {
            if (g->matrix[u][v] == 1 && g->visited[v] == 0)
            {
                dist[v] = dist[u] + 1;
                g->visited[v] = 1;
                queue[rear++] = v;
            }
        }
    }

    printf("\n===== 起点 %d 到各顶点最短路径长度 =====\n", start);
    for (int i = 0; i < g->n; i++)
    {
        if (dist[i] == -1)
        {
            printf("顶点 %d：不可到达\n", i);
        }
        else
        {
            printf("顶点 %d：最短距离 = %d\n", i, dist[i]);
        }
    }
}

/**
 * 释放邻接表全部内存，防止内存泄漏
 */
void FreeGraph(Graph *g)
{
    int i;
    EdgeNode *p, *q;
    for (i = 0; i < g->n; i++)
    {
        p = g->adjList[i].firstEdge;
        while (p != NULL)
        {
            q = p;
            p = p->next;
            free(q);
        }
    }
}

// 主函数
int main(void)
{
    Graph g;
    // 创建一共 6 个顶点的无向图
    InitGraph(&g, 6);

    // 添加边
    AddEdge(&g, 0, 1);
    AddEdge(&g, 0, 2);
    AddEdge(&g, 1, 3);
    AddEdge(&g, 2, 3);
    AddEdge(&g, 4, 5);

    PrintDegree(&g);
    GetConnectComponent(&g);
    BfsTree(&g, 0);
    ShortestPath(&g, 0);

    FreeGraph(&g);
    return 0;
}