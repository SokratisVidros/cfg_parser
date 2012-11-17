/**
 * double_list.c
 *
 * @package	 : 
 * @author	 : Vidros Sokratis <sokratis.vidros@gmail.com>
 * @date	 : 28-12-2011 
 * @copyright	 : Copyright (c) 2011 Vidros Sokratis
 * @version	 : 1.0
 * @description  : Double Linked List Structure API, Source code file
 *   
 */		
				
#include "double_list.h"


list_nodeT * init_list() {
	list_nodeT * sentinel;

	sentinel = (list_nodeT *) malloc(sizeof(list_nodeT));
	sentinel->next = sentinel;
	sentinel->previous = sentinel;

	return sentinel;
}


list_nodeT * search_node(list_nodeT *head, char *key) {
	list_nodeT * curr;

	for (curr = head->previous; strcmp(curr->content, key) < 0; curr = curr->previous);
	
	if (curr == head || strcmp(curr->content, key) != 0)
		return NULL;

	return curr;
}


list_nodeT * walk_list(list_nodeT *head) {
	list_nodeT * curr;
	curr = head->previous;
	
	return curr;
}


void print_list(list_nodeT *head) {
	list_nodeT *curr;

	for (curr = head->previous; curr != head; curr = curr->previous) {
		printf("-> '%s' ", curr->content);
	}

    printf("\n");
	free(curr);
}


int add_node(list_nodeT * head, char * value) {
	list_nodeT *new_node;
	
	new_node = (list_nodeT *) malloc(sizeof(list_nodeT));
	if (new_node == NULL)
		return -1;

	new_node->content = strdup(value);
	
	new_node->next = head->next;
	head->next->previous = new_node;
    new_node->previous = head;
	head->next = new_node;

	return 0;
}


int remove_node(list_nodeT * head, char * key) {
	list_nodeT * node;
	
	node = search_node(head, key);
	if (node == NULL)
		return 1;
	
	node->previous->next = node->next;
	node->next->previous = node->previous;
	
	free(node->content);
	free(node);
	
	return 0;
}


void destroy_list(list_nodeT * head) {
	list_nodeT * curr;

	for (curr = head->next; curr != head; ) {
		curr = curr->next;
		free(curr->previous->content);
		free(curr->previous);
	}
	free(head);
}
