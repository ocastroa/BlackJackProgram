#include<stdio.h>
#include<stdlib.h>
#include "BlackJackProgram.h"

#define Q (12)
#define K (13)
#define J (11)
#define sizeArray(x) (sizeof(x)/ sizeof((x)[0]))

// global vars
int HUMSUM;
int COMPSUM;

int cardArray[] = {3,K,Q,4,5,2,10,6,9,J,7,8,
K,2,Q,3,J,8,10,5,9,6,4,7,
6,9,7,3,8,4,Q,2,5,J,10,K,
8,3,Q,5,J,4,6,7,K,10,9,2 };

void swap(int *a, int *b) { // swap integers

	int temp = *a;
	*a = *b; 
	*b = temp;
}

void shuffle(int arr[], int n) {

	srand((unsigned)time(NULL)); // used to seed with different values, otherwise default value is 1

	// Start from the last element and swap one by one. We don't
	// need to run for the first element that's why i > 0
	for (int i = n - 1; i > 0; i--) {

		int foo = rand() % (i + 1);

		if (foo == 0) {
			foo = rand() % (i + 1);
		}

		swap(&arr[i], &arr[foo]);
	}
}

// display first out of two cards from comps hand
int passOutCompCards(int *foo) {

	int i = 0;
	int *cardPtr = foo;

	for (i = 0; i < 1; i++) {
		printf("Computer Cards are: %d", *cardPtr);
		cardPtr++;
	}

	printf(" and ? \n");
	return (cardPtr); // return pointer to address of cardPtr
}

// display first two cards from players hand. Also display sum
int passOutHumCards(int *ptrCard) {

	int i = 0;
	// pointers that store value of next two elements of array
	int *y = ptrCard + 1;
	int *z = ptrCard + 2;

	//int answer;
	HUMSUM = *y + *z; // sum up the two element values
	//	int *humanPtr = ptrCard;

	printf("Human Cards are: %d", *y);
	printf(" and %d", *z);
	printf(" --> Sum is %d\n", HUMSUM);

	if (HUMSUM == 21) {
		printf("BlackJack!");
		//CheckAgainstComp
	}

	else {
		HumanCardOperations(z, HUMSUM);
	}
	//printf("Do you want to hit Yes = 1 or No = 0: ");
	//scanf_s("%d", &answer);

	/*switch (answer) {
	case 1:
		humanHit(z, HUMSUM);
		break;

	case 0:
		break;
	}*/

}

// do mathematical operations to check sum of cards and see if they are within boundaries
int HumanCardOperations(int *z, int sum) {

	int answer;

	if (sum > 21) {
		printf("Bust!");
		reShuffle(z); // reshuffle deck
		//CheckAgainstComp
	}

	else if (sum == 21) {
		//CheckAgainstComp
	}

	else {
		printf("Do you want to hit Yes = 1 or No = 0: ");
		scanf_s("%d", &answer);

		switch (answer) {
		case 1:
			humanHit(z);
			break;

		case 0:
			//CheckAgainstComp
			break;
		}
	}

}

// players hits and gets one card at a time
int humanHit(int *z) {

	int *next = z + 1;

	if (*next != NULL) {
		HUMSUM += *next;
	}

	if (*next == NULL) { // if next element is null, shuffle array
		reShuffle(z);
	}

	int answer;

	printf("New card is %d", *next);
	printf(" --> Sum is %d\n", HUMSUM);

	HumanCardOperations(next, HUMSUM); // check if new sum is within boundaries

	//printf("Cards are now %d %d %d\n", *prev, *z, *next);

	//printf("Do you want to hit Yes = 1 or No = 0: ");
	//scanf_s("%d", &answer);

	//switch (answer) {
	//case 1:
	//	humanHit(next, HUMSUM);
	//	break;

	//case 0:
	//	break;
	//}

}

// A utility function to print an array
void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int reShuffle(int *array_pnt) {

	free(array_pnt);

	int n = sizeArray(cardArray);
	int firstHalfArray[sizeArray(cardArray) / 2];
	int secHalfArray[sizeArray(cardArray) / 2];
	int j = 24;

	// get first half of cardArray
	for (int i = 0; i < sizeArray(cardArray) / 2; i++) {
		int foo;
		foo = cardArray[i];
		firstHalfArray[i] = foo;
	}

	int size = sizeArray(firstHalfArray);
	shuffle(firstHalfArray, size);
	//printArray(firstHalfArray, size);

	// get second half of cardArray
	for (int i = 0; i < sizeArray(cardArray) / 2; i++) {
		int foo;
		foo = cardArray[j];
		secHalfArray[i] = foo;
		j++;
	}

	int sizeTwo = sizeArray(secHalfArray);
	shuffle(secHalfArray, sizeTwo);
	//printArray(secHalfArray, sizeTwo);

	int *a_array;
	a_array = (int*)malloc(sizeof(int) * sizeof(cardArray));

	// merge above two arrays into  one
	memcpy(a_array, firstHalfArray, size * sizeof(int));
	memcpy(a_array + sizeTwo, secHalfArray, sizeTwo * sizeof(int));

	shuffle(a_array, n);  // deck will be split in half, shuffle, and be merged back to shuffle one last times
	printArray(a_array, n);

	return a_array;

}

int main() {

	int *new_array = NULL;

	int *pntArry = reShuffle(new_array);
	int *compPlays = passOutCompCards(pntArry);
	int *humanPlays = passOutHumCards(compPlays);

	free(compPlays);
	free(pntArry);
	free(humanPlays);
	free(new_array);

	return 0;
}

