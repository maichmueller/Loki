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

#include "../../include/loki/common/exceptions.hpp"


namespace loki {
SyntaxParserError::SyntaxParserError(const std::string& message)
    : std::runtime_error(message) { }

SemanticParserError::SemanticParserError(const std::string& message, const std::string& error_handler_output)
    : std::runtime_error(message + "\n" + error_handler_output) { }

NotImplementedError::NotImplementedError(const std::string& message)
    : std::runtime_error(message) { }

}
