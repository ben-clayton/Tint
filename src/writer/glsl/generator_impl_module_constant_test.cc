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

#include "src/ast/override_attribute.h"
#include "src/writer/glsl/test_helper.h"

namespace tint {
namespace writer {
namespace glsl {
namespace {

using GlslGeneratorImplTest_ModuleConstant = TestHelper;

TEST_F(GlslGeneratorImplTest_ModuleConstant, Emit_ModuleConstant) {
  auto* var = Const("pos", ty.array<f32, 3>(), array<f32, 3>(1.f, 2.f, 3.f));
  WrapInFunction(Decl(var));

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitProgramConstVariable(var)) << gen.error();
  EXPECT_EQ(gen.result(), "const float pos[3] = float[3](1.0f, 2.0f, 3.0f);\n");
}

TEST_F(GlslGeneratorImplTest_ModuleConstant, Emit_SpecConstant) {
  auto* var = GlobalConst("pos", ty.f32(), Expr(3.0f),
                          ast::AttributeList{
                              create<ast::OverrideAttribute>(23),
                          });

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitProgramConstVariable(var)) << gen.error();
  EXPECT_EQ(gen.result(), R"(#ifndef WGSL_SPEC_CONSTANT_23
#define WGSL_SPEC_CONSTANT_23 3.0f
#endif
const float pos = WGSL_SPEC_CONSTANT_23;
)");
}

TEST_F(GlslGeneratorImplTest_ModuleConstant, Emit_SpecConstant_NoConstructor) {
  auto* var = GlobalConst("pos", ty.f32(), nullptr,
                          ast::AttributeList{
                              create<ast::OverrideAttribute>(23),
                          });

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitProgramConstVariable(var)) << gen.error();
  EXPECT_EQ(gen.result(), R"(#ifndef WGSL_SPEC_CONSTANT_23
#error spec constant required for constant id 23
#endif
const float pos = WGSL_SPEC_CONSTANT_23;
)");
}

TEST_F(GlslGeneratorImplTest_ModuleConstant, Emit_SpecConstant_NoId) {
  auto* a = GlobalConst("a", ty.f32(), Expr(3.0f),
                        ast::AttributeList{
                            create<ast::OverrideAttribute>(0),
                        });
  auto* b = GlobalConst("b", ty.f32(), Expr(2.0f),
                        ast::AttributeList{
                            create<ast::OverrideAttribute>(),
                        });

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.EmitProgramConstVariable(a)) << gen.error();
  ASSERT_TRUE(gen.EmitProgramConstVariable(b)) << gen.error();
  EXPECT_EQ(gen.result(), R"(#ifndef WGSL_SPEC_CONSTANT_0
#define WGSL_SPEC_CONSTANT_0 3.0f
#endif
const float a = WGSL_SPEC_CONSTANT_0;
#ifndef WGSL_SPEC_CONSTANT_1
#define WGSL_SPEC_CONSTANT_1 2.0f
#endif
const float b = WGSL_SPEC_CONSTANT_1;
)");
}

}  // namespace
}  // namespace glsl
}  // namespace writer
}  // namespace tint
