builtins/gen/isFinite/34d32b.wgsl:28:25 warning: use of deprecated builtin
  var res: vec2<bool> = isFinite(vec2<f32>());
                        ^^^^^^^^

void isFinite_34d32b() {
  bool2 res = isfinite(float2(0.0f, 0.0f));
}

struct tint_symbol {
  float4 value : SV_Position;
};

float4 vertex_main_inner() {
  isFinite_34d32b();
  return float4(0.0f, 0.0f, 0.0f, 0.0f);
}

tint_symbol vertex_main() {
  const float4 inner_result = vertex_main_inner();
  tint_symbol wrapper_result = (tint_symbol)0;
  wrapper_result.value = inner_result;
  return wrapper_result;
}

void fragment_main() {
  isFinite_34d32b();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  isFinite_34d32b();
  return;
}
