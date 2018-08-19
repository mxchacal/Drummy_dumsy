#include "hh.h"

HH::HH() {
  _attack = 20;
  _decay = 10;
  _sustain = 0.3;
  _oh_release = 1000;
  _ch_release = 270;

  _bpf_freq = 10000;
  _hpf_freq = 7000;

  _base_freq = 40;
  _ratio[0] = 2;
  _ratio[1] = 3;
  _ratio[2] = 4.16;
  _ratio[3] = 5.43;
  _ratio[4] = 6.79;
  _ratio[5] = 8.21;

  //squareosc[6]-->mixers-->bpf-->hpf-->env
  for(int i=0; i<6; i++) square[i].begin(1, _base_freq * _ratio[i], WAVEFORM_SQUARE); //begin square osc

  for(int i=0; i<2; i++) for(int j=0; j<4; j++) mixer[i].gain(j, 0.3); //square mixers
  for(int k=0; k<4; k++) mixer[2].gain(k, 0.5);

  bpf.frequency(_bpf_freq); //filters
  bpf.resonance(0.7);

  hpf.frequency(_hpf_freq);
  hpf.resonance(0.7);

  oh_env.attack(_attack);  //open hh envelope
  oh_env.hold(0);
  oh_env.decay(_decay);
  oh_env.sustain(_sustain);
  oh_env.release(_oh_release);

  ch_env.attack(_attack);  //closed hh envelope
  ch_env.hold(0);
  ch_env.decay(_decay);
  ch_env.sustain(_sustain);
  ch_env.release(_ch_release);

}

void HH::trigger(int type) {
  switch(type) {
    case 0: ch_env.noteOn();
    case 1: oh_env.noteOn();
  }
}
