#include "example_tests.h"
#include "test_util.h"

//-----------------------------------------------------------------------------
// This is an example library call only! In practice, the test functions
// will call a library that is called through a static or dynamic library.
//-----------------------------------------------------------------------------
double lib_call() {
  return 1.0;
}

//-----------------------------------------------------------------------------
// test_a
//-----------------------------------------------------------------------------
bool test_a() {
    
    QUIET_CALL(lib_call());
    
    bool check_1 = true;
    bool check_2 = true;
    bool check_3 = true;

    return check_1 && check_2 && check_3;

}

//-----------------------------------------------------------------------------
// all_tests
//-----------------------------------------------------------------------------
void all_tests() {

    run_test(test_a, "Test A");
}
