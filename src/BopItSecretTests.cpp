#include "BopIt.h"
#include <stdlib.h>
#include <iostream>
#include <ctime>

BopIt::BopIt() {
	playing = false;
	score = 0;
	currentAction = ACTION_NONE;
	respondTime = 5.0f;
	increaseSpeed = 1.2;

	mapBopItAction["ACTION_BOP"] = ACTION_BOP;
	mapBopItAction["ACTION_PULL"] = ACTION_PULL;
	mapBopItAction["ACTION_TWIST"] = ACTION_TWIST;
	mapBopItAction["ACTION_SPIN"] = ACTION_SPIN;
	mapBopItAction["ACTION_FLICK"] = ACTION_FLICK;
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
	if (currentAction == action) {
		gotRightAnswer = true;
		updateCurrentTime();
	}

	if(gotRightAnswer){
		score += 1;
	}
	else {
		endGame();
	}

	return gotRightAnswer;

	/*
	i have to end game if they preforme the wrong action
	*/
}

void BopIt::endGame() {
	playing = false;
	currentAction = ACTION_NONE;
}

BopItAction BopIt::setRandomBopItAction() {
	return (BopItAction)(rand() % NUM_ACTIONS);
}
void BopIt::updateCurrentTime() {
	startingTime = time(0);
}
