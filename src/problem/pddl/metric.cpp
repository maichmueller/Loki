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

#include "../../../include/loki/problem/pddl/metric.hpp"

#include "../../../include/loki/common/hash.hpp"
#include "../../../include/loki/common/collections.hpp"
#include "../../../include/loki/domain/pddl/function.hpp"

#include <cassert>

using namespace std;


namespace loki::pddl {
std::unordered_map<OptimizationMetricEnum, std::string> optimization_metric_enum_to_string = {
    { OptimizationMetricEnum::MINIMIZE, "minimiza" },
    { OptimizationMetricEnum::MAXIMIZE, "maximize" },
};

const std::string& to_string(pddl::OptimizationMetricEnum optimization_metric) {
    assert(optimization_metric_enum_to_string.count(optimization_metric));
    return optimization_metric_enum_to_string.at(optimization_metric);
}


OptimizationMetricImpl::OptimizationMetricImpl(int identifier, OptimizationMetricEnum optimization_metric, Function function)
    : Base(identifier)
    , m_optimization_metric(optimization_metric)
    , m_function(std::move(function))
{
}

bool OptimizationMetricImpl::are_equal_impl(const OptimizationMetricImpl& other) const {
    return (m_optimization_metric == other.m_optimization_metric)
        && (m_function == other.m_function);
}

size_t OptimizationMetricImpl::hash_impl() const {
    return hash_combine(
        m_optimization_metric,
        m_function);
}

void OptimizationMetricImpl::str_impl(std::ostringstream& out, const FormattingOptions& options) const {
    out << "(" << to_string(m_optimization_metric) << " " << *m_function << ")";
}


OptimizationMetricEnum OptimizationMetricImpl::get_optimization_metric() const {
    return m_optimization_metric;
}

const Function& OptimizationMetricImpl::get_function() const {
    return m_function;
}

}


namespace std {
    bool less<loki::pddl::OptimizationMetric>::operator()(
        const loki::pddl::OptimizationMetric& left_metric,
        const loki::pddl::OptimizationMetric& right_metric) const {
        return *left_metric < *right_metric;
    }

    std::size_t hash<loki::pddl::OptimizationMetricImpl>::operator()(const loki::pddl::OptimizationMetricImpl& metric) const {
        return metric.hash_impl();
    }
}
