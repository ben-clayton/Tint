SKIP: FAILED

#version 310 es
precision mediump float;

layout(location = 0) out vec4 x_GLF_color_1_1;
struct buf0 {
  vec2 threeandfour;
};

layout(binding = 0) uniform buf0_1 {
  vec2 threeandfour;
} x_6;

vec4 x_GLF_color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
void main_1() {
  vec4 v = vec4(0.0f, 0.0f, 0.0f, 0.0f);
  v = vec4(2.0f, 3.0f, 4.0f, 5.0f);
  float x_40 = x_6.threeandfour.y;
  vec2 x_42 = (bvec2(true, false) ? vec2(1.0f, x_40) : vec2(2.0f, 6.0f));
  vec4 x_43 = v;
  v = vec4(x_42.x, x_42.y, x_43.z, x_43.w);
  if (all(equal(v, vec4(1.0f, 6.0f, 4.0f, 5.0f)))) {
    x_GLF_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
  } else {
    x_GLF_color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
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
ERROR: 0:18: '' : boolean expression expected 
ERROR: 0:18: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



