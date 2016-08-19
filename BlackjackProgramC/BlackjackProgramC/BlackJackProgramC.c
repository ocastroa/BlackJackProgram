#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "BlackJackProgram.h"

#define Q (12)
#define K (13)
#define J (11)
#define A (1)
#define sizeArray(x) (sizeof(x)/ sizeof((x)[0]))

// global vars
int HUMSUM = 0;
int COMPSUM = 0;
int HUMPOINT = 0;
int COMPPOINT = 0;
int ACESUM = 0;
int COUNTER = 0; // keeps track of position in array. When counter reaches size of array, a new array will be made and counter will be 1

int cardArray[] = { A,3,K,Q,4,5,2,10,6,9,J,7,8,
K,2,Q,3,J,8,10,5,A,9,6,4,7,
6,9,A,7,3,8,4,Q,2,5,J,10,K,
8,3,Q,5,J,4,A,6,7,K,10,9,2,
A,3,K,Q,4,5,2,10,6,9,J,7,8,
K,2,Q,3,J,8,10,5,A,9,6,4,7,
6,9,A,7,3,8,4,Q,2,5,J,10,K,
8,3,Q,5,J,4,A,6,7,K,10,9,2,
A,3,K,Q,4,5,2,10,6,9,J,7,8,
K,2,Q,3,J,8,10,5,A,9,6,4,7,
6,9,A,7,3,8,4,Q,2,5,J,10,K,
8,3,Q,5,J,4,A,6,7,K,10,9,2 }; // 3 decks


void free(int *varToBeFree) {
	free(varToBeFree);
}

void delay(unsigned int msec) { // delays time so game appears slower to player
	clock_t goal = msec + clock();
	while (goal > clock());
}

void checkValue(int *number) { // check value that user inputs and take appropriate action
	int answer;

	printf("Do you want to hit Yes = 1 or No = 0: \n");
	scanf_s("%d", &answer);
	getchar();
	delay(1200);

	switch (answer) {

	case 9:
		printf("\n Game Terminated");
		delay(1300);
		exit(0);

	case 1:
		humanHit(number);
		break;

	case 0:
		popComputerCards(number);
		break;

	default:
		printf("Enter valid number\n");
		delay(1200);
		checkValue(number);
	}
}

void push(int *pntA, int *pntB) { // push comps cards into stack so later pushed cards can be printeds

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
						  //printArray(a_array, n);

	return a_array;

}

