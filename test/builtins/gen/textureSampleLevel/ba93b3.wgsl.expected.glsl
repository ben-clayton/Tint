SKIP: FAILED

#version 310 es

uniform highp sampler2DArrayShadow arg_0_arg_1;

void textureSampleLevel_ba93b3() {
  float res = textureLodOffset(arg_0_arg_1, vec3(0.0f, 0.0f, float(1)), 0, ivec2(0, 0)).x;
}

vec4 vertex_main() {
  textureSampleLevel_ba93b3();
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
ERROR: 0:6: 'textureLodOffset' : no matching overloaded function found 
ERROR: 0:6: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



#version 310 es
precision mediump float;

uniform highp sampler2DArrayShadow arg_0_arg_1;

void textureSampleLevel_ba93b3() {
  float res = textureLodOffset(arg_0_arg_1, vec3(0.0f, 0.0f, float(1)), 0, ivec2(0, 0)).x;
}

void fragment_main() {
  textureSampleLevel_ba93b3();
}

void main() {
  fragment_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:7: 'textureLodOffset' : no matching overloaded function found 
ERROR: 0:7: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



#version 310 es

uniform highp sampler2DArrayShadow arg_0_arg_1;

void textureSampleLevel_ba93b3() {
  float res = textureLodOffset(arg_0_arg_1, vec3(0.0f, 0.0f, float(1)), 0, ivec2(0, 0)).x;
}

void compute_main() {
  textureSampleLevel_ba93b3();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:6: 'textureLodOffset' : no matching overloaded function found 
ERROR: 0:6: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



