/*
 * Copyright (C) 2023 Dominik Drexler and Simon Stahlberg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "../../../include/loki/domain/pddl/conditions.hpp"

#include "../../../include/loki/domain/pddl/literal.hpp"
#include "../../../include/loki/common/hash.hpp"
#include "../../../include/loki/common/collections.hpp"
#include "../../../include/loki/common/pddl/visitors.hpp"


namespace loki::pddl {

/* Literal */
ConditionLiteralImpl::ConditionLiteralImpl(int identifier, Literal literal)
    : Base(identifier)
    , m_literal(std::move(literal)) { }

bool ConditionLiteralImpl::are_equal_impl(const ConditionLiteralImpl& other) const {
    if (this != &other) {
        return m_literal == other.m_literal;
    }
    return true;
}

size_t ConditionLiteralImpl::hash_impl() const {
    return std::hash<Literal>()(m_literal);
}

void ConditionLiteralImpl::str_impl(std::ostringstream& out, const FormattingOptions& /*options*/) const {
    out << *m_literal;
}

const Literal& ConditionLiteralImpl::get_literal() const {
    return m_literal;
}


/* And */
ConditionAndImpl::ConditionAndImpl(int identifier, ConditionList conditions)
    : Base(identifier)
    , m_conditions(std::move(conditions)) { }

bool ConditionAndImpl::are_equal_impl(const ConditionAndImpl& other) const {
    if (this != &other) {
        return get_sorted_vector(m_conditions) == get_sorted_vector(other.m_conditions);
    }
    return true;
}

size_t ConditionAndImpl::hash_impl() const {
    return hash_vector(get_sorted_vector(m_conditions));
}

void ConditionAndImpl::str_impl(std::ostringstream& out, const FormattingOptions& /*options*/) const {
    out << "(and ";
    for (size_t i = 0; i < m_conditions.size(); ++i) {
        if (i != 0) out << " ";
        std::visit(StringifyVisitor(out), *m_conditions[i]);
    }
    out << ")";
}

const ConditionList& ConditionAndImpl::get_conditions() const {
    return m_conditions;
}


/* Or */
ConditionOrImpl::ConditionOrImpl(int identifier, ConditionList conditions)
    : Base(identifier)
    , m_conditions(std::move(conditions)) { }

bool ConditionOrImpl::are_equal_impl(const ConditionOrImpl& other) const {
    if (this != &other) {
        return get_sorted_vector(m_conditions) == get_sorted_vector(other.m_conditions);
    }
    return true;
}

size_t ConditionOrImpl::hash_impl() const {
    return hash_vector(get_sorted_vector(m_conditions));
}

void ConditionOrImpl::str_impl(std::ostringstream& out, const FormattingOptions& /*options*/) const {
    out << "(or ";
    for (size_t i = 0; i < m_conditions.size(); ++i) {
        if (i != 0) out << " ";
        std::visit(StringifyVisitor(out), *m_conditions[i]);
    }
    out << ")";
}

const ConditionList& ConditionOrImpl::get_conditions() const {
    return m_conditions;
}


/* Not */
ConditionNotImpl::ConditionNotImpl(int identifier, Condition condition)
    : Base(identifier)
    , m_condition(std::move(condition)) { }

bool ConditionNotImpl::are_equal_impl(const ConditionNotImpl& other) const {
    if (this != &other) {
        return m_condition == other.m_condition;
    }
    return true;
}

size_t ConditionNotImpl::hash_impl() const {
    return hash_combine(m_condition);
}

void ConditionNotImpl::str_impl(std::ostringstream& out, const FormattingOptions& /*options*/) const {
    out << "(not ";
    std::visit(StringifyVisitor(out), *m_condition);
    out << ")";
}

const Condition& ConditionNotImpl::get_condition() const {
    return m_condition;
}

}

namespace std {
    bool less<loki::pddl::Condition>::operator()(
        const loki::pddl::Condition& left_condition,
        const loki::pddl::Condition& right_condition) const {
        return std::visit(loki::pddl::LessComparatorVisitor(), *left_condition, *right_condition);
    }

    std::size_t hash<loki::pddl::ConditionLiteralImpl>::operator()(const loki::pddl::ConditionLiteralImpl& condition) const {
        return condition.hash_impl();
    }

    std::size_t hash<loki::pddl::ConditionAndImpl>::operator()(const loki::pddl::ConditionAndImpl& condition) const {
        return condition.hash_impl();
    }

    std::size_t hash<loki::pddl::ConditionOrImpl>::operator()(const loki::pddl::ConditionOrImpl& condition) const {
        return condition.hash_impl();
    }

    std::size_t hash<loki::pddl::ConditionNotImpl>::operator()(const loki::pddl::ConditionNotImpl& condition) const {
        return condition.hash_impl();
    }
}
