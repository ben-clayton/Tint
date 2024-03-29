struct Uniforms {
  i : u32;
  j : u32;
}

@group(1) @binding(4) var<uniform> uniforms : Uniforms;

@stage(compute) @workgroup_size(1)
fn main() {
  var m1 : mat2x4<f32>;
  m1[uniforms.i][0] = 1.0;
}
