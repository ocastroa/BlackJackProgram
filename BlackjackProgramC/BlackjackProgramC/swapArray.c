//#include<stdio.h>
//#include<stdlib.h>
//#include<time.h>
//
//#define Q (12)
//#define K (13)
//#define J (11)
//#define sizeArray(x) (sizeof(x)/ sizeof((x)[0]))
//
//void swap(int *a, int *b) { // swap integers
//
//	int temp = *a;
//	*a = *b;
//	*b = temp;
//}
//
//// A utility function to print an array
//void printArray(int arr[], int n)
//{
//	for (int i = 0; i < n; i++)
//		printf("%d ", arr[i]);
//	printf("\n");
//}
//
//void shuffle(int arr[], int n) {
//
//	srand((unsigned)time(NULL)); // used to seed with different values, otherwise default value is 1
//
//	for (int i = n - 1; i > 0; i--) {
//
//		int foo = rand() % (i + 1);
//
//		if (foo == 0) {
//			foo = rand() % (i + 1);
//		}
//
//		swap(&arr[i], &arr[foo]);
//	}
//}
//
//int main() {
//
//	//int arr[52] = { 3,K,Q,4,5,2,10,6,9,J,7,8,
//	//	K,2,Q,3,J,8,10,5,9,6,4,7,
//	//	6,9,7,3,8,4,Q,2,5,J,10,K,
//	//	8,3,Q,5,J,4,6,7,K,10,9,2};
//
//	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
//
//	int n = sizeArray(arr);
//	shuffle(arr, n);
//	printArray(arr, n);
//	printf("%d", n);
//
//	getchar();
//
//	return 0;
//}
