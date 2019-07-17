#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <sstream>

std::string ParseEvent(std::istream& is);
void TestAll();

int main() {
    TestAll();

    Database db;

    for (std::string line; getline(std::cin, line); ) {
        std::istringstream is(line);

        std::string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print();
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const std::string& event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            std::cout << "Removed " << count << " entries" << std::endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const std::string& event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                std::cout << entry << std::endl;
            }
            std::cout << "Found " << entries.size() << " entries" << std::endl;
        } else if (command == "Last") {
            try {
                std::cout << db.Last(ParseDate(is)) << std::endl;
            } catch (std::invalid_argument&) {
                std::cout << "No entries" << std::endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw std::logic_error("Unknown command: " + command);
        }
    }

    return 0;
}

std::ostream& operator<<(std::ostream& out, const std::vector<std::string> vect) {
    for (const auto& str : vect) {
        out << str << " ";
    }
    return out;
}

template <typename T, typename U>
void AssertEqual(const T& t, const U& u, const std::string& hint) {
    if (t != u) {
        std::stringstream ss;
        ss << "Assertion failed: " << t << "!=" << u << std::endl;
        if (!hint.empty()) {
            ss << "hint: " << hint << std::endl;
        }
        throw std::runtime_error(ss.str());
    }
}

void Assert(bool b, const std::string& hint) {
    AssertEqual(b, true, hint);
}

std::string ParseEvent(std::istream& is) {
    std::string test, event;
    std::getline(is, test);
    int index = 0;
    while (index < test.size() && test[index] == ' ') {
        index = index + 1;
    }
    event = std::string(test.begin() + index, test.end());
    return event;
}

void TestParseEvent() {
    {
        std::istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        std::istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        std::istringstream is("  first event  \n  second event");
        std::vector<std::string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, std::vector<std::string>{"first event  ", "second event"}, "Parse multiple events");
    }
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
}
