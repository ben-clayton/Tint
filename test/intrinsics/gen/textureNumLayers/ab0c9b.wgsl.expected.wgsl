[[group(1), binding(0)]] var arg_0 : texture_storage_2d_array<rg32sint, read>;

fn textureNumLayers_ab0c9b() {
  var res : i32 = textureNumLayers(arg_0);
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureNumLayers_ab0c9b();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureNumLayers_ab0c9b();
}

[[stage(compute)]]
fn compute_main() {
  textureNumLayers_ab0c9b();
}