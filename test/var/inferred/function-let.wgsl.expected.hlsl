SKIP: FAILED



Validation Failure:
struct MyStruct {
  float f1;
};
struct tint_symbol {
  float4 value : SV_Target0;
};

int ret_i32() {
  return 1;
}

uint ret_u32() {
  return 1u;
}

float ret_f32() {
  return 1.0f;
}

MyStruct ret_MyStruct() {
  const MyStruct tint_symbol_1 = {0.0f};
  return tint_symbol_1;
}

float[10] ret_MyArray() {
  const float tint_symbol_2[10] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  return tint_symbol_2;
}

void let_decls() {
  const int v1 = 1;
  const uint v2 = 1u;
  const float v3 = 1.0f;
  const int3 v4 = int3(1, 1, 1);
  const uint3 v5 = uint3(1u, 1u, 1u);
  const float3 v6 = float3(1.0f, 1.0f, 1.0f);
  const float3x3 v7 = float3x3(v6, v6, v6);
  const MyStruct v8 = {1.0f};
  const float v9[10] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  const int v10 = ret_i32();
  const uint v11 = ret_u32();
  const float v12 = ret_f32();
  const MyStruct v13 = ret_MyStruct();
  const MyStruct v14 = ret_MyStruct();
  const float v15[10] = ret_MyArray();
}

tint_symbol main() {
  const tint_symbol tint_symbol_3 = {float4(0.0f, 0.0f, 0.0f, 0.0f)};
  return tint_symbol_3;
}


C:\src\temp\ut9k.0:25:24: error: brackets are not allowed here; to declare an array, place the brackets after the name
float[10] ret_MyArray() {
     ~~~~              ^
                       [10]
