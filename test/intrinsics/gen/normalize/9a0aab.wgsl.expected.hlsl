void normalize_9a0aab() {
  float4 res = normalize(float4(0.0f, 0.0f, 0.0f, 0.0f));
}

struct tint_symbol {
  float4 value : SV_Position;
};

tint_symbol vertex_main() {
  normalize_9a0aab();
  const tint_symbol tint_symbol_1 = {float4(0.0f, 0.0f, 0.0f, 0.0f)};
  return tint_symbol_1;
}

void fragment_main() {
  normalize_9a0aab();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  normalize_9a0aab();
  return;
}
