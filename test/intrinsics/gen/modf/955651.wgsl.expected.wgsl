fn modf_955651() {
  var arg_1 : vec3<f32>;
  var res : vec3<f32> = modf(vec3<f32>(), &(arg_1));
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  modf_955651();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  modf_955651();
}

[[stage(compute), workgroup_size(1)]]
fn compute_main() {
  modf_955651();
}
