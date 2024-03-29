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

////////////////////////////////////////////////////////////////////////////////
// File generated by tools/builtin-gen
// using the template:
//   src/sem/builtin_type.cc.tmpl
// and the builtin defintion file:
//   src/builtins.def
//
// Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#include "src/sem/builtin_type.h"

#include <sstream>

namespace tint {
namespace sem {

BuiltinType ParseBuiltinType(const std::string& name) {
  if (name == "abs") {
    return BuiltinType::kAbs;
  }
  if (name == "acos") {
    return BuiltinType::kAcos;
  }
  if (name == "all") {
    return BuiltinType::kAll;
  }
  if (name == "any") {
    return BuiltinType::kAny;
  }
  if (name == "arrayLength") {
    return BuiltinType::kArrayLength;
  }
  if (name == "asin") {
    return BuiltinType::kAsin;
  }
  if (name == "atan") {
    return BuiltinType::kAtan;
  }
  if (name == "atan2") {
    return BuiltinType::kAtan2;
  }
  if (name == "ceil") {
    return BuiltinType::kCeil;
  }
  if (name == "clamp") {
    return BuiltinType::kClamp;
  }
  if (name == "cos") {
    return BuiltinType::kCos;
  }
  if (name == "cosh") {
    return BuiltinType::kCosh;
  }
  if (name == "countOneBits") {
    return BuiltinType::kCountOneBits;
  }
  if (name == "cross") {
    return BuiltinType::kCross;
  }
  if (name == "degrees") {
    return BuiltinType::kDegrees;
  }
  if (name == "determinant") {
    return BuiltinType::kDeterminant;
  }
  if (name == "distance") {
    return BuiltinType::kDistance;
  }
  if (name == "dot") {
    return BuiltinType::kDot;
  }
  if (name == "dpdx") {
    return BuiltinType::kDpdx;
  }
  if (name == "dpdxCoarse") {
    return BuiltinType::kDpdxCoarse;
  }
  if (name == "dpdxFine") {
    return BuiltinType::kDpdxFine;
  }
  if (name == "dpdy") {
    return BuiltinType::kDpdy;
  }
  if (name == "dpdyCoarse") {
    return BuiltinType::kDpdyCoarse;
  }
  if (name == "dpdyFine") {
    return BuiltinType::kDpdyFine;
  }
  if (name == "exp") {
    return BuiltinType::kExp;
  }
  if (name == "exp2") {
    return BuiltinType::kExp2;
  }
  if (name == "faceForward") {
    return BuiltinType::kFaceForward;
  }
  if (name == "floor") {
    return BuiltinType::kFloor;
  }
  if (name == "fma") {
    return BuiltinType::kFma;
  }
  if (name == "fract") {
    return BuiltinType::kFract;
  }
  if (name == "frexp") {
    return BuiltinType::kFrexp;
  }
  if (name == "fwidth") {
    return BuiltinType::kFwidth;
  }
  if (name == "fwidthCoarse") {
    return BuiltinType::kFwidthCoarse;
  }
  if (name == "fwidthFine") {
    return BuiltinType::kFwidthFine;
  }
  if (name == "inverseSqrt") {
    return BuiltinType::kInverseSqrt;
  }
  if (name == "isFinite") {
    return BuiltinType::kIsFinite;
  }
  if (name == "isInf") {
    return BuiltinType::kIsInf;
  }
  if (name == "isNan") {
    return BuiltinType::kIsNan;
  }
  if (name == "isNormal") {
    return BuiltinType::kIsNormal;
  }
  if (name == "ldexp") {
    return BuiltinType::kLdexp;
  }
  if (name == "length") {
    return BuiltinType::kLength;
  }
  if (name == "log") {
    return BuiltinType::kLog;
  }
  if (name == "log2") {
    return BuiltinType::kLog2;
  }
  if (name == "max") {
    return BuiltinType::kMax;
  }
  if (name == "min") {
    return BuiltinType::kMin;
  }
  if (name == "mix") {
    return BuiltinType::kMix;
  }
  if (name == "modf") {
    return BuiltinType::kModf;
  }
  if (name == "normalize") {
    return BuiltinType::kNormalize;
  }
  if (name == "pack2x16float") {
    return BuiltinType::kPack2x16float;
  }
  if (name == "pack2x16snorm") {
    return BuiltinType::kPack2x16snorm;
  }
  if (name == "pack2x16unorm") {
    return BuiltinType::kPack2x16unorm;
  }
  if (name == "pack4x8snorm") {
    return BuiltinType::kPack4x8snorm;
  }
  if (name == "pack4x8unorm") {
    return BuiltinType::kPack4x8unorm;
  }
  if (name == "pow") {
    return BuiltinType::kPow;
  }
  if (name == "radians") {
    return BuiltinType::kRadians;
  }
  if (name == "reflect") {
    return BuiltinType::kReflect;
  }
  if (name == "refract") {
    return BuiltinType::kRefract;
  }
  if (name == "reverseBits") {
    return BuiltinType::kReverseBits;
  }
  if (name == "round") {
    return BuiltinType::kRound;
  }
  if (name == "select") {
    return BuiltinType::kSelect;
  }
  if (name == "sign") {
    return BuiltinType::kSign;
  }
  if (name == "sin") {
    return BuiltinType::kSin;
  }
  if (name == "sinh") {
    return BuiltinType::kSinh;
  }
  if (name == "smoothStep") {
    return BuiltinType::kSmoothStep;
  }
  if (name == "sqrt") {
    return BuiltinType::kSqrt;
  }
  if (name == "step") {
    return BuiltinType::kStep;
  }
  if (name == "storageBarrier") {
    return BuiltinType::kStorageBarrier;
  }
  if (name == "tan") {
    return BuiltinType::kTan;
  }
  if (name == "tanh") {
    return BuiltinType::kTanh;
  }
  if (name == "transpose") {
    return BuiltinType::kTranspose;
  }
  if (name == "trunc") {
    return BuiltinType::kTrunc;
  }
  if (name == "unpack2x16float") {
    return BuiltinType::kUnpack2x16float;
  }
  if (name == "unpack2x16snorm") {
    return BuiltinType::kUnpack2x16snorm;
  }
  if (name == "unpack2x16unorm") {
    return BuiltinType::kUnpack2x16unorm;
  }
  if (name == "unpack4x8snorm") {
    return BuiltinType::kUnpack4x8snorm;
  }
  if (name == "unpack4x8unorm") {
    return BuiltinType::kUnpack4x8unorm;
  }
  if (name == "workgroupBarrier") {
    return BuiltinType::kWorkgroupBarrier;
  }
  if (name == "textureDimensions") {
    return BuiltinType::kTextureDimensions;
  }
  if (name == "textureGather") {
    return BuiltinType::kTextureGather;
  }
  if (name == "textureGatherCompare") {
    return BuiltinType::kTextureGatherCompare;
  }
  if (name == "textureNumLayers") {
    return BuiltinType::kTextureNumLayers;
  }
  if (name == "textureNumLevels") {
    return BuiltinType::kTextureNumLevels;
  }
  if (name == "textureNumSamples") {
    return BuiltinType::kTextureNumSamples;
  }
  if (name == "textureSample") {
    return BuiltinType::kTextureSample;
  }
  if (name == "textureSampleBias") {
    return BuiltinType::kTextureSampleBias;
  }
  if (name == "textureSampleCompare") {
    return BuiltinType::kTextureSampleCompare;
  }
  if (name == "textureSampleCompareLevel") {
    return BuiltinType::kTextureSampleCompareLevel;
  }
  if (name == "textureSampleGrad") {
    return BuiltinType::kTextureSampleGrad;
  }
  if (name == "textureSampleLevel") {
    return BuiltinType::kTextureSampleLevel;
  }
  if (name == "textureStore") {
    return BuiltinType::kTextureStore;
  }
  if (name == "textureLoad") {
    return BuiltinType::kTextureLoad;
  }
  if (name == "atomicLoad") {
    return BuiltinType::kAtomicLoad;
  }
  if (name == "atomicStore") {
    return BuiltinType::kAtomicStore;
  }
  if (name == "atomicAdd") {
    return BuiltinType::kAtomicAdd;
  }
  if (name == "atomicSub") {
    return BuiltinType::kAtomicSub;
  }
  if (name == "atomicMax") {
    return BuiltinType::kAtomicMax;
  }
  if (name == "atomicMin") {
    return BuiltinType::kAtomicMin;
  }
  if (name == "atomicAnd") {
    return BuiltinType::kAtomicAnd;
  }
  if (name == "atomicOr") {
    return BuiltinType::kAtomicOr;
  }
  if (name == "atomicXor") {
    return BuiltinType::kAtomicXor;
  }
  if (name == "atomicExchange") {
    return BuiltinType::kAtomicExchange;
  }
  if (name == "atomicCompareExchangeWeak") {
    return BuiltinType::kAtomicCompareExchangeWeak;
  }
  return BuiltinType::kNone;
}

const char* str(BuiltinType i) {
  switch (i) {
    case BuiltinType::kNone:
      return "<none>";
    case BuiltinType::kAbs:
      return "abs";
    case BuiltinType::kAcos:
      return "acos";
    case BuiltinType::kAll:
      return "all";
    case BuiltinType::kAny:
      return "any";
    case BuiltinType::kArrayLength:
      return "arrayLength";
    case BuiltinType::kAsin:
      return "asin";
    case BuiltinType::kAtan:
      return "atan";
    case BuiltinType::kAtan2:
      return "atan2";
    case BuiltinType::kCeil:
      return "ceil";
    case BuiltinType::kClamp:
      return "clamp";
    case BuiltinType::kCos:
      return "cos";
    case BuiltinType::kCosh:
      return "cosh";
    case BuiltinType::kCountOneBits:
      return "countOneBits";
    case BuiltinType::kCross:
      return "cross";
    case BuiltinType::kDegrees:
      return "degrees";
    case BuiltinType::kDeterminant:
      return "determinant";
    case BuiltinType::kDistance:
      return "distance";
    case BuiltinType::kDot:
      return "dot";
    case BuiltinType::kDpdx:
      return "dpdx";
    case BuiltinType::kDpdxCoarse:
      return "dpdxCoarse";
    case BuiltinType::kDpdxFine:
      return "dpdxFine";
    case BuiltinType::kDpdy:
      return "dpdy";
    case BuiltinType::kDpdyCoarse:
      return "dpdyCoarse";
    case BuiltinType::kDpdyFine:
      return "dpdyFine";
    case BuiltinType::kExp:
      return "exp";
    case BuiltinType::kExp2:
      return "exp2";
    case BuiltinType::kFaceForward:
      return "faceForward";
    case BuiltinType::kFloor:
      return "floor";
    case BuiltinType::kFma:
      return "fma";
    case BuiltinType::kFract:
      return "fract";
    case BuiltinType::kFrexp:
      return "frexp";
    case BuiltinType::kFwidth:
      return "fwidth";
    case BuiltinType::kFwidthCoarse:
      return "fwidthCoarse";
    case BuiltinType::kFwidthFine:
      return "fwidthFine";
    case BuiltinType::kInverseSqrt:
      return "inverseSqrt";
    case BuiltinType::kIsFinite:
      return "isFinite";
    case BuiltinType::kIsInf:
      return "isInf";
    case BuiltinType::kIsNan:
      return "isNan";
    case BuiltinType::kIsNormal:
      return "isNormal";
    case BuiltinType::kLdexp:
      return "ldexp";
    case BuiltinType::kLength:
      return "length";
    case BuiltinType::kLog:
      return "log";
    case BuiltinType::kLog2:
      return "log2";
    case BuiltinType::kMax:
      return "max";
    case BuiltinType::kMin:
      return "min";
    case BuiltinType::kMix:
      return "mix";
    case BuiltinType::kModf:
      return "modf";
    case BuiltinType::kNormalize:
      return "normalize";
    case BuiltinType::kPack2x16float:
      return "pack2x16float";
    case BuiltinType::kPack2x16snorm:
      return "pack2x16snorm";
    case BuiltinType::kPack2x16unorm:
      return "pack2x16unorm";
    case BuiltinType::kPack4x8snorm:
      return "pack4x8snorm";
    case BuiltinType::kPack4x8unorm:
      return "pack4x8unorm";
    case BuiltinType::kPow:
      return "pow";
    case BuiltinType::kRadians:
      return "radians";
    case BuiltinType::kReflect:
      return "reflect";
    case BuiltinType::kRefract:
      return "refract";
    case BuiltinType::kReverseBits:
      return "reverseBits";
    case BuiltinType::kRound:
      return "round";
    case BuiltinType::kSelect:
      return "select";
    case BuiltinType::kSign:
      return "sign";
    case BuiltinType::kSin:
      return "sin";
    case BuiltinType::kSinh:
      return "sinh";
    case BuiltinType::kSmoothStep:
      return "smoothStep";
    case BuiltinType::kSqrt:
      return "sqrt";
    case BuiltinType::kStep:
      return "step";
    case BuiltinType::kStorageBarrier:
      return "storageBarrier";
    case BuiltinType::kTan:
      return "tan";
    case BuiltinType::kTanh:
      return "tanh";
    case BuiltinType::kTranspose:
      return "transpose";
    case BuiltinType::kTrunc:
      return "trunc";
    case BuiltinType::kUnpack2x16float:
      return "unpack2x16float";
    case BuiltinType::kUnpack2x16snorm:
      return "unpack2x16snorm";
    case BuiltinType::kUnpack2x16unorm:
      return "unpack2x16unorm";
    case BuiltinType::kUnpack4x8snorm:
      return "unpack4x8snorm";
    case BuiltinType::kUnpack4x8unorm:
      return "unpack4x8unorm";
    case BuiltinType::kWorkgroupBarrier:
      return "workgroupBarrier";
    case BuiltinType::kTextureDimensions:
      return "textureDimensions";
    case BuiltinType::kTextureGather:
      return "textureGather";
    case BuiltinType::kTextureGatherCompare:
      return "textureGatherCompare";
    case BuiltinType::kTextureNumLayers:
      return "textureNumLayers";
    case BuiltinType::kTextureNumLevels:
      return "textureNumLevels";
    case BuiltinType::kTextureNumSamples:
      return "textureNumSamples";
    case BuiltinType::kTextureSample:
      return "textureSample";
    case BuiltinType::kTextureSampleBias:
      return "textureSampleBias";
    case BuiltinType::kTextureSampleCompare:
      return "textureSampleCompare";
    case BuiltinType::kTextureSampleCompareLevel:
      return "textureSampleCompareLevel";
    case BuiltinType::kTextureSampleGrad:
      return "textureSampleGrad";
    case BuiltinType::kTextureSampleLevel:
      return "textureSampleLevel";
    case BuiltinType::kTextureStore:
      return "textureStore";
    case BuiltinType::kTextureLoad:
      return "textureLoad";
    case BuiltinType::kAtomicLoad:
      return "atomicLoad";
    case BuiltinType::kAtomicStore:
      return "atomicStore";
    case BuiltinType::kAtomicAdd:
      return "atomicAdd";
    case BuiltinType::kAtomicSub:
      return "atomicSub";
    case BuiltinType::kAtomicMax:
      return "atomicMax";
    case BuiltinType::kAtomicMin:
      return "atomicMin";
    case BuiltinType::kAtomicAnd:
      return "atomicAnd";
    case BuiltinType::kAtomicOr:
      return "atomicOr";
    case BuiltinType::kAtomicXor:
      return "atomicXor";
    case BuiltinType::kAtomicExchange:
      return "atomicExchange";
    case BuiltinType::kAtomicCompareExchangeWeak:
      return "atomicCompareExchangeWeak";
  }
  return "<unknown>";
}

std::ostream& operator<<(std::ostream& out, BuiltinType i) {
  out << str(i);
  return out;
}

}  // namespace sem
}  // namespace tint
