SKIP: FAILED

#version 310 es
precision mediump float;

layout(binding = 1) buffer SB_RO_1 {
  uint arg_0[];
} sb_ro;
void arrayLength_cfca0a() {
  uint tint_symbol_1 = 0u;
  sb_ro.GetDimensions(tint_symbol_1);
  uint tint_symbol_2 = ((tint_symbol_1 - 0u) / 4u);
  uint res = tint_symbol_2;
}

vec4 vertex_main() {
  arrayLength_cfca0a();
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
ERROR: 0:9: 'GetDimensions' : no such field in structure 
ERROR: 0:9: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



#version 310 es
precision mediump float;

layout(binding = 1) buffer SB_RO_1 {
  uint arg_0[];
} sb_ro;
void arrayLength_cfca0a() {
  uint tint_symbol_1 = 0u;
  sb_ro.GetDimensions(tint_symbol_1);
  uint tint_symbol_2 = ((tint_symbol_1 - 0u) / 4u);
  uint res = tint_symbol_2;
}

void fragment_main() {
  arrayLength_cfca0a();
}

void main() {
  fragment_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:9: 'GetDimensions' : no such field in structure 
ERROR: 0:9: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



#version 310 es
precision mediump float;

layout(binding = 1) buffer SB_RO_1 {
  uint arg_0[];
} sb_ro;
void arrayLength_cfca0a() {
  uint tint_symbol_1 = 0u;
  sb_ro.GetDimensions(tint_symbol_1);
  uint tint_symbol_2 = ((tint_symbol_1 - 0u) / 4u);
  uint res = tint_symbol_2;
}

void compute_main() {
  arrayLength_cfca0a();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:9: 'GetDimensions' : no such field in structure 
ERROR: 0:9: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.


