struct Uniforms {
  i : u32;
  j : u32;
}

@group(1) @binding(4) var<uniform> uniforms : Uniforms;

var<private> m1 : mat2x4<f32>;

@stage(compute) @workgroup_size(1)
fn main() {
  m1[0][uniforms.j] = 1.0;
}
