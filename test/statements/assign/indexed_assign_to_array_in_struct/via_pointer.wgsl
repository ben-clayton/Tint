struct Uniforms {
  i : u32;
};

struct InnerS {
  v : i32;
};

struct OuterS {
  a1 : array<InnerS, 8>;
};

@group(1) @binding(4) var<uniform> uniforms : Uniforms;

@stage(compute) @workgroup_size(1)
fn main() {
  var v : InnerS;
  var s1 : OuterS;
  let p = &(s1.a1[uniforms.i]);
  *p = v;
}
