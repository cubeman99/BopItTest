#include "ScoreBoard.h"
#include <fstream>
#include <sstream>


// Trim the whitespace (spaces and tabs) on both ends of a string.
static std::string trimString(const std::string& str)
{
	std::string result = str;

	size_t index = result.find_first_not_of(" \t");
	if (index != std::string::npos)
		result = result.substr(index);

	index = result.find_last_not_of(" \t");
	if (index != std::string::npos)
		result = result.substr(0, index + 1);

	return result;
}


ScoreBoard::ScoreBoard(const std::string& highScoreFileLocation) :
	m_maxNumHighScores(10),
	m_highScoreFileLocation("")
{
	setHighScoreFileLocation(highScoreFileLocation);
}
	
// load the high score values into 
// peopleHighScores
// peopleUserNames
void ScoreBoard::loadHighScores()
{
	m_highScores.clear();

	// Open the file.
	std::ifstream file;
	file.open(m_highScoreFileLocation);
	if (!file.is_open())
		return;
	
	// Read the file line-by-line
	while (file)
	{
		std::string lineStr;
		std::string name;
		std::string scoreStr;
		if (!std::getline(file, lineStr))
			break;

		std::istringstream line(lineStr);

		// Read the name and score separated by a comma.
		if (!std::getline(line, name, ','))
			continue;
		if (!std::getline(line, scoreStr, ','))
			continue;

		// Parse the score.
		scoreStr = trimString(scoreStr);
		char* endPtr;
		int score = (int) strtol(scoreStr.c_str(), &endPtr, 10);
		if (endPtr != scoreStr.c_str() + scoreStr.length())
			continue;
		
		// Add the score to the board.
		addScore(name, score);
	}

	file.close();
}

// Writes the high scores to higherScoreFilelocation
void ScoreBoard::writeHighScores()
{
	// Open the file.
	std::ofstream file;
	file.open(m_highScoreFileLocation);
	if (!file.is_open())
		return;

	// Write each score name and points.
	for (unsigned int i = 0; i < m_highScores.size(); ++i)
	{
		file << m_highScores[i].name << ", "
			<< m_highScores[i].score << std::endl;
	}

	file.close();
}


void ScoreBoard::setMaxNumHighScores(int maxNumHighScores)
{
	m_maxNumHighScores = maxNumHighScores;
}

// set the highScore file location and
// return a 0 if it fails and set the 
// filelocation to ""
bool ScoreBoard::setHighScoreFileLocation(const std::string& fileLocation)
{
	// Check if the file exists, return false if it doesn't.
	FILE* file = nullptr;
	fopen_s(&file, fileLocation.c_str(), "r");
	if (file == nullptr)
		return false;
	fclose(file);

	// The file exists! Update the file location.
	m_highScoreFileLocation = fileLocation;
	return true;
}

// adds the users to the peopleHighScores and
// peopleUsersNames and return 0 if its not high enough
bool ScoreBoard::addScore(const std::string& name, int score)
{
	// Determine the rank of this new score.
	unsigned int rank;
	for (rank = 0; rank < m_highScores.size(); ++rank)
	{
		if (score > m_highScores[rank].score)
		{
			break;
		}
	}

	if (rank < m_maxNumHighScores)
	{
		// This score is high enough to be placed on the board.
		HighScore newHighScore(name, score);
		m_highScores.insert(m_highScores.begin() + rank, newHighScore);
		if (m_highScores.size() == m_maxNumHighScores + 1)
			m_highScores.pop_back();
		return true;
	}
	else
	{
		// The board is full and this score is lower than the lowest high-score.
		return false;
	}
}

// dispaly the high scores.
// you can do what ever you like with this.
// as long as they have the high score users.
std::string ScoreBoard::displayScoresText()
{
	std::stringstream text;

	for (unsigned int i = 0; i < m_highScores.size(); ++i)
	{
		text << (i + 1) << ". " << m_highScores[i].name
			<< ": " << m_highScores[i].score << std::endl;
	}

	return text.str();
}
	



int ScoreBoard::getMaxNumHighScores() const
{
	return (int) m_maxNumHighScores;
}

int ScoreBoard::getNumHighScores() const
{
	return (int) m_highScores.size();
}
	
const std::string& ScoreBoard::getHighScoreFileLocation() const
{
	return m_highScoreFileLocation;
}

const std::string& ScoreBoard::getHighScoreName(int rank) const
{
	return m_highScores[rank].name;
}

int ScoreBoard::getHighScorePoints(int rank) const
{
	return m_highScores[rank].score;
}

