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

#ifndef SRC_WRITER_ESSL_GENERATOR_H_
#define SRC_WRITER_ESSL_GENERATOR_H_

#include <memory>
#include <sstream>
#include <string>

#include "src/writer/essl/generator_impl.h"
#include "src/writer/text.h"

namespace tint {
namespace writer {
namespace essl {

/// Class to generate ESSL source
class Generator : public Text {
 public:
  /// Constructor
  /// @param ctx the context, must be non-null
  /// @param module the module to convert
  Generator(Context* ctx, ast::Module module);
  ~Generator() override;

  /// Resets the generator
  void Reset() override;

  /// Generates the result data
  /// @returns false; only single entry point generation permitted with ESSL.
  bool Generate() override;

  /// Converts a single entry point
  /// @param stage the pipeline stage
  /// @param name the entry point name
  /// @returns true on succes; false on failure
  bool GenerateEntryPoint(ast::PipelineStage stage,
                          const std::string& name) override;

  /// @returns the result data
  std::string result() const override;

  /// @returns the error
  std::string error() const;

 private:
  std::ostringstream out_;
  std::unique_ptr<GeneratorImpl> impl_;
};

}  // namespace essl
}  // namespace writer
}  // namespace tint

#endif  // SRC_WRITER_ESSL_GENERATOR_H_

