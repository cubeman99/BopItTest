#ifndef __BOP_IT_H__
#define __BOP_IT_H__


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


// Class to manage a game of Bop-It.
class BopIt
{
public:
	BopIt() {}

	// Returns true if th game is currently being played.
	bool isPlaying() { return false; }

	// Get the current game's score
	// Returns the last game's score if not currently playing.
	int getScore() { return -1; }
	
	// Get the prompted action that the user needs to perform.
	// Returns ACTION_NONE if the game isn't currently being played.
	BopItAction getCurrentAction() { return ACTION_PULL; }

	// Get length of time in seconds by which the user needs
	// to respond with an action to keep playing.
	float getRespondTime() { return -1.0f; };

	// Start a new game if a game is not currently being played.
	void startGame() {}

	// End the current game immediately if one is currently being played.
	void endGame() {}

	// Perform an action on the bop-it.
	// Returns true if the game is still playing, or false if a game over.
	bool performAction(BopItAction action) { return false; }

	
	//-------------------------------------------------------------------------
	// Special feature

	// Insult the bop-it. This will make it not give a point for performing
	// the current action. It will also make it secretly give you half as much
	// time to complete the next action as it says it does from getRespondTime().
	// Insulting the bop-it three times will make it so that when you perform 
	// the current action, it will give you a game over with a resulting score
	// of zero points.
	void insult() {}
};


#endif // __BOP_IT_H__