#ifndef DATASELECTOR_H
#define DATASELECTOR_H
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

/***  DO NOT MODIFY THIS FILE IN ANY WAY!! ***/

/**  Data type used in persistent list of GIS records.
 */
struct _RecordEntry {
	uint32_t offset;
	char*    record;
	bool     selected;
};
typedef struct _RecordEntry RecordEntry;

/**  Builds private durable list of struct variables representing the GIS records
 *   stored in the given GIS record file.
 * 
 *   Pre:  fp is open on a file of GIS records, as described in the specification
 */
uint32_t loadRecords(FILE* fp);

/**  Compare student's found offsets to those recorded by loadRecords().
 * 
 *   Pre:  loadRecords() has been called
 *         offsets[] has been populated by call to student's findOffsets()
 *         fp is open on the log file
 *   Returns:  number of offsets that were reported correctly 
 */
uint32_t checkFoundOffsets(const uint32_t offsets[], uint32_t nCases, FILE* fp);

/**  Chooses an unused GIS record, from the previously-constructed durable list,
 *   to be used in testing the student's createStringBundle() function.
 * 
 *   Pre:  user has called loadRecords() to build a list of available GIS records
 *   Post: an unused record has been selected, and marked as used
 *   Returns:  offset of the chosen GIS record; 
 *             if no unused record is available, returns 0
 */
uint32_t selectRecordOffset();

/**  Compares record retrieved by student's retrieveRecord() to correct record from
 *   the GIS record file.
 * 
 *   Pre:  gisFile is open on the GIS record file
 *         foundRecord is the C-string retrieved by the student's function
 *         targetOffset is the offset from the record should have been retrieved
 *   Returns:  true iff the retrieved record matches the correct record
 */
bool checkRetrievedRecord(FILE* gisFile, char* foundRecord, uint32_t targetOffset, FILE* logFile);

/**  Chooses an unused GIS record, from the previously-constructed durable list,
 *   to be used in testing the student's createStringBundle() function.
 * 
 *   Pre:  user has called loadRecords() to build a list of available GIS records
 *   Post: an unused record has been selected, and marked as used
 *   Returns:  pointer to a C-string holding the record data, as stored in the
 *             given GIS file; if no unused record is available, returns NULL
 */
char* selectParsingTestCase();

/**  Frees all dynamically-allocated memory related to the list of GIS records
 *   that was created by a previous call to loadRecords().
 */
void clearRecords();

#endif
