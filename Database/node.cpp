#include "node.h"

DateComparisonNode::DateComparisonNode(const Comparison comparison, const Date &date) :
comparison_(comparison), date_(date) {}

EventComparisonNode::EventComparisonNode(const Comparison comparison, const std::string &event) :
comparison_(comparison), event_(event) {}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation operation, const std::shared_ptr<Node> left,
        const std::shared_ptr<Node> right) :
        operation_(operation), left_(left), right_(right) {}

bool DateComparisonNode::Evaluate(const Date &date, const std::string &event) const {
    if (comparison_ == Comparison::Equal) {
        return date == date_;
    } else if (comparison_ == Comparison::Greater) {
        return date > date_;
    } else if (comparison_ == Comparison::GreaterOrEqual) {
        return date >= date_;
    } else if (comparison_ == Comparison::NotEqual) {
        return date != date_;
    } else if (comparison_ == Comparison::Less) {
        return date < date_;
    } else {
        return date <= date_;
    }
}

bool EventComparisonNode::Evaluate(const Date &date, const std::string &event) const {
    if (comparison_ == Comparison::Equal) {
        return event == event_;
    } else if (comparison_ == Comparison::Greater) {
        return event > event_;
    } else if (comparison_ == Comparison::GreaterOrEqual) {
        return event >= event_;
    } else if (comparison_ == Comparison::NotEqual) {
        return event != event_;
    } else if (comparison_ == Comparison::Less) {
        return event < event_;
    } else {
        return event <= event_;
    }
}

bool LogicalOperationNode::Evaluate(const Date &date, const std::string &event) const {
    if (operation_ == LogicalOperation::Or) {
        return left_->Evaluate(date, event) || right_->Evaluate(date, event);
    } else {
        return left_->Evaluate(date, event) && right_->Evaluate(date, event);
    }
}

bool EmptyNode::Evaluate(const Date &date, const std::string &event) const {
    return true;
}