var<private> x_GLF_color : vec4<f32>;

fn main_1() {
  var f : f32;
  f = atan2(1.0, tanh(1.0));
  let x_21 : f32 = f;
  let x_23 : f32 = f;
  if (((x_21 > 0.910000026) && (x_23 < 0.930000007))) {
    x_GLF_color = vec4<f32>(1.0, 0.0, 0.0, 1.0);
  } else {
    x_GLF_color = vec4<f32>(0.0, 0.0, 0.0, 0.0);
  }
  return;
}

struct main_out {
  @location(0)
  x_GLF_color_1 : vec4<f32>;
};

@stage(fragment)
fn main() -> main_out {
  main_1();
  return main_out(x_GLF_color);
}
