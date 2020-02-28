# mtest

A micro testing framework for C

## Usage 

This framework is intended to be used as a lightweight, integrated framework when using 
an external library is unecessary or not feasible. 

### Writing Tests

Tests should be functions that return a boolean value for the result. 

```c

bool test() {
    result = // library call
    return check(result,
                 reference_vals.result,
                 "test description",
                 /*assertion*/);
}

```

Your tests should be wrapped in a single function called `all_tests()`. Each test should be
passed as a parameter to the run test function:

```c
void all_tests() {
    run_test(test_a);
    run_test(test_b);
}

```

The `all_tests()` function should be included in the `run_tests.c` file.

### Reference Values 

For numerical tests, sometimes you want to change the data passed to the functions and 
the corresponding values. To make switching datasets easy, you can pass the tests a 
list of reference values. Reference values should be in double precision hexadecimal and
listed like:

```
key=value
```

## License 

[MIT](LICENSE)