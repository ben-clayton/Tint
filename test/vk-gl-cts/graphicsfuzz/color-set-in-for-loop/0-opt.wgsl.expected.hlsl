SKIP: FAILED

vk-gl-cts/graphicsfuzz/color-set-in-for-loop/0-opt.wgsl:15:5 warning: code is unreachable
    return;
    ^^^^^^

cbuffer cbuffer_x_5 : register(b0, space0) {
  uint4 x_5[1];
};
static float4 x_GLF_color = float4(0.0f, 0.0f, 0.0f, 0.0f);

void main_1() {
  const float x_26 = asfloat(x_5[0].x);
  if ((x_26 > 1.0f)) {
    [loop] while (true) {
      x_GLF_color = float4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    return;
  }
  x_GLF_color = float4(1.0f, 0.0f, 0.0f, 1.0f);
  return;
}

struct main_out {
  float4 x_GLF_color_1;
};
struct tint_symbol {
  float4 x_GLF_color_1 : SV_Target0;
};

main_out main_inner() {
  main_1();
  const main_out tint_symbol_2 = {x_GLF_color};
  return tint_symbol_2;
}

tint_symbol main() {
  const main_out inner_result = main_inner();
  tint_symbol wrapper_result = (tint_symbol)0;
  wrapper_result.x_GLF_color_1 = inner_result.x_GLF_color_1;
  return wrapper_result;
}
error: validation errors
C:\src\temp\u1hm0.0:31: error: Loop must have break.
Validation failed.



