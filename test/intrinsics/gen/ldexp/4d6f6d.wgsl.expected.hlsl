struct tint_symbol {
  float4 value : SV_Position;
};

void ldexp_4d6f6d() {
  float4 res = ldexp(float4(0.0f, 0.0f, 0.0f, 0.0f), uint4(0u, 0u, 0u, 0u));
}

tint_symbol vertex_main() {
  ldexp_4d6f6d();
  const tint_symbol tint_symbol_1 = {float4(0.0f, 0.0f, 0.0f, 0.0f)};
  return tint_symbol_1;
}

void fragment_main() {
  ldexp_4d6f6d();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  ldexp_4d6f6d();
  return;
}
