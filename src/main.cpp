#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "drums.h"

struct IO {
  AudioOutputAnalog           output;
  AudioOutputUSB              usb;
};

IO    io;
Clap  clap;
Kick  kick;
HH    hihat;

void doCons();

void setup() {
  doCons(); //make audioconnections
}

void loop() {
}

void doCons() {
  //Clap
  AudioConnection          patchCord1(clap.noise, 0, clap.bpf, 0);
  AudioConnection          patchCord2(clap.bpf, 1, clap.env, 0);
  //Kick
  //HH
  //mixers
}
