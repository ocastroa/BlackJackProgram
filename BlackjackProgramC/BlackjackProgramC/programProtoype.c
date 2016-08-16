#include<stdio.h>
#include<stdlib.h>
#include "BlackJackProgram.h"

#define Q (12)
#define K (13)
#define J (11)
#define sizeArray(x) (sizeof(x)/ sizeof((x)[0]))

// global vars
int HUMSUM = 0;
int COMPSUM = 0;
int HUMPOINT = 0;
int COMPPOINT = 0;
int COUNTER = 0; // keeps track of position in array. When counter reaches size of array, a new array will be made and counter will be 1

int cardArray[] = { 3,K,Q,4,5,2,10,6,9,J,7,8,
K,2,Q,3,J,8,10,5,9,6,4,7,
6,9,7,3,8,4,Q,2,5,J,10,K,
8,3,Q,5,J,4,6,7,K,10,9,2 };


void push(int *pntA, int *pntB) {

	if (s.top == (MAXSIZE - 1)) {
		printf("Stack is full!\n");
		return;
	}

	else {
		s.top = s.top + 1;
		s.stk[s.top] = *pntA;

		s.top = s.top + 1;
		s.stk[s.top] = *pntB;
	}
}

int pop() {
	
	int number;

	if (s.top == -1) {
		printf("Stack is empty\n");
		return(s.top);
	}

	else {
		number = s.stk[s.top];
		s.top = s.top - 1;
	}

	return(number);
}

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
	COUNTER += 1;

	for (i = 0; i < 1; i++) {
		if (COUNTER > sizeArray(cardArray)) {
			//*foo = reShuffle();
			cardPtr = reShuffle();
			COUNTER = 1;
			printf("Computer Cards are: \n");
			clubCard(cardPtr);
			//printf("Computer Cards are: %d", *cardPtr);
			cardPtr++;
			COUNTER += 1;
		}
		else {
		//	printf("Computer Cards are: %d", *cardPtr);
			printf("Computer Cards are: \n");
			clubCard(cardPtr);
			cardPtr++;
			COUNTER += 1;
		}
	}

	if (*cardPtr == 11 || *cardPtr == 12 || *cardPtr == 13) {
		*cardPtr = 10;
	}

	int *add = cardPtr - 1;
	COMPSUM = *add + *cardPtr;

	push(cardPtr, add);

	printf("   and ? \n");
//	printf("%d\n", COUNTER);
	//printf(" --> Sum is %d\n", COMPSUM);

	return (cardPtr); // return pointer to address of cardPtr
}


