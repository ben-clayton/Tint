SKIP: FAILED

#version 310 es

void all_353d6a() {
  bool res = all(false);
}

vec4 vertex_main() {
  all_353d6a();
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
ERROR: 0:4: 'all' : no matching overloaded function found 
ERROR: 0:4: '=' :  cannot convert from ' const float' to ' temp bool'
ERROR: 0:4: '' : compilation terminated 
ERROR: 3 compilation errors.  No code generated.



#version 310 es
precision mediump float;

void all_353d6a() {
  bool res = all(false);
}

void fragment_main() {
  all_353d6a();
}

void main() {
  fragment_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:5: 'all' : no matching overloaded function found 
ERROR: 0:5: '=' :  cannot convert from ' const float' to ' temp bool'
ERROR: 0:5: '' : compilation terminated 
ERROR: 3 compilation errors.  No code generated.



#version 310 es

void all_353d6a() {
  bool res = all(false);
}

void compute_main() {
  all_353d6a();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:4: 'all' : no matching overloaded function found 
ERROR: 0:4: '=' :  cannot convert from ' const float' to ' temp bool'
ERROR: 0:4: '' : compilation terminated 
ERROR: 3 compilation errors.  No code generated.



