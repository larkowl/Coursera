#pragma once

#include <iostream>
#include <sstream>

class Date {
    int year_;
    int month_;
    int day_;
public:
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    Date(int year, int month, int day);
    Date();
    std::string ToString() const;

    friend bool operator==(const Date& lhs, const Date& rhs);
    friend bool operator!=(const Date& lhs, const Date& rhs);
    friend bool operator<(const Date& lhs, const Date& rhs);
    friend bool operator>(const Date& lhs, const Date& rhs);
    friend bool operator>=(const Date& lhs, const Date& rhs);
    friend bool operator<=(const Date& lhs, const Date& rhs);
    friend std::istream& operator>>(std::istream& stream, Date& date);
    friend std::ostream& operator<<(std::ostream& stream, const Date& date);
    friend Date ParseDate(std::istream& is);
};

Date ParseDate(std::istream& is);