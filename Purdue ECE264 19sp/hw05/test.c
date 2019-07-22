#include <stdio.h>
#include <stdlib.h>
#include "miniunit.h"
#include "three.h"

int test_plus_3() {
    mu_start();
    mu_check(plus_3(1) == 4);  // will FAIL
    mu_end();
}

int test_minus_3() {
    mu_start();
    mu_check(minus_3(1) == -2);
    mu_end();
}
int test_times_3() {
    mu_start();
    mu_check(times_3(1) == 3);
    mu_end();
}
int test_divided_by_3() {
    mu_start();
    mu_check(divided_by_3(1) == 0);  // will FAIL
    mu_end();
}

int main(int argc, char* argv[]) {
    mu_run(test_plus_3)        // will FAIL
    mu_run(test_minus_3)
    mu_run(test_times_3)
    mu_run(test_divided_by_3) // will FAIL
    return EXIT_SUCCESS;
}