RWTexture2D<int4> arg_0 : register(u0, space1);

void textureStore_804942() {
  arg_0[int2(0, 0)] = int4(0, 0, 0, 0);
}

struct tint_symbol {
  float4 value : SV_Position;
};

tint_symbol vertex_main() {
  textureStore_804942();
  const tint_symbol tint_symbol_1 = {float4(0.0f, 0.0f, 0.0f, 0.0f)};
  return tint_symbol_1;
}

void fragment_main() {
  textureStore_804942();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  textureStore_804942();
  return;
}
