[[group(1), binding(0)]] var arg_0 : texture_storage_2d_array<rg32sint, read>;

fn textureDimensions_caaabb() {
  var res : vec2<i32> = textureDimensions(arg_0);
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureDimensions_caaabb();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureDimensions_caaabb();
}

[[stage(compute)]]
fn compute_main() {
  textureDimensions_caaabb();
}