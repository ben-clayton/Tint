type Arr = @stride(16) array<i32, 2>;

struct buf0 {
  x_GLF_uniform_int_values : Arr;
};

type Arr_1 = @stride(16) array<f32, 1>;

struct buf1 {
  x_GLF_uniform_float_values : Arr_1;
};

@group(0) @binding(0) var<uniform> x_6 : buf0;

@group(0) @binding(1) var<uniform> x_8 : buf1;

var<private> x_GLF_color : vec4<f32>;

fn main_1() {
  var a : f32;
  let x_31 : i32 = x_6.x_GLF_uniform_int_values[0];
  let x_34 : i32 = x_6.x_GLF_uniform_int_values[1];
  let x_38 : i32 = x_6.x_GLF_uniform_int_values[0];
  a = vec2<f32>(f32(x_31), f32(x_34))[(x_38 | 1)];
  let x_41 : f32 = a;
  let x_43 : f32 = x_8.x_GLF_uniform_float_values[0];
  if ((x_41 == x_43)) {
    let x_48 : f32 = a;
    let x_50 : i32 = x_6.x_GLF_uniform_int_values[0];
    let x_53 : i32 = x_6.x_GLF_uniform_int_values[0];
    let x_55 : f32 = a;
    x_GLF_color = vec4<f32>(x_48, f32(x_50), f32(x_53), x_55);
  } else {
    let x_57 : f32 = a;
    x_GLF_color = vec4<f32>(x_57, x_57, x_57, x_57);
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
