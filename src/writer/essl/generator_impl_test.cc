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

#include "src/ast/binding_decoration.h"
#include "src/ast/decorated_variable.h"
#include "src/ast/function.h"
#include "src/ast/identifier_expression.h"
#include "src/ast/module.h"
#include "src/ast/set_decoration.h"
#include "src/ast/stage_decoration.h"
#include "src/ast/type/depth_texture_type.h"
#include "src/ast/type/sampled_texture_type.h"
#include "src/ast/type/storage_texture_type.h"
#include "src/ast/type/void_type.h"
#include "src/writer/essl/test_helper.h"

namespace tint {
namespace writer {
namespace essl {
namespace {

using EsslGeneratorImplTest = TestHelper;

TEST_F(EsslGeneratorImplTest, DISABLED_Generate) {
  auto* func = create<ast::Function>("my_func", ast::VariableList{}, ty.void_,
                                     create<ast::BlockStatement>());
  func->set_decorations({
      create<ast::StageDecoration>(ast::PipelineStage::kVertex, Source{})});
  mod->AddFunction(func);

  ASSERT_TRUE(gen.GenerateEntryPoint(out, ast::PipelineStage::kVertex, "my_func")) << gen.error();
  EXPECT_EQ(result(), R"(void my_func() {
}

)");
}

TEST_F(EsslGeneratorImplTest, NoCubeArrayNoTexture1d) {
  auto* func = create<ast::Function>("my_func", ast::VariableList{}, ty.void_,
                                     create<ast::BlockStatement>());
  func->set_decorations(
      {create<ast::StageDecoration>(ast::PipelineStage::kVertex, Source{})});
  mod->AddFunction(func);

  auto ext = gen.GatherExtensionData(func);
  EXPECT_FALSE(ext.needs_cube_array_ext);
  EXPECT_FALSE(ext.has_texture_1d);
}

TEST_F(EsslGeneratorImplTest, HasSampledCubeArray) {
  auto* func = create<ast::Function>("my_func", ast::VariableList{}, ty.void_,
                                     create<ast::BlockStatement>());
  func->set_decorations(
      {create<ast::StageDecoration>(ast::PipelineStage::kVertex, Source{})});
  mod->AddFunction(func);

  ast::type::SampledTextureType sampled(ast::type::TextureDimension::kCubeArray,
                                        ty.f32);
  auto* v = Var("v", ast::StorageClass::kUniformConstant, &sampled);
  ast::DecoratedVariable dv(v);
  dv.set_decorations({create<ast::BindingDecoration>(0, Source{}),
                      create<ast::SetDecoration>(0, Source{})});

  func->add_referenced_module_variable(&dv);

  auto ext = gen.GatherExtensionData(func);
  EXPECT_TRUE(ext.needs_cube_array_ext);
}

TEST_F(EsslGeneratorImplTest, HasDepthCubeArray) {
  auto* func = create<ast::Function>("my_func", ast::VariableList{}, ty.void_,
                                     create<ast::BlockStatement>());
  func->set_decorations(
      {create<ast::StageDecoration>(ast::PipelineStage::kVertex, Source{})});
  mod->AddFunction(func);

  ast::type::DepthTextureType depth(ast::type::TextureDimension::kCubeArray);
  auto* v = Var("v", ast::StorageClass::kUniformConstant, &depth);
  ast::DecoratedVariable dv(v);
  dv.set_decorations({create<ast::BindingDecoration>(0, Source{}),
                      create<ast::SetDecoration>(0, Source{})});

  func->add_referenced_module_variable(&dv);

  auto ext = gen.GatherExtensionData(func);
  EXPECT_TRUE(ext.needs_cube_array_ext);
}

TEST_F(EsslGeneratorImplTest, HasSampledTexture1D) {
  auto* func = create<ast::Function>("my_func", ast::VariableList{}, ty.void_,
                                     create<ast::BlockStatement>());
  func->set_decorations(
      {create<ast::StageDecoration>(ast::PipelineStage::kVertex, Source{})});
  mod->AddFunction(func);

  ast::type::SampledTextureType sampled(ast::type::TextureDimension::k1d,
                                        ty.f32);
  auto* v = Var("v", ast::StorageClass::kUniformConstant, &sampled);
  ast::DecoratedVariable dv(v);
  dv.set_decorations({create<ast::BindingDecoration>(0, Source{}),
                      create<ast::SetDecoration>(0, Source{})});

  func->add_referenced_module_variable(&dv);

  auto ext = gen.GatherExtensionData(func);
  EXPECT_TRUE(ext.has_texture_1d);
}

TEST_F(EsslGeneratorImplTest, HasSampledTexture1DArray) {
  auto* func = create<ast::Function>("my_func", ast::VariableList{}, ty.void_,
                                     create<ast::BlockStatement>());
  func->set_decorations(
      {create<ast::StageDecoration>(ast::PipelineStage::kVertex, Source{})});
  mod->AddFunction(func);

  ast::type::SampledTextureType sampled(ast::type::TextureDimension::k1dArray,
                                        ty.f32);
  auto* v = Var("v", ast::StorageClass::kUniformConstant, &sampled);
  ast::DecoratedVariable dv(v);
  dv.set_decorations({create<ast::BindingDecoration>(0, Source{}),
                      create<ast::SetDecoration>(0, Source{})});

  func->add_referenced_module_variable(&dv);

  auto ext = gen.GatherExtensionData(func);
  EXPECT_TRUE(ext.has_texture_1d);
}

TEST_F(EsslGeneratorImplTest, HasStorageTexture1D) {
  auto* func = create<ast::Function>("my_func", ast::VariableList{}, ty.void_,
                                     create<ast::BlockStatement>());
  func->set_decorations(
      {create<ast::StageDecoration>(ast::PipelineStage::kVertex, Source{})});
  mod->AddFunction(func);

  ast::type::StorageTextureType store(ast::type::TextureDimension::k1d,
                                      ast::AccessControl::kReadOnly,
                                      ast::type::ImageFormat::kR32Float);
  auto* v = Var("v", ast::StorageClass::kUniformConstant, &store);
  ast::DecoratedVariable dv(v);
  dv.set_decorations({create<ast::BindingDecoration>(0, Source{}),
                      create<ast::SetDecoration>(0, Source{})});

  func->add_referenced_module_variable(&dv);

  auto ext = gen.GatherExtensionData(func);
  EXPECT_TRUE(ext.has_texture_1d);
}

TEST_F(EsslGeneratorImplTest, HasStorageTexture1DArray) {
  auto* func = create<ast::Function>("my_func", ast::VariableList{}, ty.void_,
                                     create<ast::BlockStatement>());
  func->set_decorations(
      {create<ast::StageDecoration>(ast::PipelineStage::kVertex, Source{})});
  mod->AddFunction(func);

  ast::type::StorageTextureType store(ast::type::TextureDimension::k1dArray,
                                      ast::AccessControl::kReadOnly,
                                      ast::type::ImageFormat::kR32Float);
  auto* v = Var("v", ast::StorageClass::kUniformConstant, &store);
  ast::DecoratedVariable dv(v);
  dv.set_decorations({create<ast::BindingDecoration>(0, Source{}),
                      create<ast::SetDecoration>(0, Source{})});

  func->add_referenced_module_variable(&dv);

  auto ext = gen.GatherExtensionData(func);
  EXPECT_TRUE(ext.has_texture_1d);
}

}  // namespace
}  // namespace essl
}  // namespace writer
}  // namespace tint

