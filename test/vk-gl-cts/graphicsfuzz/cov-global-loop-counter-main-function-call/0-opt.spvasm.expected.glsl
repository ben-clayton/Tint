SKIP: FAILED

#version 310 es
precision mediump float;

layout(location = 0) out vec4 x_GLF_color_1_1;
struct strided_arr {
  int el;
};

struct buf0 {
  strided_arr x_GLF_uniform_int_values[3];
};

int x_GLF_global_loop_count = 0;
layout(binding = 0) uniform buf0_1 {
  strided_arr x_GLF_uniform_int_values[3];
} x_7;

vec4 x_GLF_color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
int func_() {
  while (true) {
    if ((x_GLF_global_loop_count < 100)) {
    } else {
      break;
    }
    x_GLF_global_loop_count = (x_GLF_global_loop_count + 1);
    int x_78 = x_7.x_GLF_uniform_int_values[0].el;
    return x_78;
  }
  int x_80 = x_7.x_GLF_uniform_int_values[2].el;
  return x_80;
}

void main_1() {
  int a = 0;
  x_GLF_global_loop_count = 0;
  while (true) {
    x_GLF_global_loop_count = (x_GLF_global_loop_count + 1);
    if (false) {
      return;
    }
    {
      if ((true & (x_GLF_global_loop_count < 100))) {
      } else {
        break;
      }
    }
  }
  int x_42 = func_();
  a = x_42;
  int x_43 = a;
  int x_45 = x_7.x_GLF_uniform_int_values[2].el;
  if ((x_43 == x_45)) {
    int x_51 = x_7.x_GLF_uniform_int_values[0].el;
    int x_54 = x_7.x_GLF_uniform_int_values[1].el;
    int x_57 = x_7.x_GLF_uniform_int_values[1].el;
    int x_60 = x_7.x_GLF_uniform_int_values[0].el;
    x_GLF_color = vec4(float(x_51), float(x_54), float(x_57), float(x_60));
  } else {
    int x_64 = x_7.x_GLF_uniform_int_values[1].el;
    float x_65 = float(x_64);
    x_GLF_color = vec4(x_65, x_65, x_65, x_65);
  }
  return;
}

struct main_out {
  vec4 x_GLF_color_1;
};

main_out tint_symbol() {
  main_1();
  main_out tint_symbol_1 = main_out(x_GLF_color);
  return tint_symbol_1;
}

void main() {
  main_out inner_result = tint_symbol();
  x_GLF_color_1_1 = inner_result.x_GLF_color_1;
  return;
}
Error parsing GLSL shader:
ERROR: 0:42: '&' :  wrong operand types: no operation '&' exists that takes a left-hand operand of type ' const bool' and a right operand of type ' temp bool' (or there is no acceptable conversion)
ERROR: 0:42: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



