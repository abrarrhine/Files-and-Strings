#ifndef RECORDRETRIEVER_H
#define RECORDRETRIEVER_H

/***  IF YOU NEED ADDITIONAL INCLUDE DIRECTIVES, PUT THEM ***/
/***          IN STRINGBUNDLE.C, NOT HERE!!               ***/
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

/***  DO NOT MODIFY THIS FILE IN ANY WAY!! ***/

#define MAXRECORDLENGTH  500

/**  Returns the GIS record at the given offset.
 * 
 *   Pre:  gisFile is open on a GIS record file
 *         offset is a valid offset for the given GIS record file
 *   Returns:  a valid C-string holding the specified GIS record
 */
char* retrieveRecord(FILE* gisFile, uint32_t offset);

#endif
