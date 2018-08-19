#ifndef HH_H
#define HH_H

#include <Audio.h>

class HH {
public:
  HH();
  AudioSynthWaveform        square[6];
  AudioMixer4               mixer[3];
  AudioFilterStateVariable  bpf;
  AudioFilterStateVariable  hpf;
  AudioEffectEnvelope       oh_env;
  AudioEffectEnvelope       ch_env;

private:
  int attack = 20;
  int decay = 10;
  int sustain = 0.3;
  int oh_release = 1000;
  int ch_release = 270;
  int bpf_freq = 10000;
  int hpf_freq = 7000;
  int base_freq = 40;
  float ratio[6] = {2, 3, 4.16, 5.43, 6.79, 8.21};
};


#endif
