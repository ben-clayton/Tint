struct SB_RW {
  arg_0 : array<f32>;
}

@group(0) @binding(0) var<storage, read_write> sb_rw : SB_RW;

fn arrayLength_cdd123() {
  var res : u32 = arrayLength(&(sb_rw.arg_0));
}

@stage(vertex)
fn vertex_main() -> @builtin(position) vec4<f32> {
  arrayLength_cdd123();
  return vec4<f32>();
}

@stage(fragment)
fn fragment_main() {
  arrayLength_cdd123();
}

@stage(compute) @workgroup_size(1)
fn compute_main() {
  arrayLength_cdd123();
}
