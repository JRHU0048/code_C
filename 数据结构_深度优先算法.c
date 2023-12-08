//【例8.6】的算法:输出图G中从顶点u到v的所有简单路径
//图的基本运算算法
#include <stdio.h>
#include<stdlib.h>
#include <malloc.h>
//图的两种存储结构
#define INF 32767				//定义∞
#define	MAXV 100	
int visited[MAXV];	//最大顶点个数
typedef char InfoType;

//以下定义邻接矩阵类型
typedef struct
{
	int no;						//顶点编号
	InfoType info;				//顶点其他信息
} VertexType;					//顶点类型
typedef struct
{
	int edges[MAXV][MAXV];		//邻接矩阵数组
	int n, e;					//顶点数，边数
	VertexType vexs[MAXV];		//存放顶点信息
} MatGraph;						//完整的图邻接矩阵类型

//以下定义邻接表类型
typedef struct ANode
{
	int adjvex;					//该边的邻接点编号
	struct ANode* nextarc;		//指向下一条边的指针
	int weight;					//该边的相关信息，如权值（用整型表示）
} ArcNode;						//边结点类型
typedef struct Vnode
{
	InfoType info;				//顶点其他信息
	int count;					//存放顶点入度,仅仅用于拓扑排序
	ArcNode* firstarc;			//指向第一条边
} VNode;						//邻接表头结点类型
typedef struct
{
	VNode adjlist[MAXV];		//邻接表头结点数组
	int n, e;					//图中顶点数n和边数e
} AdjGraph;						//完整的图邻接表类型

//------------------------------------------------------------
//----邻接矩阵的基本运算算法----------------------------------
//------------------------------------------------------------
void CreateMat(MatGraph& g, int A[MAXV][MAXV], int n, int e) //创建图的邻接矩阵
{
	int i, j;
	g.n = n; g.e = e;
	for (i = 0;i < g.n;i++)
		for (j = 0;j < g.n;j++)
			g.edges[i][j] = A[i][j];
}
void DispMat(MatGraph g)	//输出邻接矩阵g
{
	int i, j;
	for (i = 0;i < g.n;i++)
	{
		for (j = 0;j < g.n;j++)
			if (g.edges[i][j] != INF)
				printf("%4d ", g.edges[i][j]);
			else
				printf("%4s ", "∞");
		printf("\n");
	}
}
//------------------------------------------------------------

//------------------------------------------------------------
//----邻接表的基本运算算法------------------------------------
//------------------------------------------------------------
void CreateAdj(AdjGraph*& G, int A[MAXV][MAXV], int n, int e) //创建图的邻接表
{
	int i, j;
	ArcNode* p;
	G = (AdjGraph*)malloc(sizeof(AdjGraph));
	for (i = 0;i < n;i++)								//给邻接表中所有头结点的指针域置初值
		G->adjlist[i].firstarc = NULL;
	for (i = 0;i < n;i++)								//检查邻接矩阵中每个元素
		for (j = n - 1;j >= 0;j--)
			if (A[i][j] != 0 && A[i][j] != INF)			//存在一条边
			{
				p = (ArcNode*)malloc(sizeof(ArcNode));	//创建一个结点p
				p->adjvex = j;
				p->weight = A[i][j];
				p->nextarc = G->adjlist[i].firstarc;	//采用头插法插入结点p
				G->adjlist[i].firstarc = p;
			}
	G->n = n; G->e = n;
}
void DispAdj(AdjGraph* G)	//输出邻接表G
{
	int i;
	ArcNode* p;
	for (i = 0;i < G->n;i++)
	{
		p = G->adjlist[i].firstarc;
		printf("%3d: ", i);
		while (p != NULL)
		{
			printf("%3d[%d]→", p->adjvex, p->weight);
			p = p->nextarc;
		}
		printf("∧\n");
	}
}
void DestroyAdj(AdjGraph*& G)		//销毁图的邻接表
{
	int i;
	ArcNode* pre, * p;
	for (i = 0;i < G->n;i++)			//扫描所有的单链表
	{
		pre = G->adjlist[i].firstarc;	//p指向第i个单链表的首结点
		if (pre != NULL)
		{
			p = pre->nextarc;
			while (p != NULL)			//释放第i个单链表的所有边结点
			{
				free(pre);
				pre = p; p = p->nextarc;
			}
			free(pre);
		}
	}
	free(G);						//释放头结点数组
}
//------------------------------------------------------------

int featurePoints[] = { 1, 5, 6, 10 }; // Specify the feature points
int isFeature[MAXV]; // Flag array to mark feature points

