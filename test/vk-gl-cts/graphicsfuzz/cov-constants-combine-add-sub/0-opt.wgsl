type Arr = @stride(16) array<i32, 5>;

struct buf0 {
  x_GLF_uniform_int_values : Arr;
};

@group(0) @binding(0) var<uniform> x_8 : buf0;

var<private> x_GLF_color : vec4<f32>;

fn func_f1_(f : ptr<function, f32>) -> i32 {
  var a : i32;
  var b : i32;
  var i : i32;
  let x_60 : i32 = x_8.x_GLF_uniform_int_values[1];
  a = x_60;
  let x_62 : i32 = x_8.x_GLF_uniform_int_values[2];
  b = x_62;
  let x_64 : i32 = x_8.x_GLF_uniform_int_values[2];
  i = x_64;
  loop {
    let x_69 : i32 = i;
    let x_71 : i32 = x_8.x_GLF_uniform_int_values[4];
    if ((x_69 < x_71)) {
    } else {
      break;
    }
    let x_74 : i32 = a;
    let x_76 : i32 = x_8.x_GLF_uniform_int_values[3];
    if ((x_74 > x_76)) {
      break;
    }
    let x_80 : f32 = *(f);
    let x_83 : i32 = x_8.x_GLF_uniform_int_values[1];
    let x_86 : i32 = i;
    a = ((i32(x_80) - (x_83 / 2)) + x_86);
    let x_88 : i32 = b;
    b = (x_88 + 1);

    continuing {
      let x_90 : i32 = i;
      i = (x_90 + 1);
    }
  }
  let x_92 : i32 = b;
  let x_94 : i32 = x_8.x_GLF_uniform_int_values[0];
  if ((x_92 == x_94)) {
    let x_100 : i32 = x_8.x_GLF_uniform_int_values[1];
    return x_100;
  } else {
    let x_102 : i32 = x_8.x_GLF_uniform_int_values[2];
    return x_102;
  }
  return 0;
}

fn main_1() {
  var param : f32;
  param = 0.699999988;
  let x_34 : i32 = func_f1_(&(param));
  let x_36 : i32 = x_8.x_GLF_uniform_int_values[1];
  if ((x_34 == x_36)) {
    let x_42 : i32 = x_8.x_GLF_uniform_int_values[1];
    let x_45 : i32 = x_8.x_GLF_uniform_int_values[2];
    let x_48 : i32 = x_8.x_GLF_uniform_int_values[2];
    let x_51 : i32 = x_8.x_GLF_uniform_int_values[1];
    x_GLF_color = vec4<f32>(f32(x_42), f32(x_45), f32(x_48), f32(x_51));
  } else {
    let x_55 : i32 = x_8.x_GLF_uniform_int_values[2];
    let x_56 : f32 = f32(x_55);
    x_GLF_color = vec4<f32>(x_56, x_56, x_56, x_56);
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
