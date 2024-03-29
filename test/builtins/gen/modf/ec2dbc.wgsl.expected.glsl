SKIP: FAILED

#version 310 es

struct modf_result_vec4 {
  vec4 fract;
  vec4 whole;
};

modf_result_vec4 tint_modf(vec4 param_0) {
  float4 whole;
  float4 fract = modf(param_0, whole);
  modf_result_vec4 result = {fract, whole};
  return result;
}


void modf_ec2dbc() {
  modf_result_vec4 res = tint_modf(vec4(0.0f, 0.0f, 0.0f, 0.0f));
}

vec4 vertex_main() {
  modf_ec2dbc();
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

struct modf_result_vec4 {
  vec4 fract;
  vec4 whole;
};

modf_result_vec4 tint_modf(vec4 param_0) {
  float4 whole;
  float4 fract = modf(param_0, whole);
  modf_result_vec4 result = {fract, whole};
  return result;
}


void modf_ec2dbc() {
  modf_result_vec4 res = tint_modf(vec4(0.0f, 0.0f, 0.0f, 0.0f));
}

void fragment_main() {
  modf_ec2dbc();
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

struct modf_result_vec4 {
  vec4 fract;
  vec4 whole;
};

modf_result_vec4 tint_modf(vec4 param_0) {
  float4 whole;
  float4 fract = modf(param_0, whole);
  modf_result_vec4 result = {fract, whole};
  return result;
}


void modf_ec2dbc() {
  modf_result_vec4 res = tint_modf(vec4(0.0f, 0.0f, 0.0f, 0.0f));
}

void compute_main() {
  modf_ec2dbc();
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



