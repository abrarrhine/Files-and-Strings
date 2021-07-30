// On my honor:
//
// - I have not discussed the C language code in my program with
// anyone other than my instructor or the teaching assistants 
// assigned to this course.
//
// - I have not used C language code obtained from another student, 
// the Internet, or any other unauthorized source, either modified
// or unmodified. 
//
// - If any C language code or documentation used in my program 
// was obtained from an authorized source, such as a text book or
// course notes, that has been clearly noted with a proper citation
// in the comments of my program.
//
// - I have not designed this program in such a way as to defeat or
// interfere with the normal operation of the Curator System.
//
// <Abrar Islam>
// <abrarr18>

#include "StringBundle.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_FIELDS 20
#define FIELD_GUESS 200

/***  Declare your static helper functions here  ***/
static char* nextF(const char* const pChar){

	static char *pos = NULL, *field = NULL;

	if(pChar != NULL){
		pos = pChar;
	} 

	field = calloc(FIELD_GUESS + 1, sizeof(*field)); 

	int n, read = sscanf(pos, "%[^|]%n", field, &n);

	if(read == 1){
		pos += n;
	}
	if(*pos == '|'){
		++pos;
	}

	return field;
}

/**  Parses *str and creates a new StringBundle object containing the
 *   separate fields of *str.
 * 
 *   Pre:     str points to a GIS record string, properly terminated
 * 
 *   Returns: a pointer to a new proper StringBundle object
 */
 /**
StringBundle* createStringBundle(const char* const str) {
		
	uint32_t i = 0;
	StringBundle* result = malloc(sizeof(StringBundle));
	result->Tokens = calloc(NUM_FIELDS, sizeof(char*));
	result->nTokens = 0;

	result->Tokens[i] = nextF(str);

	for(i = 1; i < NUM_FIELDS; i++){

		result->Tokens[i] = nextF(NULL);
			
		if(result->Tokens[i] != NULL){
			result->nTokens++;
		}
		
	}

	return result;
}
**/
StringBundle* createStringBundle(const char* const str) {
		
	uint32_t i = 0;
	StringBundle* result = malloc(sizeof(StringBundle));
	result->Tokens = calloc(NUM_FIELDS, sizeof(char*));
	result->nTokens = 0;

	result->Tokens[i] = nextF(str);

	for(i = 1; i < NUM_FIELDS; i++){

		result->Tokens[i] = nextF(NULL);
			
		if(result->Tokens[i] != NULL){
			result->nTokens++;
		}
		
	}

	return result;
}
 

/**  Frees all the dynamic memory content of a StringBundle object.
 *   The StringBundle object that sb points to is NOT deallocated here,
 *   because we don't know whether that object was allocated dynamically.
 * 
 *   Pre:     *sb is a proper StringBundle object
 * 
 *   Post:    all the dynamic memory involved in *sb has been freed;
 *            *sb is proper
 */
void clearStringBundle(StringBundle* sb) {
		int i = 0;
		while(i < NUM_FIELDS){
			free(sb->Tokens[i]);
			i++;
		}
		free(sb->Tokens);
}

/**  Prints a human-friendly display of the contents of a StringBuffer
 *   object to the supplied output stream.
 * 
 *   Pre:  *sb is a proper StringBundle object
 *         fp is open on an output file
 */
void printStringBundle(FILE* fp, const StringBundle* const sb) {
	
	//fprintf(fp, "There are %"PRIu32" tokens:\n", sb->nTokens);
	
	for (uint32_t idx = 0; idx < sb->nTokens; idx++) {
		fprintf(fp, "   %3"PRIu32":  [%s]\n", idx, sb->Tokens[idx]);
	}
}
