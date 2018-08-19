#include "clap.h"

Clap::Clap() {
  noise.amplitude(1);

  bpf.frequency(3000);
  bpf.resonance(0.7);

  mixer.gain(0, 0.5);
  mixer.gain(0, 0.5);

  env_b.attack(0);
  env_b.hold(0);
  env_b.decay(250);
  env_b.sustain(0);
}

void Clap::trigger() {
  env_a.noteOn();
  env_b.noteOn();
}
