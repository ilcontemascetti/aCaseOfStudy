/* Microprocessors Based Design
 * Calin Cruceru <calin.cruceru@stud.acs.upb.ro>, 335CB
 *
 * Defines macros for error handling.
 */

#ifndef ERROR_HANDLING_H_
#define ERROR_HANDLING_H_ 1

#include <stdio.h>
#include <stdlib.h>

#if defined(_WIN32)

#include <windows.h>
#define MAX_ERR_BUF_LEN 1024

static VOID PrintLastError(const PCHAR message)
{
	CHAR errBuff[MAX_ERR_BUF_LEN];

	FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_MAX_WIDTH_MASK,
		NULL,
		GetLastError(),
		0,
		errBuff,
		sizeof(errBuff) - 1,
		NULL
	);

	fprintf(stderr, "%s: %s\n", message, errBuff);
}

#define ERR(call_description) \
	do { \
		fprintf(stderr, "(%s, %d): ", \
				__FILE__, __LINE__); \
		PrintLastError(call_description); \
	} while (0)

#elif defined(__linux__)

/* error printing macro */
#define ERR(call_description) \
	do { \
		fprintf(stderr, "(%s, %d): ", \
				__FILE__, __LINE__); \
		perror(call_description); \
	} while (0)

#else
#error "Unknown platform"
#endif

/* print error (call ERR) and exit */
#define DIE(assertion, call_description) \
	do { \
		if (assertion) { \
			ERR(call_description); \
			exit(EXIT_FAILURE); \
		} \
	} while (0)

/* surpress 'argument unused' warnings */
#define UNUSED(a) ((void)&a)

#endif /* ERROR_HANDLING_H_ */

