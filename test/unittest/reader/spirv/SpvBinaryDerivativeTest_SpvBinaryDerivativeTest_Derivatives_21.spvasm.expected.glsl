SKIP: FAILED

#version 310 es
precision mediump float;

void main_1() {
  float x_2 = ddy_coarse(50.0f);
  return;
}

void tint_symbol() {
  main_1();
}

void main() {
  tint_symbol();
  return;
}
Error parsing GLSL shader:
ERROR: 0:5: 'ddy_coarse' : no matching overloaded function found 
ERROR: 0:5: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



