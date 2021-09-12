#pragma once
#include "Vector2.h"
#include "Game.h"
#include "../Engine.h"

class PongGame : public Game {
private:
	const float playerSpeed = 8.5;
	
	// Difficulty settings:
	float timeBetweenFrames = 0.2;

	Vector2 playerPos;
	int ballX;
	int ballY;
	int speedX;
	int speedY;

	int scoreDisplayAmount;
	float lastUpdateTime;
	float elapsedTime;
	bool gameOver;
	
public:
	PongGame();
	virtual void updateLoop(Engine&);
};