type Arr = @stride(16) array<i32, 2>;

struct buf0 {
  x_GLF_uniform_int_values : Arr;
};

@group(0) @binding(0) var<uniform> x_5 : buf0;

var<private> x_GLF_color : vec4<f32>;

fn main_1() {
  let x_22 : i32 = x_5.x_GLF_uniform_int_values[0];
  if (((1 >> bitcast<u32>(x_22)) > 0)) {
    let x_29 : i32 = x_5.x_GLF_uniform_int_values[1];
    let x_32 : i32 = x_5.x_GLF_uniform_int_values[0];
    let x_35 : i32 = x_5.x_GLF_uniform_int_values[0];
    let x_38 : i32 = x_5.x_GLF_uniform_int_values[1];
    x_GLF_color = vec4<f32>(f32(x_29), f32(x_32), f32(x_35), f32(x_38));
  } else {
    let x_42 : i32 = x_5.x_GLF_uniform_int_values[0];
    let x_43 : f32 = f32(x_42);
    x_GLF_color = vec4<f32>(x_43, x_43, x_43, x_43);
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
