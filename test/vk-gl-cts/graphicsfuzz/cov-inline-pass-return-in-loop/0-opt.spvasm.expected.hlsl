static float4 x_GLF_color = float4(0.0f, 0.0f, 0.0f, 0.0f);

float func_() {
  int i = 0;
  i = 0;
  {
    for(; (i < 10); i = (i + 1)) {
      if ((i > 5)) {
        i = (i + 1);
      }
      if ((i > 8)) {
        return 0.0f;
      }
    }
  }
  return 1.0f;
}

void main_1() {
  if (false) {
    const float x_28 = func_();
    x_GLF_color = float4(x_28, x_28, x_28, x_28);
  } else {
    x_GLF_color = float4(1.0f, 0.0f, 0.0f, 1.0f);
  }
  return;
}

struct main_out {
  float4 x_GLF_color_1;
};
struct tint_symbol {
  float4 x_GLF_color_1 : SV_Target0;
};

tint_symbol main() {
  main_1();
  const main_out tint_symbol_1 = {x_GLF_color};
  const tint_symbol tint_symbol_2 = {tint_symbol_1.x_GLF_color_1};
  return tint_symbol_2;
}