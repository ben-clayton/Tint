SKIP: FAILED

vk-gl-cts/graphicsfuzz/cov-apfloat-mod-zero/0-opt.wgsl:1:13 warning: use of deprecated language feature: the @stride attribute is deprecated; use a larger type if necessary
type Arr = @stride(16) array<i32, 3>;
            ^^^^^^

vk-gl-cts/graphicsfuzz/cov-apfloat-mod-zero/0-opt.wgsl:7:15 warning: use of deprecated language feature: the @stride attribute is deprecated; use a larger type if necessary
type Arr_1 = @stride(16) array<f32, 1>;
              ^^^^^^

#version 310 es
precision mediump float;

layout(location = 0) out vec4 x_GLF_color_1_1;
struct tint_padded_array_element {
  int el;
};

struct buf1 {
  tint_padded_array_element x_GLF_uniform_int_values[3];
};

struct tint_padded_array_element_1 {
  float el;
};

struct buf0 {
  tint_padded_array_element_1 x_GLF_uniform_float_values[1];
};

layout(binding = 1) uniform buf1_1 {
  tint_padded_array_element x_GLF_uniform_int_values[3];
} x_6;

layout(binding = 0) uniform buf0_1 {
  tint_padded_array_element_1 x_GLF_uniform_float_values[1];
} x_8;

vec4 x_GLF_color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
void main_1() {
  float undefined = 0.0f;
  bool x_51 = false;
  bool x_52_phi = false;
  undefined = (5.0f % 0.0f);
  int x_10 = x_6.x_GLF_uniform_int_values[0].el;
  int x_11 = x_6.x_GLF_uniform_int_values[0].el;
  int x_12 = x_6.x_GLF_uniform_int_values[1].el;
  bool x_44 = (x_10 == (x_11 + x_12));
  x_52_phi = x_44;
  if (!(x_44)) {
    float x_48 = undefined;
    float x_50 = x_8.x_GLF_uniform_float_values[0].el;
    x_51 = (x_48 > x_50);
    x_52_phi = x_51;
  }
  if (x_52_phi) {
    int x_15 = x_6.x_GLF_uniform_int_values[0].el;
    int x_16 = x_6.x_GLF_uniform_int_values[1].el;
    int x_17 = x_6.x_GLF_uniform_int_values[1].el;
    int x_18 = x_6.x_GLF_uniform_int_values[0].el;
    x_GLF_color = vec4(float(x_15), float(x_16), float(x_17), float(x_18));
  } else {
    int x_19 = x_6.x_GLF_uniform_int_values[1].el;
    float x_66 = float(x_19);
    x_GLF_color = vec4(x_66, x_66, x_66, x_66);
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
ERROR: 0:34: '%' :  wrong operand types: no operation '%' exists that takes a left-hand operand of type ' const float' and a right operand of type ' const float' (or there is no acceptable conversion)
ERROR: 0:34: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



