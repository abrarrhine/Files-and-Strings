#ifndef STRINGBUNDLE_H
#define STRINGBUNDLE_H

/***  IF YOU NEED ADDITIONAL INCLUDE DIRECTIVES, PUT THEM ***/
/***          IN STRINGBUNDLE.C, NOT HERE!!               ***/
#include <stdio.h>
#include <inttypes.h>

/***  DO NOT MODIFY THIS FILE IN ANY WAY!! ***/

#define MAX_TOKENS       20
#define MAX_FIELDLENGTH 100

/**  A StringBundle contains an array of nTokens pointers to properly-
 *   terminated C strings (char arrays).
 * 
 *   A StringBundle is said to be proper iff:
 *     - Tokens == NULL and nTokens == 0
 *   or
 *     - nTokens > 0 and Tokens points to an array of nTokens char pointers,
 *     - each char pointer points to a char array of minimum size to hold
 *       its string, including the terminator (no wasted space)
 */
struct _StringBundle {
   char**   Tokens;    // pointer to dynamically-allocated array of char*
   uint32_t nTokens;   // dimension of array pointed to by Tokens
};
typedef struct _StringBundle StringBundle;


/**  Parses *str and creates a new StringBundle object containing the
 *   separate fields of *str.
 * 
 *   Pre:     str points to a GIS record string, properly terminated
 * 
 *   Returns: a pointer to a new proper StringBundle object
 */
StringBundle* createStringBundle(const char* const str);


/**  Frees all the dynamic memory content of a StringBundle object.
 *   The StringBundle object that sb points to is NOT deallocated here,
 *   because we don't know whether that object was allocated dynamically.
 * 
 *   Pre:     *sb is a proper StringBundle object
 * 
 *   Post:    all the dynamic memory involved in *sb has been freed;
 *            *sb is proper
 */
void clearStringBundle(StringBundle* sb);


/**  Prints a human-friendly display of the contents of a StringBuffer
 *   object to the supplied output stream.
 * 
 *   Pre:  *sb is a proper StringBundle object
 *         fp is open on an output file
 */
void printStringBundle(FILE* fp, const StringBundle* const sb);

#endif
