#include "date.h"

#include <sstream>
#include <iomanip>
#include <tuple>

int Date::GetYear() const {
    return year_;
}

int Date::GetMonth() const {
    return month_;
}

int Date::GetDay() const {
    return day_;
}

Date::Date(const int year, const int month, const int day) : year_(year), month_(month), day_(day) {}
Date::Date() : year_(0), month_(0), day_(0) {}

std::string Date::ToString() const {
    std::ostringstream ss;
    ss << std::setfill('0');
    ss << std::setw(4) << year_ << '-';
    ss << std::setw(2) << month_ << '-';
    ss << std::setw(2) << day_;
    return ss.str();
}

bool operator==(const Date& lhs, const Date& rhs) {
    return lhs.year_ == rhs.year_ && lhs.month_ == rhs.month_ && lhs.day_ == rhs.day_;
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}

bool operator<(const Date& lhs, const Date& rhs) {
    auto lhs_key = std::tie(lhs.year_, lhs.month_, lhs.day_);
    auto rhs_key = std::tie(rhs.year_, rhs.month_, rhs.day_);
    return lhs_key < rhs_key;
}

bool operator>(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs) && lhs != rhs;
}

bool operator>=(const Date& lhs, const Date& rhs) {
    return lhs > rhs || lhs == rhs;
}

bool operator<=(const Date& lhs, const Date& rhs) {
    return lhs < rhs || lhs == rhs;
}

std::istream& operator>>(std::istream& stream, Date& date) {
    std::stringstream ss;
    std::string date_format, check;
    stream >> date_format;
    ss << date_format;
    char first_symbol = ' ', second_symbol = ' ';
    if (ss >> date.year_ >> first_symbol >> date.month_ >> second_symbol >> date.day_) {
        if (ss >> check) {
            throw std::runtime_error("Wrong date format: " + date_format);
        }
        if (!(date.month_ > 0 && date.month_ < 13)) {
            throw std::runtime_error("Month value is invalid: " + std::to_string(date.month_));
        }
        if (!(date.day_ > 0 && date.day_ < 32)) {
            throw std::runtime_error("Day value is invalid: " + std::to_string(date.day_));
        }
    } else {
        throw std::runtime_error("Wrong date format: " + date_format);
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Date& date) {
    stream << date.ToString();
    return stream;
}

Date ParseDate(std::istream& is) {
    Date date;
    std::stringstream ss;
    std::string date_format, check;
    is >> date_format;
    ss << date_format;
    char first_symbol = ' ', second_symbol = ' ';
    if (ss >> date.year_ >> first_symbol >> date.month_ >> second_symbol >> date.day_) {
        if (ss >> check) {
            throw std::runtime_error("Wrong date format: " + date_format);
        }
        if (!(date.month_ > 0 && date.month_ < 13)) {
            throw std::runtime_error("Month value is invalid: " + std::to_string(date.month_));
        }
        if (!(date.day_ > 0 && date.day_ < 32)) {
            throw std::runtime_error("Day value is invalid: " + std::to_string(date.day_));
        }
    } else {
        throw std::runtime_error("Wrong date format: " + date_format);
    }
    return date;
}
