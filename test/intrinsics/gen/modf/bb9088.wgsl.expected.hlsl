groupshared float3 arg_1;

void modf_bb9088() {
  float3 res = modf(float3(0.0f, 0.0f, 0.0f), arg_1);
}

struct tint_symbol_1 {
  uint local_invocation_index : SV_GroupIndex;
};

[numthreads(1, 1, 1)]
void compute_main(tint_symbol_1 tint_symbol) {
  const uint local_invocation_index = tint_symbol.local_invocation_index;
  if ((local_invocation_index == 0u)) {
    arg_1 = float3(0.0f, 0.0f, 0.0f);
  }
  GroupMemoryBarrierWithGroupSync();
  modf_bb9088();
  return;
}
