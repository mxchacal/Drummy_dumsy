#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Encoder.h>
#include "utils.h"
#include "kick.h"
#include "clap.h"
#include "hh.h"

#define DEBUG 0
#define TEST  1
#define CHH   0
#define OHH   1

Encoder enc_a(1, 2);
Encoder enc_b(3, 4);
Encoder enc_c(5, 6);
Encoder enc_d(7, 8);
Encoder enc_e(9, 10);

IO    io;
Clap  clap;
Kick  kick;
HH    hihat;

void doCons();
void NoteOn(byte channel, byte note, byte velocity);

void setup() {
  Serial.begin(115200);
  Serial.println("Beginning setup:");

  usbMIDI.setHandleNoteOn(NoteOn);

  doCons(); //make connections


}

void loop() {
  usbMIDI.read();
  Serial.println("usbMIDI.read");
  delay(200);
}

void doCons() {
  AudioConnection          patchCord1(clap.noise, 0, clap.bpf, 0);
  AudioConnection          patchCord2(clap.bpf, 1, clap.env_a, 0);
  AudioConnection          patchCord3(clap.bpf, 1, clap.env_b, 0);
  AudioConnection          patchCord4(clap.env_a, 0, clap.mixer, 0);
  AudioConnection          PatchCord5(clap.env_b, 0, clap.mixer, 1);
  AudioConnection          patchCord6(clap.mixer, 0, io.mixout, 0);

  AudioConnection          patchCord46(io.mixout, 0, io.usb, 0);
  AudioConnection          patchCord47(io.mixout, 0, io.output, 0);
}

void NoteOn(byte channel, byte note, byte velocity) {
  switch(note) {
    case(36): kick.trigger(); //Kick
    case(39): clap.trigger(); //Clap
    case(42): hihat.trigger(CHH); //Closed hh
    case(46): hihat.trigger(OHH); //Opened hh
  }
}
