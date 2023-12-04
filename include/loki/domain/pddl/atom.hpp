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


#ifndef LOKI_INCLUDE_LOKI_DOMAIN_PDDL_ATOM_HPP_
#define LOKI_INCLUDE_LOKI_DOMAIN_PDDL_ATOM_HPP_

#include "declarations.hpp"

#include "../../common/pddl/base.hpp"


namespace loki {
template<typename... Ts>
class ReferenceCountedObjectFactory;
}


namespace loki::pddl {
class AtomImpl : public Base<AtomImpl> {
private:
    Predicate m_predicate;
    TermList m_terms;

    template<typename... Ts>
    friend class loki::ReferenceCountedObjectFactory;

public:
    AtomImpl(int identifier, const Predicate& predicate, const TermList& terms);

    /// @brief Test for semantic equivalence
    bool are_equal_impl(const AtomImpl& other) const;
    size_t hash_impl() const;
    void str_impl(std::stringstream& out, const FormattingOptions& options) const;

    const Predicate& get_predicate() const;
    const TermList& get_terms() const;
};

}


namespace std {
    // Inject comparison and hash function to make pointers behave appropriately with ordered and unordered datastructures
    template<>
    struct less<loki::pddl::Atom>
    {
        bool operator()(const loki::pddl::Atom& left_atom, const loki::pddl::Atom& right_atom) const;
    };

    template<>
    struct hash<loki::pddl::AtomImpl>
    {
        std::size_t operator()(const loki::pddl::AtomImpl& atom) const;
    };
}

#endif
