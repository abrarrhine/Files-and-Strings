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


#include "recordRetriever.h"
#include <stdlib.h>
#include <string.h>

/**  Returns the GIS record at the given offset.
 * 
 *   Pre:  gisFile is open on a GIS record file
 *         offset is a valid offset for the given GIS record file
 *   Returns:  a valid C-string holding the specified GIS record
 */
char* retrieveRecord(FILE* gisFile, uint32_t offset) {
	//printf("inside retrive");
	
	/***  Complete the implementation of this function  ***/
	// use calloc (I haven't used it yet. Recommendation from TA) 
	char* placeholder = calloc(500, sizeof(char));
	
	
    fseek(gisFile, offset, SEEK_SET);
	fgets(placeholder, 500, gisFile);
	
	char* newCopy = strtok(placeholder, "\n");
	//printf("inside retrive end");
	
	return newCopy;
}
