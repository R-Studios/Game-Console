#include "PongGame.h"
#include "Arduino.h"

PongGame::PongGame() {
	playerPos.x = 0;
	playerPos.y = 4;
	ballX = 2;
	ballY = 4;
	speedX = 1;
	speedY = 1;
	lastUpdateTime = 0;
	elapsedTime = 0;
	gameOver = false;
	scoreDisplayAmount = 0;
}

void PongGame::updateLoop(Engine& engine) {
	
	if (gameOver) {
		scoreDisplayAmount += engine.deltaTime * 10;
		for (int i = 0; i < scoreDisplayAmount; i ++) {
			int x = i % 16;
			int y = i / 16;
			engine.setPixel(x, y);
		}
		return;
	}
	elapsedTime += engine.deltaTime;

	// Move player
	playerPos.y += engine.deltaTime * playerSpeed * engine.inputY;
	if (playerPos.y > 6) {
		playerPos.y = 6;
	}
	else if (playerPos.y < 1) {
		playerPos.y = 1;
	}

	// Draw player
	int playerCoordX = (int)playerPos.x;
	int playerCoordY = (int)playerPos.y;
	engine.setPixel(playerCoordX, playerCoordY - 1);
	engine.setPixel(playerCoordX, playerCoordY);
	engine.setPixel(playerCoordX, playerCoordY + 1);

	// Update ball
	if (elapsedTime - lastUpdateTime > timeBetweenFrames) {
		lastUpdateTime = elapsedTime;

		if (ballX == 1) {
			if (ballY >= playerCoordY - 1 && ballY <= playerCoordY + 1) {
				speedX = -speedX;
				scoreDisplayAmount++;
				if (timeBetweenFrames <= 0) {
					timeBetweenFrames = 0.01;
				}
				else {
					timeBetweenFrames -= 0.01;
				}
			}
			else {
				gameOver = true;
			}
		}
		if (ballX == 14) {
			speedX = -speedX;
		}
		if (ballY == 0 || ballY == 7) {
			speedY = -speedY;
		}
		ballX += speedX;
		ballY += speedY;
	}

	// Draw enemy paddle
	int paddleCoordY = ballY;
	if (ballY < 1) {
		paddleCoordY = 1;
	}
	else if (ballY > 6) {
		paddleCoordY = 6;
	}
	engine.setPixel(15, paddleCoordY - 1);
	engine.setPixel(15, paddleCoordY);
	engine.setPixel(15, paddleCoordY + 1);

	// Draw ball
	engine.setPixel(ballX, ballY);
}