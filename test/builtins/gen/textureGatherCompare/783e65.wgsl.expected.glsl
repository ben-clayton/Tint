SKIP: FAILED

#version 310 es

uniform highp sampler2DArrayShadow arg_0_arg_1;

void textureGatherCompare_783e65() {
  vec4 res = textureGather(arg_0_arg_1, vec4(0.0f, 0.0f, float(1), 1.0f));
}

vec4 vertex_main() {
  textureGatherCompare_783e65();
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
ERROR: 0:6: 'textureGather' : no matching overloaded function found 
ERROR: 0:6: '=' :  cannot convert from ' const float' to ' temp highp 4-component vector of float'
ERROR: 0:6: '' : compilation terminated 
ERROR: 3 compilation errors.  No code generated.



#version 310 es
precision mediump float;

uniform highp sampler2DArrayShadow arg_0_arg_1;

void textureGatherCompare_783e65() {
  vec4 res = textureGather(arg_0_arg_1, vec4(0.0f, 0.0f, float(1), 1.0f));
}

void fragment_main() {
  textureGatherCompare_783e65();
}

void main() {
  fragment_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:7: 'textureGather' : no matching overloaded function found 
ERROR: 0:7: '=' :  cannot convert from ' const float' to ' temp mediump 4-component vector of float'
ERROR: 0:7: '' : compilation terminated 
ERROR: 3 compilation errors.  No code generated.



#version 310 es

uniform highp sampler2DArrayShadow arg_0_arg_1;

void textureGatherCompare_783e65() {
  vec4 res = textureGather(arg_0_arg_1, vec4(0.0f, 0.0f, float(1), 1.0f));
}

void compute_main() {
  textureGatherCompare_783e65();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:6: 'textureGather' : no matching overloaded function found 
ERROR: 0:6: '=' :  cannot convert from ' const float' to ' temp highp 4-component vector of float'
ERROR: 0:6: '' : compilation terminated 
ERROR: 3 compilation errors.  No code generated.



