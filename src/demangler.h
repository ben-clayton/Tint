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

#ifndef SRC_DEMANGLER_H_
#define SRC_DEMANGLER_H_

#include <string>

#include "src/ast/module.h"

namespace tint {

/// Helper to demangle strings and replace symbols with original names
class Demangler {
 public:
  /// Constructor
  Demangler();
  /// Destructor
  ~Demangler();

  /// Transforms given string and replaces any symbols with original names
  /// @param mod the module where the symbols are registered
  /// @param str the string to replace
  /// @returns the string with any symbol replacements performed.
  std::string Demangle(const ast::Module& mod, const std::string& str) const;
};

}  // namespace tint

#endif  // SRC_DEMANGLER_H_