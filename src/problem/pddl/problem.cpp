/*
 * Copyright (C) 2023 Dominik Drexler
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

#include "../../../include/loki/problem/pddl/problem.hpp"
#include "../../../include/loki/common/hash.hpp"
#include "../../../include/loki/common/collections.hpp"
#include "../../../include/loki/domain/pddl/conditions.hpp"
#include "../../../include/loki/domain/pddl/literal.hpp"
#include "../../../include/loki/domain/pddl/domain.hpp"
#include "../../../include/loki/domain/pddl/requirements.hpp"
#include "../../../include/loki/domain/pddl/object.hpp"

using namespace std;


namespace loki::pddl {
ProblemImpl::ProblemImpl(int identifier, const Domain& domain, const std::string& name, const Requirements& requirements, const ObjectList& objects, const LiteralList& initial_literals, const Condition& goal_condition)
    : Base(identifier)
    , m_domain(domain)
    , m_name(name)
    , m_requirements(requirements)
    , m_objects(objects)
    , m_initial_literals(initial_literals)
    , m_goal_condition(goal_condition)
{
}

bool ProblemImpl::are_equal_impl(const ProblemImpl& other) const {
    return (m_domain == other.m_domain)
        && (m_name == other.m_name)
        && (m_requirements == other.m_requirements)
        && (get_sorted_vector(m_objects) == get_sorted_vector(other.m_objects))
        && (get_sorted_vector(m_initial_literals)) == get_sorted_vector(other.m_initial_literals)
        && (m_goal_condition == other.m_goal_condition);
}

size_t ProblemImpl::hash_impl() const {
    return hash_combine(
        m_domain,
        m_name,
        m_requirements,
        hash_vector(get_sorted_vector(m_objects)),
        hash_vector(get_sorted_vector(m_initial_literals)),
        m_goal_condition);
}

void ProblemImpl::str_impl(std::ostringstream& out, const FormattingOptions& options) const {
    out << string(options.indent, ' ') << "(define (problem " << m_name << ")\n";
    auto nested_options = FormattingOptions{options.indent + options.add_indent, options.add_indent};
    out << string(nested_options.indent, ' ') << "(:domain " << m_domain->get_name() << ")\n";
    if (!m_requirements->get_requirements().empty()) {
        out << string(nested_options.indent, ' ') << *m_requirements << "\n";
    }
    if (!m_objects.empty()) {
        out << string(nested_options.indent, ' ') << "(:objects ";
        for (size_t i = 0; i < m_objects.size(); ++i) {
            if (i != 0) out << " ";
            out << *m_objects[i];
        }
        out << ")\n";
    }
    out << string(nested_options.indent, ' ') << "(:init ";
    for (size_t i = 0; i < m_initial_literals.size(); ++i) {
        if (i != 0) out << " ";
        out << *m_initial_literals[i];
    }
    out << ")\n";
    out << string(nested_options.indent, ' ') << "(:goal " << *m_goal_condition << ")\n";

    /*
    if (node.constraints.has_value()) {
        ss << string(nested_options.indent, ' ') << parse_text(node.constraints.value(), nested_options) << "\n";
    }
    if (node.metric_specification.has_value()) {
        ss << string(nested_options.indent, ' ') << parse_text(node.metric_specification.value(), nested_options) << "\n";
    }
    */

    out << string(options.indent, ' ') << ")";
}


const Domain& ProblemImpl::get_domain() const {
    return m_domain;
}

const std::string& ProblemImpl::get_name() const {
    return m_name;
}

const Requirements& ProblemImpl::get_requirements() const {
    return m_requirements;
}

const ObjectList& ProblemImpl::get_objects() const {
    return m_objects;
}

const LiteralList& ProblemImpl::get_initial_literals() const {
    return m_initial_literals;
}

const Condition& ProblemImpl::get_goal_condition() const {
    return m_goal_condition;
}

}


namespace std {
    bool less<loki::pddl::Problem>::operator()(
        const loki::pddl::Problem& left_problem,
        const loki::pddl::Problem& right_problem) const {
        return *left_problem < *right_problem;
    }

    std::size_t hash<loki::pddl::ProblemImpl>::operator()(const loki::pddl::ProblemImpl& problem) const {
        return problem.hash_impl();
    }
}
