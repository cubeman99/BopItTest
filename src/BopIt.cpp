#include "BopIt.h"
#include <stdlib.h>
#include <iostream>
#include <ctime>


BopIt::BopIt() {
	playing = false;
	score = 0;
	currentAction = ACTION_NONE;
	respondTime = 5.0f;
	increaseSpeed = 0.9f;
	insultedCounter = 0;
	instultedFlag = 0;
}

void BopIt::startGame() {
	playing = true;
	currentAction = ACTION_TWIST;
	updateCurrentTime();
}

BopItAction BopIt::getCurrentAction() { 
	if (playing == false) {
		return ACTION_NONE;
	}
	else {
		return currentAction;
	}	 
}
/*
i think having a enum of this might be a problem
*/
bool BopIt::performAction(BopItAction action) {
	bool gotRightAnswer = false;

	float timeElapsed = float(clock() - startingTime) / CLOCKS_PER_SEC;

	float insultPenalty = respondTime * float(.25 * insultedCounter);
	if (timeElapsed > (respondTime - insultPenalty)) {
		endGame();
		return false;
	}

	if (currentAction == action) {
		gotRightAnswer = true;
		score += 1;
		respondTime *= increaseSpeed;
		updateCurrentTime();
	}
	else {
		endGame();
	}

	if (instultedFlag == true) {
		score -= 1;
		instultedFlag = false;
		if (insultedCounter >= 3) {
			endGame();
			score = 0;
			return false;
		}
	}
	return gotRightAnswer;

}

void BopIt::endGame() {
	playing = false;
	currentAction = ACTION_NONE;
}

BopItAction BopIt::setRandomBopItAction() {
	return (BopItAction)(rand() % NUM_ACTIONS);
}
void BopIt::updateCurrentTime() {
	startingTime = clock();
}


void BopIt::insult() {
	instultedFlag = 1;
	insultedCounter++;
}

