SKIP: FAILED

#version 310 es

struct modf_result_vec2 {
  vec2 fract;
  vec2 whole;
};

modf_result_vec2 tint_modf(vec2 param_0) {
  float2 whole;
  float2 fract = modf(param_0, whole);
  modf_result_vec2 result = {fract, whole};
  return result;
}


void modf_f5f20d() {
  modf_result_vec2 res = tint_modf(vec2(0.0f, 0.0f));
}

vec4 vertex_main() {
  modf_f5f20d();
  return vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

void main() {
  vec4 inner_result = vertex_main();
  gl_Position = inner_result;
  gl_Position.y = -(gl_Position.y);
  gl_Position.z = ((2.0f * gl_Position.z) - gl_Position.w);
  return;
}
Error parsing GLSL shader:
ERROR: 0:9: 'float2' : undeclared identifier 
ERROR: 0:9: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



#version 310 es
precision mediump float;

struct modf_result_vec2 {
  vec2 fract;
  vec2 whole;
};

modf_result_vec2 tint_modf(vec2 param_0) {
  float2 whole;
  float2 fract = modf(param_0, whole);
  modf_result_vec2 result = {fract, whole};
  return result;
}


void modf_f5f20d() {
  modf_result_vec2 res = tint_modf(vec2(0.0f, 0.0f));
}

void fragment_main() {
  modf_f5f20d();
}

void main() {
  fragment_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:10: 'float2' : undeclared identifier 
ERROR: 0:10: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



#version 310 es

struct modf_result_vec2 {
  vec2 fract;
  vec2 whole;
};

modf_result_vec2 tint_modf(vec2 param_0) {
  float2 whole;
  float2 fract = modf(param_0, whole);
  modf_result_vec2 result = {fract, whole};
  return result;
}


void modf_f5f20d() {
  modf_result_vec2 res = tint_modf(vec2(0.0f, 0.0f));
}

void compute_main() {
  modf_f5f20d();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:9: 'float2' : undeclared identifier 
ERROR: 0:9: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



