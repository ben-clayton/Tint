#version 310 es

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void unused_entry_point() {
  return;
}
struct S {
  ivec4 arr[4];
};

ivec4 src_private[4] = ivec4[4](ivec4(0, 0, 0, 0), ivec4(0, 0, 0, 0), ivec4(0, 0, 0, 0), ivec4(0, 0, 0, 0));
shared ivec4 src_workgroup[4];
layout(binding = 0) uniform S_1 {
  ivec4 arr[4];
} src_uniform;

layout(binding = 1, std430) buffer S_2 {
  ivec4 arr[4];
} src_storage;
ivec4 dst[4] = ivec4[4](ivec4(0, 0, 0, 0), ivec4(0, 0, 0, 0), ivec4(0, 0, 0, 0), ivec4(0, 0, 0, 0));
int dst_nested[4][3][2] = int[4][3][2](int[3][2](int[2](0, 0), int[2](0, 0), int[2](0, 0)), int[3][2](int[2](0, 0), int[2](0, 0), int[2](0, 0)), int[3][2](int[2](0, 0), int[2](0, 0), int[2](0, 0)), int[3][2](int[2](0, 0), int[2](0, 0), int[2](0, 0)));
ivec4[4] ret_arr() {
  ivec4 tint_symbol[4] = ivec4[4](ivec4(0, 0, 0, 0), ivec4(0, 0, 0, 0), ivec4(0, 0, 0, 0), ivec4(0, 0, 0, 0));
  return tint_symbol;
}

S ret_struct_arr() {
  S tint_symbol_1 = S(ivec4[4](ivec4(0, 0, 0, 0), ivec4(0, 0, 0, 0), ivec4(0, 0, 0, 0), ivec4(0, 0, 0, 0)));
  return tint_symbol_1;
}

void foo(ivec4 src_param[4]) {
  ivec4 src_function[4] = ivec4[4](ivec4(0, 0, 0, 0), ivec4(0, 0, 0, 0), ivec4(0, 0, 0, 0), ivec4(0, 0, 0, 0));
  ivec4 tint_symbol_2[4] = ivec4[4](ivec4(1), ivec4(2), ivec4(3), ivec4(3));
  dst = tint_symbol_2;
  dst = src_param;
  dst = ret_arr();
  ivec4 src_let[4] = ivec4[4](ivec4(0, 0, 0, 0), ivec4(0, 0, 0, 0), ivec4(0, 0, 0, 0), ivec4(0, 0, 0, 0));
  dst = src_let;
  dst = src_function;
  dst = src_private;
  dst = src_workgroup;
  dst = ret_struct_arr().arr;
  dst = src_uniform.arr;
  dst = src_storage.arr;
  int src_nested[4][3][2] = int[4][3][2](int[3][2](int[2](0, 0), int[2](0, 0), int[2](0, 0)), int[3][2](int[2](0, 0), int[2](0, 0), int[2](0, 0)), int[3][2](int[2](0, 0), int[2](0, 0), int[2](0, 0)), int[3][2](int[2](0, 0), int[2](0, 0), int[2](0, 0)));
  dst_nested = src_nested;
}

