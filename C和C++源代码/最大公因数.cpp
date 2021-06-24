#include<stdio.h>
#include<time.h>
int Euclid(int x, int y) {
	while (x%y != 0) {
		int z = x % y;
		x = y;
		y = z;
	}
	return y;
}
int main(void) {
	clock_t start, finish;
	double duration;
	start = clock();
	int a, b;
	printf("Enter a here:");
	scanf("%d", &a);
	printf("Enter b here:");
	scanf("%d", &b);
	if (a >= b) printf("The greatest common factor is %d", Euclid(a, b));
	else printf("The greatest common factor is %d", Euclid(b, a));
	
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("\n\n%f seconds\n", duration);
}