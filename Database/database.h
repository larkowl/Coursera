#pragma once

#include "date.h"

#include <map>
#include <vector>
#include <set>
#include <functional>

class Database {
    std::map<Date, std::vector<std::string>> base;
    std::map<Date, std::set<std::string>> unique;
public:
    void Add(const Date& date, const std::string& event);
    int RemoveIf(const std::function<bool(const Date& date, const std::string& event)>& predicate);
    std::vector<std::string> FindIf(const std::function<bool(const Date& date, const std::string& event)>& predicate) const;
    std::string Last(const Date& date) const;
    void Print(std::ostream& output = std::cout) const;
};