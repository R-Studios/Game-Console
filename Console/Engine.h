#pragma once
#include <Arduino.h>
#include <LedControl.h>

class Engine {

private:

  // Input pins:
  const int aPin = 8; // Button A
  const int bPin = 9; // Button B
  const int xPin = 4; // X Axis
  const int yPin = 3; // Y Axis
  
  // Display pins:
  const int dinPin = 12; // DIN (data in)
  const int csPin = 11; // CLK (clock)
  const int clkPin = 10; // CS (chip select)
  const int numDisplays = 2;

  LedControl ledController = LedControl(dinPin, clkPin, csPin, numDisplays); // (DIN, CLK, CS, num displays)

  unsigned char rowsDisplayA[8];
  unsigned char rowsDisplayB[8];
  int buttonAState;
  int buttonBState;

  float remap(float, float, float, float, float);

public:

  float deltaTime;
  unsigned long time;

  // Player input info:
  float inputX;
  float inputY;
  bool buttonADown;
  bool buttonAUpThisFrame;
  bool buttonADownThisFrame;
  float buttonADownDuration;
  bool buttonBDown;
  bool buttonBUpThisFrame;
  bool buttonBDownThisFrame;
  float buttonBDownDuration;

  Engine();
  void updateLoop(float);
  void clearScreen();
  void setPixel(int x, int y);
  void setPixelToValue(int x, int y, bool on);
  void drawToDisplay();
  void setDisplayBrightness(int);
  
};
