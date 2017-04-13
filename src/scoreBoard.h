#ifndef _SCORE_BOARD_H_
#define _SCORE_BOARD_H_

#include <gtest/gtest.h>


struct HighScore
{
	std::string name;
	int score;

	HighScore(const std::string& name, int score) :
		name(name),
		score(score)
	{
	}
};


class ScoreBoard
{
public:
	ScoreBoard(const std::string& highScoreFileLocation);
	
	// load the high score values into 
	// peopleHighScores
	// peopleUserNames
	void loadHighScores();

	// Writes the high scores to highScoreFilelocation
	void writeHighScores();

	void setMaxNumHighScores(int maxNumHighScores);

	// set the highScore file location and
	// return a 0 if it fails and set the 
	// filelocation to ""
	bool setHighScoreFileLocation(const std::string& fileLocation);

	// adds the users to the peopleHighScores and
	// peopleUsersNames and return 0 if its not high enough
	bool addScore(const std::string& name, int score);

	// dispaly the high scores.
	// you can do what ever you like with this.
	// as long as they have the high score users.
	std::string displayScoresText();
	

	int getMaxNumHighScores() const;

	int getNumHighScores() const;
	
	const std::string& getHighScoreFileLocation() const;

	const std::string& getHighScoreName(int rank) const;

	int getHighScorePoints(int rank) const;


private:
	unsigned int m_maxNumHighScores;
	std::string m_highScoreFileLocation;
	std::vector<HighScore> m_highScores;
};


#endif // _SCORE_BOARD_H_