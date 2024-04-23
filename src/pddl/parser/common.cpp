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

#include "common.hpp"

#include "error_handling.hpp"
#include "loki/details/pddl/exceptions.hpp"

using namespace std;

namespace loki
{

/* Name */
string parse(const ast::Name& node) { return node.characters; }

/* Variable */
Variable parse(const ast::Variable& node, Context& context)
{
    const auto variable = context.factories.get_or_create_variable(node.characters);
    context.references.untrack(variable);
    context.positions.push_back(variable, node);
    return variable;
}

/* Term */
TermDeclarationTermVisitor::TermDeclarationTermVisitor(Context& context_) : context(context_) {}

Term TermDeclarationTermVisitor::operator()(const ast::Name& node) const
{
    const auto constant_name = parse(node);
    test_undefined_constant(constant_name, node, context);
    // Constant are not tracked and hence must not be untracked.
    const auto binding = context.scopes.top().get_object(constant_name);
    const auto [constant, _position, _error_handler] = binding.value();
    const auto term = context.factories.get_or_create_term_object(constant);
    context.positions.push_back(term, node);
    return term;
}

Term TermDeclarationTermVisitor::operator()(const ast::Variable& node) const
{
    const auto variable = parse(node, context);
    test_multiple_definition_variable(variable, node, context);
    context.scopes.top().insert_variable(variable->get_name(), variable, node);
    const auto term = context.factories.get_or_create_term_variable(variable);
    context.positions.push_back(term, node);
    return term;
}

TermReferenceTermVisitor::TermReferenceTermVisitor(Context& context_) : context(context_) {}

Term TermReferenceTermVisitor::operator()(const ast::Name& node) const
{
    const auto object_name = parse(node);
    test_undefined_constant(object_name, node, context);
    const auto binding = context.scopes.top().get_object(object_name);
    const auto [object, _position, _error_handler] = binding.value();
    context.references.untrack(object);
    const auto term = context.factories.get_or_create_term_object(object);
    context.positions.push_back(term, node);
    return term;
}

Term TermReferenceTermVisitor::operator()(const ast::Variable& node) const
{
    const auto variable = parse(node, context);
    test_undefined_variable(variable, node, context);
    const auto term = context.factories.get_or_create_term_variable(variable);
    context.positions.push_back(term, node);
    return term;
}

/* Number */
double parse(const ast::Number& node) { return node.value; }

}
