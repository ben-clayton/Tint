type Arr = @stride(16) array<i32, 2>;

struct buf0 {
  x_GLF_uniform_int_values : Arr;
};

type Arr_1 = @stride(16) array<f32, 2>;

struct buf1 {
  x_GLF_uniform_float_values : Arr_1;
};

@group(0) @binding(0) var<uniform> x_6 : buf0;

@group(0) @binding(1) var<uniform> x_8 : buf1;

var<private> x_GLF_color : vec4<f32>;

fn main_1() {
  var data : array<f32, 2>;
  var a : f32;
  let x_33 : i32 = x_6.x_GLF_uniform_int_values[0];
  let x_35 : f32 = x_8.x_GLF_uniform_float_values[0];
  data[x_33] = x_35;
  let x_38 : i32 = x_6.x_GLF_uniform_int_values[1];
  let x_40 : f32 = x_8.x_GLF_uniform_float_values[1];
  data[x_38] = x_40;
  let x_43 : i32 = x_6.x_GLF_uniform_int_values[1];
  let x_47 : f32 = data[(1 ^ (x_43 & 2))];
  a = x_47;
  let x_48 : f32 = a;
  let x_50 : f32 = x_8.x_GLF_uniform_float_values[1];
  if ((x_48 == x_50)) {
    let x_56 : f32 = x_8.x_GLF_uniform_float_values[1];
    let x_58 : f32 = x_8.x_GLF_uniform_float_values[0];
    let x_60 : f32 = x_8.x_GLF_uniform_float_values[0];
    let x_62 : f32 = x_8.x_GLF_uniform_float_values[1];
    x_GLF_color = vec4<f32>(x_56, x_58, x_60, x_62);
  } else {
    let x_65 : f32 = x_8.x_GLF_uniform_float_values[0];
    x_GLF_color = vec4<f32>(x_65, x_65, x_65, x_65);
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
