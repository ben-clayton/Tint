SKIP: FAILED

#version 310 es

struct frexp_result_vec4 {
  vec4 sig;
  ivec4 exp;
};

frexp_result_vec4 tint_frexp(vec4 param_0) {
  float4 exp;
  float4 sig = frexp(param_0, exp);
  frexp_result_vec4 result = {sig, int4(exp)};
  return result;
}


void frexp_3c4f48() {
  frexp_result_vec4 res = tint_frexp(vec4(0.0f, 0.0f, 0.0f, 0.0f));
}

vec4 vertex_main() {
  frexp_3c4f48();
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
ERROR: 0:9: 'float4' : undeclared identifier 
ERROR: 0:9: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



#version 310 es
precision mediump float;

struct frexp_result_vec4 {
  vec4 sig;
  ivec4 exp;
};

frexp_result_vec4 tint_frexp(vec4 param_0) {
  float4 exp;
  float4 sig = frexp(param_0, exp);
  frexp_result_vec4 result = {sig, int4(exp)};
  return result;
}


void frexp_3c4f48() {
  frexp_result_vec4 res = tint_frexp(vec4(0.0f, 0.0f, 0.0f, 0.0f));
}

void fragment_main() {
  frexp_3c4f48();
}

void main() {
  fragment_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:10: 'float4' : undeclared identifier 
ERROR: 0:10: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



#version 310 es

struct frexp_result_vec4 {
  vec4 sig;
  ivec4 exp;
};

frexp_result_vec4 tint_frexp(vec4 param_0) {
  float4 exp;
  float4 sig = frexp(param_0, exp);
  frexp_result_vec4 result = {sig, int4(exp)};
  return result;
}


void frexp_3c4f48() {
  frexp_result_vec4 res = tint_frexp(vec4(0.0f, 0.0f, 0.0f, 0.0f));
}

void compute_main() {
  frexp_3c4f48();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:9: 'float4' : undeclared identifier 
ERROR: 0:9: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



