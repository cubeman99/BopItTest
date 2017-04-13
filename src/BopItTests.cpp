
#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include "BopIt.h"
#include <iostream>

using namespace std::this_thread;
using namespace std::chrono;


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

	// Start the game and check the initial game state.
	bopit.startGame();
	ASSERT_TRUE(bopit.isPlaying());
	EXPECT_NE(ACTION_NONE, bopit.getCurrentAction());
	EXPECT_EQ(0, bopit.getScore()); 
	EXPECT_LT(0.0f, bopit.getRespondTime());

	// Calling startGame while playing a game shouldn't do anything.
	bopit.startGame();
	ASSERT_TRUE(bopit.isPlaying());
	EXPECT_NE(ACTION_NONE, bopit.getCurrentAction());
	EXPECT_EQ(0, bopit.getScore());
	EXPECT_LT(0.0f, bopit.getRespondTime());
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
	ASSERT_EQ(3, bopit.getScore());
	
	// End the game, expect the score to remain.
	bopit.endGame();
	ASSERT_FALSE(bopit.isPlaying());
	EXPECT_EQ(ACTION_NONE, bopit.getCurrentAction());
	EXPECT_EQ(3, bopit.getScore());
	
	// Ending the game twice shouldn't change anything.
	bopit.endGame();
	ASSERT_FALSE(bopit.isPlaying());
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
	EXPECT_NE((int)ACTION_NONE, (int) bopit.getCurrentAction());
	EXPECT_GE((int)NUM_ACTIONS, (int) bopit.getCurrentAction());
	EXPECT_LT((int)ACTION_NONE, (int) bopit.getCurrentAction());

	bopit.endGame();
	//EXPECT_EQ(ACTION_NONE, bopit.getCurrentAction());
}

// Test the performAction function with the prompted action, expecting
// the game to continue and score to rise.
TEST(BopIt, performAction_correct)
{
	BopIt bopit;
	bopit.startGame();
	ASSERT_TRUE(bopit.isPlaying());
	ASSERT_EQ(0, bopit.getScore());

	// Perform two correct actions.
	ASSERT_TRUE(bopit.performAction(bopit.getCurrentAction()));
	ASSERT_EQ(1, bopit.getScore());
	ASSERT_TRUE(bopit.isPlaying());
	ASSERT_TRUE(bopit.performAction(bopit.getCurrentAction()));
	ASSERT_EQ(2, bopit.getScore());
	ASSERT_TRUE(bopit.isPlaying());
}

// Test the performAction function with an action other than the prompted
// action, expecting the game to end and the score to not change.
TEST(BopIt, performAction_incorrect)
{
	BopIt bopit;
	bopit.startGame();
	ASSERT_TRUE(bopit.isPlaying());

	// Perform an incorrect action, thus ending the game.
	BopItAction incorrectAction = (BopItAction)
		(((int) bopit.getCurrentAction() + 1));
	ASSERT_FALSE(bopit.performAction(incorrectAction));
	ASSERT_FALSE(bopit.isPlaying());
}

// Test the performAction function by waiting too long that it
// will cause a game over
TEST(BopIt, performAction_timeout)
{
	BopIt bopit;
	bopit.startGame();

	// Perform the action at 50% of the duration.
	// This means we perform the action before the response time expires.
	sleep_for(milliseconds((int) (bopit.getRespondTime() * 500.0f)));
	ASSERT_TRUE(bopit.performAction(bopit.getCurrentAction()));
	ASSERT_TRUE(bopit.isPlaying());
	
	// Perform the action at 150% the duration.
	// Because we waited past the response time, we should get a game over.
	sleep_for(milliseconds((int) (bopit.getRespondTime() * 1500.0f)));
	EXPECT_FALSE(bopit.performAction(bopit.getCurrentAction()));
	EXPECT_FALSE(bopit.isPlaying());
}


