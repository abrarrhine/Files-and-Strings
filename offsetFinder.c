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

#include "offsetFinder.h"

/**  Reads a GIS record file (as described in the corresponding project
 *   specification), and determines, for each GIS record contained in that
 *   file, the offset at which that record begins.  The offsets are stored
 *   into an array supplied by the caller.
 * 
 *   Pre:  gisFile is open on a GIS record file
 *         offsets[] is an array large enough to hold the offsets
 *   Post: offsets[] contains the GIS record offsets, in the order
 *            the records occur in the file
 *   Returns:  the number of offsets that were stored in offsets[]
 */
uint32_t findOffsets(FILE* gisFile, uint32_t offsets[]) {
	//printf("inside offset");
	
	char placeholder[501];
	int i = 0; 
	while(fgets(placeholder, 500, gisFile))
	{
		uint32_t j = ftell(gisFile);
		
		if( fgets(placeholder, 2, gisFile)){
		offsets[i] = j;
	
		i++;
		}
		
		
	}
	//printf("Accident Offset");
	
	return i;
}

