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

#ifndef SRC_AST_DISABLE_VALIDATION_ATTRIBUTE_H_
#define SRC_AST_DISABLE_VALIDATION_ATTRIBUTE_H_

#include <string>

#include "src/ast/internal_attribute.h"

namespace tint {
namespace ast {

/// Enumerator of validation features that can be disabled with a
/// DisableValidationAttribute attribute.
enum class DisabledValidation {
  /// When applied to a function, the validator will not complain there is no
  /// body to a function.
  kFunctionHasNoBody,
  /// When applied to a module-scoped variable, the validator will not complain
  /// if two resource variables have the same binding points.
  kBindingPointCollision,
  /// When applied to a variable, the validator will not complain about the
  /// declared storage class.
  kIgnoreStorageClass,
  /// When applied to an entry-point function parameter, the validator will not
  /// check for entry IO attributes.
  kEntryPointParameter,
  /// When applied to a function parameter, the validator will not
  /// check if parameter type is constructible
  kIgnoreConstructibleFunctionParameter,
  /// When applied to a member attribute, a stride attribute may be applied to
  /// non-array types.
  kIgnoreStrideAttribute,
  /// When applied to a pointer function parameter, the validator will not
  /// require a function call argument passed for that parameter to have a
  /// certain form.
  kIgnoreInvalidPointerArgument,
};

/// An internal attribute used to tell the validator to ignore specific
/// violations. Typically generated by transforms that need to produce ASTs that
/// would otherwise cause validation errors.
class DisableValidationAttribute
    : public Castable<DisableValidationAttribute, InternalAttribute> {
 public:
  /// Constructor
  /// @param program_id the identifier of the program that owns this node
  /// @param validation the validation to disable
  explicit DisableValidationAttribute(ProgramID program_id,
                                      DisabledValidation validation);

  /// Destructor
  ~DisableValidationAttribute() override;

  /// @return a short description of the internal attribute which will be
  /// displayed in WGSL as `@internal(<name>)` (but is not parsable).
  std::string InternalName() const override;

  /// Performs a deep clone of this object using the CloneContext `ctx`.
  /// @param ctx the clone context
  /// @return the newly cloned object
  const DisableValidationAttribute* Clone(CloneContext* ctx) const override;

  /// The validation that this attribute disables
  const DisabledValidation validation;
};

}  // namespace ast
}  // namespace tint

#endif  // SRC_AST_DISABLE_VALIDATION_ATTRIBUTE_H_
