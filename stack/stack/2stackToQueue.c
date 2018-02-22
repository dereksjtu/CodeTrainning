//232. Implement Queue using Stacks
//Implement the following operations of a queue using stacks.
//
//push(x) --Push element x to the back of queue.
//pop() --Removes the element from in front of queue.
//peek() --Get the front element.
//empty() --Return whether the queue is empty.

typedef int ElementType;
typedef struct StackNode_H {
	ElementType val;
	struct StackNode_H *next;
}StackNode, *StackPtr;
typedef struct
{
	StackPtr top;
	int size;
	int capacity;
}LinkStack;

void initStack(LinkStack *s, int capacity)
{
	s->top = (StackPtr)malloc(sizeof(StackNode));
	s->top = NULL;
	s->size = 0;
	s->capacity = capacity;
}

bool isStackEmpty(LinkStack *s)
{
	return s->size == 0;
}
bool isStackFull(LinkStack *s)
{
	return s->size == s->capacity;
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

typedef struct {
	LinkStack p;
	LinkStack q;
} MyQueue;

/** Initialize your data structure here. */
MyQueue* myQueueCreate(int maxSize) {
	MyQueue *queue;
	queue = malloc(sizeof(MyQueue));
	initStack(&(queue->p), maxSize);
	initStack(&(queue->q), maxSize);
	return queue;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
	pushStack(&(obj->p), x);
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
	while (obj->p.size > 1) {
		ElementType x = popStack(&(obj->p));
		pushStack(&(obj->q), x);
	}
	ElementType ret = popStack(&(obj->p));
	while (obj->q.size) {
		ElementType x = popStack(&(obj->q));
		pushStack(&(obj->p), x);
	}
	return ret;
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
	while (obj->p.size > 1) {
		ElementType x = popStack(&(obj->p));
		pushStack(&(obj->q), x);
	}
	ElementType ret = frontStack(&(obj->p));
	while (obj->q.size) {
		ElementType x = popStack(&(obj->q));
		pushStack(&(obj->p), x);
	}
	return ret;
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
	return isStackEmpty(&(obj->p));
}

void myQueueFree(MyQueue* obj) {
	clearStack(&(obj->p));
	clearStack(&(obj->q));
}

/**
* Your MyQueue struct will be instantiated and called as such:
* struct MyQueue* obj = myQueueCreate(maxSize);
* myQueuePush(obj, x);
* int param_2 = myQueuePop(obj);
* int param_3 = myQueuePeek(obj);
* bool param_4 = myQueueEmpty(obj);
* myQueueFree(obj);
*/