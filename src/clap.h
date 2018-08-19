#ifndef CLAP_H
#define CLAP_H

#include <Audio.h>
#include "Effect-ClapEnv.h"

class Clap {
public:
  Clap();

  void trigger();

  void decay(int decay)   { env_b.decay(decay); }
  void cutoff(int cutoff) { bpf.frequency(cutoff); }
  void rez(int rez)       { bpf.resonance(rez); }

  AudioSynthNoiseWhite     noise;
  AudioFilterStateVariable bpf;
  AudioEffectClapEnvelope  env_a;
  AudioEffectEnvelope      env_b;
  AudioMixer4              mixer;
};

#endif
