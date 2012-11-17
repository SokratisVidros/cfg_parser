/**
 * recursive_generator.c
 *
 * @package	 : 
 * @author	 : Vidros Sokratis <sokratis.vidros@gmail.com>
 * @date        : 30-12-2011 
 * @copyright	 : Copyright (c) 2011 Vidros Sokratis
 * @version	 : 1.0
 * @description : Sentence producer from CFG. It produces a random valid 
 *		   sentence from a given grammar
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grammar.c"
#include "trimmer.c"
#include "file_manager.c"

#define MAX_STRING_SIZE 60

#define START_ELEMENT "<start>"

int char_counter = 0;

FILE * infile, * outfile;

void print_formatted(char * str) {
	int length = strlen(str) + 1;

	char_counter += length;	
	if (char_counter > 60) {
		fprintf(outfile, "\n%s ", str);
		char_counter = length;
	}
	else
		fprintf(outfile, "%s ", str);
}

void parse_file(FILE *f) {
	int length, i, is_new_prod = 0;
	char c;
	char delims[] = " ";
	char to_be_removed[] = "; \t\n";
	char * tokens, * non_term, * clean_token = NULL;
	char s[MAX_STRING_SIZE], s2[MAX_STRING_SIZE];

    do {
    	c = fgetc(f);
        if(c == '{')
        {
            fseek(f, 1, SEEK_CUR);
     
			fgets(s, MAX_STRING_SIZE, f);

			length = strlen(s) - 1;
			strncpy(s2, s, length);
			
			for(i=length; i < MAX_STRING_SIZE; i++)
				s2[i] = '\0';
	
			non_term = strdup(s2);
			non_term = remove_chars(non_term, to_be_removed);			

			/* Extract the root non terminal symbol */
			grammar_nodeT new_node = create_g_node(non_term);
	
			is_new_prod = 0;

	        do {
				fgets(s, 5 * MAX_STRING_SIZE, f);
				tokens = (char *) strtok(s, delims);

				if(strchr(tokens, '}'))
					continue;

				while (tokens != NULL) { 
					clean_token = remove_chars(tokens, to_be_removed);

					if(strlen(clean_token)==0)
						break;

					/* Get terminal and non terminal symbols for the specific production */
					if(is_new_prod)
						add_element_to_g_node(&new_node, clean_token, NEW_PRODUCTION);
					else						
						add_element_to_g_node(&new_node, clean_token, KEEP_PRODUCTION);
    				tokens = (char *) strtok( NULL, delims );
					is_new_prod = 0;
				}
				is_new_prod = 1;
			} while (strcmp(s, "}") <= 0);

			/* Insert new node to grammar */
			insert_to_grammar(new_node);
 		}
    } while (c != EOF);
}


/*
 *
 */

void generate_sentence(char * element) {
	list_nodeT * curr_node, * production = NULL;

	production = get_non_terminal_random_production(element);
	
	if(production == NULL ) {
		printf("ERROR!");
		fprintf(stderr, "ERROR: No production found for the '%s' non terminal element.\nQuiting...\n", element);
		exit(-1);
	}

	curr_node = walk_list(production);

	while ( production != curr_node ) {
		char * token = curr_node->content;

		if (is_non_terminal(token)) {
			generate_sentence(token);
		}
		else {
			print_formatted(token);
		}
		curr_node = walk_list(curr_node);
	}
	
	return;
}

int main (int argc, char *argv[]) {

	char * in_name, * in_ext, * in_filename, * out_filename;

	if (argc != 2) {
		printf("Usage %s <grammar_filename>\n", argv[0]);
		return 1;
	}

	in_filename = argv[1];
	infile = fopen(in_filename, "r");
	if (infile == NULL) {
		fprintf(stderr, "ERROR: Could not open file \"%s\"\n", in_filename);
		return 1;
	}

	in_ext = get_filename_extension(in_filename);
	in_name = get_filename(in_filename);
	out_filename = store_to_file(in_name, in_ext);

	printf("###\tRecursive Generator\t###\n");

	outfile = fopen(out_filename, "w");
	if (outfile == NULL) {
		fprintf(stderr, "ERROR:Could not open file \"%s\"\n", outfile);
		fclose(infile);
		return 1;
	}

	printf("Parsing file %s...\n", in_filename);
	parse_file(infile);

	//print_grammar();
	printf("Output filename: %s\n", out_filename);
	printf("Generating sentence... \t");

	generate_sentence(START_ELEMENT);

	printf("Done!\n");

	fprintf(outfile, "\n");
	fclose(infile);
	fclose(outfile);

	printf("Quiting...\n");
	destroy_grammar();

	return 0;
}
