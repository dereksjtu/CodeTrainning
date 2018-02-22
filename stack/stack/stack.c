#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 10

typedef int ElementType;
typedef struct StackNode_H {
	ElementType val;
	struct StackNode_H *next;
}StackNode, *StackPtr;
typedef struct
{
	StackPtr top;
	int size;
}LinkStack;

void initStack(LinkStack *s)
{
	s->top = malloc(sizeof(StackNode));
	s->top = NULL;
	s->size = 0;
}

bool isStackEmpty(LinkStack *s)
{
	return s->size == 0;
}
bool isStackFull(LinkStack *s)
{
	return s->size == MAXSIZE;
}
void pushStack(LinkStack *s, ElementType x)
{
	if (isStackFull(s))
		return;
	StackNode *newNode = malloc(sizeof(StackNode));
	newNode->val = x;
	newNode->next = s->top;
	s->top = newNode;
	s->size++;
}

ElementType popStack(LinkStack *s)
{
	if (isStackEmpty(s))
		return -1;
	StackPtr p;
	ElementType e;
	p = s->top;
	s->top = s->top->next;
	e = p->val;
	free(p);
	s->size--;
	return e;
}

ElementType frontStack(LinkStack *s)
{
	if (isStackEmpty(s))
		return -1;
	return s->top->val;
}

void clearStack(LinkStack *s)
{
	if (isStackFull(s))
		return;
	while (s->top) {
		StackNode *p;
		p = s->top;
		s->top = s->top->next;
		free(p);
	}
	s->size = 0;
}