var<private> arg_1 : vec3<f32>;

fn modf_9cecfc() {
  var res : vec3<f32> = modf(vec3<f32>(), &(arg_1));
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  modf_9cecfc();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  modf_9cecfc();
}

[[stage(compute)]]
fn compute_main() {
  modf_9cecfc();
}