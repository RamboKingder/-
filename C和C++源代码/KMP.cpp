#include<stdio.h>
#include<time.h>
/*尝试一下KMP算法并且看看VS到底怎么显示程序运行的时间*/

int Index(char S[], char T[], int pos) {

}

int main(void) {
	clock_t start, finish;
	double duration;
	start = clock();

	char S[] = "So now we are doing test on KMP algorithm and this is our main string.";
	char p[] = "KMP";



	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%f seconds\n", duration);

	return 0;
}