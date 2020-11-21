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

#include <memory>

#include "src/ast/function.h"
#include "src/ast/identifier_expression.h"
#include "src/ast/module.h"
#include "src/ast/type/void_type.h"
#include "src/writer/essl/test_helper.h"
#include "src/ast/stage_decoration.h"

namespace tint {
namespace writer {
namespace essl {
namespace {

using EsslGeneratorImplTest = TestHelper;

TEST_F(EsslGeneratorImplTest, DISABLED_Generate) {
  ast::type::VoidType void_type;
  auto* func = create<ast::Function>("my_func", ast::VariableList{}, &void_type,
                                     create<ast::BlockStatement>());
  func->set_decorations({
      create<ast::StageDecoration>(ast::PipelineStage::kVertex, Source{})});
  mod.AddFunction(func);

  ASSERT_TRUE(gen.GenerateEntryPoint(out, ast::PipelineStage::kVertex, "my_func")) << gen.error();
  EXPECT_EQ(result(), R"(void my_func() {
}

)");
}

}  // namespace
}  // namespace essl
}  // namespace writer
}  // namespace tint

