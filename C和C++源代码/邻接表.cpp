#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX_NUM 20
typedef enum{FALSE, TRUE}BOOL;
typedef struct ArcNode {
	int adjvex;//该弧所指向顶点的位置
	struct ArcNode *nextarc;//指向下一条弧的指针
	int weigth;//该弧的权重
}ArcNode;
typedef struct VNode {
	int data;//顶点信息
	ArcNode *firstarc;//指针第一条依附该顶点的弧的指针
}VNode,AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
}ALGraph;

typedef struct QNode {
	int data;
	struct QNode *next;
}QNode, *QueuePtr;

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

int Locate(ALGraph G, int u) {
	//若u节点存在，返回u的位置
	for (int v = 0; v < G.vexnum; v++)
		if (G.vertices[v].data == u)
			return v;
	return -1;
}

void CreateUND(ALGraph &G) {
	printf("Plese enter the number of vertex:");
	scanf("%d", &G.vexnum);
	printf("Plese enter the number of arcs:");
	scanf("%d", &G.arcnum);
	for (int v = 0; v < G.vexnum; v++) {//构造顶点表
		printf("Please enter the value of the %dth vertex:",v+1);
		scanf("%d", &G.vertices[v].data);
		G.vertices[v].firstarc = NULL;
	}
	for (int v = 0; v < G.vexnum; v++) {//构造弧链表
		//printf("How many adjacent vertexes does the %dth vertex have? ",v+1);
		//int adjnum; scanf("%d", &adjnum);
		for (int i = 0; i < 2; i++) {//用书上例子所以adjnum设为2
			printf("Please enter the %dth adjacent vertex's value and thier weight:",i+1);
			ArcNode* s = (ArcNode*)malloc(sizeof(ArcNode));
			int value; scanf("%d", &value); s->adjvex =Locate(G,value) ;
			s->nextarc = G.vertices[v].firstarc; G.vertices[v].firstarc = s;
		}
	}
}

int FirstAdjVex(ALGraph G, int v) {
	//返回v的第一个邻接点，若存在则返回邻接点的位置，否则返回-1
	if (G.vertices[v].firstarc != NULL)
		return G.vertices[v].firstarc->adjvex;
	else return -1;
}

int NextAdjVex(ALGraph G, int v, int w) {
	//返回v相对于w的下一个临界点,若没有则返回-1
	for (ArcNode* p = G.vertices[v].firstarc; p!=NULL; p = p->nextarc) {
		if (p->adjvex == v) {
			if (p->nextarc) return p->nextarc->adjvex;
			else return -1;
		}
	}
	return -1;
}

BOOL visited[MAX_VERTEX_NUM];//访问标志数组

void DFS(ALGraph G,int v){
	//从第v个顶点出发深度优先遍历图G
	visited[v] = TRUE; printf("%d->", G.vertices[v].data);
	for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
		if (!visited[w]) DFS(G, w);
}

void DFSTraverse(ALGraph G) {
	//对图G做深度优先遍历
	for (int v = 0; v < G.vexnum; v++) visited[v] = FALSE;
	for (int v = 0; v < G.vexnum; v++)
		if (!visited[v]) DFS(G, v);
}

void BFSTraverse(ALGraph G) {
	//对图做广度优先遍历
	for (int v = 0; v < G.vexnum; v++) visited[v] = FALSE;
	LinkQueue Q;		InitQueue(Q);  //置空的辅助队列Q
	for (int v = 0; v < G.vexnum; v++)
		if (!visited[v]) {
			visited[v] = TRUE; printf("%d->", G.vertices[v]);
			EnQueue(Q, v);
			while (!QueueEmpty(Q)) {
				int u;  DeQueue(Q, u);
				for (int w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
					if (!visited[w]) {
						visited[w] = TRUE; printf("%d->", G.vertices[w]);
						EnQueue(Q, w);
					}//if
			}//while
		}//if
}

int main(void) {
	ALGraph ORIGIN;
	CreateUND(ORIGIN);
	printf("The Depth First Search Traverse goes like this:");
	DFSTraverse(ORIGIN);
	printf("\nThe Broadth First Search Traverse goes like this:");
	BFSTraverse(ORIGIN);


	return 0;
}
