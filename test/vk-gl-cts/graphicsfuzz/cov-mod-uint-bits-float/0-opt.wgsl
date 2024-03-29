type Arr = @stride(16) array<f32, 3>;

struct buf0 {
  x_GLF_uniform_float_values : Arr;
};

var<private> x_GLF_color : vec4<f32>;

@group(0) @binding(0) var<uniform> x_6 : buf0;

fn main_1() {
  var a : f32;
  a = (bitcast<f32>(1u) % 1.0);
  let x_29 : f32 = x_6.x_GLF_uniform_float_values[1];
  x_GLF_color = vec4<f32>(x_29, x_29, x_29, x_29);
  let x_31 : f32 = a;
  let x_33 : f32 = x_6.x_GLF_uniform_float_values[2];
  if ((x_31 < x_33)) {
    let x_38 : f32 = x_6.x_GLF_uniform_float_values[0];
    let x_40 : f32 = x_6.x_GLF_uniform_float_values[1];
    let x_42 : f32 = x_6.x_GLF_uniform_float_values[1];
    let x_44 : f32 = x_6.x_GLF_uniform_float_values[0];
    x_GLF_color = vec4<f32>(x_38, x_40, x_42, x_44);
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
