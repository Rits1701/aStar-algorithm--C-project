#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List* newList(compFun comp,prFun pr) {
	List* l = malloc(sizeof(List));
	if (l == NULL) {
		return 0;
    }
	l->nelts = 0;
	l->head = NULL;
	l->comp = comp;
	l->pr = pr;
	return l;
}

void delList(List* l) {
	Node* e = l->head;
	while (e != NULL) {
		Node* next = e->next;
		free(e);
		e = next;
	}
	free(l);
}

status nthInList(List* l,int n,void** e) {
	Node* el = l->head;
	while (n--)	{
		if (el == NULL) {
			break;
        }
		el = el->next;
	}
	if (el == NULL) {
		return ERRINDEX;
	}
	*e = el->val;
	return OK;
}

status addListAt(List* l,int p,void* e) {
	Node* newNode = malloc(sizeof(Node));
	if (newNode == NULL) {
		return ERRALLOC;
    }
	newNode->val = e;
	if (p == 0) {
		newNode->next = l->head;
		l->head = newNode;
	} else {
		Node* el = l->head;
		while (--p) {
			if (el == NULL) {
				return ERRINDEX;
            }
			el = el->next;
		}
		if (el == NULL) {
			return ERRINDEX;
        }
		newNode->next = el->next;
		el->next = newNode;
	}
	l->nelts++;
	return OK;
}

status remFromListAt(List* l,int p,void** e) {
	Node* el = l->head;
	if (el == NULL) {
		return ERRINDEX;
    }
	if (p == 0) {
		l->head = el->next;
	} else {
		Node* prev = el;
		while (p--) {
			el = el->next;
			if (el == NULL) {
				return ERRINDEX;
            }
			prev = el;
		}
		prev->next = el->next;
	}
	*e = el->val;
	free(el);
	l->nelts--;
	return OK;
}

status remFromList(List* l,void* e) {
	Node* el = l->head;
	if (el == NULL) {
		return ERRABSENT;
    }
	if (el->val == e) {
		l->head = el->next;
	} else {
		Node* prev = el;
		el = el->next;
		while (el != NULL) {
			if (el->val == e) {
				prev->next = el->next;
				break;
			}
			prev = el;
			el = el->next;
		}
		if (el == NULL) {
			return ERRABSENT;
		}
	}
	free(el);
	l->nelts--;
	return OK;
}

void displayList(List* l) {
	putchar('[');
	Node* el = l->head;
	while (el != NULL) {
		(*l->pr)(el->val);
		putchar(' ');
		el = el->next;
	}
	putchar(']');
}

void forEach(List* l,void(*f)(void*)) {
	Node* el = l->head;
	while (el != NULL) {
		(*f)(el->val);
		el = el->next;
	}
}

int lengthList(List* l) {
	return l->nelts;
}

status addList(List* l,void* e) {
	Node* newNode = malloc(sizeof(Node));
	if (newNode == NULL)
		return ERRALLOC;
	newNode->val = e;
	Node* el = l->head;
	if (el == NULL) {
		l->head = newNode;
		newNode->next = NULL;
	} else if ((*l->comp)(e, el->val) <= 0) {
		newNode->next = l->head;
		l->head = newNode;
	} else {
		Node* prev = el;
		el = el->next;
		while (el != NULL) {
			if ((*l->comp)(e, el->val) <= 0) {
				break;
			}
			prev = el;
			el = el->next;
		}
		prev->next = newNode;
		newNode->next = el;
	}
	l->nelts++;
	return OK;
}

Node* isInList(List* l,void* e) {
	Node* el = l->head;
	while (el != NULL) {
		if (e == el->val) {
			return (Node*)1;
        }
		el = el->next;
	}
	return 0;
}
