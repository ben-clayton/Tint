SKIP: FAILED

#version 310 es

uniform highp samplerCubeArrayShadow arg_0_arg_1;

void textureSampleLevel_ae5e39() {
  float res = textureLod(arg_0_arg_1, vec4(0.0f, 0.0f, 0.0f, float(1)), 0).x;
}

vec4 vertex_main() {
  textureSampleLevel_ae5e39();
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
ERROR: 0:3: 'samplerCubeArrayShadow' : Reserved word. 
ERROR: 0:3: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



#version 310 es
precision mediump float;

uniform highp samplerCubeArrayShadow arg_0_arg_1;

void textureSampleLevel_ae5e39() {
  float res = textureLod(arg_0_arg_1, vec4(0.0f, 0.0f, 0.0f, float(1)), 0).x;
}

void fragment_main() {
  textureSampleLevel_ae5e39();
}

void main() {
  fragment_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:4: 'samplerCubeArrayShadow' : Reserved word. 
ERROR: 0:4: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



#version 310 es

uniform highp samplerCubeArrayShadow arg_0_arg_1;

void textureSampleLevel_ae5e39() {
  float res = textureLod(arg_0_arg_1, vec4(0.0f, 0.0f, 0.0f, float(1)), 0).x;
}

void compute_main() {
  textureSampleLevel_ae5e39();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:3: 'samplerCubeArrayShadow' : Reserved word. 
ERROR: 0:3: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



