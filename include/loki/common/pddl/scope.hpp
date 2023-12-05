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

#ifndef LOKI_INCLUDE_LOKI_COMMON_PDDL_SCOPE_HPP_
#define LOKI_INCLUDE_LOKI_COMMON_PDDL_SCOPE_HPP_

#include "../../domain/pddl/type.hpp"
#include "../../domain/pddl/object.hpp"
#include "../../domain/pddl/predicate.hpp"
#include "../../domain/pddl/function_skeleton.hpp"
#include "../../domain/pddl/variable.hpp"

#include <boost/spirit/home/x3/support/ast/position_tagged.hpp>

#include <cassert>
#include <unordered_map>
#include <memory>
#include <tuple>
#include <optional>


namespace loki {
class Scope;

template<typename T>
using BindingPtrType = std::shared_ptr<const T>;

using PositionType = boost::spirit::x3::position_tagged;

template<typename T>
struct ValueType {
    BindingPtrType<T> object;
    std::optional<PositionType> position;
};

template<typename T>
using MapType = std::unordered_map<std::string, ValueType<T>>;


/// @brief Encapsulates bindings for different types.
template<typename... Ts>
class Bindings {
    private:
        std::tuple<MapType<Ts>...> bindings;

    public:
        /// @brief Returns an existing binding.
        template<typename T>
        std::optional<ValueType<T>> get(const std::string& key) const;

        /// @brief Returns all bindings of type T defined in the scope includings its parent scopes.
        template<typename T>
        std::optional<ValueType<T>> getWithParent(const std::string& key, const Scope* parent_scope) const;

        /// @brief Gets all bindings of type T.
        template<typename T>
        const MapType<T>& get() const;

        /// @brief Returns all bindings of type T defined in the scope includings its parent scopes.
        template<typename T>
        MapType<T> getWithParent(const Scope* parent_scope) const;

        /// @brief Inserts a binding of type T
        template<typename T>
        void insert(const std::string& key, const BindingPtrType<T>& binding, const std::optional<PositionType>& position);
};


/// @brief Wraps bindings in a scope with reference to a parent scope.
class Scope {
    private:
        std::shared_ptr<const Scope> m_parent_scope;

        Bindings<pddl::TypeImpl
            , pddl::ObjectImpl
            , pddl::PredicateImpl
            , pddl::FunctionSkeletonImpl
            , pddl::VariableImpl> bindings;

    public:
        explicit Scope(std::shared_ptr<const Scope> parent_scope = nullptr)
            : m_parent_scope(parent_scope) { }

        /// @brief Returns a existing binding.
        template<typename T>
        std::optional<ValueType<T>> get(const std::string& name) const;

        /// @brief Returns all bindings of type T defined in the scope includings its parent scopes.
        template<typename T>
        MapType<T> get() const;

        /// @brief Insert binding of type T.
        template<typename T>
        void insert(const std::string& name, const BindingPtrType<T>& binding, const std::optional<PositionType>& position = std::optional<PositionType>());
};

}

#include "scope.tpp"

#endif
