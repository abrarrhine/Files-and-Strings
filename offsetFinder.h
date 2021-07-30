#ifndef OFFSETFINDER_H
#define OFFSETFINDER_H

/***  IF YOU NEED ADDITIONAL INCLUDE DIRECTIVES, PUT THEM ***/
/***          IN STRINGBUNDLE.C, NOT HERE!!               ***/
#include <stdio.h>
#include <inttypes.h>

/***  DO NOT MODIFY THIS FILE IN ANY WAY!! ***/

#define MAXLINELENGTH 500

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
uint32_t findOffsets(FILE* gisFile, uint32_t offsets[]);

#endif
