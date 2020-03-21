#include "structure.h"

stack create_stack(){
	a=malloc(sizeof(stack));
	return a;
}

int is_empty_stack(stack a){
	if a==NULL
		return 1;
	else
		return 0;
}

void push_stack(int e, stack* a){
	p=*a;
	a->val=e;
	a->next=p;
}

int pop_stack(stack* a){
	*a=a->next;
	return a->val;
}

