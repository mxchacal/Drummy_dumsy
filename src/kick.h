#ifndef KICK_H
#define KICK_H

#include <Audio.h>

class Kick {
public:
  Kick();
  AudioSynthWaveformModulated  sine;
  AudioFilterStateVariable     lpf;
  AudioEffectEnvelope          env;
private:
};


#endif
