void asin_8cd9c9() {
  float3 res = asin(float3(0.0f, 0.0f, 0.0f));
}

struct tint_symbol {
  float4 value : SV_Position;
};

tint_symbol vertex_main() {
  asin_8cd9c9();
  const tint_symbol tint_symbol_1 = {float4(0.0f, 0.0f, 0.0f, 0.0f)};
  return tint_symbol_1;
}

void fragment_main() {
  asin_8cd9c9();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  asin_8cd9c9();
  return;
}
