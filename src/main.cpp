#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "kick.h"
#include "clap.h"
#include "hh.h"
#include "seq.h"

#define DEBUG 0

struct IO {
  AudioMixer4                 mixout;
  AudioOutputAnalog           output;
  AudioOutputUSB              usb;
};

IO    io;
Clap  clap;
Kick  kick;
HH    hihat;

void doCons();

void setup() {
  Serial.begin(115200);
  Serial.println("Beginning setup:");

  doCons(); //make connections


}

void loop() {

}

void doCons() {
  Serial.print("  Initializing AudioConnections ... ");
  //Clap
  AudioConnection          patchCord1(clap.noise, 0, clap.bpf, 0);
  AudioConnection          patchCord2(clap.bpf, 1, clap.env, 0);
  AudioConnection          patchCord3(clap.env, 0, io.mixout, 0);
  Serial.println("    Clap");
  delay(500);
  //Kick

  Serial.println("    Kick");
  delay(500);
  //HH

  Serial.println("    Hihats");
  //output
  AudioConnection          patchCord46(io.mixout, 0, io.usb, 0);
  AudioConnection          patchCord47(io.mixout, 0, io.output, 0);
  Serial.println("Done");
}
