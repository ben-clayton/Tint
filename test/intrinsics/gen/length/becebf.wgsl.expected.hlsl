struct tint_symbol {
  float4 value : SV_Position;
};

void length_becebf() {
  float res = length(float4(0.0f, 0.0f, 0.0f, 0.0f));
}

tint_symbol vertex_main() {
  length_becebf();
  const tint_symbol tint_symbol_1 = {float4(0.0f, 0.0f, 0.0f, 0.0f)};
  return tint_symbol_1;
}

void fragment_main() {
  length_becebf();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  length_becebf();
  return;
}
