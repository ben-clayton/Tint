fn isFinite_426f9f() {
  var res : bool = isFinite(1.0);
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  isFinite_426f9f();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  isFinite_426f9f();
}

[[stage(compute)]]
fn compute_main() {
  isFinite_426f9f();
}