
#include <gtest/gtest.h>
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;


// List of possible actions for a game of Bop-It.
enum BopItAction
{
	ACTION_NONE = -1,
	
	ACTION_BOP,
	ACTION_PULL,
	ACTION_TWIST,
	ACTION_SPIN,
	ACTION_FLICK,

	NUM_ACTIONS,
};


// Class to manage a game of Bop-It
class BopIt
{
public:
	BopIt() {}

	// Getters
	int getScore() { return -1; }
	BopItAction getCurrentAction() { return ACTION_PULL; }
	bool isPlaying() { return false; }

	// User interaction
	void startGame() {}
	void endGame() {}
	bool performAction(BopItAction action) { return false; }
};



// Test the initial state of a constructed BopIt object.
TEST(BopIt, constructor)
{
	BopIt bopit;
	EXPECT_FALSE(bopit.isPlaying());
	EXPECT_EQ(0, bopit.getScore());
	EXPECT_EQ(ACTION_NONE, bopit.getCurrentAction());
}

// Start a bop-it game and expect its state to change accordingly.
TEST(BopIt, startGame)
{
	BopIt bopit;
	bopit.startGame();
	EXPECT_TRUE(bopit.isPlaying());
	EXPECT_NE(ACTION_NONE, bopit.getCurrentAction());
	EXPECT_EQ(0, bopit.getScore());
}

// End a bop-it game and expect its state to change accordingly
// The score should stay even after the game ends, so the user can
// check the score they got.
TEST(BopIt, endGame)
{
	BopIt bopit;
	
	// Play a game scoring 3 points
	bopit.startGame();
	bopit.performAction(bopit.getCurrentAction());
	bopit.performAction(bopit.getCurrentAction());
	bopit.performAction(bopit.getCurrentAction());
	EXPECT_EQ(3, bopit.getScore());
	
	// End the game, expect the score to remain.
	bopit.endGame();
	EXPECT_FALSE(bopit.isPlaying());
	EXPECT_EQ(ACTION_NONE, bopit.getCurrentAction());
	EXPECT_EQ(3, bopit.getScore());
}

// Test the function to get the currently prompted action for a bop-it game,
// making sure the action is valid when playing.
TEST(BopIt, getCurrentAction)
{
	BopIt bopit;
	EXPECT_EQ(ACTION_NONE, bopit.getCurrentAction());

	// Expect a valid current action.
	bopit.startGame();
	EXPECT_NE(ACTION_NONE, (int) bopit.getCurrentAction());
	EXPECT_GE(0, (int) bopit.getCurrentAction());
	EXPECT_LT((int) NUM_ACTIONS, (int) bopit.getCurrentAction());

	bopit.endGame();
	EXPECT_EQ(ACTION_NONE, bopit.getCurrentAction());
}

// Test the performAction function with the prompted action, expecting
// the game to continue and score to rise.
TEST(BopIt, performAction_correct)
{
	BopIt bopit;
	bopit.startGame();
	EXPECT_TRUE(bopit.isPlaying());

	// Perform two correct actions.
	EXPECT_TRUE(bopit.performAction(bopit.getCurrentAction()));
	EXPECT_EQ(1, bopit.getScore());
	EXPECT_TRUE(bopit.isPlaying());
	EXPECT_TRUE(bopit.performAction(bopit.getCurrentAction()));
	EXPECT_EQ(2, bopit.getScore());
	EXPECT_TRUE(bopit.isPlaying());
}

// Test the performAction function with an action other than the prompted
// action, expecting the game to end and the score to not change.
TEST(BopIt, performAction_incorrect)
{
	BopIt bopit;
	bopit.startGame();
	EXPECT_TRUE(bopit.isPlaying());

	// Perform an incorrect action, thus ending the game.
	BopItAction incorrectAction = (BopItAction)
		(((int) bopit.getCurrentAction() + 1) % NUM_ACTIONS);
	EXPECT_FALSE(bopit.performAction(incorrectAction));
	EXPECT_FALSE(bopit.isPlaying());
}


