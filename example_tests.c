#include "example_tests.h"
#include "test_util.h"

//-----------------------------------------------------------------------------
// This is an example library call only! In practice, the test functions
// will call a library that is called through a static or dynamic library.
//-----------------------------------------------------------------------------
void lib_call(double num, double *result) {

  printf("This will not be printed.\n");
  *result = num;
}

//-----------------------------------------------------------------------------
// test_a
//-----------------------------------------------------------------------------
bool test_a() {
    
    double result, result_2;
    QUIET_CALL(lib_call(1.0, &result));
    QUIET_CALL(lib_call(2.0, &result_2));

    bool check_1 = check(result,
                         reference_vals.key_1,
                         "Test Value #1",
                         are_close_double(result, reference_vals.key_1));
    
    bool check_2 = check(result_2,
                         reference_vals.key_2,
                         "Test Value #2",
                         are_close_double(2.0, reference_vals.key_2));

    return check_1 && check_2;
}

//-----------------------------------------------------------------------------
// test_b
//-----------------------------------------------------------------------------
bool test_b() {

    double result;
    QUIET_CALL(lib_call(3.0, &result));

    return check(result,
                 reference_vals.key_3,
                 "Test Value #3",
                 are_close_double(result, reference_vals.key_3));
}

//-----------------------------------------------------------------------------
// test_c
//-----------------------------------------------------------------------------
bool test_c() {

    double result;
    QUIET_CALL(lib_call(4.0, &result));

    return check(result,
                 reference_vals.key_4,
                 "Test Value #4",
                  are_close_double(result, reference_vals.key_4));
}

//-----------------------------------------------------------------------------
// all_tests
//-----------------------------------------------------------------------------
void all_tests() {

    run_test(test_a, "Test A");
    run_test(test_b, "Test B");
    run_test(test_c, "Test C");
}
