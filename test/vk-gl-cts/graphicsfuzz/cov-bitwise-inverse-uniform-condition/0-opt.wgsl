struct buf2 {
  zero : f32;
};

type Arr = @stride(16) array<f32, 1>;

struct buf0 {
  x_GLF_uniform_float_values : Arr;
};

type Arr_1 = @stride(16) array<i32, 2>;

struct buf1 {
  x_GLF_uniform_int_values : Arr_1;
};

@group(0) @binding(2) var<uniform> x_6 : buf2;

@group(0) @binding(0) var<uniform> x_8 : buf0;

@group(0) @binding(1) var<uniform> x_10 : buf1;

var<private> x_GLF_color : vec4<f32>;

fn main_1() {
  var a : i32;
  var x_32 : i32;
  let x_34 : f32 = x_6.zero;
  let x_36 : f32 = x_8.x_GLF_uniform_float_values[0];
  if ((x_34 < x_36)) {
    let x_42 : i32 = x_10.x_GLF_uniform_int_values[1];
    x_32 = x_42;
  } else {
    let x_44 : i32 = x_10.x_GLF_uniform_int_values[0];
    x_32 = x_44;
  }
  let x_45 : i32 = x_32;
  a = ~((x_45 | 1));
  let x_48 : i32 = a;
  let x_50 : i32 = x_10.x_GLF_uniform_int_values[0];
  if ((x_48 == ~(x_50))) {
    let x_57 : i32 = x_10.x_GLF_uniform_int_values[0];
    let x_60 : i32 = x_10.x_GLF_uniform_int_values[1];
    let x_63 : i32 = x_10.x_GLF_uniform_int_values[1];
    let x_66 : i32 = x_10.x_GLF_uniform_int_values[0];
    x_GLF_color = vec4<f32>(f32(x_57), f32(x_60), f32(x_63), f32(x_66));
  } else {
    let x_70 : i32 = x_10.x_GLF_uniform_int_values[1];
    let x_71 : f32 = f32(x_70);
    x_GLF_color = vec4<f32>(x_71, x_71, x_71, x_71);
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
