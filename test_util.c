#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "example_tests.h"
#include "test_util.h"

//-----------------------------------------------------------------------------
// hex_to_double
//-----------------------------------------------------------------------------
double hex_to_double(char *hex_string) {
    uint64_t hex_num;
    double double_value;

    sscanf(hex_string, "%lx", &hex_num);  // assumes you checked input
    double_value = *((double*)&hex_num);

    return double_value;
}

//-----------------------------------------------------------------------------
// read_reference_file
//-----------------------------------------------------------------------------
int read_reference_file(char *reference_file, reference *reference) {
    char *search = "=";
	char *key;
    char *value;

    if (reference_file == NULL || reference == NULL) {
        return UNINITIALIZED_ARG;
    }

	FILE *file = fopen(reference_file, "r");
	if (file != NULL) {
	    char line[128]; 
	    while (fgets(line, sizeof(line), file) != NULL) {
	        key = strtok(line, search);
	        value = strtok(NULL, search);

            if (strcmp(key, "key_1") == 0) {
                reference->key_1 = hex_to_double(value);
            } else if (strcmp(key, "key_2") == 0) {
                reference->key_2 = hex_to_double(value);
            } else if (strcmp(key, "key_3") == 0) {
                reference->key_3 = hex_to_double(value);
            } else if (strcmp(key, "key_4") == 0) {
                reference->key_4 = hex_to_double(value); 
            } else { // default
                fprintf(stderr, "ERROR: Can't find key: %s.\n", key);
            }
        
	    }

	   fclose(file);
	}

	return SUCCESS;
}

//-----------------------------------------------------------------------------
// check_double
//-----------------------------------------------------------------------------
int are_close_double(double actual, double expected) {
	
    return (fabs(actual - expected) < EPSILON);
}

//-----------------------------------------------------------------------------
// check
//-----------------------------------------------------------------------------
bool check(double actual, double expected, char *desc, bool condition) {
    total_checks++;

    if (!condition) {
        printf("\t[X]: %s, expected %f, actual was %f\n",
            desc, expected, actual);
        return false;
    } else {
        printf("\t[\xE2\x9C\x93]: %s\n", desc);
        return true;
    }
}

//-----------------------------------------------------------------------------
// run_test
//-----------------------------------------------------------------------------
void run_test(bool (*test)(), char *name) {

    if(!test()) {
        printf("[FAILED]: %s\n\n", name);
        failed_tests++;
    } else {
        printf("[PASSED]: %s\n\n", name);
    }

    tests_run++;
}