void FindAllPathWithMandatoryFeature(AdjGraph* G, int u, int v, int path[], int d) {
	int w, i;
	ArcNode* p;
	d++;
	path[d] = u;
	visited[u] = 1;

	// Check if the current vertex is one of the specified feature points
	isFeature[u] = 1;

	if (u == v && d >= 0) {
		// Check if at least one feature point is mandatory
		int mandatoryFeatureVisited = 0;
		for (i = 0; i < sizeof(featurePoints) / sizeof(featurePoints[0]); i++) {
			if (visited[featurePoints[i]]) {
				mandatoryFeatureVisited = 1;
				break;
			}
		}

		if (mandatoryFeatureVisited) {
			for (i = 0; i <= d; i++)
				printf("%2d ", path[i]);
			printf("\n");
		}
	}

	p = G->adjlist[u].firstarc;
	while (p != NULL) {
		w = p->adjvex;
		if (!visited[w]) {
			FindAllPathWithMandatoryFeature(G, w, v, path, d);
		}
		p = p->nextarc;
	}

	visited[u] = 0;
	isFeature[u] = 0;
}

void FindAllPathWithAvoidedFeature(AdjGraph* G, int u, int v, int path[], int d) {
	int w, i;
	ArcNode* p;
	d++;
	path[d] = u;
	visited[u] = 1;

	
	isFeature[u] = 1;

	if (u == v && d >= 0) {
		
		int avoidedFeatureVisited = 0;
		for (i = 0; i < sizeof(featurePoints) / sizeof(featurePoints[0]); i++) {
			if (visited[featurePoints[i]]) {
				avoidedFeatureVisited = 1;
				break;
			}
		}

		if (!avoidedFeatureVisited) {
			for (i = 0; i <= d; i++)
				printf("%2d ", path[i]);
			printf("\n");
		}
	}

	p = G->adjlist[u].firstarc;
	while (p != NULL) {
		w = p->adjvex;
		if (!visited[w] && !isFeature[w]) {
			FindAllPathWithAvoidedFeature(G, w, v, path, d);
		}
		p = p->nextarc;
	}

	visited[u] = 0;
	isFeature[u] = 0;
}


int main()
{
	AdjGraph* G;
	int A[MAXV][MAXV] = { {0,	1,	1	,1,	1,	0	,0,	0,	0,	0	,0,	0,	0	,0,	0},
		{1,	0	,0,	0,	0,	0,	1,	0,	1	,0,	0	,0,	0	,0,	0},
		{1,	0,	0	,0,	0,	0,	0,	0,	0	,0,	0,	0,	0,	0,	0},
		{1,	0	,0,	0,	0,	0,	1,	0,	0,	0,	0	,0,	0	,0,	0},
		{1,	0,	0	,0,	0,	0,	0,	1,	0	,0	,0,	0,	0,	0,	0},
		{0,	0,	0	,0	,0,	0,	0,	0,	1,	1,	0	,0	,0,	0,	0} ,
		{0	,1	,0,	1,	0,	0,	0,	1,	0,	1,	0	,0,	0,	0,	0},
		{0,	0,	0	,0,	1,	0,	1,	0,	0	,0,	1	,1,	0	,0,	0},
		{0,	1	,0	,0,	0,	1,	0,	0,	0	,0,	0	,0,	1,	0,	0},
		{0, 0,  0,	0,	0,	1,	1,	0	,0,	0,	1,	0,	1,	0	,0},
		{0,	0,	0,	0,	0,	0,	0	,1	,0	,1,	0	,0	,0,	1,	0},
		{0, 0,	0,  0,	0,  0,	0,	1,	0,	0,	0,	0	,0	,1,	0},
		{0, 0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	1},
		{0, 0,  0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	1},
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0},
	};
	int n = 15, e = 42;
	CreateAdj(G, A, n, e);			//建立《教程》中图8.1(a)的邻接表
	printf("图G的邻接表:\n");
	DispAdj(G);					//输出邻接表G
	int u = 0, v = 14;
	int path[MAXV];
	//printf("\n图G中顶点%d到顶点%d的所有简单路径:\n", u, v);

	printf("特征点之一是必经点的路径:\n");
	FindAllPathWithMandatoryFeature(G, u, v, path, -1);
	printf("特征点是回避点的路径:\n");
	FindAllPathWithAvoidedFeature(G, u, v, path, -1);

	DestroyAdj(G);				//销毁邻接表
	system("pause");
	return 1;
}
