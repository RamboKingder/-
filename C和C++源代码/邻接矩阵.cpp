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

//�����ڽӾ����Ԫ�ؽṹ��ֱ��typedef��һ���ڽӾ�������
typedef struct ArcCell {
	int adj;  //����Ĺ�ϵ��1Ϊ�ڽ�0Ϊ���ڽ�
	void *info;//�û������Ϣ��ָ��
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
	int vexs[MAX_VERTEX_NUM];//��������
	AdjMatrix arcs;
	int vexnum, arcnum;//ͼ�ĵ�ǰ�������ͻ���
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
	//�������飨�ڽӾ��󣩹���������G
	printf("Please enter the number of vertexes:");
	scanf("%d", &G.vexnum);
	printf("Please enter the number of arcs:");
	scanf("%d", &G.arcnum);
	for (int i = 0; i < G.vexnum; i++) {//���춥������
		printf("Please enter the value of the V%d:", i+1);
		scanf("%d", &G.vexs[i]);
	}
	for (int i = 0; i < G.vexnum; i++)//��ʼ���ڽӾ���
		for (int j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = { INFINITY,NULL };
	int vertex1, vertex2, weight;
	for (int k = 0; k < G.arcnum; k++) {//�����ڽӾ���
		printf("Please enter the vertex1 ,vertex2,and their weight:");
		scanf("%d %d %d", &vertex1, &vertex2, &weight);
		int i = LocateVex(G, vertex1); int j = LocateVex(G, vertex2);//ȷ��vertex1��vertex2��G�е�λ��
		G.arcs[i][j].adj = weight;
		G.arcs[j][i].adj = G.arcs[i][j].adj;
	}
}//CreateUDN

BOOLTYPE visited[MAX_VERTEX_NUM];//���ʱ�־����

void DFS(MGraph G, int v) {
	//�ӵ�v����������ݹ��������ȱ���ͼG
	visited[v] = TRUE;
	printf("%d->", G.vexs[v]);
	//���ʵ�v������
	for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
		if (!visited[w]) DFS(G, w);
}

void DFSTraverse(MGraph G) {
	//��ͼG��������ȱ���
	for (int v = 0; v < G.vexnum; v++) visited[v] = FALSE;
	for (int v = 0; v < G.vexnum; v++)
		if (!visited[v]) DFS(G, v);
}

void BFSTraverse(MGraph G) {
	//��������ȷǵݹ����ͼG��ʹ�ø�������Q�ͷ��ʱ�־����visited
	for (int v = 0; v < G.vexnum; v++) visited[v] = FALSE;
	LinkQueue Q;		InitQueue(Q);  //�ÿյĸ�������Q
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
