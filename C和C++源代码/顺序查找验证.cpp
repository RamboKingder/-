#include<stdio.h>
#include<time.h>
//这里用顺序表验证顺序查找实在太麻烦了，不如直接用数组
int Search_Seq(int x[], int key) {
	x[0] = key;
	int i =16;
	while (x[i] != key)	i--;
	return i;
}

int Search_Bin(int x[], int key) {
	int low = 1; int high = 16;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (x[mid] == key) return mid;
		else if (x[mid] < key) low = mid + 1;
		else high = mid - 1;
	}
}

int main(void) {
	clock_t start = clock();
	int arr[17] = { 0,5,13,19,21,37,56,64,75,80,88,92,100,123,134,254,354, };
	/*程序正常运行情况应该用这一段代码
	int num;
	do {
		printf("Enter a number to search in the Sequential Search Table(<0 to quit):");
		scanf("%d", &num);
		if (!Search_Seq(arr, num)) printf("Not found!\n");
		else printf("%d is the %dth number in the table\n", num, Search_Seq(arr, num));
	} while (num >= 0);*/

	//测试代码
	for (int i = 1; i <= 16; i++) {
		if (!Search_Seq(arr, arr[i])) printf("Not found!\n");
		else printf("%d is the %dth number in the table\n", arr[i], Search_Seq(arr, arr[i]));
	}
	clock_t finish = clock();
	printf("\nSequential Search: %d clocks\n\n", finish-start);

	clock_t start2 = clock();
	for (int i = 1; i <= 16; i++) {
		if (!Search_Bin(arr, arr[i])) printf("Not found!\n");
		else printf("%d is the %dth number in the table\n", arr[i], Search_Bin(arr, arr[i]));
	}
	clock_t finish2 = clock();
	printf("\nBinary Search: %d clocks\n", finish2 - start2);

	return 0;
}