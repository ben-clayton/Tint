Texture2DArray arg_0 : register(t0, space1);

void textureLoad_9b2667() {
  float res = arg_0.Load(int4(0, 0, 1, 0)).x;
}

struct tint_symbol {
  float4 value : SV_Position;
};

tint_symbol vertex_main() {
  textureLoad_9b2667();
  const tint_symbol tint_symbol_1 = {float4(0.0f, 0.0f, 0.0f, 0.0f)};
  return tint_symbol_1;
}

void fragment_main() {
  textureLoad_9b2667();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  textureLoad_9b2667();
  return;
}
