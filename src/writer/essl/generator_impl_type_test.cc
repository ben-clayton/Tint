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

#include "src/ast/struct.h"
#include "src/ast/struct_block_decoration.h"
#include "src/ast/struct_member.h"
#include "src/ast/struct_member_offset_decoration.h"
#include "src/ast/type/alias_type.h"
#include "src/ast/type/depth_texture_type.h"
#include "src/ast/type/multisampled_texture_type.h"
#include "src/ast/type/pointer_type.h"
#include "src/ast/type/sampled_texture_type.h"
#include "src/ast/type/storage_texture_type.h"
#include "src/ast/type/struct_type.h"
#include "src/writer/essl/test_helper.h"

namespace tint {
namespace writer {
namespace essl {
namespace {

using EsslGeneratorImplTest_Type = TestHelper;

TEST_F(EsslGeneratorImplTest_Type, EmitType_Alias) {
  ast::type::AliasType alias("alias", ty.f32);

  ASSERT_TRUE(gen.EmitType(out, &alias, "")) << gen.error();
  EXPECT_EQ(result(), "alias");
}

TEST_F(EsslGeneratorImplTest_Type, EmitType_Array) {
  ast::type::ArrayType a(ty.bool_, 4);

  ASSERT_TRUE(gen.EmitType(out, &a, "ary")) << gen.error();
  EXPECT_EQ(result(), "bool ary[4]");
}

TEST_F(EsslGeneratorImplTest_Type, EmitType_ArrayOfArray) {
  ast::type::ArrayType a(ty.bool_, 4);
  ast::type::ArrayType c(&a, 5);

  ASSERT_TRUE(gen.EmitType(out, &c, "ary")) << gen.error();
  EXPECT_EQ(result(), "bool ary[5][4]");
}

// TODO(dsinclair): Is this possible? What order should it output in?
TEST_F(EsslGeneratorImplTest_Type,
       DISABLED_EmitType_ArrayOfArrayOfRuntimeArray) {
  ast::type::ArrayType a(ty.bool_, 4);
  ast::type::ArrayType c(&a, 5);
  ast::type::ArrayType d(&c);

  ASSERT_TRUE(gen.EmitType(out, &c, "ary")) << gen.error();
  EXPECT_EQ(result(), "bool ary[5][4][1]");
}

TEST_F(EsslGeneratorImplTest_Type, EmitType_ArrayOfArrayOfArray) {
  ast::type::ArrayType a(ty.bool_, 4);
  ast::type::ArrayType c(&a, 5);
  ast::type::ArrayType d(&c, 6);

  ASSERT_TRUE(gen.EmitType(out, &d, "ary")) << gen.error();
  EXPECT_EQ(result(), "bool ary[6][5][4]");
}

TEST_F(EsslGeneratorImplTest_Type, EmitType_Array_WithoutName) {
  ast::type::ArrayType a(ty.bool_, 4);

  ASSERT_TRUE(gen.EmitType(out, &a, "")) << gen.error();
  EXPECT_EQ(result(), "bool[4]");
}

TEST_F(EsslGeneratorImplTest_Type, DISABLED_EmitType_RuntimeArray) {
  ast::type::ArrayType a(ty.bool_);

  ASSERT_TRUE(gen.EmitType(out, &a, "ary")) << gen.error();
  EXPECT_EQ(result(), "bool ary[]");
}

TEST_F(EsslGeneratorImplTest_Type, EmitType_Bool) {
  ASSERT_TRUE(gen.EmitType(out, ty.bool_, "")) << gen.error();
  EXPECT_EQ(result(), "bool");
}

TEST_F(EsslGeneratorImplTest_Type, EmitType_F32) {
  ASSERT_TRUE(gen.EmitType(out, ty.f32, "")) << gen.error();
  EXPECT_EQ(result(), "float");
}

TEST_F(EsslGeneratorImplTest_Type, EmitType_I32) {
  ASSERT_TRUE(gen.EmitType(out, ty.i32, "")) << gen.error();
  EXPECT_EQ(result(), "int");
}

TEST_F(EsslGeneratorImplTest_Type, EmitType_Matrix) {
  ast::type::MatrixType m(ty.f32, 3, 2);

  ASSERT_TRUE(gen.EmitType(out, &m, "")) << gen.error();
  EXPECT_EQ(result(), "mat2x3");
}

// TODO(dsinclair): How to annotate as workgroup?
TEST_F(EsslGeneratorImplTest_Type, DISABLED_EmitType_Pointer) {
  ast::type::PointerType p(ty.f32, ast::StorageClass::kWorkgroup);

  ASSERT_TRUE(gen.EmitType(out, &p, "")) << gen.error();
  EXPECT_EQ(result(), "float*");
}

TEST_F(EsslGeneratorImplTest_Type, EmitType_StructDecl) {
  ast::StructMemberList members;
  members.push_back(create<ast::StructMember>(
      "a", ty.i32, ast::StructMemberDecorationList{}));

  ast::StructMemberDecorationList b_deco;
  b_deco.push_back(create<ast::StructMemberOffsetDecoration>(4, Source{}));
  members.push_back(create<ast::StructMember>("b", ty.f32, b_deco));

  auto* str = create<ast::Struct>();
  str->set_members(members);

  ast::type::StructType s("S", str);
  ASSERT_TRUE(gen.EmitStructType(out, &s, "S")) << gen.error();
  EXPECT_EQ(result(), R"(struct S {
  int a;
  float b;
};
)");
}

TEST_F(EsslGeneratorImplTest_Type, EmitType_Struct) {
  ast::StructMemberList members;
  members.push_back(create<ast::StructMember>(
      "a", ty.i32, ast::StructMemberDecorationList{}));

  ast::StructMemberDecorationList b_deco;
  b_deco.push_back(create<ast::StructMemberOffsetDecoration>(4, Source{}));
  members.push_back(create<ast::StructMember>("b", ty.f32, b_deco));

  auto* str = create<ast::Struct>();
  str->set_members(members);

  ast::type::StructType s("S", str);

  ASSERT_TRUE(gen.EmitType(out, &s, "")) << gen.error();
  EXPECT_EQ(result(), "S");
}

TEST_F(EsslGeneratorImplTest_Type, DISABLED_EmitType_Struct_InjectPadding) {
  ast::StructMemberDecorationList decos;
  decos.push_back(create<ast::StructMemberOffsetDecoration>(4, Source{}));

  ast::StructMemberList members;
  members.push_back(create<ast::StructMember>("a", ty.i32, decos));

  decos.push_back(create<ast::StructMemberOffsetDecoration>(32, Source{}));
  members.push_back(create<ast::StructMember>("b", ty.f32, decos));

  decos.push_back(create<ast::StructMemberOffsetDecoration>(128, Source{}));
  members.push_back(create<ast::StructMember>("c", ty.f32, decos));

  auto* str = create<ast::Struct>();
  str->set_members(members);

  ast::type::StructType s("S", str);

  ASSERT_TRUE(gen.EmitType(out, &s, "")) << gen.error();
  EXPECT_EQ(result(), R"(struct {
  int8_t pad_0[4];
  int a;
  int8_t pad_1[24];
  float b;
  int8_t pad_2[92];
  float c;
})");
}

// TODO(dsinclair): How to translate [[block]]
TEST_F(EsslGeneratorImplTest_Type, DISABLED_EmitType_Struct_WithDecoration) {
  ast::StructMemberList members;
  members.push_back(create<ast::StructMember>(
      "a", ty.i32, ast::StructMemberDecorationList{}));

  ast::StructMemberDecorationList b_deco;
  b_deco.push_back(create<ast::StructMemberOffsetDecoration>(4, Source{}));
  members.push_back(create<ast::StructMember>("b", ty.f32, b_deco));

  ast::StructDecorationList decos;
  decos.push_back(create<ast::StructBlockDecoration>(Source{}));

  auto* str = create<ast::Struct>(decos, members);

  ast::type::StructType s("S", str);

  ASSERT_TRUE(gen.EmitStructType(out, &s, "B")) << gen.error();
  EXPECT_EQ(result(), R"(struct B {
  int a;
  float b;
})");
}

TEST_F(EsslGeneratorImplTest_Type, EmitType_U32) {
  ast::type::U32Type u32;

  ASSERT_TRUE(gen.EmitType(out, &u32, "")) << gen.error();
  EXPECT_EQ(result(), "uint");
}

TEST_F(EsslGeneratorImplTest_Type, EmitType_Vector) {
  ast::type::VectorType v(ty.f32, 3);

  ASSERT_TRUE(gen.EmitType(out, &v, "")) << gen.error();
  EXPECT_EQ(result(), "vec3");
}

TEST_F(EsslGeneratorImplTest_Type, EmitType_Void) {
  ASSERT_TRUE(gen.EmitType(out, ty.void_, "")) << gen.error();
  EXPECT_EQ(result(), "void");
}

TEST_F(EsslGeneratorImplTest_Type, EmitSampler) {
  ast::type::SamplerType sampler(ast::type::SamplerKind::kSampler);

  ASSERT_FALSE(gen.EmitType(out, &sampler, "")) << gen.error();
}

TEST_F(EsslGeneratorImplTest_Type, EmitSamplerComparison) {
  ast::type::SamplerType sampler(ast::type::SamplerKind::kComparisonSampler);

  ASSERT_FALSE(gen.EmitType(out, &sampler, "")) << gen.error();
}

struct EsslDepthTextureData {
  ast::type::TextureDimension dim;
  std::string result;
};
inline std::ostream& operator<<(std::ostream& out, EsslDepthTextureData data) {
  out << data.dim;
  return out;
}
using EsslDepthtexturesTest = TestParamHelper<EsslDepthTextureData>;
TEST_P(EsslDepthtexturesTest, Emit) {
  auto params = GetParam();

  ast::type::DepthTextureType s(params.dim);

  ASSERT_TRUE(gen.EmitType(out, &s, "")) << gen.error();
  EXPECT_EQ(result(), params.result);
}
INSTANTIATE_TEST_SUITE_P(
    EsslGeneratorImplTest_Type,
    EsslDepthtexturesTest,
    testing::Values(EsslDepthTextureData{ast::type::TextureDimension::k2d,
                                         "sampler2DShadow"},
                    EsslDepthTextureData{ast::type::TextureDimension::k2dArray,
                                         "sampler2DArrayShadow"},
                    EsslDepthTextureData{ast::type::TextureDimension::kCube,
                                         "samplerCubeShadow"},
                    EsslDepthTextureData{
                        ast::type::TextureDimension::kCubeArray,
                        "samplerCubeArrayShadow"}));

struct EsslTextureData {
  ast::type::TextureDimension dim;
  std::string result;
};
inline std::ostream& operator<<(std::ostream& out, EsslTextureData data) {
  out << data.dim;
  return out;
}
using EsslSampledtexturesTest = TestParamHelper<EsslTextureData>;
TEST_P(EsslSampledtexturesTest, Emit) {
  auto params = GetParam();

  ast::type::SampledTextureType s(params.dim, ty.f32);

  ASSERT_TRUE(gen.EmitType(out, &s, "")) << gen.error();
  EXPECT_EQ(result(), params.result);
}
INSTANTIATE_TEST_SUITE_P(
    EsslGeneratorImplTest_Type,
    EsslSampledtexturesTest,
    testing::Values(
        EsslTextureData{ast::type::TextureDimension::k2d, "sampler2D"},
        EsslTextureData{ast::type::TextureDimension::k2dArray,
                        "sampler2DArray"},
        EsslTextureData{ast::type::TextureDimension::k3d, "sampler3D"},
        EsslTextureData{ast::type::TextureDimension::kCube, "samplerCube"},
        EsslTextureData{ast::type::TextureDimension::kCubeArray,
                        "samplerCubeArray"}));

TEST_F(EsslGeneratorImplTest_Type, EmitMultisampledTexture) {
  ast::type::MultisampledTextureType s(ast::type::TextureDimension::k2d,
                                       ty.f32);

  ASSERT_TRUE(gen.EmitType(out, &s, "")) << gen.error();
  EXPECT_EQ(result(), "sampler2DMS");
}

struct EsslStorageTextureData {
  ast::type::TextureDimension dim;
  bool ro;
  std::string result;
};
inline std::ostream& operator<<(std::ostream& out,
                                EsslStorageTextureData data) {
  out << data.dim << (data.ro ? "ReadOnly" : "WriteOnly");
  return out;
}
using EsslStoragetexturesTest = TestParamHelper<EsslStorageTextureData>;
TEST_P(EsslStoragetexturesTest, Emit) {
  auto params = GetParam();

  ast::type::StorageTextureType s(params.dim,
                                  params.ro ? ast::AccessControl::kReadOnly
                                            : ast::AccessControl::kWriteOnly,
                                  ast::type::ImageFormat::kR16Float);

  ASSERT_TRUE(gen.EmitType(out, &s, "")) << gen.error();
  EXPECT_EQ(result(), params.result);
}
INSTANTIATE_TEST_SUITE_P(
    EsslGeneratorImplTest_Type,
    EsslStoragetexturesTest,
    testing::Values(
        EsslStorageTextureData{ast::type::TextureDimension::k2d, true,
                               "image2D"},
        EsslStorageTextureData{ast::type::TextureDimension::k2dArray, true,
                               "image2DArray"},
        EsslStorageTextureData{ast::type::TextureDimension::k3d, true,
                               "image3D"},
        EsslStorageTextureData{ast::type::TextureDimension::k2d, false,
                               "image2D"},
        EsslStorageTextureData{ast::type::TextureDimension::k2dArray, false,
                               "image2DArray"},
        EsslStorageTextureData{ast::type::TextureDimension::k3d, false,
                               "image3D"}));

}  // namespace
}  // namespace essl
}  // namespace writer
}  // namespace tint
