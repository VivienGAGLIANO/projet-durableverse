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

void push_last_stack(int e, stack* a){
	stack * p;
	while a->next!=NULL{
		a->next;
	}
	p->val=e;
	p->next=NULL;
	a->next=p;
}
int pop_last_stack(stack* a){
	while (a->next)->next!=NULL{
		*a=a->next;

	}
	p=(a->next)->val;
	a->next=NULL;
	return a->val;
}
int get_stack_ele_position(elm e, stack a){
	int i = 0;
	while a->val!=e{
		a=a->next;
		i=i+1;
	}
	return i;
}

int len_stack(stack a){
	int i = 0;
	while a->next!=NULL{
		a=a->next;
		i=i+1;
	}
	return i;
}
