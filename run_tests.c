#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>

#include "example_tests.h"
#include "test_util.h"

//
// Initialize global variables 
//
int tests_run = 0;
int failed_tests = 0;
int total_checks = 0;
reference reference_vals;

static void print_help(const char *argv0) {
    fprintf(stderr, "\n");
    fprintf(stderr, "Mtest micro testing framework.\n\n");
    fprintf(stderr, "The tests use a reference file (reference.dat) to read\n");
    fprintf(stderr, "in values. If you want to update those numbers, you can\n");
    fprintf(stderr, "provide new reference numbers with the -u option.\n\n");
    fprintf(stderr, "Usage: %s [-u filename]\n", argv0);
    
    exit(FAIL);
}

static void print_usage(const char *argv0) {
    fprintf(stderr, "Usage: %s [-u filename]\n", argv0);

    exit(FAIL);
}

void test_runner(void (*all_tests)()) {

    printf("Running Tests...\n\n");

    // run tests
    all_tests();

    // print summary 
    if (failed_tests != 0) {
        if (failed_tests == 1) {
            printf("%d test failed.\n", failed_tests);
        } else {
            printf("%d tests failed.\n", failed_tests);
        }
    }
    else {
        printf("ALL TESTS PASSED.\n");
    }
    printf("%d tests run, %d checks.\n", tests_run, total_checks);

}

int main(int argc, char **argv) {
    
    int c;
    while((c = getopt(argc, argv, "hu:")) != -1) {
        switch(c) {
            case 'u':
                read_reference_file(argv[2], &reference_vals);
                test_runner(all_tests);
                break;
            case 'h':
                print_help(argv[0]);
                break;
            case '?':
                if (optopt == 'u') {
                    fprintf(stderr, "Option -%c requires a reference file as an argument.\n\n", optopt);
                    print_usage(argv[0]);
                } else if (isprint (optopt)) {
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                    print_usage(argv[0]);
                } else {
                    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                    print_usage(argv[0]);

                }
                return -1;
            default: 
                print_help(argv[0]);
        }
    }

    //
    // No arguments 
    //
    if ((argc == 1) && (c == (-1))) { 

        read_reference_file("./reference.dat", &reference_vals);
        test_runner(all_tests);
    } 

}
