static int3 arg_1;

void frexp_6efa09() {
  float3 tint_tmp;
  float3 tint_tmp_1 = frexp(float3(0.0f, 0.0f, 0.0f), tint_tmp);
  arg_1 = int3(tint_tmp);
  float3 res = tint_tmp_1;
}

struct tint_symbol {
  float4 value : SV_Position;
};

tint_symbol vertex_main() {
  frexp_6efa09();
  const tint_symbol tint_symbol_1 = {float4(0.0f, 0.0f, 0.0f, 0.0f)};
  return tint_symbol_1;
}

void fragment_main() {
  frexp_6efa09();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  frexp_6efa09();
  return;
}