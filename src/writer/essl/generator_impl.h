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

#ifndef SRC_WRITER_ESSL_GENERATOR_IMPL_H_
#define SRC_WRITER_ESSL_GENERATOR_IMPL_H_

#include "src/ast/module.h"
#include "src/context.h"
#include "src/diagnostic/diagnostic.h"
#include "src/diagnostic/formatter.h"

namespace tint {
namespace writer {
namespace essl {

/// Implementation class for ESSL generator
class GeneratorImpl {
 public:
  /// Constructor
  /// @param module the module to generate
  GeneratorImpl(ast::Module* module);
  ~GeneratorImpl();

  /// Increment the emitter indent level
  void increment_indent() { indent_ += 2; }
  /// Decrement the emitter indent level
  void decrement_indent() {
    if (indent_ < 2) {
      indent_ = 0;
      return;
    }
    indent_ -= 2;
  }

  /// Writes the current indent to the output stream
  /// @param out the output stream
  void make_indent(std::ostream& out);

  /// @returns the parser error string
  std::string error() const {
    diag::Formatter formatter{{false, false, false}};
    return formatter.format(diags_);
  }

  /// Generates a single entry point
  /// @param out the output stream
  /// @param stage the pipeline stage
  /// @param name the entry point name
  /// @returns true on successful generation; false otherwise
  bool GenerateEntryPoint(std::ostream& out,
                          ast::PipelineStage stage,
                          const std::string& name);

  /// Handles generating a binary expression
  /// @param out the output of the expression stream
  /// @param expr the binary expression
  /// @returns true if the expression was emitted, false otherwise
  bool EmitBinary(std::ostream& out,
                  ast::BinaryExpression* expr);
  /// Handles generating an Expression
  /// @param out the output of the expression stream
  /// @param expr the expression
  /// @returns true if the expression was emitted
  bool EmitExpression(std::ostream& out, ast::Expression* expr);
  /// Handles generating an identifier expression
  /// @param out the output stream
  /// @param expr the identifier expression
  /// @returns true if the identifier was emitted
  bool EmitIdentifier(std::ostream& out, ast::IdentifierExpression* expr);
  /// Handles generating type
  /// @param out the output stream
  /// @param type the type to generate
  /// @param name the name of the variable, only used for array emission
  /// @returns true if the type is emitted
  bool EmitType(std::ostream& out,
                ast::type::Type* type,
                const std::string& name);
  /// Handles generating a structure declaration
  /// @param out the output stream
  /// @param ty the struct to generate
  /// @param name the struct name
  /// @returns true if the struct is emitted
  bool EmitStructType(std::ostream& out,
                      const ast::type::StructType* ty,
                      const std::string& name);

  /// Information on needed ESSL extensions
  struct ExtensionData {
    /// Do we need EXT_texture_cube_map_array
    bool needs_cube_array_ext = false;
    /// 1D textures are supported, we can't convert if they're used
    bool has_texture_1d = false;
  };

  /// Returns information on needed extensions
  /// @param func the function to gather the data from
  /// @return the information on needed extensions
  ExtensionData GatherExtensionData(ast::Function* func);

 private:
  void add_error(const std::string& err);

  diag::List diags_;
  size_t indent_ = 0;

  ast::Module* module_ = nullptr;
};

}  // namespace essl
}  // namespace writer
}  // namespace tint

#endif  // SRC_WRITER_ESSL_GENERATOR_IMPL_H_

