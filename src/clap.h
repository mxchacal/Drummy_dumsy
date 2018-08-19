#ifndef CLAP_H
#define CLAP_H

#include <Audio.h>

class Clap {
public:
  Clap();
  AudioSynthNoiseWhite     noise;
  AudioFilterStateVariable bpf;
  AudioEffectEnvelope      env;

private:
};

#endif
