#include<stdio.h>
int Max_Int(int x, int y) {
	return (x > y) ? x : y;
}
int(*fp)(int a, int b);

int main(void) {
	/*int max;
	int m = 5; int n = 8;
	fp = Max_Int;
	max = (*fp)(m, n);
	max = fp(m, n);
	printf("The max value is %d\n", max);
	函数指针的例子
	*/

	/*
	int a[3] = { 1,2,3 };
	printf("The value of a is %d\n", *a);
	printf("The value of &a is %d\n", *&a);
	a是a[0]的地址 &a是整个数组地址
	a和&a的实际值是一样的
	但是他们的对象是不相同的
	因此*a和*&a输出不同
	*/


	/*nt a[2][2] = { {11, 12}, { 21,22 } };
	printf("The value of a[0][0] is %d\n", a[0][0]);
	printf("The value of a[0]       is %d\n", *a[0]);
	printf("The value of a             is %d\n", **a);*/

	int a[2][2] = { {11, 12}, { 21,22 } };
	printf("The value of a[0][0] is %d\n", a[0][0]);
	printf("The value of a[0]    is %d\n", *a[0]);
	printf("The value of a       is %d\n", **a);


	return 0;
}