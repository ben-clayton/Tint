type Arr = @stride(16) array<i32, 2>;

struct buf0 {
  x_GLF_uniform_int_values : Arr;
};

@group(0) @binding(0) var<uniform> x_6 : buf0;

var<private> x_GLF_color : vec4<f32>;

fn main_1() {
  var a : i32;
  a = -7563;
  let x_25 : i32 = x_6.x_GLF_uniform_int_values[1];
  let x_26 : i32 = a;
  let x_29 : i32 = x_6.x_GLF_uniform_int_values[0];
  if (((x_25 / x_26) == x_29)) {
    let x_35 : i32 = x_6.x_GLF_uniform_int_values[1];
    let x_38 : i32 = x_6.x_GLF_uniform_int_values[0];
    let x_41 : i32 = x_6.x_GLF_uniform_int_values[0];
    let x_44 : i32 = x_6.x_GLF_uniform_int_values[1];
    x_GLF_color = vec4<f32>(f32(x_35), f32(x_38), f32(x_41), f32(x_44));
  } else {
    let x_48 : i32 = x_6.x_GLF_uniform_int_values[0];
    let x_49 : f32 = f32(x_48);
    x_GLF_color = vec4<f32>(x_49, x_49, x_49, x_49);
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
