SKIP: FAILED

static uint x_1 = 0u;
static uint x_2 = 0u;
static uint x_3 = 0u;
static uint x_4 = 0u;

void main_1() {
  return;
}

struct main_out {
  uint x_2_1;
  uint x_4_1;
};
struct tint_symbol_1 {
  uint x_1_param : TEXCOORD0;
  uint x_3_param : TEXCOORD30;
};
struct tint_symbol_2 {
  uint x_2_1 : SV_Target0;
  uint x_4_1 : SV_Target40;
};

tint_symbol_2 main(tint_symbol_1 tint_symbol) {
  const uint x_1_param = tint_symbol.x_1_param;
  const uint x_3_param = tint_symbol.x_3_param;
  x_1 = x_1_param;
  x_3 = x_3_param;
  main_1();
  const main_out tint_symbol_3 = {x_2, x_4};
  const tint_symbol_2 tint_symbol_4 = {tint_symbol_3.x_2_1, tint_symbol_3.x_4_1};
  return tint_symbol_4;
}
warning: DXIL.dll not found.  Resulting DXIL will not be signed for use in release environments.

error: validation errors
error: SV_Target semantic index exceeds maximum (7).
Validation failed.


