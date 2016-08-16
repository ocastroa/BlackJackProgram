#pragma once // compiles only once in a single compile

// constants to be used as gloabl vars
extern int HUMSUM;
extern int COMPSUM;
extern int HUMPOINT;
extern int COMPPOINT;
extern int COUNTER;

#define MAXSIZE 2

struct stack
{
	int stk[MAXSIZE];
	int top;
};

typedef struct stack STACK;
STACK s;

void push(int *s, int *r);
int  pop(void);

void HumanCardOperations(int *zTwo, int sum);
int humanHit(int *zThree);

void CompOperations(int *aPointer);
void compHit(int *hit);
void CheckSums();

int clubCard(int *cardNum);

int reShuffle();