// display first out of two cards from comps hand
int passOutCompCards(int *foo) {
	int i = 0;
	int *cardPtr = foo;
	COUNTER += 1;

	for (i = 0; i < 1; i++) {
		if (COUNTER > sizeArray(cardArray)) { // if COUNTER is greater then size of array, reshuffle
			printf("Shuffling Cards\n");
			delay(1200);
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

	if (*cardPtr == 11 || *cardPtr == 12 || *cardPtr == 13) { // change value to 10 for face cards
		*cardPtr = 10;
	}

	int *add = cardPtr - 1;

	if (*add == 1 || *cardPtr == 1) { // check if cards are Aces
		int checkValue = blackJack(add, cardPtr, COMPSUM);
		if (checkValue == 21) { // check if sum is 21
			COMPSUM = 21;
		}
		else {
			COMPSUM = checkValue;
		}
	}

	else {
		COMPSUM = *add + *cardPtr;
	}

	push(cardPtr, add);

	printf("\n    and ? \n\n"); 
	delay(1000);
//	printf("%d\n", COUNTER);
	//printf(" --> Sum is %d\n", COMPSUM);

	return (cardPtr); // return pointer to address of cardPtr
}

void popComputerCards(int *value) { // pop comp cards and print them to screen
	printf("Computer cards are \n");
	clubCardTwo(pop());
	clubCardTwo(pop());
	if (COMPSUM == 21) {
		printf("BlackJack!\n");
	}
	printf(" \n--> Sum is %d\n", COMPSUM);
	delay(1100);
	CompOperations(value);
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
		printf("Shuffling Cards\n");
		delay(1200);
		y = reShuffle();
		COUNTER = 1;
		z = y + 1;
		COUNTER += 1;
	}

	printf("Human Cards are: \n");
	clubCard(y);
	clubCard(z);

	if (*y == 1 || *z == 1) { // check if any of both cards are Aces
		int checkValue = blackJack(y, z, HUMSUM);
		int sum = 0;

		if (checkValue == 21) {
			HUMSUM = 21;
		}

		else {
			if (*y == 1) { // if first card is an Ace, make that value 11 and add it to second card value
				int otherSum = 11;
				sum = checkValue;
				HUMSUM = otherSum + *z;
			}
			else {
				int otherSum = 11; // add first card value to second Ace card with value 11, max can be at most 21
				sum = checkValue;
				HUMSUM = otherSum + *y;
			}
		}
		printf(" \n--> Sum is %d / %d \n", sum, HUMSUM);
		delay(1100);
	}

	else {
		HUMSUM = *y + *z; // sum up the two element values
		printf(" \n--> Sum is %d\n", HUMSUM);
		delay(1100);
	}
	//printf(" and ", *z);
//	printf(" \n--> Sum is %d\n", HUMSUM);
	//delay(1100);
	//printf("%d\n", COUNTER);

	if (HUMSUM == 21) {
		printf("BlackJack!\n");
		popComputerCards(z);
	}

	else {
		HumanCardOperations(z, HUMSUM);
	}
}

// do mathematical operations to check sum of cards and see if they are within boundaries
void HumanCardOperations(int *zTwo, int sum) {

	int answer;

	if (sum > 21) {
		printf("Bust!\n\n");
		popComputerCards(zTwo);
	}

	else if (sum == 21) {
		popComputerCards(zTwo);
	}

	else {
		printf("Do you want to hit Yes = 1 or No = 0: \n");
		scanf_s("%d", &answer);
		delay(1200);

		switch (answer) {

		case 9:
			printf("\n Game Terminated");
			delay(1300);
			exit(0);

		case 1:
			humanHit(zTwo);
			break;

		case 0:
			popComputerCards(zTwo);
			break;

		default:
			checkValue(zTwo);
		}
	}

}

void hit(int *newCard, int cardNumOne, int cardNumTwo) { // this function is when an Ace was first hit and player wants to hit again; takes account of possible double values

	int *nextCard = newCard + 1;
	COUNTER += 1;
	int answer;

	if (COUNTER > sizeArray(cardArray)) {
		printf("Shuffling Cards\n");
		delay(1200);
		nextCard = reShuffle();
		COUNTER = 1;
	}

	if (*nextCard == 11 || *nextCard == 12 || *nextCard == 13) {
		*nextCard = 10;
		cardNumOne += *nextCard;
		cardNumTwo += *nextCard;

		printf("\nNew card is: \n");
		clubCard(nextCard);

		if (cardNumTwo >= 21 & cardNumOne >= 21) { // if both possible values of cards is greater then 21
			printf("Bust!");
			popComputerCards(nextCard);
		}

		if (cardNumTwo >= 21) { // if second possible value is greater then 21, only print out the first possible value
			printf(" \n--> Sum is %d\n", cardNumOne);
			delay(1100);
		}
		else {
			printf(" \n--> Sum is %d / %d \n", cardNumOne, cardNumTwo); // else print out both possible values
			delay(1100);
		}
	}

	if (*nextCard == A) { // if the other card hit is an Ace
		int aceEleven = 11;
		int answer;

		// check both possible cases when Ace is 1 and 11
		cardNumOne += *nextCard;
		cardNumTwo += aceEleven;
		printf("New card is: \n");
		clubCard(nextCard);

		if (cardNumTwo >= 21) { // if second sum is greter then 21, make Ace value 1
			printf(" \n--> Sum is %d\n", cardNumOne);
			delay(1100);
		}
		else {
			printf(" \n--> Sum is %d / %d \n", cardNumOne, cardNumTwo);
			delay(1100);
		}
	}

	else {
		// add new card value to both values and see which one is greater
		cardNumOne += *nextCard;
		cardNumTwo += *nextCard;

		printf("\nNew card is: \n");
		clubCard(nextCard);
		if (cardNumTwo >= 21) {
			printf(" \n--> Sum is %d\n", cardNumOne);
			delay(1100);
		}
		else {
			printf(" \n--> Sum is %d / %d \n", cardNumOne, cardNumTwo);
			delay(1100);
		}
	}

	printf("Do you want to hit Yes = 1 or No = 0: \n");
	scanf_s("%d", &answer);
	delay(1200);

	switch (answer) {

	case 9:
		printf("\n Game Terminated");
		delay(1300);
		exit(0);

	case 1:
		if (cardNumTwo >= 21) {
			HUMSUM += cardNumOne;
			humanHit(nextCard);
		}

		else {
			hit(nextCard,cardNumOne, cardNumTwo);
		}

	case 0:
		if (cardNumTwo <= 21) {
			HUMSUM += cardNumTwo;
		}
		else {
			HUMSUM += cardNumOne;
		}
		popComputerCards(nextCard);
		break;

	default:
		checkValue(nextCard);
	}
}

// players hits and gets one card at a time
int humanHit(int *zThree) {

	int *next = zThree + 1;
	COUNTER += 1;

	if (COUNTER > sizeArray(cardArray)) {
		printf("Shuffling Cards\n");
		delay(1200);
		next = reShuffle();
		COUNTER = 1;
	}

	if (*next == 11 || *next == 12 || *next == 13) {
		*next = 10;
	}

	if (*next == 1) {
		int aceEleven = 11;
		int answer;

		int sumOne = HUMSUM + *next;
		int sumTwo = HUMSUM + aceEleven;
		printf("\nNew card is: \n");
		clubCard(next);

		if (sumTwo >= 21) {
			printf(" \n--> Sum is %d\n", sumOne);
			delay(1100);
		}
		else {
			printf(" \n--> Sum is %d / %d \n", sumOne, sumTwo);
			delay(1100);
		}

		printf("Do you want to hit Yes = 1 or No = 0: \n");
		scanf_s("%d", &answer);
		delay(1200);

		switch (answer) {

		case 9:
			printf("\n Game Terminated");
			delay(1300);
			exit(0);

		case 1:
			if (sumTwo > 21) {
				humanHit(next);
			}
			else {
				hit(next, sumOne, sumTwo);
			}
			break;

		case 0:
			if (sumTwo <= 21) {
				HUMSUM = sumTwo;
			}
			else {
				HUMSUM += sumOne;
			}
			passOutHumCards(next);
			break;

		default:
			checkValue(next);
		}
	}
	
	else {
		HUMSUM += *next;

		printf("New card is: \n");
		clubCard(next);
		printf(" \n--> Sum is %d\n", HUMSUM);
		delay(1100);
		//printf("%d\n", COUNTER);

		HumanCardOperations(next, HUMSUM);
	}
}

void CompOperations(int *aPointer) { // do arithmetic operations on comp card values

	if (COMPSUM == 21) {
		CheckSums(); // compare card values with that of humans
		printf("-------------------------------------------------------------------\n");
		delay(3000);
		int *compPlaysAgain = passOutCompCards(aPointer + 1); // restart game; goes into this loop forever until player quits
		int *humanPlaysAgain = passOutHumCards(compPlaysAgain);
	}

	else if (COMPSUM > 21) {
		printf("Bust!\n");
		CheckSums();
		printf("-------------------------------------------------------------------\n");
		delay(3000);
		int *compPlaysAgain = passOutCompCards(aPointer + 1);
		int *humanPlaysAgain = passOutHumCards(compPlaysAgain);
	}

	else if (COMPSUM < 17) {
		compHit(aPointer);
	}

	else if (COMPSUM >= 17 || COMPSUM < 21) {
		CheckSums();
		printf("-------------------------------------------------------------------\n");
		delay(3000);
		int *compPlaysAgain = passOutCompCards(aPointer + 1);
		int *humanPlaysAgain = passOutHumCards(compPlaysAgain);
	}
}


void compHit(int *hit) { // computers hits 

	int *nextCard = hit + 1;
	COUNTER += 1;

	if (COUNTER > sizeArray(cardArray)) {
		printf("Shuffling Cards\n");
		delay(1200);
		nextCard = reShuffle();
		COUNTER = 1;
	}

	if (*nextCard == 11 || *nextCard == 12 || *nextCard == 13) {
		*nextCard = 10;
	}
	
	if (*nextCard == 1) {
		int cardResult = checkAce(nextCard, COMPSUM); // check possible scenarios for when card is Ace
		COMPSUM = cardResult;
	}

	else {
		COMPSUM += *nextCard;
	}

	printf("New card is: \n");
	clubCard(nextCard);
	printf(" \n--> Sum is %d\n", COMPSUM);
	delay(1100);
	//printf("%d\n", COUNTER);

	CompOperations(nextCard); // check if new sum is within boundaries

}

int blackJack(int *firstCard, int *secondCard, int sum) { // check the sums of first two cards, if sum is 21 then blackjack, else continue

	int blackjack = 21;

	if (*firstCard == 10 || *secondCard == 10) {
		return blackjack;
	}

	else {
		int addCards = *firstCard + *secondCard;
		return addCards;
	}
	return;
}

int checkAce(int *checkCard, int sumCard) { // checks scenarios for when computer hits Ace

	int addCards = 0;
	int changeValue = 1;

	if (sumCard > 10) {
		*checkCard = changeValue;
		addCards = *checkCard + sumCard;
		return addCards;
	}

	else if (sumCard <= 10) {
		*checkCard = 11;
		addCards = *checkCard + sumCard;
	}

	return;
}


void CheckSums() { // compare human sums and computer sums

	int cpSum = COMPSUM;
	int huSum = HUMSUM;

	if (cpSum == 21 & huSum == 21) {// if both cards are 21 then its a push
		printf("\nPush, no points ");
		printf(" ---> Computer's Total = %d  Your Total = %d \n\n", COMPPOINT, HUMPOINT);
		delay(3000);
		//printf("%d\n", COUNTER);
	}

	else if (cpSum == huSum) { // if value of both cards are the same then its a push
		printf("\nPush, no points ");
		printf(" ---> Computer's Total = %d  Your Total = %d \n\n", COMPPOINT, HUMPOINT);
		delay(3000);
		//printf("%d\n", COUNTER);
	}

	else if (cpSum > 21) { // if compsum is greater then 21 but human sum is less then 21, then human wins
		if (huSum <= 21) {
			HUMPOINT += 1;
			printf("\n+1 You ---> Computer's Total = %d Your Total = %d \n\n", COMPPOINT, HUMPOINT);
			delay(3000);
		//	printf("%d\n", COUNTER);
		}

		else {
			printf("\nNo winners ");
			printf(" ---> Computer's Total = %d  Your Total = %d \n\n", COMPPOINT, HUMPOINT);
			delay(3000);
		//	printf("%d\n", COUNTER);
		}
	}

	else if (huSum > 21) { // if humans sum is greater then 21 and comp sum is less then 21, comp wins
		if (cpSum <= 21) {
			COMPPOINT += 1;
			printf("\n+1 Computer ---> Computer's Total = %d  Your Total = %d \n\n", COMPPOINT, HUMPOINT);
			delay(3000);
	//		printf("%d\n", COUNTER);
		}
	}

	else if (cpSum < huSum) { // if comp sum is less then human sum, human wins
		printf("\nYou win!\n");
		HUMPOINT += 1;
		printf("+1 You ---> Computer's Total = %d  Your Total = %d \n\n", COMPPOINT, HUMPOINT);
		delay(3000);
	//	printf("%d\n", COUNTER);
	}

	else if (huSum < cpSum) { // if human sum is less then comp sum comp wins
		printf("\nYou lose!\n");
		COMPPOINT += 1;
		printf("+1 Computer ---> Computer's Total = %d  Your Total = %d \n\n", COMPPOINT, HUMPOINT);
		delay(3000);
	//	printf("%d\n", COUNTER);
	}
}

int clubCard(int *cardNum) { // print out cards for pointers

	if (*cardNum > 1 & *cardNum <= 10) {
			printf(" ----------\n");
			printf("|          |\n");
			printf("|    %02d    |\n", *cardNum);
			printf("|          |\n");
			printf(" -----------\n");
			delay(1400);
			return cardNum;
	}

	if (*cardNum == 1) {
		printf(" ----------\n");
		printf("|          |\n");
		printf("|     A    |\n");
		printf("|          |\n");
		printf(" ----------\n");
		delay(1400);
		return cardNum;
	}

	if (*cardNum == 11) {
		    *cardNum = 10;
			printf(" ----------\n");
			printf("|          |\n");
			printf("|     J    |\n");
			printf("|          |\n");
			printf(" ----------\n");
			delay(1400);
			return cardNum;
		}

	if (*cardNum == 12) {
		*cardNum = 10;
		printf(" ----------\n");
		printf("|          |\n");
		printf("|     Q    |\n");
		printf("|          |\n");
		printf(" ----------\n");
		delay(1400);
		return cardNum;
	}

	if (*cardNum == 13) {
		*cardNum = 10;
		printf(" ----------\n");
		printf("|          |\n");
		printf("|     K    |\n");
		printf("|          |\n");
		printf(" ----------\n");
		delay(1400);
		return cardNum;
	}
	return;
	}

int clubCardTwo(int Nums) { // print out cards for stack

	if (Nums > 1 & Nums <= 10) {
		printf(" ----------\n");
		printf("|          |\n");
		printf("|    %02d    |\n", Nums);
		printf("|          |\n");
		printf(" -----------\n");
		delay(1400);
		return Nums;
	}

	if (Nums == 1) {
		printf(" ----------\n");
		printf("|          |\n");
		printf("|     A    |\n");
		printf("|          |\n");
		printf(" ----------\n");
		delay(1400);
		return Nums;
	}

	if (Nums == 11) {
		Nums = 10; //Set card value to 10
		printf(" ----------\n");
		printf("|          |\n");
		printf("|     J    |\n");
		printf("|          |\n");
		printf(" ----------\n");
		delay(1400);
		return Nums;
	}

	if (Nums == 12) {
		Nums = 10; //Set card value to 10
		printf(" ----------\n");
		printf("|          |\n");
		printf("|     Q    |\n");
		printf("|          |\n");
		printf(" ----------\n");
		delay(1400);
		return Nums;
	}

	if (Nums == 13) {
		Nums = 10; //Set card value to 10
		printf("----------\n");
		printf("|         |\n");
		printf("|    K    |\n");
		printf("|         |\n");
		printf("-----------\n");
		delay(1400);
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

int main() {

	s.top = -1;

	printf("--------------------------------------------------------------------------\n");
	printf("                    Welcome to the game of Blackjack                      \n");
	printf("                         Created by Oscar Castro                        \n\n");
	printf("            To hit press 1, to stay press 0, to quit game press 9          ");
	printf("\n\n                                    Enjoy!!!                           \n");
	printf("---------------------------------------------------------------------------\n\n");

	int *pntArry = reShuffle();
	int *compPlays = passOutCompCards(pntArry);
	int *humanPlays = passOutHumCards(compPlays);

	free(pntArry);

	return 0;
}

