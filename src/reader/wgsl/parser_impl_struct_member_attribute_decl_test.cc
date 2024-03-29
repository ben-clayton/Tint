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

TEST_F(ParserImplTest, AttributeDecl_EmptyStr) {
  auto p = parser("");
  auto attrs = p->attribute_list();
  EXPECT_FALSE(p->has_error());
  EXPECT_FALSE(attrs.errored);
  EXPECT_FALSE(attrs.matched);
  EXPECT_EQ(attrs.value.size(), 0u);
}

// TODO(crbug.com/tint/1382): Remove
TEST_F(ParserImplTest, DEPRECATED_AttributeDecl_EmptyBlock) {
  auto p = parser("[[]]");
  auto attrs = p->attribute_list();
  EXPECT_TRUE(p->has_error());
  EXPECT_TRUE(attrs.errored);
  EXPECT_FALSE(attrs.matched);
  EXPECT_EQ(attrs.value.size(), 0u);
  EXPECT_EQ(
      p->error(),
      R"(1:1: use of deprecated language feature: [[attribute]] style attributes have been replaced with @attribute style
1:3: empty attribute list)");
}

TEST_F(ParserImplTest, AttributeDecl_Single) {
  auto p = parser("@size(4)");
  auto attrs = p->attribute_list();
  EXPECT_FALSE(p->has_error());
  EXPECT_FALSE(attrs.errored);
  EXPECT_TRUE(attrs.matched);
  ASSERT_EQ(attrs.value.size(), 1u);
  auto* attr = attrs.value[0]->As<ast::Attribute>();
  ASSERT_NE(attr, nullptr);
  EXPECT_TRUE(attr->Is<ast::StructMemberSizeAttribute>());
}

TEST_F(ParserImplTest, AttributeDecl_InvalidAttribute) {
  auto p = parser("@size(nan)");
  auto attrs = p->attribute_list();
  EXPECT_TRUE(p->has_error()) << p->error();
  EXPECT_TRUE(attrs.errored);
  EXPECT_FALSE(attrs.matched);
  EXPECT_EQ(p->error(),
            "1:7: expected signed integer literal for size attribute");
}

TEST_F(ParserImplTest, AttributeDecl_MissingClose) {
  auto p = parser("[[size(4)");
  auto attrs = p->attribute_list();
  EXPECT_TRUE(p->has_error()) << p->error();
  EXPECT_TRUE(attrs.errored);
  EXPECT_FALSE(attrs.matched);
  EXPECT_EQ(
      p->error(),
      R"(1:1: use of deprecated language feature: [[attribute]] style attributes have been replaced with @attribute style
1:10: expected ']]' for attribute list)");
}

TEST_F(ParserImplTest, StructMemberAttributeDecl_SizeMissingClose) {
  auto p = parser("[[size(4)");
  auto attrs = p->attribute_list();
  EXPECT_TRUE(p->has_error()) << p->error();
  EXPECT_TRUE(attrs.errored);
  EXPECT_FALSE(attrs.matched);
  EXPECT_EQ(
      p->error(),
      R"(1:1: use of deprecated language feature: [[attribute]] style attributes have been replaced with @attribute style
1:10: expected ']]' for attribute list)");
}

}  // namespace
}  // namespace wgsl
}  // namespace reader
}  // namespace tint
