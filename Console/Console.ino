#include "Engine.h"
#include "src/SnakeGame.h"
#include "src/SpaceGame.h"
#include "src/PongGame.h"
#include "src/Game.h"

const bool showStartupSequence = true;
const int numGames = 3;

int activeGameIndex = 0;
unsigned long timeOld;

Engine engine = Engine();
Game* game = new SnakeGame();

void setup() {
  Serial.begin(115200);
  
  engine.setDisplayBrightness(4);

  if (showStartupSequence) {
    startupSequence();
  }
  
  timeOld = millis();
}

void loop() {
  // Calculate delta time
  unsigned long frameStartTime = millis();
  unsigned long deltaTimeMillis = frameStartTime - timeOld;
  float deltaTime = deltaTimeMillis / 1000.0;
  timeOld = frameStartTime;

  // Update
  engine.clearScreen();
  engine.updateLoop(deltaTime);
  handleGames(deltaTime);
  engine.drawToDisplay();

  // Wait for target fps
  unsigned long endTime = millis();
  unsigned long frameTime = endTime - frameStartTime;

  const unsigned long targetDelay = 16;
  if (frameTime < targetDelay) {
    unsigned long waitForFPSTime = targetDelay - frameTime;
    delay(waitForFPSTime);
  }

}

void handleGames(float deltaTime) {
  game->updateLoop(engine);

  const float switchGameButtonHoldTime = 0.75;
  if (engine.buttonBUpThisFrame && engine.buttonBDownDuration > switchGameButtonHoldTime) {
    switchGame();
  }
}

void switchGame() {
  activeGameIndex += 1;
  activeGameIndex %= numGames;
  delete game;
  
  if (activeGameIndex == 0) {
    game = new SnakeGame;
  }
  else if (activeGameIndex == 1) {
    game = new SpaceGame;
  }
  else if (activeGameIndex == 2) {
    game = new PongGame;
  }

}

void startupSequence() {
  // Frame 1
  for (int y = 0; y < 8; y ++) {
    for (int x = 0; x < 16; x ++) {
      if (!(x <= y || x-8 >= y)) {
        engine.setPixel(x,y);
      }
    }
  }
  engine.drawToDisplay();
  delay(320);

  // Frame 2
  for (int y = 0; y < 8; y ++) {
    for (int x = 0; x < 16; x ++) {
      if (x <= y) {
        engine.setPixel(x,y);
      }
    }
  }
  engine.drawToDisplay();
  delay(320);

  // Frame 3
  for (int y = 0; y < 8; y ++) {
    for (int x = 0; x < 16; x ++) {
        engine.setPixel(x,y);
     }
   }
  engine.drawToDisplay();
  delay(700);

  // Transition out
  for (int i = 0; i < 16; i ++) {
    for (int x = 0; x < 16; x ++) {
      for (int y = 0; y < 8; y ++) {
        if ((x+(8-y) <= i || 16-x+y <= i)) {
          engine.setPixelToValue(x, y, false);
        }
      }
    }
    engine.drawToDisplay();
    delay(35);
  }
  delay(30);
}
