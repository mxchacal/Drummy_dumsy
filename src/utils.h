#ifndef UTILS_H
#define UTILS_H
#include <Audio.h>

struct IO {
  AudioMixer4                 mixout;
  AudioOutputAnalog           output;
  AudioOutputUSB              usb;
};

#endif
