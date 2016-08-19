#pragma once // compiles only once in a single compile

// constants to be used as gloabl vars
extern int HUMSUM;
extern int COMPSUM;
extern int HUMPOINT;
extern int COMPPOINT;
extern int COUNTER;
extern int ACESUM;

#define MAXSIZE 2

struct stack
{
	int stk[MAXSIZE];
	int top;
};

typedef struct stack STACK;
STACK s;

void delay(unsigned int msec);

void push(int *s, int *r);
int  pop(void);

int passOutCompCards(int *foo);
int passOutHumCards(int *ptrCard);
int reShuffle();

void HumanCardOperations(int *zTwo, int sum);
void hit(int *newCard, int cardNumOne, int cardNumTwo);
int humanHit(int *zThree);

void CompOperations(int *aPointer);
void popComputerCards(int *value);
void compHit(int *hit);
int blackJack(int *firstCard, int *secondCard, int sum);
int checkAce(int *checkCard, int sumCard);

void CheckSums();

int clubCard(int *cardNum);

int reShuffle();


