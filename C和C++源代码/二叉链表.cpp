#include<stdio.h>
#include<stdlib.h>
typedef struct BiTNode {
	char data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;
void CreateBiTree(BiTree &T) {
	//按照先序输入二叉树中节点的值（一个字符）空格字符表示空树
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
	//先序遍历二叉树T，输出每个元素
	if (T) {
		printf("%c",T->data);
		PreOrderOutput(T->lchild);
		PreOrderOutput(T->rchild);
	}
}

void InOrderOutput(BiTree T) {
	//中序遍历二叉树T，输出每个元素
	if (T) {
		InOrderOutput(T->lchild);
		printf("%c", T->data);
		InOrderOutput(T->rchild);
	}
}

void PostOrderOutput(BiTree T) {
	//后序遍历二叉树T,输出每个元素
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
	printf("按照先序序列输入:");
	BiTree root = NULL;
	CreateBiTree(root);
	printf("先序遍历序列为：");
	PreOrderOutput(root);
	printf("\n");
	printf("中序遍历序列为：");
	InOrderOutput(root);
	printf("\n");
	printf("后序遍历序列为：");
	PostOrderOutput(root);
	printf("\n");
	printf("此二叉树的深度为：%d", Depth(root));

	return 0;
}