// display first two cards from players hand. Also display sum
int passOutHumCards(int *ptrCard) {

	int i = 0;
	// pointers that store value of next two elements of array
	int *y = ptrCard + 1;
	COUNTER += 1;
	int *z = ptrCard + 2;
	COUNTER += 1;

	if (COUNTER > sizeArray(cardArray)) {
		//*ptrCard = reShuffle();
		y = reShuffle();
		COUNTER = 1;
		z = y + 1;
		COUNTER += 1;
	}

	//int answer;
//	HUMSUM = *y + *z; // sum up the two element values
	//	int *humanPtr = ptrCard;

	printf("Human Cards are: \n");
	clubCard(y);
//	printf("\t");
	clubCard(z);

	HUMSUM = *y + *z; // sum up the two element values

	//printf(" and ", *z);
	printf(" \n--> Sum is %d\n", HUMSUM);
	//printf("%d\n", COUNTER);

	if (HUMSUM == 21) {
		printf("BlackJack!\n");
		printf("Computer cards are \n");
		clubCardTwo(pop());
		printf("   ");
		clubCardTwo(pop());
		//printf(" and %d\n", pop());
		printf(" \n--> Sum is %d\n", COMPSUM);

		CompOperations(z);
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
void HumanCardOperations(int *zTwo, int sum) {

	int answer;

	if (sum > 21) {
		printf("Bust!\n\n");
		printf("Computer cards are \n");
		clubCardTwo(pop());
		printf("   ");
		clubCardTwo(pop());

	//	printf(" and %d", pop());
		printf(" \n--> Sum is %d\n", COMPSUM);
		CompOperations(zTwo);
	//	reShuffle(z); // reshuffle deck
	//	CheckSums
	}

	else if (sum == 21) {
		printf("\nComputer cards are \n");
		clubCardTwo(pop());
		clubCardTwo(pop());
	//	printf(" and %d", pop());
		printf(" \n--> Sum is %d\n", COMPSUM);
		CompOperations(zTwo);
		//CheckSums
	}

	else {
		printf("Do you want to hit Yes = 1 or No = 0: ");
		scanf_s("%d", &answer);

		switch (answer) {
		case 1:
			humanHit(zTwo);
			break;

		case 0:
			printf("\nComputer cards are \n");
			clubCardTwo(pop());
			clubCardTwo(pop());
			//printf("\nComputer cards are %d", pop());
			//printf(" and %d", pop());
			printf(" --> Sum is %d\n", COMPSUM);
			CompOperations(zTwo);
//			CheckSums();
			break;
		}
	}

}

// players hits and gets one card at a time
int humanHit(int *zThree) {

	int *next = zThree + 1;
	COUNTER += 1;

	if (COUNTER > sizeArray(cardArray)) {
		next = reShuffle();
		COUNTER = 1;
	}

	if (*next == 11 || *next == 12 || *next == 13) {
		*next = 10;
		HUMSUM += *next;
	}
	
	else {
		HUMSUM += *next;
	}

	//int answer;

	printf("New card is: \n");
	clubCard(next);
	printf(" \n--> Sum is %d\n", HUMSUM);
	printf("%d\n", COUNTER);

	HumanCardOperations(next, HUMSUM);
}

void CompOperations(int *aPointer) {

//	int counter = 0;
	//counter += 1;

	if (COMPSUM == 21) {
		//if (counter == 1) { // fix counter
			printf("BlackJack!\n");
		//}
		CheckSums();
	//	counter -= 1;
		printf("-------------------------------------------------------------------\n");
		int *compPlaysAgain = passOutCompCards(aPointer + 1);
		int *humanPlaysAgain = passOutHumCards(compPlaysAgain);
	}

	else if (COMPSUM > 21) {
		printf("Bust!\n");
		CheckSums();
		printf("-------------------------------------------------------------------\n");
		int *compPlaysAgain = passOutCompCards(aPointer + 1);
		int *humanPlaysAgain = passOutHumCards(compPlaysAgain);
	}

	else if (COMPSUM < 17) {
		compHit(aPointer);
	}

	else if (COMPSUM >= 17 || COMPSUM < 21) {
		CheckSums();
		printf("-------------------------------------------------------------------\n");
		int *compPlaysAgain = passOutCompCards(aPointer + 1);
		int *humanPlaysAgain = passOutHumCards(compPlaysAgain);
	}
}


void compHit(int *hit) {

	int *nextCard = hit + 1;
	COUNTER += 1;

	if (COUNTER > sizeArray(cardArray)) {
		nextCard = reShuffle();
		COUNTER = 1;
	}

	if (*nextCard == 11 || *nextCard == 12 || *nextCard == 13) {
		*nextCard = 10;
		COMPSUM += *nextCard;
	}

	else {
		COMPSUM += *nextCard;
	}

	printf("New card is: \n");
	clubCard(nextCard);
	printf(" \n--> Sum is %d\n", COMPSUM);
	printf("%d\n", COUNTER);

	CompOperations(nextCard); // check if new sum is within boundaries

}

void CheckSums() {

	int cpSum = COMPSUM;
	int huSum = HUMSUM;

	if (cpSum == 21 & huSum == 21) {
		printf("\nPush, no points ");
		printf(" ---> Computer's Total = %d  Your Total = %d \n\n", COMPPOINT, HUMPOINT);
		printf("%d\n", COUNTER);
	}

	else if (cpSum == huSum) {
		printf("\nPush, no points ");
		printf(" ---> Computer's Total = %d  Your Total = %d \n\n", COMPPOINT, HUMPOINT);
		printf("%d\n", COUNTER);
	}

	else if (cpSum > 21) {
		if (huSum <= 21) {
			HUMPOINT += 1;
			printf("\n+1 You ---> Computer's Total = %d Your Total = %d \n\n", COMPPOINT, HUMPOINT);
			printf("%d\n", COUNTER);
		}

		else {
			printf("\nNo winners ");
			printf(" ---> Computer's Total = %d  Your Total = %d \n\n", COMPPOINT, HUMPOINT);
			printf("%d\n", COUNTER);
		}
	}

	else if (huSum > 21) {
		if (cpSum <= 21) {
			COMPPOINT += 1;
			printf("\n+1 Computer ---> Computer's Total = %d  Your Total = %d \n\n", COMPPOINT, HUMPOINT);
			printf("%d\n", COUNTER);
		}
	}

	else if (cpSum < huSum) {
		printf("\nYou win!\n");
		HUMPOINT += 1;
		printf("+1 You ---> Computer's Total = %d  Your Total = %d \n\n", COMPPOINT, HUMPOINT);
		printf("%d\n", COUNTER);
	}

	else if (huSum < cpSum) {
		printf("\nYou lose!\n");
		COMPPOINT += 1;
		printf("+1 Computer ---> Computer's Total = %d  Your Total = %d \n\n", COMPPOINT, HUMPOINT);
		printf("%d\n", COUNTER);
	}
}

int clubCard(int *cardNum) { // print out cards for pointers

	if (*cardNum <= 10) {
			//Heart Card
			printf(" ----------\n");
			printf("|          |\n");
			printf("|    %02d    |\n", *cardNum);
			printf("|          |\n");
			printf(" -----------\n");
			return cardNum;
	}

	if (*cardNum == 11) {
			//Heart Card
		    *cardNum = 10;

			printf(" ----------\n");
			printf("|          |\n");
			printf("|     J    |\n");
			printf("|          |\n");
			printf(" ----------\n");
		//	*cardNum = 10;
			return cardNum;
		}

	if (*cardNum == 12) {
		//Heart Card
		*cardNum = 10;

		printf(" ----------\n");
		printf("|          |\n");
		printf("|     Q    |\n");
		printf("|          |\n");
		printf(" ----------\n");
	//	*cardNum = 10; //Set card value to 10
		return cardNum;
	}

	if (*cardNum == 13) {
		//Heart Card
		*cardNum = 10;

		printf(" ----------\n");
		printf("|          |\n");
		printf("|     K    |\n");
		printf("|          |\n");
		printf(" ----------\n");
	//	*cardNum = 10; //Set card value to 10
		return cardNum;
	}

	return;
	}

int clubCardTwo(int Nums) { // print out cards for stack

	if (Nums <= 10) {
		printf(" ----------\n");
		printf("|          |\n");
		printf("|    %02d    |\n", Nums);
		printf("|          |\n");
		printf(" -----------\n");
		return Nums;
	}

	if (Nums == 11) {
		//Heart Card
		Nums = 10; //Set card value to 10

		printf(" ----------\n");
		printf("|          |\n");
		printf("|     J    |\n");
		printf("|          |\n");
		printf(" ----------\n");
	//	Nums = 10;
		return Nums;
	}

	if (Nums == 12) {
		//Heart Card
		Nums = 10; //Set card value to 10

		printf(" ----------\n");
		printf("|          |\n");
		printf("|     Q    |\n");
		printf("|          |\n");
		printf(" ----------\n");
		//Nums = 10; //Set card value to 10
		return Nums;
	}

	if (Nums == 13) {
		//Heart Card
		Nums = 10; //Set card value to 10

		printf("----------\n");
		printf("|         |\n");
		printf("|    K    |\n");
		printf("|         |\n");
		printf("-----------\n");
	//	Nums = 10; //Set card value to 10
		return Nums;
	}

	return;
}

// A utility function to print an array
void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d(%d) ", arr[i], i+1);

	printf("\n%d", sizeArray(cardArray));
	printf("\n");
}

int reShuffle() {


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

	s.top = -1;

	int *pntArry = reShuffle();
	int *compPlays = passOutCompCards(pntArry);
	int *humanPlays = passOutHumCards(compPlays);

	free(compPlays);
	free(pntArry);
	free(humanPlays);

	return 0;
}

