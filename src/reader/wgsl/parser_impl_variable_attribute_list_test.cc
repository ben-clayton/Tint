// Copyright 2020 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/reader/wgsl/parser_impl_test_helper.h"

namespace tint {
namespace reader {
namespace wgsl {
namespace {

TEST_F(ParserImplTest, AttributeList_Parses) {
  auto p = parser(R"(@location(4) @builtin(position))");
  auto attrs = p->attribute_list();
  ASSERT_FALSE(p->has_error()) << p->error();
  ASSERT_FALSE(attrs.errored);
  ASSERT_TRUE(attrs.matched);
  ASSERT_EQ(attrs.value.size(), 2u);

  auto* attr_0 = attrs.value[0]->As<ast::Attribute>();
  auto* attr_1 = attrs.value[1]->As<ast::Attribute>();
  ASSERT_NE(attr_0, nullptr);
  ASSERT_NE(attr_1, nullptr);

  ASSERT_TRUE(attr_0->Is<ast::LocationAttribute>());
  EXPECT_EQ(attr_0->As<ast::LocationAttribute>()->value, 4u);
  ASSERT_TRUE(attr_1->Is<ast::BuiltinAttribute>());
  EXPECT_EQ(attr_1->As<ast::BuiltinAttribute>()->builtin,
            ast::Builtin::kPosition);
}

TEST_F(ParserImplTest, AttributeList_Invalid) {
  auto p = parser(R"(@invalid)");
  auto attrs = p->attribute_list();
  EXPECT_TRUE(p->has_error());
  EXPECT_TRUE(attrs.errored);
  EXPECT_FALSE(attrs.matched);
  EXPECT_TRUE(attrs.value.empty());
  EXPECT_EQ(p->error(), R"(1:2: expected attribute)");
}

TEST_F(ParserImplTest, AttributeList_InvalidValue) {
  auto p = parser("@builtin(invalid)");
  auto attrs = p->attribute_list();
  EXPECT_TRUE(p->has_error());
  EXPECT_TRUE(attrs.errored);
  EXPECT_FALSE(attrs.matched);
  EXPECT_TRUE(attrs.value.empty());
  EXPECT_EQ(p->error(), "1:10: invalid value for builtin attribute");
}

// TODO(crbug.com/tint/1382): Remove
TEST_F(ParserImplTest, DEPRECATED_AttributeList_Empty) {
  auto p = parser(R"([[]])");
  auto attrs = p->attribute_list();
  EXPECT_TRUE(p->has_error());
  EXPECT_TRUE(attrs.errored);
  EXPECT_FALSE(attrs.matched);
  EXPECT_TRUE(attrs.value.empty());
  EXPECT_EQ(
      p->error(),
      R"(1:1: use of deprecated language feature: [[attribute]] style attributes have been replaced with @attribute style
1:3: empty attribute list)");
}

// TODO(crbug.com/tint/1382): Remove
TEST_F(ParserImplTest, DEPRECATED_AttributeList_Invalid) {
  auto p = parser(R"([[invalid]])");
  auto attrs = p->attribute_list();
  EXPECT_TRUE(p->has_error());
  EXPECT_TRUE(attrs.errored);
  EXPECT_FALSE(attrs.matched);
  EXPECT_TRUE(attrs.value.empty());
  EXPECT_EQ(
      p->error(),
      R"(1:1: use of deprecated language feature: [[attribute]] style attributes have been replaced with @attribute style
1:3: expected attribute)");
}

// TODO(crbug.com/tint/1382): Remove
TEST_F(ParserImplTest, DEPRECATED_AttributeList_ExtraComma) {
  auto p = parser(R"([[builtin(position), ]])");
  auto attrs = p->attribute_list();
  EXPECT_TRUE(p->has_error());
  EXPECT_TRUE(attrs.errored);
  EXPECT_FALSE(attrs.matched);
  EXPECT_TRUE(attrs.value.empty());
  EXPECT_EQ(
      p->error(),
      R"(1:1: use of deprecated language feature: [[attribute]] style attributes have been replaced with @attribute style
1:22: expected attribute)");
}

// TODO(crbug.com/tint/1382): Remove
TEST_F(ParserImplTest, DEPRECATED_AttributeList_MissingComma) {
  auto p = parser(R"([[binding(4) location(5)]])");
  auto attrs = p->attribute_list();
  EXPECT_TRUE(p->has_error());
  EXPECT_TRUE(attrs.errored);
  EXPECT_FALSE(attrs.matched);
  EXPECT_TRUE(attrs.value.empty());
  EXPECT_EQ(
      p->error(),
      R"(1:1: use of deprecated language feature: [[attribute]] style attributes have been replaced with @attribute style
1:14: expected ',' for attribute list)");
}

// TODO(crbug.com/tint/1382): Remove
TEST_F(ParserImplTest, DEPRECATED_AttributeList_InvalidValue) {
  auto p = parser("[[builtin(invalid)]]");
  auto attrs = p->attribute_list();
  EXPECT_TRUE(p->has_error());
  EXPECT_TRUE(attrs.errored);
  EXPECT_FALSE(attrs.matched);
  EXPECT_TRUE(attrs.value.empty());
  EXPECT_EQ(
      p->error(),
      R"(1:1: use of deprecated language feature: [[attribute]] style attributes have been replaced with @attribute style
1:11: invalid value for builtin attribute)");
}

}  // namespace
}  // namespace wgsl
}  // namespace reader
}  // namespace tint
