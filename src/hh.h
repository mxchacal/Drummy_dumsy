#ifndef HH_H
#define HH_H

#include <Audio.h>

class HH {
public:
  HH();
  void trigger(int type);

  void decay(int decay)   { oh_env.release(decay); }
  void cutoff(int cutoff) { bpf.frequency(cutoff); hpf.frequency(cutoff - 3000);}
  void rez(int rez)       { bpf.resonance(rez); hpf.resonance(rez); }

  AudioSynthWaveform        square[6];
  AudioMixer4               mixer[3];
  AudioFilterStateVariable  bpf;
  AudioFilterStateVariable  hpf;
  AudioEffectEnvelope       oh_env;
  AudioEffectEnvelope       ch_env;

private:
  int _attack, _decay, _sustain, _oh_release, _ch_release;
  int _base_freq, _bpf_freq, _hpf_freq;
  float _ratio[6];
};


#endif
