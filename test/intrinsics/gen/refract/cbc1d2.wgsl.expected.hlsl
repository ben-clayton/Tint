void refract_cbc1d2() {
  float3 res = refract(float3(0.0f, 0.0f, 0.0f), float3(0.0f, 0.0f, 0.0f), 1.0f);
}

struct tint_symbol {
  float4 value : SV_Position;
};

tint_symbol vertex_main() {
  refract_cbc1d2();
  const tint_symbol tint_symbol_1 = {float4(0.0f, 0.0f, 0.0f, 0.0f)};
  return tint_symbol_1;
}

void fragment_main() {
  refract_cbc1d2();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  refract_cbc1d2();
  return;
}
