/**  Test driver for StringBundle project.
 *   CS 2505 Spring 2021
 * 
 *   Invocation:  c04driver <name of GIS record file> <name of logFile file> [-repeat]
 * 
 *   Only use -repeat if you have previously run the program without the switch,
 *   and want to test again with the same selection of data records.
 * 
 *   You can modify the number of test cases used by editing the initializations of 
 *   some variables (like nOffsetCases) below.  In early testing, you may find it useful
 *   to set those variables to 1 so you can focus on a single case (using -repeat as
 *   described above).
 * 
 *   You might even want to comment out parts of main() to focus on testing a single
 *   phase.
 * 
 *   You can modify this file, but be aware that the final grading will be done with
 *   the original version of this test driver.
 */

#include <stdio.h>       // for general I/O functionality
#include <stdlib.h>      // for memory allocation and other functionality
#include <inttypes.h>    // for exact-width integer types
#include <string.h>      // for C-string functionality
#include <stdbool.h>     // for Boolean variables
#include <time.h>        // used in random data generation

#include "dataSelector.h"
#include "checkStringBundle.h"

#include "offsetFinder.h"
#include "recordRetriever.h"

#include "StringBundle.h"

#define MAXNAMELENGTH 100

static char* copyOf(const char* const str);

int main(int argc, char** argv) {
	
	//printf("main function"); 
	
    // Check for correct number of parameters (must be 3 or 4); if more than 4 are supplied,
    // the extra one(s) will simply be ignored.
	if ( argc < 3 ) {
		printf("Error: gisFile file not specified.\n");
		printf("Invocation: c04driver <name of GIS record file> <name of logFile file> [-repeat]\n");
		exit(1);
	}

    // Try to open the gisFile file:
	FILE* gisFile  = fopen(argv[1], "r");
    // If the gisFile file cannot be opened, exit with an appropriate error message:
	if ( gisFile == NULL ) {
		printf("GIS record file %s was not found.\n", argv[1]);
		exit(2);
	}
	
    // Generate a new random seed value unless -repeat is specified.  If -repeat
    // IS specified but no seed file is found, exit with an error message:
	uint32_t seed;
	if ( argc == 4 && strcmp(argv[3], "-repeat") == 0 ) {
		FILE* fp = fopen("seed.txt", "r");
		if ( fp == NULL ) {
			printf("Could not open seed file.\n");
			printf("You must first run this program without the switch -repeat.\n");
         fclose(gisFile);
			exit(3);
		}
		fscanf(fp, "%"PRIu32, &seed);
		fclose(fp);
	}
	else {
		seed = (uint32_t) time( NULL );
		FILE* fp = fopen("seed.txt", "w");
		fprintf(fp, "%"PRIu32"\n", seed);
		fclose(fp);
	}
	srand(seed);
	
	// Load GIS records from file
	uint32_t nRecords = loadRecords(gisFile);

    // Try to create logFile file:
	FILE*	logFile = fopen(argv[2], "w");
    // If the logFile file could not be created (very unlikely), exit with an
    // error message.
    if ( logFile == NULL ) {
		fprintf(logFile, "Output file %s could not be created.\n", argv[2]);
        fclose(gisFile);
		exit(4);
    }
	
	////////////////////////////////////////////////////////////////////////////////////  Test offset finding
	uint32_t nOffsetCases = 8;       // Any logic errors here are likely to show up right away.
	                                  
	//  Create array to hold offsets found by findOffsets()
	uint32_t* offsets = calloc(nRecords, sizeof(uint32_t));
	
	//  Call student fn to compute offsets; if student code does not halt correctly
	//  at end of gisFile file, this could cause a segfault
	fprintf(logFile, "Phase 1:  Testing ability to find GIS record offsets.");
	fprintf(logFile, "Calling findOffsets()...\n");
	uint32_t nOffsetsReported = findOffsets(gisFile, offsets);
	
	//  Check reported number of offsets found; there should be one for each of the
	//  GIS records in the file.
    if ( nOffsetsReported != nRecords ) {
        fprintf(logFile, "   Error:  reported %d offsets, should have been %d\n", nOffsetsReported, nRecords);
    	fprintf(logFile, "\n");
        fprintf(logFile, "   1 >> score for offset count:   0 / 20\n");
    }
    else {
		fprintf(logFile, "   Correct: reported %d offsets\n", nOffsetsReported);
    	fprintf(logFile, "\n");
        fprintf(logFile, "   1 >> score for offset count:  20 / 20\n");
	}
	fprintf(logFile, "\n");
	
	//  Check the first few reported offsets
	fprintf(logFile, "Checking the first %d reported offsets...\n", nOffsetCases);
	uint32_t nCorrectOffsets = checkFoundOffsets(offsets, nOffsetCases, logFile);
	fprintf(logFile, "\n");
	fprintf(logFile, "   2 >> score for found offsets:  %2d / %d\n", 10 * nCorrectOffsets, 10 * nOffsetCases);
	fprintf(logFile, "\n");
	//  Free array of found offsets
	free( offsets );
	
	//  Rewind GIS record file stream for parsing tests
	rewind(gisFile);
	
	////////////////////////////////////////////////////////////////////////////////////  Test record retrievals
	uint32_t nRetrievalCases = 5;
	
	fprintf(logFile, "Phase 2:  Testing ability to retrieve GIS records given record offsets.\n");

    uint32_t nMatches = 0;
    for (uint32_t idx = 1; idx <= nRetrievalCases; idx++) {
		
		uint32_t targetOffset = selectRecordOffset();        // get offset for random GIS record
		
		char* foundRecord = retrieveRecord(gisFile, targetOffset);   // try to retrieve matching record
		
		if ( checkRetrievedRecord(gisFile, foundRecord, targetOffset, logFile) ) {  // see if record does match
			nMatches++;
		}
		
		free(foundRecord);    // deallocate array created by retrieveRecord()
	}
	fprintf(logFile, "   3 >> score for retrieved records:  %2d / %d\n", 20 * nMatches, 20 * nRetrievalCases);
	fprintf(logFile, "\n");
	
	
	////////////////////////////////////////////////////////////////////////////////////  Test record parsing
	uint32_t nParseCases = 10;
    uint32_t parseScore = 0;
    
	for (uint32_t idx = 1; idx <= nParseCases; idx++) {
		
		char* pRecord = selectParsingTestCase();  // Get a random test case.
      
        // Copy the string so the parsing code cannot mess up the original:
		char* pCopy = copyOf(pRecord);     
		
        // Call the student's soln to parse the selected string:
		StringBundle* currBundle = createStringBundle(pRecord);
		
        // Echo the test string and the student's parse of it to the logFile file:
		fprintf(logFile, "Results for test case %"PRIu32" follow:\n\n", idx);
		fprintf(logFile, "  Test string: %s\n\n", pRecord);
		fprintf(logFile, "  Student's string bundle:\n");
		printStringBundle(logFile, currBundle);
		fprintf(logFile, "\n");
		
        // Compare the student's parse to the reference parse of the string:
		uint32_t testScore = checkStringBundle(logFile, currBundle, pCopy);
      
        // Deallocate memory "internal" to the student's StringBundle, using the
        // student's deallocation function (which may be incorrect):
		clearStringBundle(currBundle);
      
        // Deallocate the student's StringBundle object:
		free(currBundle);
      
        // Deallocate the copy of the test string:
	  	free(pCopy);
		
		parseScore += testScore;
		
        // Log the score for this test case:
		fprintf(logFile, "   score for this test: %2"PRIu32" / %"PRIu32"\n", 
		        testScore, MAX_TOKENS);
		
		fprintf(logFile, "--------------------------------------------------\n");
	}
	
     // Log the total parsing score:
	fprintf(logFile, "\n");
	fprintf(logFile, "   4 >> total score for GIS record parsing: %"PRIu32" / %"PRIu32"\n", parseScore, MAX_TOKENS * nParseCases);

	// Free records created by loadRecords():
	clearRecords();
	
	// Close the gisFile and logFile files:
	fclose(gisFile);
	fclose(logFile);
	
	return 0;
}

/**  Here's a freebie, use it as you wish:
 * 
 *   Makes a dynamically-allocated copy of a given C-string.  The new
 *   string is of minimum length to hold the contents of the original
 *   string.
 * 
 *   Pre:
 *      str points to a proper C-string, or is NULL
 * 
 *   Returns:
 *      pointer to a dynamically-allocated C-string holding the
 *      characters in *str; returns an empty string if str == NULL.
 */
static char* copyOf(const char* const str) {
	
	char* cpy;
   // If you give me a NULL pointer, I'll make an empty string instead...
	if ( str == NULL ) {
		cpy = calloc(1, sizeof(char));
		return cpy;
	}
	
   // Otherwise, make an appropriate array to hold a copy:
	cpy = calloc(sizeof(char), strlen(str) + 1);
   
   // Then, use the Standard Library to copy the contents:
	strcpy(cpy, str);
	return cpy;
}
