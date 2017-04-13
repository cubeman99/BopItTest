#include <gtest/gtest.h>

class ScoreBoard {
public:
	ScoreBoard(std::string highScoreFileLocation);
	
	//load the high score values into 
	//peopleHighScores
	//peopleUserNames
	void loadHighScores();

	//wrights the high scores to higherScoreFilelocation
	void wrightHighScores();

	//set the highScore file location and
	//return a 0 if it fails and set the 
	//filelocation to ""
	bool setHighScoreFileLocation(std::string);

	// adds the users to the peopleHighScores and
	// peopleUsersNames and return 0 if its not high enough
	bool addScore(std::string, int);

	// dispaly the high scores.
	// you can do what ever you like with this.
	// as long as they have the high score users.
	std::string displayScoresText();




	int highScoreLimit;
	std::string highScoreFileLocation;

	int peopleHighScores[];
	std::string peopleUserNames[];
};