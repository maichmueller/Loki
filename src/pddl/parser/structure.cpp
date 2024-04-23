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

#include "structure.hpp"

#include "common.hpp"
#include "conditions.hpp"
#include "effects.hpp"
#include "error_handling.hpp"
#include "literal.hpp"
#include "loki/details/pddl/action.hpp"
#include "loki/details/pddl/axiom.hpp"
#include "loki/details/pddl/exceptions.hpp"
#include "parameters.hpp"
#include "predicates.hpp"
#include "reference_utils.hpp"

namespace loki
{

std::tuple<std::optional<Condition>, std::optional<Effect>> parse(const ast::ActionBody& node, Context& context)
{
    std::optional<Condition> condition;
    if (node.precondition_goal_descriptor.has_value())
    {
        condition = parse(node.precondition_goal_descriptor.value(), context);
    }
    std::optional<Effect> effect;
    if (node.effect.has_value())
    {
        effect = parse(node.effect.value(), context);
    }
    return { condition, effect };
}

Action parse(const ast::Action& node, Context& context)
{
    context.scopes.open_scope();
    auto name = parse(node.action_symbol.name);
    auto parameter_list = boost::apply_visitor(ParameterListVisitor(context), node.typed_list_of_variables);
    track_variable_references(parameter_list, context);
    auto [condition, effect] = parse(node.action_body, context);
    test_variable_references(parameter_list, context);
    context.scopes.close_scope();
    const auto action = context.factories.get_or_create_action(name, parameter_list, condition, effect);
    context.positions.push_back(action, node);
    return action;
}

Axiom parse(const ast::Axiom& node, Context& context)
{
    if (!context.requirements->test(RequirementEnum::DERIVED_PREDICATES))
    {
        throw UndefinedRequirementError(RequirementEnum::DERIVED_PREDICATES, context.scopes.top().get_error_handler()(node, ""));
    }
    context.references.untrack(RequirementEnum::DERIVED_PREDICATES);

    const auto literal = parse(node.literal, context);
    if (context.derived_predicates.count(literal->get_atom()->get_predicate()) == 0)
    {
        throw ExpectedDerivedPredicate(literal->get_atom()->get_predicate()->get_name(), context.scopes.top().get_error_handler()(node, ""));
    }
    const auto condition = parse(node.goal_descriptor, context);

    const auto axiom = context.factories.get_or_create_axiom(literal, condition);
    context.positions.push_back(axiom, node);
    return axiom;
}

StructureVisitor::StructureVisitor(Context& context_) : context(context_) {}

boost::variant<Axiom, Action> parse(const ast::Structure& node, Context& context) { return boost::apply_visitor(StructureVisitor(context), node); }

}
