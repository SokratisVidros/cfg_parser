/**
 * trimmer.c
 *
 * @package	 : 
 * @author	 : Vidros Sokratis <sokratis.vidros@gmail.com>
 * @date	 : 29-12-2011 
 * @copyright	 : Copyright (c) 2011 Vidros Sokratis
 * @version	 : 1.0
 * @description : Character eliminator
 * @tribute	 : http://www.daniweb.com/software-development/c/threads/15538
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE    1
#define FALSE   0


/*
 * Remove given characters form string
 */

char * remove_chars( char *src, char *key ) {

   char * dest;
   size_t len_src, len_key;
   int found, i, j, k;

   i = 0;
   j = 0;
   k = 0;
   len_src = 0;
   len_key = 0;
   dest = NULL;

   len_src = strlen( src );
   len_key = strlen( key );

   /*
   	* Allocate memory for the destination and initialise it
    */
   dest = (char *) malloc( sizeof( char ) * len_src + 1 );
   if ( NULL == dest ) {
      fprintf(stderr,"ERROR: Unable to allocate memory!\n");
   }

   memset( dest, 0x00, sizeof( char ) * len_src + 1 );

   /*
    * For each character in the source, we check against the key.
    * We use the 'found' boolean to evaluate whether we need to copy or not.
    */
   for ( i = 0; i < len_src; i++ ) {
      found = FALSE;
      for ( j = 0; j < len_key; j++ ) {
         if ( src[i] == key[j] )
            found = TRUE;
      }

      /*
       * Copy the character if it was not found in the key
       */
      if ( FALSE == found ) {
         dest[k] = src[i];
         k++;
      }
   }
   return dest;
}
