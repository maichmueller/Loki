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

#ifndef LOKI_INCLUDE_LOKI_COMMON_HASH_HPP_
#define LOKI_INCLUDE_LOKI_COMMON_HASH_HPP_

#include <functional>
#include <cstddef>
#include <set>
#include <vector>


namespace loki {

// --------------
// Hash functions
// --------------

template<typename T>
inline void hash_combine(size_t& seed, const T& val)
{
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<>
inline void hash_combine(size_t& seed, const std::size_t& val)
{
    seed ^= val + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename... Types>
inline size_t hash_combine(const Types&... args)
{
    size_t seed = 0;
    (hash_combine(seed, args), ...);
    return seed;
}

template<class T>
inline std::size_t hash_vector(const std::vector<T>& vector)
{
    const auto hash_function = std::hash<T>();
    std::size_t aggregated_hash = 0;
    for (const auto& item : vector)
    {
        const auto item_hash = hash_function(item);
        hash_combine(aggregated_hash, item_hash);
    }
    return aggregated_hash;
}

template<typename T>
struct hash_vector_type {
    size_t operator()(const std::vector<T>& vector) const {
        return hash_vector(vector);
    }
};

template<class T>
inline std::size_t hash_set(const std::set<T>& vector)
{
    const auto hash_function = std::hash<T>();
    std::size_t aggregated_hash = 0;
    for (const auto& item : vector)
    {
        const auto item_hash = hash_function(item);
        hash_combine(aggregated_hash, item_hash);
    }
    return aggregated_hash;
}

}


#endif