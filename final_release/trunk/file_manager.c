/**
 * file_manager.c
 *
 * @package	 : 
 * @author	 : Vidros Sokratis <sokratis.vidros@gmail.com>
 * @date	 : 30-12-2011 
 * @copyright	 : Copyright (c) 2011 Vidros Sokratis
 * @version	 : 1.0
 * @description : File IO functions
 *   
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define MAX_FILENAME_SIZE 256


/*
 * Extract filename extension
 */

char * get_filename_extension(char * filename) {
    char * dot = strrchr(filename, '.');
	if (dot) 
		return dot + 1;
	else
		return "";
}


/*
 * Extract filename by removing the extension
 */

char * get_filename(char * filename) {
	char * name, * f = NULL;
	char delims[] = ".";
	
	name = strtok( filename, delims );
	if( name != NULL ) 
		return name;
	else
		return "";
}


/*
 * Generate a valid output filename according to the requirements
 */

char * store_to_file(char * filename, char * ext) {
	int counter = 0;
	int length = 0;
	char * output_filename;

	while (1) {
		counter ++;
		length = (strlen(filename) + strlen(ext) + 1);
		output_filename = malloc(length * sizeof(char));
		sprintf( output_filename, "%s%d.%s", filename, counter, ext);

		if ( access( output_filename, F_OK ) == -1 )
			break;
		free(output_filename);
	}

	return output_filename;
}
