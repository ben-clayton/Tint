SKIP: FAILED

#version 310 es

void select_80a9a9() {
  bvec3 res = (bvec3(false, false, false) ? bvec3(false, false, false) : bvec3(false, false, false));
}

vec4 vertex_main() {
  select_80a9a9();
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
ERROR: 0:4: '' : boolean expression expected 
ERROR: 0:4: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



#version 310 es
precision mediump float;

void select_80a9a9() {
  bvec3 res = (bvec3(false, false, false) ? bvec3(false, false, false) : bvec3(false, false, false));
}

void fragment_main() {
  select_80a9a9();
}

void main() {
  fragment_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:5: '' : boolean expression expected 
ERROR: 0:5: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



#version 310 es

void select_80a9a9() {
  bvec3 res = (bvec3(false, false, false) ? bvec3(false, false, false) : bvec3(false, false, false));
}

void compute_main() {
  select_80a9a9();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:4: '' : boolean expression expected 
ERROR: 0:4: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



