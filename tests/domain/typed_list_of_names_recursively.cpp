#include <gtest/gtest.h>

#include "include/loki/common/parser_wrapper.hpp"
#include "include/loki/domain/parser.hpp"
#include "include/loki/domain/printer.hpp"


namespace loki::domain::tests {

TEST(LokiTests, TypedListOfNamesRecursivelyTest) {
    ast::TypedListOfNamesRecursively ast;

    EXPECT_NO_THROW(parse_ast("name1 name2 - type1", typed_list_of_names_recursively(), ast));
    EXPECT_EQ(parse_text(ast), "name1 name2 - type1");

    EXPECT_ANY_THROW(parse_ast("name1 name2", typed_list_of_names_recursively(), ast));
    EXPECT_ANY_THROW(parse_ast("?var1 ?var2", typed_list_of_names_recursively(), ast));
}

}
