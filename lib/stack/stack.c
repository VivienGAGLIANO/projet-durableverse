#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"

/* @requires: nothing
 * @assigns: nothing
 * @ensures: returns an empty stack (ie. a null pointer)
 */
stack create_stack() {
  return NULL;
}

/* @requires: s is a valid stack
 * @assigns: nothing
 * @ensures: returns 1 if s is an empty stack, 0 otherwise
 */
int is_stack_empty(stack s) {
  return s == NULL;
}

/* @requires: s is a valid stack and doesn't loop
 * @assigns: creates a new stack
 * @ensures: returns a reversed copy of s
 */
stack reverse_stack(stack s) {
  stack new_stack = create_stack();
  while (s) {
    push(s->head, &new_stack);
    s = s->tail;
  }
  return new_stack;
}

/* @requires: s is a valid stack
 * @assigns: creates a new stack and copies each element of s in the new stack, in the same order
 * @ensures: returns a copy of the stack s
 */
stack copy_stack(stack s) {
  if (is_stack_empty(s))
    return create_stack();
  stack new_stack = (stack) malloc(sizeof(item));
  stack prev = new_stack;
  prev->head = s->head;
  s = s->tail;
  while (s) {
    stack new = (stack) malloc(sizeof(item));
    new->head = s->head;
    prev->tail = new;
    prev = new;
    s = s->tail;
  }
  prev->tail = NULL;
  return new_stack;
}

/* @requires: s is a valid stack and doesn't loop
 * @assigns: creates a new stack and pushes each element of s in it in a random order
 * @ensures: returns a shuffled copy of the stack s
 */
stack shuffle_stack(stack s) {
  s = copy_stack(s);
  stack new = create_stack();
  int n = stack_len(s);
  // srand(time(NULL));
  while (!is_stack_empty(s)) {
    push(pop_stack_elem(&s, rand() % n), &new);
    n--;
  }
  return new;
}

/* @requires: *s is a valid stack
 * @assigns: modifies s
 * @ensures: adds e to the begginning of s
 */
void push(stack_elem e, stack* s) {
  stack new = (stack) malloc(sizeof(item));
  new->head = e;
  new->tail = *s;
  *s = new;
}

/* @requires: *s is a valid, non empty stack
 * @assigns: modifies s
 * @ensures: removes the first element of the stack and returns it
 */
stack_elem pop(stack* s) {
  stack_elem e = (*s)->head;
  stack tmp = *s;
  *s = (*s)->tail;
  free(tmp);
  return e;
}

/* @requires: s is a valid, non empty stack
 * @assigns: nothing
 * @ensures: returns the first element of s
 */
stack_elem peek(stack s) {
  return s->head;
}

/* @requires: *s is a valid stack and doesn't loop
 * @assigns: modifies the stack
 * @ensures: adds e at the end of *s
 */
void push_last(stack_elem e, stack* s) {
  if (is_stack_empty(*s)) {
    return push(e, s);
  }
  stack new = (stack) malloc(sizeof(item));
  new->head = e;
  new->tail = NULL;
  stack c = *s;
  while (c->tail != NULL) {
    c = c->tail;
  }
  c->tail = new;
}

/* @requires: *s is a valid, non-empty stack and doesn't loop
 * @assigns: modifies the stack
 * @ensures: removes the last element of the stack and returns it
 */
stack_elem pop_last(stack* s) {
  if ((*s)->tail == NULL)
    return pop(s);
  stack c = *s;
  while (c->tail->tail != NULL) {
    c = c->tail;
  }
  stack_elem e = c->tail->head;
  free(c->tail);
  c->tail = NULL;
  return e;
}

/* @requires: s is a valid, non empty stack and doesn't loop
 * @assigns: nothing
 * @ensures: returns the last element of s
 */
stack_elem peek_last(stack s) {
  while (s->tail != NULL) {
    s = s->tail;
  }
  return s->head;
}

/* @requires: s is a valid stack, 0 <= index < stack_len(s)
 * @assigns: nothing
 * @ensures: returns the index-th stack_element of s
 */
