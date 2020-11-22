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

#include "src/ast/identifier_expression.h"
#include "src/ast/type/array_type.h"
#include "src/ast/type/matrix_type.h"
#include "src/ast/type/struct_type.h"
#include "src/ast/type/texture_type.h"
#include "src/ast/type/vector_type.h"

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

  auto ext = GatherExtensionData(func);
  if (ext.has_texture_1d) {
    add_error("texture1D not supported in ESSL");
    return false;
  }

  return true;
}

GeneratorImpl::ExtensionData GeneratorImpl::GatherExtensionData(
    ast::Function* func) {
  ExtensionData ext;
  for (const auto& data : func->referenced_sampled_texture_variables()) {
    auto* var = data.first;
    if (var->type()->UnwrapAll()->AsTexture()->dim() ==
        ast::type::TextureDimension::kCubeArray) {
      ext.needs_cube_array_ext = true;
      break;
    }
  }

  if (!ext.needs_cube_array_ext) {
    for (const auto& data : func->referenced_depth_texture_variables()) {
      auto* var = data.first;
      if (var->type()->UnwrapAll()->AsTexture()->dim() ==
          ast::type::TextureDimension::kCubeArray) {
        ext.needs_cube_array_ext = true;
        break;
      }
    }
  }

  for (const auto& data : func->referenced_texture_variables()) {
    auto* var = data.first;
    auto dim = var->type()->UnwrapAll()->AsTexture()->dim();
    if (dim == ast::type::TextureDimension::k1d ||
        dim == ast::type::TextureDimension::k1dArray) {
      ext.has_texture_1d = true;
      break;
    }
  }
  return ext;
}

bool GeneratorImpl::EmitExpression(std::ostream& out, ast::Expression* expr) {
  if (expr->IsIdentifier()) {
    return EmitIdentifier(out, expr->AsIdentifier());
  }

  add_error("unknown expression type: " + expr->str());
  return false;
}

bool GeneratorImpl::EmitIdentifier(std::ostream& out,
                                   ast::IdentifierExpression* expr) {
  out << expr->name();
  return true;
}

bool GeneratorImpl::EmitType(std::ostream& out,
                             ast::type::Type* type,
                             const std::string& name) {
  if (type->IsAlias()) {
    out << type->AsAlias()->name();
  } else if (type->IsArray()) {
    auto* ary = type->AsArray();

    ast::type::Type* base_type = ary;
    std::vector<uint32_t> sizes;
    while (base_type->IsArray()) {
      if (base_type->AsArray()->IsRuntimeArray()) {
        // TODO(dsinclair): Support runtime arrays
        add_error("runtime array not supported yet.");
        return false;
      } else {
        sizes.push_back(base_type->AsArray()->size());
      }
      base_type = base_type->AsArray()->type();
    }
    if (!EmitType(out, base_type, "")) {
      return false;
    }
    if (!name.empty()) {
      out << " " << name;
    }
    for (uint32_t size : sizes) {
      out << "[" << size << "]";
    }
  } else if (type->IsBool()) {
    out << "bool";
  } else if (type->IsF32()) {
    out << "float";
  } else if (type->IsI32()) {
    out << "int";
  } else if (type->IsMatrix()) {
    auto* mat = type->AsMatrix();
    out << "mat" << mat->columns() << "x" << mat->rows();
  } else if (type->IsPointer()) {
    // TODO(dsinclair): What do we do with pointers in ESSL?
    add_error("pointers not supported in ESSL");
    return false;
  } else if (type->IsSampler()) {
    add_error("samplers are unsupported");
    return false;
  } else if (type->IsStruct()) {
    out << type->AsStruct()->name();
  } else if (type->IsTexture()) {
    auto* tex = type->AsTexture();
    if (tex->IsStorage()) {
      out << "image";
    } else {
      out << "sampler";
    }

    switch (tex->dim()) {
      case ast::type::TextureDimension::k1d:
        out << "1D";
        break;
      case ast::type::TextureDimension::k1dArray:
        out << "1DArray";
        break;
      case ast::type::TextureDimension::k2d:
        out << "2D";
        break;
      case ast::type::TextureDimension::k2dArray:
        out << "2DArray";
        break;
      case ast::type::TextureDimension::k3d:
        out << "3D";
        break;
      case ast::type::TextureDimension::kCube:
        out << "Cube";
        break;
      case ast::type::TextureDimension::kCubeArray:
        out << "CubeArray";
        break;
      default:
        add_error("Invalid texture dimensions");
        return false;
    }

    if (tex->IsMultisampled()) {
      out << "MS";
    }
    if (tex->IsDepth()) {
      out << "Shadow";
    }

  } else if (type->IsU32()) {
    out << "uint";
  } else if (type->IsVector()) {
    auto* vec = type->AsVector();
    auto size = vec->size();
    if (vec->type()->IsF32() && size >= 1 && size <= 4) {
      out << "vec" << size;
    } else if (vec->type()->IsI32() && size >= 1 && size <= 4) {
      out << "ivec" << size;
    } else if (vec->type()->IsU32() && size >= 1 && size <= 4) {
      out << "uvec" << size;
    } else {
      add_error("unsupported vector format : " + vec->type()->type_name());
      return false;
    }
  } else if (type->IsVoid()) {
    out << "void";
  } else {
    add_error("unknown type in EmitType: " + type->type_name());
    return false;
  }
  return true;
}
bool GeneratorImpl::EmitStructType(std::ostream& out,
                                   const ast::type::StructType* str,
                                   const std::string& name) {
  // TODO(dsinclair): Block decoration?
  // if (str->impl()->decoration() != ast::StructDecoration::kNone) {
  // }
  out << "struct " << name << " {" << std::endl;

  increment_indent();
  for (auto* mem : str->impl()->members()) {
    make_indent(out);
    // TODO(dsinclair): Handle [[offset]] annotation on structs

    if (!EmitType(out, mem->type(), mem->name())) {
      return false;
    }
    // Array member name will be output with the type
    if (!mem->type()->IsArray()) {
      out << " " << mem->name();
    }
    out << ";" << std::endl;
  }
  decrement_indent();
  make_indent(out);

  out << "};" << std::endl;

  return true;
}

}  // namespace essl
}  // namespace writer
}  // namespace tint
