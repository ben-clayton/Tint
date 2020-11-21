  /// Copyright 2020 The Tint Authors.
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

#include "src/writer/essl/generator_impl.h"

#include <sstream>

namespace tint {
namespace writer {
namespace essl {

GeneratorImpl::GeneratorImpl(ast::Module* module) : module_(module) {}

GeneratorImpl::~GeneratorImpl() = default;

void GeneratorImpl::make_indent(std::ostream& out) {
  for (size_t i = 0; i < indent_; i++) {
    out << " ";
  }
}

void GeneratorImpl::add_error(const std::string& err) {
  diag::Diagnostic diagnostic;
  diagnostic.severity = diag::Severity::Error;
  diagnostic.message = err;
  diags_.add(std::move(diagnostic));
}

bool GeneratorImpl::GenerateEntryPoint(std::ostream&, ast::PipelineStage stage,
                          const std::string& name) {
  auto* func = module_->FindFunctionByNameAndStage(name, stage);
  if (func == nullptr) {
    std::stringstream err;
    err << "Unable to find entry point: " << name << " with stage: " << stage;
    add_error(err.str());
    return false;
  }

  return true;
}

}  // namespace essl
}  // namespace writer
}  // namespace tint
