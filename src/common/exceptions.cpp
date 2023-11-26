#include "../../include/loki/common/exceptions.hpp"

#include "../../include/loki/domain/pddl/predicate.hpp"
#include "../../include/loki/domain/pddl/requirements.hpp"
#include "../../include/loki/domain/pddl/domain.hpp"


namespace loki {

SyntaxParserError::SyntaxParserError(const std::string& message)
    : std::runtime_error(message) { }


SemanticParserError::SemanticParserError(const std::string& message, const std::string& error_handler_output)
    : std::runtime_error(message + "\n" + error_handler_output) { }

UndefinedTypeError::UndefinedTypeError(const std::string& name, const std::string& error_handler_output)
    : SemanticParserError(
        "The type with name \"" + name + "\" is undefined.", error_handler_output) { }

UndefinedPredicateError::UndefinedPredicateError(const std::string& name, const std::string& error_handler_output)
    : SemanticParserError(
        "The predicate with name \"" + name + "\" is undefined.", error_handler_output) { }

UndefinedConstantError::UndefinedConstantError(const std::string& name, const std::string& error_handler_output)
    : SemanticParserError(
        "The constant with name \"" + name + "\" is undefined.", error_handler_output) { }

UndefinedVariableError::UndefinedVariableError(const std::string& name, const std::string& error_handler_output)
    : SemanticParserError(
        "The variable with name \"" + name + "\" is not defined in the current scope.", error_handler_output) { }

UndefinedRequirementError::UndefinedRequirementError(pddl::RequirementEnum requirement, const std::string& error_handler_output)
    : SemanticParserError("Undefined requirement: " + to_string(requirement), error_handler_output) { }

MismatchedPredicateTermListError::MismatchedPredicateTermListError(
    const pddl::Predicate& predicate,
    const pddl::TermList& term_list,
    const std::string& error_handler_output)
    : SemanticParserError(
        "Mismatched number of terms for predicate \""
            + predicate->get_name()
            + "\" with sizes "
            + std::to_string(predicate->get_parameters().size())
            + "!="
            + std::to_string(term_list.size())
            + ".",
        error_handler_output) { }


MismatchedDomainError::MismatchedDomainError(
    const pddl::Domain& domain,
    const std::string& domain_name,
    const std::string& error_handler_output)
    : SemanticParserError(
        "Mismatched domain names \""
            + domain->get_name()
            + "!="
            + domain_name
            + ".",
        error_handler_output) { }

NotImplementedError::NotImplementedError(const std::string& message)
    : std::runtime_error(message) { }


NotSupportedError::NotSupportedError(pddl::RequirementEnum requirement, const std::string& error_handler_output)
    : std::runtime_error("Unsupported requirement: " + to_string(requirement) + "\n" + error_handler_output) { }

}