SKIP: FAILED


fn modf_4fe3d9() {
  var arg_1 : vec3<f32>;
  var res : vec3<f32> = modf(vec3<f32>(), &(arg_1));
}

struct tint_symbol {
  [[builtin(position)]]
  value : vec4<f32>;
};

[[stage(vertex)]]
fn vertex_main() -> tint_symbol {
  modf_4fe3d9();
  let tint_symbol_1 : tint_symbol = tint_symbol(vec4<f32>());
  return tint_symbol_1;
}

[[stage(fragment)]]
fn fragment_main() {
  modf_4fe3d9();
}

[[stage(compute)]]
fn compute_main() {
  modf_4fe3d9();
}

Failed to generate: error: Unknown builtin method: modf