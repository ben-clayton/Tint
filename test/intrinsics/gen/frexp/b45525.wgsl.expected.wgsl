var<private> arg_1 : vec4<i32>;

fn frexp_b45525() {
  var res : vec4<f32> = frexp(vec4<f32>(), &(arg_1));
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  frexp_b45525();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  frexp_b45525();
}

[[stage(compute)]]
fn compute_main() {
  frexp_b45525();
}