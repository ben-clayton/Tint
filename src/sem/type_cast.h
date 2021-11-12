// Copyright 2021 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0(the "License");
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

#ifndef SRC_SEM_TYPE_CAST_H_
#define SRC_SEM_TYPE_CAST_H_

#include "src/sem/call_target.h"

namespace tint {
namespace sem {

/// TypeCast is the CallTarget for a type cast.
class TypeCast : public Castable<TypeCast, CallTarget> {
 public:
  /// Constructor
  /// @param type the target type of the cast
  /// @param parameter the type cast parameter
  TypeCast(const sem::Type* type, const sem::Parameter* parameter);

  /// Destructor
  ~TypeCast() override;

  /// @returns the cast source type
  const sem::Type* Source() const { return Parameters()[0]->Type(); }

  /// @returns the cast target type
  const sem::Type* Target() const { return ReturnType(); }
};

}  // namespace sem
}  // namespace tint

#endif  // SRC_SEM_TYPE_CAST_H_