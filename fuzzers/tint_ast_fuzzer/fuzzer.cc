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

#include <cstddef>
#include <cstdint>

#include "fuzzers/tint_ast_fuzzer/cli.h"
#include "fuzzers/tint_ast_fuzzer/mt_rng.h"
#include "fuzzers/tint_ast_fuzzer/mutator.h"
#include "fuzzers/tint_common_fuzzer.h"

#include "src/reader/wgsl/parser.h"
#include "src/writer/wgsl/generator.h"

namespace tint {
namespace fuzzers {
namespace ast_fuzzer {
namespace {

CliParams cli_params{};

extern "C" int LLVMFuzzerInitialize(int* argc, char*** argv) {
  // Parse CLI parameters. `ParseCliParams` will call `exit` if some parameter
  // is invalid.
  cli_params = ParseCliParams(argc, *argv);
  return 0;
}

extern "C" size_t LLVMFuzzerCustomMutator(uint8_t* data,
                                          size_t size,
                                          size_t max_size,
                                          unsigned seed) {
  Source::File file("test.wgsl", {reinterpret_cast<char*>(data), size});
  auto program = reader::wgsl::Parse(&file);
  if (!program.IsValid()) {
    std::cout << "Trying to mutate an invalid program:" << std::endl
              << program.Diagnostics().str() << std::endl;
    return 0;
  }

  // Run the mutator.
  MtRng mt_rng(seed);
  ProbabilityContext probability_context(&mt_rng);
  program = Mutate(std::move(program), &probability_context,
                   cli_params.enable_all_mutations,
                   cli_params.mutation_batch_size, nullptr);

  if (!program.IsValid()) {
    std::cout << "Mutator produced invalid WGSL:" << std::endl
              << "  seed: " << seed << std::endl
              << program.Diagnostics().str() << std::endl;
    return 0;
  }

  auto result = writer::wgsl::Generate(&program, writer::wgsl::Options());
  if (!result.success) {
    std::cout << "Can't generate WGSL for a valid tint::Program:" << std::endl
              << result.error << std::endl;
    return 0;
  }

  // +1 to account for \0 at the end of a string.
  auto mutated_size = result.wgsl.size() + 1;
  if (mutated_size > max_size) {
    return 0;
  }

  std::memcpy(data, result.wgsl.data(), mutated_size);
  return mutated_size;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  struct Target {
    FuzzingTarget fuzzing_target;
    OutputFormat output_format;
    const char* name;
  };

  Target targets[] = {{FuzzingTarget::kWgsl, OutputFormat::kWGSL, "WGSL"},
                      {FuzzingTarget::kHlsl, OutputFormat::kHLSL, "HLSL"},
                      {FuzzingTarget::kMsl, OutputFormat::kMSL, "MSL"},
                      {FuzzingTarget::kSpv, OutputFormat::kSpv, "SPV"}};

  for (auto target : targets) {
    if ((target.fuzzing_target & cli_params.fuzzing_target) !=
        target.fuzzing_target) {
      continue;
    }

    CommonFuzzer fuzzer(InputFormat::kWGSL, target.output_format);
    fuzzer.EnableInspector();
    fuzzer.Run(data, size);
    if (fuzzer.HasErrors()) {
      std::cout << "Fuzzing " << target.name
                << " produced an error:" << std::endl
                << fuzzer.GetErrors() << std::endl;
    }
  }

  return 0;
}

}  // namespace
}  // namespace ast_fuzzer
}  // namespace fuzzers
}  // namespace tint