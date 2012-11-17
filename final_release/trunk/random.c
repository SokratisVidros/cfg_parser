/**
 * random.c
 *
 * @package	 : 
 * @author	 : Vidros Sokratis <vidros@eurecom.fr>
 * @date	 : 29-12-2011 
 * @copyright	 : Copyright (c) 2011 Vidros Sokratis
 * @version	 : 1.0
 * @description : Random Integer Generator
 *   
 */

#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

int random_generator(int max_number) {
	struct timeval t1;
	gettimeofday(&t1, NULL);
	srand(t1.tv_usec * t1.tv_sec);
	return (rand() % max_number);
}