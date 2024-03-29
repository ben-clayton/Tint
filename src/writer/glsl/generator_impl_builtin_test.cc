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

#include "gmock/gmock.h"
#include "src/ast/call_statement.h"
#include "src/ast/stage_attribute.h"
#include "src/sem/call.h"
#include "src/writer/glsl/test_helper.h"

namespace tint {
namespace writer {
namespace glsl {
namespace {

using BuiltinType = sem::BuiltinType;

using ::testing::HasSubstr;

using GlslGeneratorImplTest_Builtin = TestHelper;

enum class ParamType {
  kF32,
  kU32,
  kBool,
};

struct BuiltinData {
  BuiltinType builtin;
  ParamType type;
  const char* glsl_name;
};
inline std::ostream& operator<<(std::ostream& out, BuiltinData data) {
  out << data.glsl_name;
  switch (data.type) {
    case ParamType::kF32:
      out << "f32";
      break;
    case ParamType::kU32:
      out << "u32";
      break;
    case ParamType::kBool:
      out << "bool";
      break;
  }
  out << ">";
  return out;
}

const ast::CallExpression* GenerateCall(BuiltinType builtin,
                                        ParamType type,
                                        ProgramBuilder* builder) {
  std::string name;
  std::ostringstream str(name);
  str << builtin;
  switch (builtin) {
    case BuiltinType::kAcos:
    case BuiltinType::kAsin:
    case BuiltinType::kAtan:
    case BuiltinType::kCeil:
    case BuiltinType::kCos:
    case BuiltinType::kCosh:
    case BuiltinType::kDpdx:
    case BuiltinType::kDpdxCoarse:
    case BuiltinType::kDpdxFine:
    case BuiltinType::kDpdy:
    case BuiltinType::kDpdyCoarse:
    case BuiltinType::kDpdyFine:
    case BuiltinType::kExp:
    case BuiltinType::kExp2:
    case BuiltinType::kFloor:
    case BuiltinType::kFract:
    case BuiltinType::kFwidth:
    case BuiltinType::kFwidthCoarse:
    case BuiltinType::kFwidthFine:
    case BuiltinType::kInverseSqrt:
    case BuiltinType::kIsFinite:
    case BuiltinType::kIsInf:
    case BuiltinType::kIsNan:
    case BuiltinType::kIsNormal:
    case BuiltinType::kLength:
    case BuiltinType::kLog:
    case BuiltinType::kLog2:
    case BuiltinType::kNormalize:
    case BuiltinType::kRound:
    case BuiltinType::kSin:
    case BuiltinType::kSinh:
    case BuiltinType::kSqrt:
    case BuiltinType::kTan:
    case BuiltinType::kTanh:
    case BuiltinType::kTrunc:
    case BuiltinType::kSign:
      return builder->Call(str.str(), "f2");
    case BuiltinType::kLdexp:
      return builder->Call(str.str(), "f2", "i2");
    case BuiltinType::kAtan2:
    case BuiltinType::kDot:
    case BuiltinType::kDistance:
    case BuiltinType::kPow:
    case BuiltinType::kReflect:
    case BuiltinType::kStep:
      return builder->Call(str.str(), "f2", "f2");
    case BuiltinType::kCross:
      return builder->Call(str.str(), "f3", "f3");
    case BuiltinType::kFma:
    case BuiltinType::kMix:
    case BuiltinType::kFaceForward:
    case BuiltinType::kSmoothStep:
      return builder->Call(str.str(), "f2", "f2", "f2");
    case BuiltinType::kAll:
    case BuiltinType::kAny:
      return builder->Call(str.str(), "b2");
    case BuiltinType::kAbs:
      if (type == ParamType::kF32) {
        return builder->Call(str.str(), "f2");
      } else {
        return builder->Call(str.str(), "u2");
      }
    case BuiltinType::kCountOneBits:
    case BuiltinType::kReverseBits:
      return builder->Call(str.str(), "u2");
    case BuiltinType::kMax:
    case BuiltinType::kMin:
      if (type == ParamType::kF32) {
        return builder->Call(str.str(), "f2", "f2");
      } else {
        return builder->Call(str.str(), "u2", "u2");
      }
    case BuiltinType::kClamp:
      if (type == ParamType::kF32) {
        return builder->Call(str.str(), "f2", "f2", "f2");
      } else {
        return builder->Call(str.str(), "u2", "u2", "u2");
      }
    case BuiltinType::kSelect:
      return builder->Call(str.str(), "f2", "f2", "b2");
    case BuiltinType::kDeterminant:
      return builder->Call(str.str(), "m2x2");
    case BuiltinType::kTranspose:
      return builder->Call(str.str(), "m3x2");
    default:
      break;
  }
  return nullptr;
}
using GlslBuiltinTest = TestParamHelper<BuiltinData>;
TEST_P(GlslBuiltinTest, Emit) {
  auto param = GetParam();

  Global("f2", ty.vec2<f32>(), ast::StorageClass::kPrivate);
  Global("f3", ty.vec3<f32>(), ast::StorageClass::kPrivate);
  Global("u2", ty.vec2<u32>(), ast::StorageClass::kPrivate);
  Global("i2", ty.vec2<i32>(), ast::StorageClass::kPrivate);
  Global("b2", ty.vec2<bool>(), ast::StorageClass::kPrivate);
  Global("m2x2", ty.mat2x2<f32>(), ast::StorageClass::kPrivate);
  Global("m3x2", ty.mat3x2<f32>(), ast::StorageClass::kPrivate);

  auto* call = GenerateCall(param.builtin, param.type, this);
  ASSERT_NE(nullptr, call) << "Unhandled builtin";
  Func("func", {}, ty.void_(), {CallStmt(call)},
       {create<ast::StageAttribute>(ast::PipelineStage::kFragment)});

  GeneratorImpl& gen = Build();

  auto* sem = program->Sem().Get(call);
  ASSERT_NE(sem, nullptr);
  auto* target = sem->Target();
  ASSERT_NE(target, nullptr);
  auto* builtin = target->As<sem::Builtin>();
  ASSERT_NE(builtin, nullptr);

  EXPECT_EQ(gen.generate_builtin_name(builtin), param.glsl_name);
}
INSTANTIATE_TEST_SUITE_P(
    GlslGeneratorImplTest_Builtin,
    GlslBuiltinTest,
    testing::Values(
        BuiltinData{BuiltinType::kAbs, ParamType::kF32, "abs"},
        BuiltinData{BuiltinType::kAbs, ParamType::kU32, "abs"},
        BuiltinData{BuiltinType::kAcos, ParamType::kF32, "acos"},
        BuiltinData{BuiltinType::kAll, ParamType::kBool, "all"},
        BuiltinData{BuiltinType::kAny, ParamType::kBool, "any"},
        BuiltinData{BuiltinType::kAsin, ParamType::kF32, "asin"},
        BuiltinData{BuiltinType::kAtan, ParamType::kF32, "atan"},
        BuiltinData{BuiltinType::kAtan2, ParamType::kF32, "atan"},
        BuiltinData{BuiltinType::kCeil, ParamType::kF32, "ceil"},
        BuiltinData{BuiltinType::kClamp, ParamType::kF32, "clamp"},
        BuiltinData{BuiltinType::kClamp, ParamType::kU32, "clamp"},
        BuiltinData{BuiltinType::kCos, ParamType::kF32, "cos"},
        BuiltinData{BuiltinType::kCosh, ParamType::kF32, "cosh"},
        BuiltinData{BuiltinType::kCountOneBits, ParamType::kU32, "countbits"},
        BuiltinData{BuiltinType::kCross, ParamType::kF32, "cross"},
        BuiltinData{BuiltinType::kDeterminant, ParamType::kF32, "determinant"},
        BuiltinData{BuiltinType::kDistance, ParamType::kF32, "distance"},
        BuiltinData{BuiltinType::kDot, ParamType::kF32, "dot"},
        BuiltinData{BuiltinType::kDpdx, ParamType::kF32, "ddx"},
        BuiltinData{BuiltinType::kDpdxCoarse, ParamType::kF32, "ddx_coarse"},
        BuiltinData{BuiltinType::kDpdxFine, ParamType::kF32, "ddx_fine"},
        BuiltinData{BuiltinType::kDpdy, ParamType::kF32, "ddy"},
        BuiltinData{BuiltinType::kDpdyCoarse, ParamType::kF32, "ddy_coarse"},
        BuiltinData{BuiltinType::kDpdyFine, ParamType::kF32, "ddy_fine"},
        BuiltinData{BuiltinType::kExp, ParamType::kF32, "exp"},
        BuiltinData{BuiltinType::kExp2, ParamType::kF32, "exp2"},
        BuiltinData{BuiltinType::kFaceForward, ParamType::kF32, "faceforward"},
        BuiltinData{BuiltinType::kFloor, ParamType::kF32, "floor"},
        BuiltinData{BuiltinType::kFma, ParamType::kF32, "mad"},
        BuiltinData{BuiltinType::kFract, ParamType::kF32, "frac"},
        BuiltinData{BuiltinType::kFwidth, ParamType::kF32, "fwidth"},
        BuiltinData{BuiltinType::kFwidthCoarse, ParamType::kF32, "fwidth"},
        BuiltinData{BuiltinType::kFwidthFine, ParamType::kF32, "fwidth"},
        BuiltinData{BuiltinType::kInverseSqrt, ParamType::kF32, "rsqrt"},
        BuiltinData{BuiltinType::kIsFinite, ParamType::kF32, "isfinite"},
        BuiltinData{BuiltinType::kIsInf, ParamType::kF32, "isinf"},
        BuiltinData{BuiltinType::kIsNan, ParamType::kF32, "isnan"},
        BuiltinData{BuiltinType::kLdexp, ParamType::kF32, "ldexp"},
        BuiltinData{BuiltinType::kLength, ParamType::kF32, "length"},
        BuiltinData{BuiltinType::kLog, ParamType::kF32, "log"},
        BuiltinData{BuiltinType::kLog2, ParamType::kF32, "log2"},
        BuiltinData{BuiltinType::kMax, ParamType::kF32, "max"},
        BuiltinData{BuiltinType::kMax, ParamType::kU32, "max"},
        BuiltinData{BuiltinType::kMin, ParamType::kF32, "min"},
        BuiltinData{BuiltinType::kMin, ParamType::kU32, "min"},
        BuiltinData{BuiltinType::kMix, ParamType::kF32, "mix"},
        BuiltinData{BuiltinType::kNormalize, ParamType::kF32, "normalize"},
        BuiltinData{BuiltinType::kPow, ParamType::kF32, "pow"},
        BuiltinData{BuiltinType::kReflect, ParamType::kF32, "reflect"},
        BuiltinData{BuiltinType::kReverseBits, ParamType::kU32, "reversebits"},
        BuiltinData{BuiltinType::kRound, ParamType::kU32, "round"},
        BuiltinData{BuiltinType::kSign, ParamType::kF32, "sign"},
        BuiltinData{BuiltinType::kSin, ParamType::kF32, "sin"},
        BuiltinData{BuiltinType::kSinh, ParamType::kF32, "sinh"},
        BuiltinData{BuiltinType::kSmoothStep, ParamType::kF32, "smoothstep"},
        BuiltinData{BuiltinType::kSqrt, ParamType::kF32, "sqrt"},
        BuiltinData{BuiltinType::kStep, ParamType::kF32, "step"},
        BuiltinData{BuiltinType::kTan, ParamType::kF32, "tan"},
        BuiltinData{BuiltinType::kTanh, ParamType::kF32, "tanh"},
        BuiltinData{BuiltinType::kTranspose, ParamType::kF32, "transpose"},
        BuiltinData{BuiltinType::kTrunc, ParamType::kF32, "trunc"}));

TEST_F(GlslGeneratorImplTest_Builtin, DISABLED_Builtin_IsNormal) {
  FAIL();
}

TEST_F(GlslGeneratorImplTest_Builtin, Builtin_Call) {
  auto* call = Call("dot", "param1", "param2");

  Global("param1", ty.vec3<f32>(), ast::StorageClass::kPrivate);
  Global("param2", ty.vec3<f32>(), ast::StorageClass::kPrivate);

  WrapInFunction(CallStmt(call));

  GeneratorImpl& gen = Build();

  gen.increment_indent();
  std::stringstream out;
  ASSERT_TRUE(gen.EmitExpression(out, call)) << gen.error();
  EXPECT_EQ(out.str(), "dot(param1, param2)");
}

TEST_F(GlslGeneratorImplTest_Builtin, Select_Scalar) {
  auto* call = Call("select", 1.0f, 2.0f, true);
  WrapInFunction(CallStmt(call));
  GeneratorImpl& gen = Build();

  gen.increment_indent();
  std::stringstream out;
  ASSERT_TRUE(gen.EmitExpression(out, call)) << gen.error();
  EXPECT_EQ(out.str(), "(true ? 2.0f : 1.0f)");
}

TEST_F(GlslGeneratorImplTest_Builtin, Select_Vector) {
  auto* call =
      Call("select", vec2<i32>(1, 2), vec2<i32>(3, 4), vec2<bool>(true, false));
  WrapInFunction(CallStmt(call));
  GeneratorImpl& gen = Build();

  gen.increment_indent();
  std::stringstream out;
  ASSERT_TRUE(gen.EmitExpression(out, call)) << gen.error();
  EXPECT_EQ(out.str(), "(bvec2(true, false) ? ivec2(3, 4) : ivec2(1, 2))");
}

#if 0
TEST_F(GlslGeneratorImplTest_Builtin, Modf_Scalar) {
  auto* res = Var("res", ty.f32());
  auto* call = Call("modf", 1.0f, AddressOf(res));
  WrapInFunction(res, call);

  GeneratorImpl& gen = SanitizeAndBuild();

  ASSERT_TRUE(gen.Generate()) << gen.error();
  EXPECT_THAT(gen.result(), HasSubstr("modf(1.0f, res)"));
}

TEST_F(GlslGeneratorImplTest_Builtin, Modf_Vector) {
  auto* res = Var("res", ty.vec3<f32>());
  auto* call = Call("modf", vec3<f32>(), AddressOf(res));
  WrapInFunction(res, call);

  GeneratorImpl& gen = SanitizeAndBuild();

  ASSERT_TRUE(gen.Generate()) << gen.error();
  EXPECT_THAT(gen.result(), HasSubstr("modf(vec3(0.0f, 0.0f, 0.0f), res)"));
}

TEST_F(GlslGeneratorImplTest_Builtin, Frexp_Scalar_i32) {
  auto* exp = Var("exp", ty.i32());
  auto* call = Call("frexp", 1.0f, AddressOf(exp));
  WrapInFunction(exp, call);

  GeneratorImpl& gen = SanitizeAndBuild();

  ASSERT_TRUE(gen.Generate()) << gen.error();
  EXPECT_THAT(gen.result(), HasSubstr(R"(
  float tint_tmp;
  float tint_tmp_1 = frexp(1.0f, tint_tmp);
  exp = int(tint_tmp);
  tint_tmp_1;
)"));
}

TEST_F(GlslGeneratorImplTest_Builtin, Frexp_Vector_i32) {
  auto* res = Var("res", ty.vec3<i32>());
  auto* call = Call("frexp", vec3<f32>(), AddressOf(res));
  WrapInFunction(res, call);

  GeneratorImpl& gen = SanitizeAndBuild();

  ASSERT_TRUE(gen.Generate()) << gen.error();
  EXPECT_THAT(gen.result(), HasSubstr(R"(
  vec3 tint_tmp;
  vec3 tint_tmp_1 = frexp(vec3(0.0f, 0.0f, 0.0f), tint_tmp);
  res = ivec3(tint_tmp);
  tint_tmp_1;
)"));
}

TEST_F(GlslGeneratorImplTest_Builtin, IsNormal_Scalar) {
  auto* val = Var("val", ty.f32());
  auto* call = Call("isNormal", val);
  WrapInFunction(val, call);

  GeneratorImpl& gen = SanitizeAndBuild();

  ASSERT_TRUE(gen.Generate()) << gen.error();
  EXPECT_THAT(gen.result(), HasSubstr(R"(
  uint tint_isnormal_exponent = asuint(val) & 0x7f80000;
  uint tint_isnormal_clamped = clamp(tint_isnormal_exponent, 0x0080000, 0x7f00000);
  (tint_isnormal_clamped == tint_isnormal_exponent);
)"));
}

TEST_F(GlslGeneratorImplTest_Builtin, IsNormal_Vector) {
  auto* val = Var("val", ty.vec3<f32>());
  auto* call = Call("isNormal", val);
  WrapInFunction(val, call);

  GeneratorImpl& gen = SanitizeAndBuild();

  ASSERT_TRUE(gen.Generate()) << gen.error();
  EXPECT_THAT(gen.result(), HasSubstr(R"(
  uvec3 tint_isnormal_exponent = asuint(val) & 0x7f80000;
  uvec3 tint_isnormal_clamped = clamp(tint_isnormal_exponent, 0x0080000, 0x7f00000);
  (tint_isnormal_clamped == tint_isnormal_exponent);
)"));
}
#endif

TEST_F(GlslGeneratorImplTest_Builtin, Degrees_Scalar) {
  auto* val = Var("val", ty.f32());
  auto* call = Call("degrees", val);
  WrapInFunction(val, call);

  GeneratorImpl& gen = SanitizeAndBuild();

  ASSERT_TRUE(gen.Generate()) << gen.error();
  EXPECT_EQ(gen.result(), R"(#version 310 es

float tint_degrees(float param_0) {
  return param_0 * 57.295779513082322865;
}


void test_function() {
  float val = 0.0f;
  float tint_symbol = tint_degrees(val);
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  test_function();
  return;
}
)");
}

TEST_F(GlslGeneratorImplTest_Builtin, Degrees_Vector) {
  auto* val = Var("val", ty.vec3<f32>());
  auto* call = Call("degrees", val);
  WrapInFunction(val, call);

  GeneratorImpl& gen = SanitizeAndBuild();

  ASSERT_TRUE(gen.Generate()) << gen.error();
  EXPECT_EQ(gen.result(), R"(#version 310 es

vec3 tint_degrees(vec3 param_0) {
  return param_0 * 57.295779513082322865;
}


void test_function() {
  vec3 val = vec3(0.0f, 0.0f, 0.0f);
  vec3 tint_symbol = tint_degrees(val);
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  test_function();
  return;
}
)");
}

TEST_F(GlslGeneratorImplTest_Builtin, Radians_Scalar) {
  auto* val = Var("val", ty.f32());
  auto* call = Call("radians", val);
  WrapInFunction(val, call);

  GeneratorImpl& gen = SanitizeAndBuild();

  ASSERT_TRUE(gen.Generate()) << gen.error();
  EXPECT_EQ(gen.result(), R"(#version 310 es

float tint_radians(float param_0) {
  return param_0 * 0.017453292519943295474;
}


void test_function() {
  float val = 0.0f;
  float tint_symbol = tint_radians(val);
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  test_function();
  return;
}
)");
}

TEST_F(GlslGeneratorImplTest_Builtin, Radians_Vector) {
  auto* val = Var("val", ty.vec3<f32>());
  auto* call = Call("radians", val);
  WrapInFunction(val, call);

  GeneratorImpl& gen = SanitizeAndBuild();

  ASSERT_TRUE(gen.Generate()) << gen.error();
  EXPECT_EQ(gen.result(), R"(#version 310 es

vec3 tint_radians(vec3 param_0) {
  return param_0 * 0.017453292519943295474;
}


void test_function() {
  vec3 val = vec3(0.0f, 0.0f, 0.0f);
  vec3 tint_symbol = tint_radians(val);
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  test_function();
  return;
}
)");
}

#if 0
TEST_F(GlslGeneratorImplTest_Builtin, Pack4x8Snorm) {
  auto* call = Call("pack4x8snorm", "p1");
  Global("p1", ty.vec4<f32>(), ast::StorageClass::kPrivate);
  WrapInFunction(CallStmt(call));
  GeneratorImpl& gen = Build();

  gen.increment_indent();
  std::stringstream out;
  ASSERT_TRUE(gen.EmitExpression(out, call)) << gen.error();
  EXPECT_THAT(gen.result(), HasSubstr("ivec4 tint_tmp = ivec4(round(clamp(p1, "
                                      "-1.0, 1.0) * 127.0)) & 0xff;"));
  EXPECT_THAT(out.str(), HasSubstr("asuint(tint_tmp.x | tint_tmp.y << 8 | "
                                   "tint_tmp.z << 16 | tint_tmp.w << 24)"));
}

TEST_F(GlslGeneratorImplTest_Builtin, Pack4x8Unorm) {
  auto* call = Call("pack4x8unorm", "p1");
  Global("p1", ty.vec4<f32>(), ast::StorageClass::kPrivate);
  WrapInFunction(CallStmt(call));
  GeneratorImpl& gen = Build();

  gen.increment_indent();
  std::stringstream out;
  ASSERT_TRUE(gen.EmitExpression(out, call)) << gen.error();
  EXPECT_THAT(gen.result(), HasSubstr("uvec4 tint_tmp = uvec4(round(clamp(p1, "
                                      "0.0, 1.0) * 255.0));"));
  EXPECT_THAT(out.str(), HasSubstr("(tint_tmp.x | tint_tmp.y << 8 | "
                                   "tint_tmp.z << 16 | tint_tmp.w << 24)"));
}

TEST_F(GlslGeneratorImplTest_Builtin, Pack2x16Snorm) {
  auto* call = Call("pack2x16snorm", "p1");
  Global("p1", ty.vec2<f32>(), ast::StorageClass::kPrivate);
  WrapInFunction(CallStmt(call));
  GeneratorImpl& gen = Build();

  gen.increment_indent();
  std::stringstream out;
  ASSERT_TRUE(gen.EmitExpression(out, call)) << gen.error();
  EXPECT_THAT(gen.result(), HasSubstr("int2 tint_tmp = int2(round(clamp(p1, "
                                      "-1.0, 1.0) * 32767.0)) & 0xffff;"));
  EXPECT_THAT(out.str(), HasSubstr("asuint(tint_tmp.x | tint_tmp.y << 16)"));
}

TEST_F(GlslGeneratorImplTest_Builtin, Pack2x16Unorm) {
  auto* call = Call("pack2x16unorm", "p1");
  Global("p1", ty.vec2<f32>(), ast::StorageClass::kPrivate);
  WrapInFunction(CallStmt(call));
  GeneratorImpl& gen = Build();

  gen.increment_indent();
  std::stringstream out;
  ASSERT_TRUE(gen.EmitExpression(out, call)) << gen.error();
  EXPECT_THAT(gen.result(), HasSubstr("uint2 tint_tmp = uint2(round(clamp(p1, "
                                      "0.0, 1.0) * 65535.0));"));
  EXPECT_THAT(out.str(), HasSubstr("(tint_tmp.x | tint_tmp.y << 16)"));
}

TEST_F(GlslGeneratorImplTest_Builtin, Pack2x16Float) {
  auto* call = Call("pack2x16float", "p1");
  Global("p1", ty.vec2<f32>(), ast::StorageClass::kPrivate);
  WrapInFunction(CallStmt(call));
  GeneratorImpl& gen = Build();

  gen.increment_indent();
  std::stringstream out;
  ASSERT_TRUE(gen.EmitExpression(out, call)) << gen.error();
  EXPECT_THAT(gen.result(), HasSubstr("uint2 tint_tmp = f32tof16(p1);"));
  EXPECT_THAT(out.str(), HasSubstr("(tint_tmp.x | tint_tmp.y << 16)"));
}

TEST_F(GlslGeneratorImplTest_Builtin, Unpack4x8Snorm) {
  auto* call = Call("unpack4x8snorm", "p1");
  Global("p1", ty.u32(), ast::StorageClass::kPrivate);
  WrapInFunction(CallStmt(call));
  GeneratorImpl& gen = Build();

  gen.increment_indent();
  std::stringstream out;
  ASSERT_TRUE(gen.EmitExpression(out, call)) << gen.error();
  EXPECT_THAT(gen.result(), HasSubstr("int tint_tmp_1 = int(p1);"));
  EXPECT_THAT(gen.result(),
              HasSubstr("ivec4 tint_tmp = ivec4(tint_tmp_1 << 24, tint_tmp_1 "
                        "<< 16, tint_tmp_1 << 8, tint_tmp_1) >> 24;"));
  EXPECT_THAT(out.str(),
              HasSubstr("clamp(float4(tint_tmp) / 127.0, -1.0, 1.0)"));
}

TEST_F(GlslGeneratorImplTest_Builtin, Unpack4x8Unorm) {
  auto* call = Call("unpack4x8unorm", "p1");
  Global("p1", ty.u32(), ast::StorageClass::kPrivate);
  WrapInFunction(CallStmt(call));
  GeneratorImpl& gen = Build();

  gen.increment_indent();
  std::stringstream out;
  ASSERT_TRUE(gen.EmitExpression(out, call)) << gen.error();
  EXPECT_THAT(gen.result(), HasSubstr("uint tint_tmp_1 = p1;"));
  EXPECT_THAT(
      gen.result(),
      HasSubstr("uvec4 tint_tmp = uvec4(tint_tmp_1 & 0xff, (tint_tmp_1 >> "
                "8) & 0xff, (tint_tmp_1 >> 16) & 0xff, tint_tmp_1 >> 24);"));
  EXPECT_THAT(out.str(), HasSubstr("float4(tint_tmp) / 255.0"));
}

TEST_F(GlslGeneratorImplTest_Builtin, Unpack2x16Snorm) {
  auto* call = Call("unpack2x16snorm", "p1");
  Global("p1", ty.u32(), ast::StorageClass::kPrivate);
  WrapInFunction(CallStmt(call));
  GeneratorImpl& gen = Build();

  gen.increment_indent();
  std::stringstream out;
  ASSERT_TRUE(gen.EmitExpression(out, call)) << gen.error();
  EXPECT_THAT(gen.result(), HasSubstr("int tint_tmp_1 = int(p1);"));
  EXPECT_THAT(
      gen.result(),
      HasSubstr("int2 tint_tmp = int2(tint_tmp_1 << 16, tint_tmp_1) >> 16;"));
  EXPECT_THAT(out.str(),
              HasSubstr("clamp(float2(tint_tmp) / 32767.0, -1.0, 1.0)"));
}

TEST_F(GlslGeneratorImplTest_Builtin, Unpack2x16Unorm) {
  auto* call = Call("unpack2x16unorm", "p1");
  Global("p1", ty.u32(), ast::StorageClass::kPrivate);
  WrapInFunction(CallStmt(call));
  GeneratorImpl& gen = Build();

  gen.increment_indent();
  std::stringstream out;
  ASSERT_TRUE(gen.EmitExpression(out, call)) << gen.error();
  EXPECT_THAT(gen.result(), HasSubstr("uint tint_tmp_1 = p1;"));
  EXPECT_THAT(gen.result(),
              HasSubstr("uint2 tint_tmp = uint2(tint_tmp_1 & 0xffff, "
                        "tint_tmp_1 >> 16);"));
  EXPECT_THAT(out.str(), HasSubstr("float2(tint_tmp) / 65535.0"));
}

TEST_F(GlslGeneratorImplTest_Builtin, Unpack2x16Float) {
  auto* call = Call("unpack2x16float", "p1");
  Global("p1", ty.u32(), ast::StorageClass::kPrivate);
  WrapInFunction(CallStmt(call));
  GeneratorImpl& gen = Build();

  gen.increment_indent();
  std::stringstream out;
  ASSERT_TRUE(gen.EmitExpression(out, call)) << gen.error();
  EXPECT_THAT(gen.result(), HasSubstr("uint tint_tmp = p1;"));
  EXPECT_THAT(out.str(),
              HasSubstr("f16tof32(uint2(tint_tmp & 0xffff, tint_tmp >> 16))"));
}

#endif

TEST_F(GlslGeneratorImplTest_Builtin, StorageBarrier) {
  Func("main", {}, ty.void_(),
       {CallStmt(Call("storageBarrier"))},
       {
           Stage(ast::PipelineStage::kCompute),
           WorkgroupSize(1),
       });

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.Generate()) << gen.error();
  EXPECT_EQ(gen.result(), R"(#version 310 es

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  { barrier(); memoryBarrierBuffer(); };
  return;
}
)");
}

TEST_F(GlslGeneratorImplTest_Builtin, WorkgroupBarrier) {
  Func("main", {}, ty.void_(),
       {CallStmt(Call("workgroupBarrier"))},
       {
           Stage(ast::PipelineStage::kCompute),
           WorkgroupSize(1),
       });

  GeneratorImpl& gen = Build();

  ASSERT_TRUE(gen.Generate()) << gen.error();
  EXPECT_EQ(gen.result(), R"(#version 310 es

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  barrier();
  return;
}
)");
}

TEST_F(GlslGeneratorImplTest_Builtin, DotI32) {
  Global("v", ty.vec3<i32>(), ast::StorageClass::kPrivate);
  WrapInFunction(CallStmt(Call("dot", "v", "v")));

  GeneratorImpl& gen = SanitizeAndBuild();

  ASSERT_TRUE(gen.Generate()) << gen.error();
  EXPECT_EQ(gen.result(), R"(#version 310 es

int tint_int_dot(ivec3 a, ivec3 b) {
  return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

ivec3 v = ivec3(0, 0, 0);
void test_function() {
  tint_int_dot(v, v);
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  test_function();
  return;
}
)");
}

TEST_F(GlslGeneratorImplTest_Builtin, DotU32) {
  Global("v", ty.vec3<u32>(), ast::StorageClass::kPrivate);
  WrapInFunction(CallStmt(Call("dot", "v", "v")));

  GeneratorImpl& gen = SanitizeAndBuild();

  ASSERT_TRUE(gen.Generate()) << gen.error();
  EXPECT_EQ(gen.result(), R"(#version 310 es

uint tint_int_dot(uvec3 a, uvec3 b) {
  return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

uvec3 v = uvec3(0u, 0u, 0u);
void test_function() {
  tint_int_dot(v, v);
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  test_function();
  return;
}
)");
}

}  // namespace
}  // namespace glsl
}  // namespace writer
}  // namespace tint
