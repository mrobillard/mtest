#ifndef TEST_UTIL_H__
#define TEST_UTIL_H__

#include <stdbool.h>
#include <stdio.h>

/*
 * Return codes.
 */
#define SUCCESS (0)
#define UNINITIALIZED_ARG (1)
#define FAIL (2)
#define IO_ERROR (4)

/*
 * Epsilon. Used as the max relative difference when comparing two floating
 * point values. 
 */
#define EPSILON (0.00000001)

/*
 * Silence stdout from any function call. Useful for third party
 * function calls. 
 */
#define QUIET_CALL(noisy) { \
    FILE* tmp = stdout;\
    stdout = tmpfile();\
    (noisy);\
    fclose(stdout);\
    stdout = tmp;\
}

/*
 * Reference structure for tests.
 */
struct reference {
	
	double key_1;
	double key_2;
	double key_3;
	double key_4;

} typedef reference;

/*
 * Read reference file and populates the internal reference structure, where
 * each key/value pair in the reference file corresponds to each member in
 * the reference structure. 
 * 
 * Note: this expects an initialized reference structure. 
 */
int read_reference_file(char *reference_file, reference *reference);

/*
 * Converts a hex string to a double. 
 *
 * Note: this does not validate the hex value. 
 */
double hex_to_double(char *hex_value);

/*
 * Checks to see if two double precision values are close within an 
 * excepted range. 
 *
 * Note: if magnitude difference is unknown, use DBL_EPSILON for 
 *       epsilon. 
 */
int are_close_double(double actual, double expected);

/*
 * Checks whether test returns a non-zero value. If not, the message with 
 * error description is returned.  
 */
bool check(double actual, double expected, char *desc, bool condition);

/*
 * Runs a single test. 
 */
void run_test(bool (*test)(), char *name);

/*
 * Globals to keep track of total tests run. 
 */
extern int tests_run;
extern int failed_tests;
extern int total_checks;

/*
 * Global reference values.
 */
extern reference reference_vals;

#endif // TEST_UTIL_H__
