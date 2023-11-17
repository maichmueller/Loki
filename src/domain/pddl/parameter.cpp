#include "help_functions.hpp"

#include "../../../include/loki/domain/pddl/parameter.hpp"

#include <memory>


namespace loki::pddl
{
    ParameterImpl::ParameterImpl(const std::string& name, const TypeSet& types)
        : name(name), types(types) { }

    Parameter create_parameter(const std::string& name, const TypeSet& types) {
        return std::make_shared<ParameterImpl>(name, types);
    }
}
