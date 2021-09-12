#include "Engine.h"
#include "src/Game.h"

Engine::Engine() {
  ledController.shutdown(0, false);
  ledController.shutdown(1, false);

  pinMode(aPin, INPUT);
  pinMode(bPin, INPUT);

  clearScreen();
  time = 0;
}

void Engine::updateLoop(float deltaTime) {
  this->deltaTime = deltaTime;
  time += deltaTime;

  // Button input:
  int buttonAStateOld = buttonAState;
  buttonAState = digitalRead(aPin);
  buttonADown = buttonAState == 1;
  buttonADownThisFrame = buttonADown && buttonAState != buttonAStateOld;
  buttonAUpThisFrame = buttonAState == 0 && buttonAStateOld == 1;

  if (buttonADownThisFrame) {
    buttonADownDuration = 0;
  }
  if (buttonADown) {
    buttonADownDuration += deltaTime;
  }

  int buttonBStateOld = buttonBState;
  buttonBState = digitalRead(bPin);
  buttonBDown = buttonBState == 1;
  buttonBDownThisFrame = buttonBDown && buttonBState != buttonBStateOld;
  buttonBUpThisFrame = buttonBState == 0 && buttonBStateOld == 1;

  if (buttonBDownThisFrame) {
    buttonBDownDuration = 0;
  }
  if (buttonBDown) {
    buttonBDownDuration += deltaTime;
  }

  // Get analog stick input:
  const float inputThreshold = 0.2;
  inputX = -remap(analogRead(xPin), 0, 1023, -1, 1);
  inputY = -remap(analogRead(yPin), 0, 1023, -1, 1);

  Serial.print("X: ");
  Serial.print(inputX);
  Serial.print(" Y: ");
  Serial.print(inputY);
  Serial.print("\n");

  if (abs(inputX) < inputThreshold) {
    inputX = 0;
  }
  if (abs(inputY) < inputThreshold) {
    inputY = 0;
  }
}

void Engine::clearScreen() {
  for (int i = 0; i < 8; i ++) {
    rowsDisplayA[i] = 0;
    rowsDisplayB[i] = 0;
  }
}

void Engine::drawToDisplay() {
  for (int row = 0; row < 8; row ++) {
    ledController.setRow(0, row, rowsDisplayA[row]);
    ledController.setRow(1, row, rowsDisplayB[row]);
  }
}


// set display brightness [0,15]
void Engine::setDisplayBrightness(int brightness) {
  ledController.setIntensity(0, brightness);
  ledController.setIntensity(1, brightness);
}

void Engine::setPixel(int x, int y) {
  setPixelToValue(x, y, true);
}

void Engine::setPixelToValue(int x, int y, bool on) {
  if (x >= 16 || x < 0 || y >= 8 || y < 0) {
    return;
  }

  if (x < 8) {
    if (on) {
      rowsDisplayA[x] |= 1 << y;
    }
    else {
      rowsDisplayA[x] &= ~(1 << y);
    }
  }
  else {
    if (on) {
      rowsDisplayB[x - 8] |= 1 << y;
    }
    else {
      rowsDisplayB[x - 8] &= ~(1 << y);
    }
  }
}

float Engine::remap(float value, float minOld, float maxOld, float minNew, float maxNew) {
  return minNew + (value - minOld) / (maxOld - minOld) * (maxNew - minNew);
}
