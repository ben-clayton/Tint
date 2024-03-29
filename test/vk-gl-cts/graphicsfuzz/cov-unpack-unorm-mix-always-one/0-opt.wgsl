type Arr = @stride(16) array<u32, 1>;

struct buf0 {
  x_GLF_uniform_uint_values : Arr;
};

type Arr_1 = @stride(16) array<i32, 2>;

struct buf1 {
  x_GLF_uniform_int_values : Arr_1;
};

type Arr_2 = @stride(16) array<f32, 3>;

struct buf2 {
  x_GLF_uniform_float_values : Arr_2;
};

@group(0) @binding(0) var<uniform> x_6 : buf0;

@group(0) @binding(1) var<uniform> x_8 : buf1;

@group(0) @binding(2) var<uniform> x_10 : buf2;

var<private> x_GLF_color : vec4<f32>;

fn main_1() {
  var v : vec4<f32>;
  let x_39 : u32 = x_6.x_GLF_uniform_uint_values[0];
  let x_41 : u32 = x_6.x_GLF_uniform_uint_values[0];
  v = unpack4x8unorm((x_39 / select(x_41, 92382u, true)));
  let x_45 : vec4<f32> = v;
  let x_47 : i32 = x_8.x_GLF_uniform_int_values[0];
  let x_50 : i32 = x_8.x_GLF_uniform_int_values[0];
  let x_53 : i32 = x_8.x_GLF_uniform_int_values[0];
  let x_56 : f32 = x_10.x_GLF_uniform_float_values[1];
  let x_58 : f32 = x_10.x_GLF_uniform_float_values[2];
  let x_63 : f32 = x_10.x_GLF_uniform_float_values[0];
  if ((distance(x_45, vec4<f32>(f32(x_47), f32(x_50), f32(x_53), (x_56 / x_58))) < x_63)) {
    let x_69 : i32 = x_8.x_GLF_uniform_int_values[1];
    let x_72 : i32 = x_8.x_GLF_uniform_int_values[0];
    let x_75 : i32 = x_8.x_GLF_uniform_int_values[0];
    let x_78 : i32 = x_8.x_GLF_uniform_int_values[1];
    x_GLF_color = vec4<f32>(f32(x_69), f32(x_72), f32(x_75), f32(x_78));
  } else {
    let x_82 : i32 = x_8.x_GLF_uniform_int_values[0];
    let x_83 : f32 = f32(x_82);
    x_GLF_color = vec4<f32>(x_83, x_83, x_83, x_83);
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
