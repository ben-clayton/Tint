Texture2D<int4> arg_0 : register(t0, space1);

void textureLoad_dee8e7() {
  int4 res = arg_0.Load(int3(0, 0, 0));
}

struct tint_symbol {
  float4 value : SV_Position;
};

tint_symbol vertex_main() {
  textureLoad_dee8e7();
  const tint_symbol tint_symbol_1 = {float4(0.0f, 0.0f, 0.0f, 0.0f)};
  return tint_symbol_1;
}

void fragment_main() {
  textureLoad_dee8e7();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  textureLoad_dee8e7();
  return;
}
