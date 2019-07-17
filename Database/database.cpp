#include "database.h"

#include <functional>

void Database::Print(std::ostream& output) const {
    for (const auto& [date, events] : base) {
        for (const auto& event : events) {
            output << date << ' ' << event << std::endl;
        }
    }
}

void Database::Add(const Date &date, const std::string &event) {
    if (unique[date].count(event)) {
        return;
    }
    base[date].push_back(event);
    unique[date].insert(event);
}

int Database::RemoveIf(const std::function<bool(const Date &, const std::string &)> &predicate) {
    std::map<Date, std::vector<std::string>> notRemoved;
    std::map<Date, std::set<std::string>> notRemovedUnique;
    int entries = 0;
    for (const auto& [date, events] : base) {
        for (const auto& event : events) {
            if (predicate(date, event)) {
                entries = entries + 1;
                continue;
            }
            notRemoved[date].emplace_back(event);
            notRemovedUnique[date].insert(event);
        }
    }
    base = notRemoved;
    unique = notRemovedUnique;
    return entries;
}

std::vector<std::string> Database::FindIf(const std::function<bool(const Date& date,
        const std::string& event)>& predicate) const {
    std::vector<std::string> predicates_events;
    for (const auto& [date, events] : base) {
        for (const auto& event : events) {
            if (predicate(date, event)) {
                predicates_events.emplace_back(date.ToString() + ' ' + event);
            }
        }
    }
    return predicates_events;
}

std::string Database::Last(const Date &date_) const {
    auto it = base.upper_bound(date_);
    if (it == base.begin()) {
        return "No entries";
    }
    it = std::prev(it);
    auto [date, events] = *it;
    return date.ToString() + ' ' + *(std::prev(events.end()));

}