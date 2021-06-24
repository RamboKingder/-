#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include<string.h>
#include<conio.h>

struct student {
	int num;
	char name[16];
	char sex[2];
	int age;
	double score[3];
	double sum;
	double ave;
};

typedef struct node {
	struct student data;
	struct node *next;
}Node, *link;

int menu_select() {
	int i;
	printf("\n\n\t ***************************STUDENT LIST***************************\n");
	printf("\t}*                     1.input record                             *|\n");
	printf("\t}*                     2.delete record                            *|\n");
	printf("\t}*                     3.list record                              *|\n");
	printf("\t}*                     4.search record                            *|\n");
	printf("\t}*                     5.save record                              *|\n");
	printf("\t}*                     6.load record                              *|\n");
	printf("\t}*                     7.quit                                     *|\n");
	printf("\t *******************************************************************\n");
	do {
		printf("\n\tEnter your choice:");
		scanf("%d", &i);
	} while (i <= 0 || i > 7);
		return i;
}

void input(link l) {
	int i; link p, q;
	while (1) {
		p = (link)malloc(sizeof(Node));
		if (!p) { printf("memory allocate failure"); return; }
		printf("input number:");
		scanf("%d", &p->data.num);
		if (p->data.num == 0) break;
		for (q = l; q->next; q = q->next) {
			if (q->data.num == p->data.num) {
				printf("the number has existed,please input again:");
				scanf("%d", &p->data.num);
			}
		}
		printf("input name:");
		scanf("%s", &p->data.name);
		printf("input sex:");
		scanf("%s", &p->data.sex);
		printf("input age:");
		scanf("%d", &p->data.age);
		printf("Input Chinese,Math,English scores:");
		for (i = 0; i < 3; i++) scanf("%lf", &p->data.score[i]);
		p->data.sum = p->data.score[0] + p->data.score[1] + p->data.score[2];
		p->data.ave = p->data.sum / 3;
		p->next = NULL;
		q->next = p;
		q = p;
	}
}

void save(link l) {
	link p = l->next;
	FILE *fp;
	if ((fp = fopen("data", "wb")) == NULL) {
		printf("can not open file\n");
		exit(-1);
	}
	printf("\nSaving  file\n");
	while (p) {
		fwrite(p, sizeof(Node), 1, fp);
		p = p->next;
	}
	fclose(fp);
	getch();
}

void load(link l) {
	link p, r;
	FILE *fp;
	l->next = NULL;
	r = l;
	if ((fp = fopen("data", "rb")) == NULL) {
		printf("can not open file\n");
		exit(1);
	}
	printf("\nloading file\n");
	while (!feof(fp)) {
		p = (link)malloc(sizeof(Node));
		if (!p) { printf("memory allocate failure"); return; }
		if (fread(p, sizeof(Node), 1, fp) != 1) break;
		else {
			p->next = NULL;
			r->next = p;
			r = p;
		}
	}
	fclose(fp);
	getch();
}

void display(link p) {
	printf("\nSTUDENT INFORMATION\n");
	printf("number:%d\n", p->data.num);
	printf("name:%s\n", p->data.name);
	printf("sex:%s\n", p->data.sex);
	printf("age:%d\n", p->data.age);
	printf("Chinese:%.2f\n", p->data.score[0]);
	printf("Math:%.2f\n", p->data.score[1]);
	printf("English:%.2f\n", p->data.score[2]);
	printf("sum=%.2f\n", p->data.sum);
	printf("average=%.2f\n", p->data.ave);
}

void list(link l) {
	link p = l->next;
	if (!p) printf("no student record!");
	while (p) {
		display(p);
		p = p->next;
	}
	getch();
}

void search(link l) {
	int num;
	link p = l->next;
	printf("input number of the student:");
	scanf("%d", &num);
	while (p) {
		if (p->data.num == num) {
			display(p);
			getch();
			break;
		}
		p = p->next;
	}
	if (!p) printf("can not find the student!");
}

void del(link l) {
	int num;
	link p, q;
	q = l; p = q->next;
	printf("input the student number you want to delete:");
	scanf("%d", &num);
	while (p) {
		if (p->data.num == num) {
			q->next = p->next;
			free(p);
			printf("delete successfully");
			break;
		}
		else {
			q = p; 
			p = p->next;
		}
	}
	if (!p) printf("can not find the student you want to delete!");
	getch();
}

int main(void){
	link l = (Node *)malloc(sizeof(Node));
	if (!l) {
		printf("\n allocate memory failure");
		return -1;
	}
	l->next = NULL;
	//创建头节点
	while (1) {
		system("cls");
		switch (menu_select()) {
		case 1: input(l); break;
		case 2: del(l); break;
		case 3: list(l); break;
		case 4: search(l); break;
		case 5: save(l); break;
		case 6: load(l); break;
		case 7: exit(0);
		}
	}

	return 0;
}
