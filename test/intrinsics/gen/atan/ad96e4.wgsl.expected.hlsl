struct tint_symbol {
  float4 value : SV_Position;
};

void atan_ad96e4() {
  float2 res = atan(float2(0.0f, 0.0f));
}

tint_symbol vertex_main() {
  atan_ad96e4();
  const tint_symbol tint_symbol_1 = {float4(0.0f, 0.0f, 0.0f, 0.0f)};
  return tint_symbol_1;
}

void fragment_main() {
  atan_ad96e4();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  atan_ad96e4();
  return;
}