stack_elem get_stack_elem(stack s, int index) {
  for (int i = 0; i < index; i++) {
    s = s->tail;
  }
  return s->head;
}

/* @requires: *s is a valid stack, 0 <= index < stack_len(*s)
 * @assigns: changes the index-th element of the stack to e
 * @ensures: changes the index-th element of the stack to e
 */
void set_stack_elem(stack *s, stack_elem e, int index) {
  stack l = *s;
  for (int i = 0; i < index; i++) {
    l = l->tail;
  }
  l->head = e;
}

/* @requires: *s is a valid stack, 0 <= index <= stack_len(*s)
 * @assigns: modifies the stack
 * @ensures: inserts the stack_element e at the index-th place in the stack
 */
void insert_stack_elem(stack* s, stack_elem e, int index) {
  if (index == 0) {
    return push(e, s);
  }
  stack cur = *s;
  for (int i = 0; i < index - 1; i++) {
    cur = cur->tail;
  }
  item* new = (item*) malloc(sizeof(item));
  new->head = e;
  new->tail = cur->tail;
  cur->tail = new;
}

/* @requires: *s is a valid stack, 0 <= index < stack_len(*s)
 * @assigns: modifies the stack
 * @ensures: removes the index-th element of the stack, frees the memory previously allocated to it and returns the element removed
 */
stack_elem pop_stack_elem(stack *s, int index) {
  if (index == 0) {
    return pop(s);
  } else {
    stack cur = *s;
    for (int i = 0; i < index - 1; i++) {
      cur = cur->tail;
    }
    stack tmp = cur->tail->tail;
    stack_elem e = cur->tail->head;
    free(cur->tail);
    cur->tail = tmp;
    return e;
  }
}

/* @requires: *s is a valid stack, 0 <= i1, i2 < stack_len(*s)
 * @assigns: modifies the stack
 * @ensures: switch the e1-th and the e2-th elements of the stack
 */
void switch_stack_elem(stack *s, int e1, int e2) {
  if (e1 == e2) return;
  int i1 = e1 < e2 ? e1 : e2;
  int i2 = e1 < e2 ? e2 : e1;
  stack cur = *s;
  int i = 0;
  for (; i < i1; i++) {
    cur = cur->tail;
  }
  stack node1 = cur;
  for (; i < i2; i++) {
    cur = cur->tail;
  }
  stack node2 = cur;
  stack_elem elem1 = node1->head;
  node1->head = node2->head;
  node2->head = elem1;
}

/* @requires: s is a valid stack and (e is in s or s doesn't loop)
 * @assigns: nothing
 * @ensures: returns the index of the first occurence of e in s, or -1 if e is not in s
 */
int seek_stack_elem(stack_elem e, stack s) {
  if (is_stack_empty(s))
    return -1;
  int index = 0;
  while (s->head != e && s->tail != NULL) {
    s = s->tail;
    index++;
  }
  return s->head == e ? index : -1;
}

/* @requires: s is a valid stack and doesn't loop
 * @assigns: nothing
 * @ensures: returns the length of s (ie. the number of elements it contains)
 */
int stack_len(stack s) {
  int i = 0;
  while (s != NULL) {
    s = s->tail;
    i++;
  }
  return i;
}

/* @requires: *s is a valid stack and doesn't loop
 * @assigns: frees the memory used by each item of the stack
 * @ensures: frees the memory used by the stack
 */
void free_stack(stack* s) {
  stack cur = *s;
  while (cur != NULL) {
    stack tmp = cur->tail;
    free(cur);
    cur = tmp;
  }
}

/* @requires: s is a valid stack and doesn't loop
 * @assigns: nothing
 * @ensures: prints the stack s in the format [stack_elem1] -> [stack_elem2] -> ... -> []
 */
#if DEFINE_PRINT_STACK_FUNCTION >= 1
void print_stack(stack s) {
  while (s != NULL) {
    printf("[%d] -> ", s->head);
    s = s->tail;
  }
  printf("[]\n");
}
#endif
