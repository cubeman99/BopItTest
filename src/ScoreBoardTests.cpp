#include <gtest/gtest.h>
#include "scoreBoard.h"


// Test the initial state of a constructed Score Board.
TEST(ScoreBoard, checkInit)
{
	std::string fileLocation = "testHighScore.txt";
	ScoreBoard scoreB = ScoreBoard(fileLocation);
	EXPECT_EQ(fileLocation, scoreB.highScoreFileLocation);
	EXPECT_LT(0, sizeof(scoreB.highScoreLimit));
	EXPECT_LT(0, sizeof(scoreB.highScoreFileLocation));
}

// Test Function
//			setHighScoreFileLocation
//
//		should set the file location as "" if file doesn't exit and return 0
TEST(ScoreBoard, fileExists) 
{
	std::string fileLocation = "randomPlace.txt";
	ScoreBoard scoreB = ScoreBoard(fileLocation);
	EXPECT_EQ("", scoreB.highScoreFileLocation);


	bool passed = scoreB.setHighScoreFileLocation("anotherRandomPlace.txt");
	ASSERT_TRUE(passed);
}
// Test Function
//			loadHighScores()
//
//		Should load values into peopleHighScores and peopleUserNames
TEST(ScoreBoard, testLoadFile)
{
	std::string fileLocation = "testHighScore.txt";
	ScoreBoard scoreB = ScoreBoard(fileLocation);
	scoreB.loadHighScores()
	EXPECT_EQ(999999999, scoreB.peopleHighScores[0])
	EXPECT_EQ("Jesus",scoreB.peopleUserNames[0])
	EXPECT_EQ(19, scoreB.peopleHighScores[1])
	EXPECT_EQ("donkey kong", scoreB.peopleUserNames[1])
}

// Test Function - addScore()
//
//		Should not add elements if the number 
//		of elements would be over highScoreLimit
TEST(ScoreBoard, testAddedScore) {
	std::string fileLocation = "testHighScore.txt";
	ScoreBoard scoreB = ScoreBoard(fileLocation);
	scoreB.highScoreLimit = 2;

	bool wasAdded = scoreB.addScore("phillip j fry", 0);
	ASSERT_FALSE(wasAdded);
}

// Test Function - loadHighScores()
//
//		Testing the loading function by 
//		add a user and wrighting it and the
//		amidentity wrighting it.
TEST(ScoreBoard, wrightingFile)
{
	std::string fileLocation = "testHighScore.txt";
	ScoreBoard scoreB = ScoreBoard(fileLocation);
	scoreB.highScoreLimit = 4;

	bool wasAdded = scoreB.addScore("phillip j fry", 1);
	ASSERT_TRUE(wasAdded);

	scoreB.loadHighScores();
	scoreB.wrightHighScores();
	scoreB.loadHighScores();
	EXPECT_EQ(999999999, scoreB.peopleHighScores[0])
	EXPECT_EQ("Jesus", scoreB.peopleUserNames[0])
	EXPECT_EQ(19, scoreB.peopleHighScores[1])
	EXPECT_EQ("donkey kong", scoreB.peopleUserNames[1])
	EXPECT_EQ(1, scoreB.peopleHighScores[2])
	EXPECT_EQ("Jesus", scoreB.peopleUserNames[2])
}

// testing highScoreLimits variable()
//
//		It should only ever wright
//		the number of of elements
//		upto the highScoreLimit nubmer.
TEST(ScoreBoard, wrightingFile)
{
	std::string fileLocation = "testHighScore.txt";
	ScoreBoard scoreB = ScoreBoard(fileLocation);
	scoreB.highScoreLimit = 2;

	scoreB.addScore("phillip j fry", 1);

	scoreB.addScore("batman", 10);

	scoreB.addScore("monkey", 9);
	
	scoreB.wrightHighScores();
	scoreB.loadHighScores();
	
	EXPECT_EQ(2, sizeof(scoreB.peopleHighScores) / sizeof(int));

}
// Test Function - displayScoresText()
//
//		just making sure that when you displayScoresText
//		that all the people with top scores get shown.
TEST(ScoreBoard, testOutput)
{
	std::string fileLocation = "testHighScore.txt";
	ScoreBoard scoreB = ScoreBoard(fileLocation);
	scoreB.loadHighScores();
	std::string text = scoreB.displayScoresText();

	int found = text.find("Jesus");
	EXPECT_LT(0, found);
	
	found = text.find("999999999");
	EXPECT_LT(0, found);

	found = text.find("19");
	EXPECT_LT(0, found);

	found = text.find("1");
	EXPECT_LT(0, found);
}