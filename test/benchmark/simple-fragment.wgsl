struct Input {
  @location(0) color: vec4<f32>;
};

struct Output {
  @location(0) color: vec4<f32>;
};

@stage(fragment)
fn main(in : Input) -> Output {
  return Output(in.color);
}
