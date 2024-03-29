type Arr = @stride(16) array<i32, 4>;

struct buf0 {
  x_GLF_uniform_int_values : Arr;
};

type Arr_1 = @stride(16) array<f32, 2>;

struct buf1 {
  x_GLF_uniform_float_values : Arr_1;
};

@group(0) @binding(0) var<uniform> x_6 : buf0;

@group(0) @binding(1) var<uniform> x_9 : buf1;

var<private> x_GLF_color : vec4<f32>;

fn main_1() {
  var m : mat3x3<f32>;
  var a : i32;
  var arr : array<vec3<f32>, 2>;
  var v : vec3<f32>;
  let x_45 : i32 = x_6.x_GLF_uniform_int_values[0];
  let x_46 : f32 = f32(x_45);
  m = mat3x3<f32>(vec3<f32>(x_46, 0.0, 0.0), vec3<f32>(0.0, x_46, 0.0), vec3<f32>(0.0, 0.0, x_46));
  let x_52 : i32 = x_6.x_GLF_uniform_int_values[0];
  a = x_52;
  let x_53 : i32 = a;
  let x_54 : i32 = a;
  let x_56 : f32 = x_9.x_GLF_uniform_float_values[0];
  m[x_53][x_54] = x_56;
  let x_59 : vec3<f32> = m[1];
  let x_61 : vec3<f32> = m[1];
  arr = array<vec3<f32>, 2>(x_59, x_61);
  let x_64 : f32 = x_9.x_GLF_uniform_float_values[1];
  v = vec3<f32>(x_64, x_64, x_64);
  let x_66 : i32 = a;
  let x_68 : vec3<f32> = arr[x_66];
  let x_69 : vec3<f32> = v;
  v = (x_69 + x_68);
  let x_71 : vec3<f32> = v;
  let x_73 : i32 = x_6.x_GLF_uniform_int_values[1];
  let x_76 : i32 = x_6.x_GLF_uniform_int_values[2];
  let x_79 : i32 = x_6.x_GLF_uniform_int_values[1];
  if (all((x_71 == vec3<f32>(f32(x_73), f32(x_76), f32(x_79))))) {
    let x_88 : i32 = x_6.x_GLF_uniform_int_values[0];
    let x_91 : i32 = x_6.x_GLF_uniform_int_values[3];
    let x_94 : i32 = x_6.x_GLF_uniform_int_values[3];
    let x_97 : i32 = x_6.x_GLF_uniform_int_values[0];
    x_GLF_color = vec4<f32>(f32(x_88), f32(x_91), f32(x_94), f32(x_97));
  } else {
    let x_101 : i32 = x_6.x_GLF_uniform_int_values[3];
    let x_102 : f32 = f32(x_101);
    x_GLF_color = vec4<f32>(x_102, x_102, x_102, x_102);
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
