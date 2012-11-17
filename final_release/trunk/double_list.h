/**
 * double_list.h
 *
 * @package	 : 
 * @author	 : Vidros Sokratis <sokratis.vidros@gmail.com>
 * @date	 : 28-12-2011 
 * @copyright	 : Copyright (c) 2011 Vidros Sokratis
 * @version	 : 1.0
 * @description : Double Linked List Header file.
 *   
 */

#define MAX_CONTENT_SIZE 60

struct list_node {
	char *content;
	struct list_node *next;
	struct list_node *previous;
};

typedef struct list_node list_nodeT;


/* 
 * Initializes a new list. Returns a pointer to the sentinel allocated
 * allocated for the new list
 */

list_nodeT *init_list();


/* 
 * Returns a pointer to the node containing the data we are looking for.
 */

list_nodeT *search_node(list_nodeT *head, char *key);


/*
 * List walker
 */

list_nodeT * walk_list(list_nodeT *head);


/* 
 * Print the list
 */

void print_list(list_nodeT *head);


/*
 * Add a new node to the list
 */

int add_node(list_nodeT *head, char *value);


/*
 * Remove node based on key value
 */

int remove_node(list_nodeT *head, char *key);


/* 
 * Scans the list and destroys all nodes 
 */

void destroy_list(list_nodeT *head);