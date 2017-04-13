#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include "BopIt.h"

using namespace std::this_thread;
using namespace std::chrono;


// Test that insulting the bop-it will not make it not give a
// point for the current action.
TEST(BopItSecret, insult_points)
{
	BopIt bopit;
	bopit.startGame();
	
	// Insult the bopit. The first action should now not give us a point.
	bopit.insult();
	ASSERT_EQ(0, bopit.getScore());
	ASSERT_TRUE(bopit.performAction(bopit.getCurrentAction()));
	ASSERT_EQ(0, bopit.getScore());
	
	// Rack up 2 points.
	ASSERT_TRUE(bopit.performAction(bopit.getCurrentAction()));
	ASSERT_EQ(1, bopit.getScore());
	ASSERT_TRUE(bopit.performAction(bopit.getCurrentAction()));
	ASSERT_EQ(2, bopit.getScore());

	// Now insult the bopit again and check that we stay at 2 points.
	bopit.insult();
	ASSERT_EQ(2, bopit.getScore());
	ASSERT_TRUE(bopit.performAction(bopit.getCurrentAction()));
	ASSERT_EQ(2, bopit.getScore());
	ASSERT_TRUE(bopit.performAction(bopit.getCurrentAction()));
	ASSERT_EQ(3, bopit.getScore());
}

// Test that insulting the bop-it will make it give you half the
// time as it says it does to perform your next action.
TEST(BopItSecret, insult_timeout)
{
	BopIt bopit;
	bopit.startGame();
	
	// Insult and perform the next action at 25% of the duration.
	// This should still be early enough to get a point.
	bopit.insult();
	ASSERT_TRUE(bopit.performAction(bopit.getCurrentAction()));
	sleep_for(milliseconds((int) (bopit.getRespondTime() * 250.0f)));
	ASSERT_TRUE(bopit.performAction(bopit.getCurrentAction()));
	ASSERT_TRUE(bopit.isPlaying());
	
	// Insult again and perform the next action at 75% the duration.
	// Because the response time is secretly halved, we should get a game
	// over for waiting too long.
	bopit.insult();
	ASSERT_TRUE(bopit.performAction(bopit.getCurrentAction()));
	sleep_for(milliseconds((int) (bopit.getRespondTime() * 750.0f)));
	ASSERT_FALSE(bopit.performAction(bopit.getCurrentAction()));
	ASSERT_FALSE(bopit.isPlaying());
}

// Test that insulting the bop-it three times will result
// in a game over and a score of zero points.
TEST(BopItSecret, insult_gameOver)
{
	BopIt bopit;
	bopit.startGame();

	// Insult the bopit twice.
	bopit.insult();
	ASSERT_TRUE(bopit.isPlaying());
	bopit.insult();
	ASSERT_TRUE(bopit.isPlaying());
	
	// Rack up some points.
	ASSERT_TRUE(bopit.performAction(bopit.getCurrentAction()));
	ASSERT_TRUE(bopit.performAction(bopit.getCurrentAction()));
	ASSERT_TRUE(bopit.performAction(bopit.getCurrentAction()));
	ASSERT_TRUE(bopit.performAction(bopit.getCurrentAction()));

	// Insulting the 3rd time should give us a game over after
	// completing the current action. Score should also turn to zero.
	bopit.insult();
	ASSERT_TRUE(bopit.isPlaying());
	ASSERT_FALSE(bopit.performAction(bopit.getCurrentAction()));
	ASSERT_FALSE(bopit.isPlaying());
	ASSERT_EQ(0, bopit.getScore());
}
