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

#include "parser_def.hpp"

#include "../../../include/loki/common/ast/config.hpp"


namespace loki::domain::parser
{
    using iterator_type = loki::iterator_type;
    using phrase_context_type = loki::phrase_context_type;
    using context_type = loki::context_type;

    BOOST_SPIRIT_INSTANTIATE(requirement_strips_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_typing_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_negative_preconditions_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_disjunctive_preconditions_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_equality_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_existential_preconditions_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_universal_preconditions_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_quantified_preconditions_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_conditional_effects_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_fluents_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_object_fluents_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_numeric_fluents_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_adl_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_durative_actions_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_derived_predicates_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_timed_initial_literals_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_preferences_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_constraints_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_action_costs_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirement_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(type_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(type_either_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(typed_list_of_names_recursively_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(typed_list_of_names_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(typed_list_of_variables_recursively_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(typed_list_of_variables_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(atomic_formula_skeleton_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(function_type_number_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(function_type_type_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(function_type_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(atomic_function_skeleton_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(function_typed_list_of_atomic_function_skeletons_recursively_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(function_typed_list_of_atomic_function_skeletons_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(atomic_formula_of_terms_predicate_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(atomic_formula_of_terms_equality_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(atomic_formula_of_terms_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(atom_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(negated_atom_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(literal_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(multi_operator_mul_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(multi_operator_plus_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(multi_operator_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(binary_operator_minus_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(binary_operator_div_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(binary_operator_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(binary_comparator_greater_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(binary_comparator_less_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(binary_comparator_equal_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(binary_comparator_greater_equal_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(binary_comparator_less_equal_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(binary_comparator_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(function_expression_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(function_head_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(function_expression_number_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(function_expression_binary_op_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(function_expression_minus_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(function_expression_head_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(goal_descriptor_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(goal_descriptor_atom_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(goal_descriptor_literal_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(goal_descriptor_and_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(goal_descriptor_or_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(goal_descriptor_not_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(goal_descriptor_imply_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(goal_descriptor_exists_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(goal_descriptor_forall_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(goal_descriptor_function_comparison_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(constraint_goal_descriptor_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(constraint_goal_descriptor_and_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(constraint_goal_descriptor_forall_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(constraint_goal_descriptor_at_end_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(constraint_goal_descriptor_always_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(constraint_goal_descriptor_sometime_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(constraint_goal_descriptor_within_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(constraint_goal_descriptor_at_most_once_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(constraint_goal_descriptor_sometime_after_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(constraint_goal_descriptor_sometime_before_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(constraint_goal_descriptor_always_within_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(constraint_goal_descriptor_hold_during_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(constraint_goal_descriptor_hold_after_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(precondition_goal_descriptor_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(preference_name_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(precondition_goal_descriptor_simple_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(precondition_goal_descriptor_and_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(precondition_goal_descriptor_preference_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(precondition_goal_descriptor_forall_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(assign_operator_assign_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(assign_operator_scale_up_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(assign_operator_scale_down_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(assign_operator_increase_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(assign_operator_decrease_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(assign_operator_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(effect_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(effect_production_literal_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(effect_production_numeric_fluent_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(effect_production_object_fluent_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(effect_production_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(effect_conditional_forall_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(effect_conditional_when_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(effect_conditional_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(action_symbol_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(action_body_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(action_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(derived_predicate_type, iterator_type, context_type)

    BOOST_SPIRIT_INSTANTIATE(domain_name_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(requirements_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(types_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(constants_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(predicates_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(functions_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(constraints_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(structure_type, iterator_type, context_type)
    BOOST_SPIRIT_INSTANTIATE(domain_type, iterator_type, context_type)
}
