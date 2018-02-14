#include "Game.h"
#include "Gameover.h"
#include "GameTask.h"
#include "GameSystem.h"

bool IsGameover;

Game::Game() {
	InitializeTask();
	IsGameover = false;
}

void Game::Update() {
	UpdateTask();
}

void Game::Draw() {
	DrawTask();
	if (IsGameover) {
		Gameover();
		IsGameover = false;
	}
}

Game::~Game() {
	FinalizeTask();
}

void SetGameover() {
	IsGameover = true;
}