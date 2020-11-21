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

#ifndef SRC_WRITER_ESSL_TEST_HELPER_H_
#define SRC_WRITER_ESSL_TEST_HELPER_H_

#include <memory>
#include <sstream>
#include <string>
#include <utility>

#include "gtest/gtest.h"
#include "src/ast/module.h"
#include "src/context.h"
#include "src/type_determiner.h"
#include "src/writer/essl/generator_impl.h"

namespace tint {
namespace writer {
namespace essl {

/// Helper class for testing
template <typename BODY>
class TestHelperBase : public BODY {
 public:
  TestHelperBase() : td(&ctx, &mod), gen(&mod) {}
  ~TestHelperBase() = default;

  /// @returns the result string
  std::string result() const { return out.str(); }

  /// Creates a new `ast::Node` owned by the Module. When the Module is
  /// destructed, the `ast::Node` will also be destructed.
  /// @param args the arguments to pass to the type constructor
  /// @returns the node pointer  template <typename T, typename... ARGS>
  template <typename T, typename... ARGS>
  T* create(ARGS&&... args) {
    return mod.create<T>(std::forward<ARGS>(args)...);
  }

  /// The context
  Context ctx;
  /// The module
  ast::Module mod;
  /// The type determiner
  TypeDeterminer td;
  /// The generator
  GeneratorImpl gen;

  /// The output stream
  std::ostringstream out;
};
using TestHelper = TestHelperBase<testing::Test>;

template <typename T>
using TestParamHelper = TestHelperBase<testing::TestWithParam<T>>;

}  // namespace essl
}  // namespace writer
}  // namespace tint

#endif  // SRC_WRITER_ESSL_TEST_HELPER_H_

