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
  var undefined : f32;
  var x_45 : bool;
  var x_46_phi : bool;
  undefined = sinh(0x1.8p+128);
  let x_10 : i32 = x_6.x_GLF_uniform_int_values[0];
  let x_38 : bool = (1 == x_10);
  x_46_phi = x_38;
  if (!(x_38)) {
    let x_42 : f32 = undefined;
    let x_44 : f32 = x_8.x_GLF_uniform_float_values[0];
    x_45 = (x_42 > x_44);
    x_46_phi = x_45;
  }
  let x_46 : bool = x_46_phi;
  if (x_46) {
    let x_12 : i32 = x_6.x_GLF_uniform_int_values[0];
    let x_13 : i32 = x_6.x_GLF_uniform_int_values[1];
    let x_14 : i32 = x_6.x_GLF_uniform_int_values[1];
    let x_15 : i32 = x_6.x_GLF_uniform_int_values[0];
    x_GLF_color = vec4<f32>(f32(x_12), f32(x_13), f32(x_14), f32(x_15));
  } else {
    let x_16 : i32 = x_6.x_GLF_uniform_int_values[1];
    let x_60 : f32 = f32(x_16);
    x_GLF_color = vec4<f32>(x_60, x_60, x_60, x_60);
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
