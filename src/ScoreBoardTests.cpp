#include <gtest/gtest.h>
#include "scoreBoard.h"


#define TEST_HIGH_SCORE_INPUT_FILE		"../test/testHighScoresInput.txt"
#define TEST_HIGH_SCORE_OUTPUT_FILE		"../test/testHighScoresOutput.txt"


// Test the initial state of a constructed Score Board.
TEST(ScoreBoard, checkInit)
{
	std::string fileLocation = TEST_HIGH_SCORE_INPUT_FILE;
	ScoreBoard scoreB = ScoreBoard(fileLocation);
	EXPECT_EQ(fileLocation, scoreB.getHighScoreFileLocation());
	EXPECT_LT(0, scoreB.getMaxNumHighScores());
	EXPECT_LT(0u, scoreB.getHighScoreFileLocation().length());
}

// Test Function
//			setHighScoreFileLocation
//
//		should set the file location as "" if file doesn't exist and return 0
TEST(ScoreBoard, fileExists) 
{
	std::string fileLocation = "randomPlace.txt";
	ScoreBoard scoreB = ScoreBoard(fileLocation);
	EXPECT_EQ("", scoreB.getHighScoreFileLocation());
	
	bool passed = scoreB.setHighScoreFileLocation("anotherRandomPlace.txt");
	ASSERT_FALSE(passed);
}
// Test Function
//			loadHighScores()
//
//		Should load values into peopleHighScores and peopleUserNames
TEST(ScoreBoard, testLoadFile)
{
	std::string fileLocation = TEST_HIGH_SCORE_INPUT_FILE;
	ScoreBoard scoreB = ScoreBoard(fileLocation);
	scoreB.loadHighScores();
	ASSERT_EQ(2, scoreB.getNumHighScores());
	EXPECT_EQ(999999999, scoreB.getHighScorePoints(0));
	EXPECT_EQ("Jesus",scoreB.getHighScoreName(0));
	EXPECT_EQ(19, scoreB.getHighScorePoints(1));
	EXPECT_EQ("donkey kong", scoreB.getHighScoreName(1));
}

// Test Function - addScore()
//
//		Should not add elements if the number 
//		of elements would be over highScoreLimit
TEST(ScoreBoard, testAddedScore) {
	std::string fileLocation = TEST_HIGH_SCORE_INPUT_FILE;
	ScoreBoard scoreB = ScoreBoard(fileLocation);
	scoreB.setMaxNumHighScores(2);

	ASSERT_TRUE(scoreB.addScore("phillip j fry 2", 2));
	ASSERT_TRUE(scoreB.addScore("phillip j fry 1", 5));
	ASSERT_FALSE(scoreB.addScore("phillip j fry 3", 0));
}

// Test Function - loadHighScores()
//
//		Testing the loading function by 
//		add a user and writing it and the
//		amidentity writing it.
TEST(ScoreBoard, writingFile)
{
	std::string fileLocation = TEST_HIGH_SCORE_INPUT_FILE;
	ScoreBoard scoreB = ScoreBoard(fileLocation);
	scoreB.setMaxNumHighScores(4);
	scoreB.loadHighScores();

	bool wasAdded = scoreB.addScore("phillip j fry", 1);
	ASSERT_TRUE(wasAdded);

	ASSERT_TRUE(scoreB.setHighScoreFileLocation(TEST_HIGH_SCORE_OUTPUT_FILE));
	scoreB.writeHighScores();
	scoreB.loadHighScores();
	ASSERT_EQ(3, scoreB.getNumHighScores());
	EXPECT_EQ(999999999, scoreB.getHighScorePoints(0));
	EXPECT_EQ("Jesus", scoreB.getHighScoreName(0));
	EXPECT_EQ(19, scoreB.getHighScorePoints(1));
	EXPECT_EQ("donkey kong", scoreB.getHighScoreName(1));
	EXPECT_EQ(1, scoreB.getHighScorePoints(2));
	EXPECT_EQ("phillip j fry", scoreB.getHighScoreName(2));
}

// testing highScoreLimits variable()
//
//		It should only ever write
//		the number of of elements
//		upto the highScoreLimit nubmer.
TEST(ScoreBoard, getNumHighScores)
{
	std::string fileLocation = TEST_HIGH_SCORE_INPUT_FILE;
	ScoreBoard scoreB = ScoreBoard(fileLocation);
	scoreB.setMaxNumHighScores(2);

	scoreB.addScore("phillip j fry", 1);

	scoreB.addScore("batman", 10);

	scoreB.addScore("monkey", 9);
	
	EXPECT_EQ(2, scoreB.getNumHighScores());

}
// Test Function - displayScoresText()
//
//		just making sure that when you displayScoresText
//		that all the people with top scores get shown.
TEST(ScoreBoard, testOutput)
{
	std::string fileLocation = TEST_HIGH_SCORE_INPUT_FILE;
	ScoreBoard scoreB = ScoreBoard(fileLocation);
	scoreB.loadHighScores();
	std::string text = scoreB.displayScoresText();

	int found = text.find("Jesus");
	EXPECT_LT(0, found);
	
	found = text.find("999999999");
	EXPECT_LT(0, found);

	found = text.find("19");
	EXPECT_LT(0, found);

	found = text.find("donkey kong");
	EXPECT_LT(0, found);
}
