#include "test_runner.h"

#include <vector>
#include <string>
#include <functional>

void TestRunner::RunTest(const std::function<void()> function, const std::string &test) {
    try {
        function();
        std::cerr << test << " OK" << std::endl;
    }
    catch (std::runtime_error& ex) {
        ++fail_count;
        std::cerr << test << " fail: " << ex.what() << std::endl;
    }
    catch (std::exception& ex) {
        ++fail_count;
        std::cerr << "Unknown exception caught" << std::endl;
    }
}

TestRunner::~TestRunner() {
    if (fail_count > 0) {
        std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
        exit(1);
    }
}