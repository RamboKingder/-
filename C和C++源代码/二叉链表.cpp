#include<stdio.h>
#include<stdlib.h>
typedef struct BiTNode {
	char data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;
void CreateBiTree(BiTree &T) {
	//������������������нڵ��ֵ��һ���ַ����ո��ַ���ʾ����
	char ch;
	scanf("%c", &ch);
	if (ch == ' ') T = NULL;
	else {
		T = (BiTNode*)malloc(sizeof(BiTNode));
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}//CreateBiTree
void PreOrderOutput(BiTree T) {
	//�������������T�����ÿ��Ԫ��
	if (T) {
		printf("%c",T->data);
		PreOrderOutput(T->lchild);
		PreOrderOutput(T->rchild);
	}
}

void InOrderOutput(BiTree T) {
	//�������������T�����ÿ��Ԫ��
	if (T) {
		InOrderOutput(T->lchild);
		printf("%c", T->data);
		InOrderOutput(T->rchild);
	}
}

void PostOrderOutput(BiTree T) {
	//�������������T,���ÿ��Ԫ��
	if (T) {
		PostOrderOutput(T->lchild);
		PostOrderOutput(T->rchild);
		printf("%c", T->data);
	}
}

int Depth(BiTree T) {
	int depthvalue;
	if (!T) depthvalue = 0;
	else {
		int depthLeft = Depth(T->lchild);
		int depthRight = Depth(T->rchild);
		depthvalue = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
	}
	return depthvalue;
}

int main(void) {
	printf("����������������:");
	BiTree root = NULL;
	CreateBiTree(root);
	printf("�����������Ϊ��");
	PreOrderOutput(root);
	printf("\n");
	printf("�����������Ϊ��");
	InOrderOutput(root);
	printf("\n");
	printf("�����������Ϊ��");
	PostOrderOutput(root);
	printf("\n");
	printf("�˶����������Ϊ��%d", Depth(root));

	return 0;
}