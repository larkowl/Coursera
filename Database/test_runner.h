#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <functional>

class TestRunner {
    int fail_count = 0;
public:
    void RunTest(std::function<void()> function, const std::string &test);
    ~TestRunner();
};

template <typename T, typename U>
void AssertEqual(const T& t, const U& u, const std::string& hint);
void Assert(bool b, const std::string& hint);