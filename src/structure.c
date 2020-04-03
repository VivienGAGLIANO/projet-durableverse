#include "../headers/structure.h"

stack create_stack(){
	return NULL;
}

int is_empty_stack(stack a){
	return a == NULL;
}

void push_stack(stack_elm e, stack* a){
	stack new_cell = (stack) malloc(sizeof(struct elm));
	
	/* Checking malloc failure */
	if (new_cell == NULL) {
		perror("Memory allocation failure");
		exit(1);
	}

	new_cell->val = e;
	new_cell->next = *a;
	*a = new_cell;
}

stack_elm pop_stack(stack* a){
	*a=a->next;
	return a->val;
}

void push_last_stack(stack_elm e, stack* a){
	stack * p;
	while (a->next!=NULL){
		a->next;
	}
	p->val=e;
	p->next=NULL;
	a->next=p;
}
stack_elm pop_last_stack(stack* a){
	while ((a->next)->next!=NULL){
		*a=a->next;
	}
	int p;
	p=(a->next)->val;
	a->next=NULL;
	return a->val;
}
int get_stack_ele_position(elm e, stack a){
	int i = 0;
	while (a->val!=e){
		a=a->next;
		i=i+1;
	}
	return i;
}

int len_stack(stack a){
	int i = 0;
	while (a->next!=NULL){
		a=a->next;
		i=i+1;
	}
	return i;
}
