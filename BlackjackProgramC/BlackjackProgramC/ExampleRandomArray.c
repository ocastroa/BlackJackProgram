//#include<stdio.h>
//#include<stdlib.h>
//#include<time.h>
//
//#define Q (12)
//#define K (13)
//#define J (11)
//#define sizeArray(x) (sizeof(x)/ sizeof((x)[0]))
//
//int cards[52] = { 2,3,4,5,6,7,8,9,10,J,Q,K,
//				  2,3,4,5,6,7,8,9,10,J,Q,K,
//				  2,3,4,5,6,7,8,9,10,J,Q,K,
//				  2,3,4,5,6,7,8,9,10,J,Q,K};
//
//int cardCopy[52];
//
//int main() {
//
//	int n = 2, random;
//	int foo = 0;
//	srand((unsigned)time(NULL)); // used to seed with different values, otherwise default value is 1
//
//	for (int i = 0; i < 2; i++) {
//		random = rand() % (51 + 1 - 0) + 0;
//		cardCopy[foo] = random;
//		foo++;
//		if()
//		int num = cards[random];
//
//
//
//	
//	}
//
//	for (int i = 0; i < 2; i++) {
//		random = rand() % (51 + 1 - 0) + 0;
//		int num = cards[random];
//		int arrayTracker = 0;
//
//		if (num == 0) {
//			while (num == 0) {
//				arrayTracker += 1;
//				if (arrayTracker == sizeArray(cards) + 1) {
//					shuffleCards();
//					arrayTracker = 0;
//				}
//				else {
//					random = rand() % (51 + 1 - 0) + 0;
//					int	num = cards[random];
//				}
//			}
//
//		printf("%d\n", num);
//		num = 0;
//		printf("%d\n", num);
//		}
//
//		else {
//			printf("%d\n", num);
//			num = 0;
//			printf("%d\n", num);
//		}
//
//	}
//
//	//printf("%d", cards[11]);
//
//	getchar();
//
//	return 0;
//}
