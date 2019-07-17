#pragma once

#include <memory>
#include "date.h"

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    Or,
    And
};

class Node {
public:
    virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};

class EmptyNode : public Node {
    bool Evaluate(const Date& date, const std::string& event) const override;
};

class DateComparisonNode : public Node {
    const Date date_;
    const Comparison comparison_;
public:
    DateComparisonNode(Comparison comparison, const Date& date);
    bool Evaluate(const Date& date, const std::string& event) const override;
};

class EventComparisonNode : public Node {
    const std::string event_;
    const Comparison comparison_;
public:
    EventComparisonNode(Comparison comparison, const std::string& event);
    bool Evaluate(const Date& date, const std::string& event) const override;
};

class LogicalOperationNode : public Node {
    const std::shared_ptr<Node> left_;
    const std::shared_ptr<Node> right_;
    const LogicalOperation operation_;

public:
    LogicalOperationNode(LogicalOperation operation,
            std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    bool Evaluate(const Date& date, const std::string& event) const override;
};