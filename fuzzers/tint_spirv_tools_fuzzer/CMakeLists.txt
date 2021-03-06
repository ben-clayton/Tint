# Copyright 2021 The Tint Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set(FUZZER_SOURCES
        cli.cc
        fuzzer.cc
        mutator.cc
        mutator_cache.cc
        spirv_fuzz_mutator.cc
        spirv_opt_mutator.cc
        spirv_reduce_mutator.cc
        util.cc)

set(FUZZER_SOURCES ${FUZZER_SOURCES}
        cli.h
        mutator.h
        mutator_cache.h
        spirv_fuzz_mutator.h
        spirv_opt_mutator.h
        spirv_reduce_mutator.h
        util.h)

set(FUZZER_SOURCES ${FUZZER_SOURCES}
        ../tint_common_fuzzer.h
        ../tint_common_fuzzer.cc)

function(configure_spirv_tools_fuzzer_target NAME SOURCES)
    add_executable(${NAME} ${SOURCES})
    target_link_libraries(${NAME} SPIRV-Tools SPIRV-Tools-opt SPIRV-Tools-fuzz SPIRV-Tools-reduce)
    tint_default_compile_options(${NAME})
    target_compile_options(${NAME} PRIVATE
            -Wno-missing-prototypes
            -Wno-zero-as-null-pointer-constant
            -Wno-reserved-id-macro
            -Wno-sign-conversion
            -Wno-extra-semi-stmt
            -Wno-inconsistent-missing-destructor-override
            -Wno-newline-eof
            -Wno-old-style-cast
            -Wno-weak-vtables
            -Wno-undef)
    target_include_directories(${NAME} PRIVATE
            ${spirv-tools_SOURCE_DIR}
            ${spirv-tools_BINARY_DIR})
endfunction()

configure_spirv_tools_fuzzer_target(tint_spirv_tools_fuzzer "${FUZZER_SOURCES}")
target_compile_definitions(tint_spirv_tools_fuzzer PUBLIC CUSTOM_MUTATOR)
target_compile_definitions(tint_spirv_tools_fuzzer PRIVATE TARGET_FUZZER)
target_link_libraries(tint_spirv_tools_fuzzer libtint-fuzz)

set(DEBUGGER_SOURCES
        cli.cc
        mutator.cc
        mutator_debugger.cc
        spirv_fuzz_mutator.cc
        spirv_opt_mutator.cc
        spirv_reduce_mutator.cc
        util.cc)

set(DEBUGGER_SOURCES ${DEBUGGER_SOURCES}
        cli.h
        mutator.h
        spirv_fuzz_mutator.h
        spirv_opt_mutator.h
        spirv_reduce_mutator.h
        util.h)

configure_spirv_tools_fuzzer_target(tint_spirv_tools_mutator_debugger "${DEBUGGER_SOURCES}")
target_compile_definitions(tint_spirv_tools_mutator_debugger PRIVATE TARGET_DEBUGGER)
