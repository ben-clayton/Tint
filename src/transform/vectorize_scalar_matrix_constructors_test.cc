// Copyright 2021 The Tint Authors.
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

#include "src/transform/vectorize_scalar_matrix_constructors.h"

#include <string>
#include <utility>

#include "src/transform/test_helper.h"
#include "src/utils/string.h"

namespace tint {
namespace transform {
namespace {

using VectorizeScalarMatrixConstructorsTest =
    TransformTestWithParam<std::pair<uint32_t, uint32_t>>;

TEST_F(VectorizeScalarMatrixConstructorsTest, ShouldRunEmptyModule) {
  auto* src = R"()";

  EXPECT_FALSE(ShouldRun<VectorizeScalarMatrixConstructors>(src));
}

TEST_P(VectorizeScalarMatrixConstructorsTest, Basic) {
  uint32_t cols = GetParam().first;
  uint32_t rows = GetParam().second;
  std::string mat_type =
      "mat" + std::to_string(cols) + "x" + std::to_string(rows) + "<f32>";
  std::string vec_type = "vec" + std::to_string(rows) + "<f32>";
  std::string scalar_values;
  std::string vector_values;
  for (uint32_t c = 0; c < cols; c++) {
    if (c > 0) {
      vector_values += ", ";
      scalar_values += ", ";
    }
    vector_values += vec_type + "(";
    for (uint32_t r = 0; r < rows; r++) {
      if (r > 0) {
        scalar_values += ", ";
        vector_values += ", ";
      }
      auto value = std::to_string(c * rows + r) + ".0";
      scalar_values += value;
      vector_values += value;
    }
    vector_values += ")";
  }

  std::string tmpl = R"(
@stage(fragment)
fn main() {
  let m = ${matrix}(${values});
}
)";
  tmpl = utils::ReplaceAll(tmpl, "${matrix}", mat_type);
  auto src = utils::ReplaceAll(tmpl, "${values}", scalar_values);
  auto expect = utils::ReplaceAll(tmpl, "${values}", vector_values);

  EXPECT_TRUE(ShouldRun<VectorizeScalarMatrixConstructors>(src));

  auto got = Run<VectorizeScalarMatrixConstructors>(src);

  EXPECT_EQ(expect, str(got));
}

TEST_P(VectorizeScalarMatrixConstructorsTest, NonScalarConstructors) {
  uint32_t cols = GetParam().first;
  uint32_t rows = GetParam().second;
  std::string mat_type =
      "mat" + std::to_string(cols) + "x" + std::to_string(rows) + "<f32>";
  std::string vec_type = "vec" + std::to_string(rows) + "<f32>";
  std::string columns;
  for (uint32_t c = 0; c < cols; c++) {
    if (c > 0) {
      columns += ", ";
    }
    columns += vec_type + "()";
  }

  std::string tmpl = R"(
@stage(fragment)
fn main() {
  let m = ${matrix}(${columns});
}
)";
  tmpl = utils::ReplaceAll(tmpl, "${matrix}", mat_type);
  auto src = utils::ReplaceAll(tmpl, "${columns}", columns);
  auto expect = src;

  EXPECT_FALSE(ShouldRun<VectorizeScalarMatrixConstructors>(src));

  auto got = Run<VectorizeScalarMatrixConstructors>(src);

  EXPECT_EQ(expect, str(got));
}

INSTANTIATE_TEST_SUITE_P(VectorizeScalarMatrixConstructorsTest,
                         VectorizeScalarMatrixConstructorsTest,
                         testing::Values(std::make_pair(2, 2),
                                         std::make_pair(2, 3),
                                         std::make_pair(2, 4),
                                         std::make_pair(3, 2),
                                         std::make_pair(3, 3),
                                         std::make_pair(3, 4),
                                         std::make_pair(4, 2),
                                         std::make_pair(4, 3),
                                         std::make_pair(4, 4)));

}  // namespace
}  // namespace transform
}  // namespace tint
