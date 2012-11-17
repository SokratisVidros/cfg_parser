/** 
 * grammar.c
 *
 * @package	 : 
 * @author	 : Vidros Sokratis <sokratis.vidros@gmail.com>
 * @date	 : 28-12-2011 
 * @copyright	 : Copyright (c) 2011 Vidros Sokratis
 * @version	 : 1.0
 * @description  : Grammar structure API
 *   
 */
								
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "double_list.c"
#include "random.c"


#define MAX_CONTENT_SIZE 60
#define MAX_PRODUCTION_SIZE 10

#define KEEP_PRODUCTION 0
#define NEW_PRODUCTION 1


/*
 * Grammar Node Structure
 */

struct grammar_node {
	char * non_terminal;
	int num_of_productions;
	list_nodeT * productions[MAX_PRODUCTION_SIZE];
};

typedef struct grammar_node grammar_nodeT;


int g_num_elements = 0;
int g_num_allocated = 0;


/* 
 * Global Grammar Data Structure 
 */

grammar_nodeT * grammar;	


/*
 * Create a node of the grammar containing a non-terminal, the number_of_productions and the productions
 */

grammar_nodeT create_g_node(char * non_terminal) {

	grammar_nodeT new_g_node;
	new_g_node.non_terminal = strdup(non_terminal);
	new_g_node.num_of_productions = 1;
	new_g_node.productions[0] = init_list();
	return new_g_node;
}


/*
 * Add element to grammar node, means to add a new terminal or non terminal element to the production
 */

void add_element_to_g_node(grammar_nodeT * g_node, char * element, int is_new_production) {

	if (is_new_production == NEW_PRODUCTION) {	
		g_node->productions[g_node->num_of_productions] = init_list();
		g_node->num_of_productions++;
	}

	if (add_node(g_node->productions[g_node->num_of_productions - 1], element) == -1) {
		fprintf(stderr, "ERROR: Memory allocation error in node addition!\n");
		exit(1);
	}
}


/*
 * Insert the grammar node to the global grammar structure
 */

int insert_to_grammar(grammar_nodeT g_node) {

    if(g_num_allocated == g_num_elements)
    {
		if (g_num_allocated == 0)
			g_num_allocated++;
		else
			g_num_allocated *= 2;
		
		grammar = (grammar_nodeT * ) realloc(grammar, (g_num_allocated * sizeof(grammar_nodeT)));

		if (!grammar) {
			fprintf(stderr, "ERROR: Couldn't realloc memory!\n");
            return(-1);
        }
	}

    grammar[g_num_elements] = g_node;
    g_num_elements++;

	return g_num_elements;
}


/*
 * Get the Non Terminal element at a specific position
 */

char * get_root_non_terminal_at (int pos) {
	return grammar[pos].non_terminal;
}


/*
 * Get random production for a given non terminal
 */

list_nodeT * get_non_terminal_random_production(char * non_terminal) {
	int i = 0;
	char * nt;
	for(i = 0; i<g_num_elements; i++) {	
		nt = get_root_non_terminal_at(i); 
		if(strcmp(nt,non_terminal) == 0){
			int r = random_generator(grammar[i].num_of_productions);
			return grammar[i].productions[r];
		}
	}
	
	return NULL;
}

/*
 *
 */

int is_non_terminal(char * element){
	return (strchr(element, '<') && strchr(element, '>'));
}  

/*
 * Print grammar
 */

void print_grammar() {

	int i,j;

	printf("\n### Grammar ###\nNumber of Nodes: %d\nNumber of allocated Nodes: %d\n\n", g_num_elements, g_num_allocated);

	for(i=0; i<g_num_elements; i++) {
		printf("Root-N: %s\n", get_root_non_terminal_at(i));

		for(j=0; j < grammar[i].num_of_productions; j++) {
			printf("Element: %d,%d\n", i, j);
			print_list(grammar[i].productions[j]);
		}
		printf("\n");
	}

	return;
}


/*
 * Destroy grammar structure and free memory
 */

void destroy_grammar() {
	int i,j;

	for(i=0; i<g_num_elements; i++) {
		for(j=0; j < grammar[i].num_of_productions; j++) {
			destroy_list(grammar[i].productions[j]);
		}
	}

	free(grammar);
	return;
}
