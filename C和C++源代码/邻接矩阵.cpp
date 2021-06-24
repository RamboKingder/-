#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
typedef enum{DG, DN, UDG, UDN}GraphKind;
typedef enum{FALSE,TRUE}BOOLTYPE;

typedef struct QNode {
	int data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

void InitQueue(LinkQueue &Q) {
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	Q.front->next = NULL;
}

void EnQueue(LinkQueue &Q, int e) {
	QNode *s = (QueuePtr)malloc(sizeof(QNode));
	s->data = e;	s->next = NULL;
	Q.rear->next = s;
	Q.rear = s;
}

void DeQueue(LinkQueue &Q, int &e) {
	QueuePtr p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	free(p);
}

int QueueEmpty(LinkQueue Q) {
	if (!Q.front->next) return 1;
	else return 0;
}

//定义邻接矩阵的元素结构并直接typedef了一个邻接矩阵数组
typedef struct ArcCell {
	int adj;  //顶点的关系，1为邻接0为不邻接
	void *info;//该弧相关信息的指针
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
	int vexs[MAX_VERTEX_NUM];//顶点向量
	AdjMatrix arcs;
	int vexnum, arcnum;//图的当前顶点数和弧数
	GraphKind kind;
}MGraph;

int LocateVex(MGraph X, int u) {
	for (int i = 0; i <X.vexnum; i++)
		if (X.vexs[i] == u)return i;
	printf("The vertex you are searching dosn't exist in this Graph!");
}

int FirstAdjVex(MGraph G, int v) {
	for (int i = 0;i < G.vexnum; i++)
		if (G.arcs[v][i].adj != INFINITY) return i;
	return -1;
}

int NextAdjVex(MGraph G, int v, int w) {
	for(int i=w+1;i<G.vexnum;i++)
		if (G.arcs[v][i].adj != INFINITY) return i;
	return -1;
}

void CreateUDN(MGraph &G) {
	//采用数组（邻接矩阵）构造无向网G
	printf("Please enter the number of vertexes:");
	scanf("%d", &G.vexnum);
	printf("Please enter the number of arcs:");
	scanf("%d", &G.arcnum);
	for (int i = 0; i < G.vexnum; i++) {//构造顶点向量
		printf("Please enter the value of the V%d:", i+1);
		scanf("%d", &G.vexs[i]);
	}
	for (int i = 0; i < G.vexnum; i++)//初始化邻接矩阵
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = { INFINITY,NULL };
	int vertex1, vertex2, weight;
	for (int k = 0; k < G.arcnum; k++) {//构造邻接矩阵
		printf("Please enter the vertex1 ,vertex2,and their weight:");
		scanf("%d %d %d", &vertex1, &vertex2, &weight);
		int i = LocateVex(G, vertex1); int j = LocateVex(G, vertex2);//确定vertex1和vertex2在G中的位置
		G.arcs[i][j].adj = weight;
		G.arcs[j][i].adj = G.arcs[i][j].adj;
	}
}//CreateUDN

BOOLTYPE visited[MAX_VERTEX_NUM];//访问标志数组

void DFS(MGraph G, int v) {
	//从第v个顶点出发递归地深度优先遍历图G
	visited[v] = TRUE;
	printf("%d->", G.vexs[v]);
	//访问第v个顶点
	for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
		if (!visited[w]) DFS(G, w);
}

void DFSTraverse(MGraph G) {
	//对图G做深度优先遍历
	for (int v = 0; v < G.vexnum; v++) visited[v] = FALSE;
	for (int v = 0; v < G.vexnum; v++)
		if (!visited[v]) DFS(G, v);
}

void BFSTraverse(MGraph G) {
	//按广度优先非递归遍历图G。使用辅助队列Q和访问标志数组visited
	for (int v = 0; v < G.vexnum; v++) visited[v] = FALSE;
	LinkQueue Q;		InitQueue(Q);  //置空的辅助队列Q
	for (int v = 0; v < G.vexnum; v++) 
		if (!visited[v]) {
			visited[v] = TRUE; printf("%d->", G.vexs[v]);
			EnQueue(Q, v);
			while (!QueueEmpty(Q)) {
				int u;  DeQueue(Q, u);
				for (int w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
					if (!visited[w]) {
						visited[w] = TRUE; printf("%d->", G.vexs[w]);
						EnQueue(Q, w);
					}//if
			}//while
		}//if
}//BFSTraverse


int main(void) {
	MGraph ORIGIN;
	CreateUDN(ORIGIN);
	printf("\nSo the Depth First Search sequence goes like this:\n");
	DFSTraverse(ORIGIN);
	printf("\nSo the Broath First Search sequence goes like this:\n");
	BFSTraverse(ORIGIN);

	return 0;
}
