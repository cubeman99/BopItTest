#include "Languages.h"
#include <sstream>
#include <algorithm> 


static bool isVowel(char c)
{
	return isalpha((int) c) &&
		(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
		 c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

static bool isConsonent(char c)
{
	return (isalpha((int) c) && !isVowel(c));
}


//-----------------------------------------------------------------------------
// PigLatinTranslater
//-----------------------------------------------------------------------------

std::string PigLatinTranslater::translate(const std::string& text)
{
	if (text.length() == 0)
		return text;

	std::string translation = "";

	if (isConsonent(text[0]))
	{
		// For words that begin with consonant sounds, all letters before the
		// initial vowel are placed at the end of the word sequence. Then, 
		// "ay" is added. When words begin with consonant clusters (multiple
		// consonants that form one sound), the whole sound is added to the end.

		// Count the number of consonents in the beginning.
		unsigned int numConsonents = 0;
		for (unsigned int i = 0; i < text.length(); ++i)
		{
			if (!isConsonent(text[i]))
			{
				numConsonents = i;
				break;
			}
		}

		// Move the consonents to the end of the string and add "ay"
		translation = text.substr(numConsonents) +
			text.substr(0, numConsonents) + "ay";
		
		// Conver the translation to lowercase.
		std::transform(translation.begin(), translation.end(),
			translation.begin(), ::tolower);
		
		// Keep the original sequence of uppercase characters.
		for (unsigned int i = 0; i < numConsonents; ++i)
		{
			if (isupper(text[i]))
				translation[i] = toupper(translation[i]);
		}
	}
	else
	{
		// For words that begin with vowel sounds, add "way" to the end.
		translation = text + "way";
	}

	return translation;
}

//-----------------------------------------------------------------------------
// OpishTranslater
//-----------------------------------------------------------------------------

std::string OpishTranslater::translate(const std::string& text)
{
	if (text.length() == 0)
		return text;
	
	// http://www.urbandictionary.com/define.php?term=opish
	// "Opish is a language were you take the first letter and put it
	//  at the end of the word and then add op to the end of your word."

	std::string translation = text.substr(1) + text[0] + "op";
	return translation;
}

//-----------------------------------------------------------------------------
// HexTranslater
//-----------------------------------------------------------------------------

std::string HexTranslater::translate(const std::string& text)
{
	std::stringstream translation;

	// Convert each character to hex
	for (unsigned int i = 0; i < text.length(); ++i)
	{
		unsigned int c = (unsigned int) text[i];
		translation << std::hex << c;
	}
	
	return translation.str();
}


//-----------------------------------------------------------------------------
// LanguageConverter
//-----------------------------------------------------------------------------

LanguageConverter::LanguageConverter()
{
}

bool LanguageConverter::checkValidChoice(const std::string& languageName)
{
	return (getLanguageTranslater(languageName) != nullptr);
}

std::string LanguageConverter::convertText(const std::string& choice, const std::string& text)
{
	 ILanguageTranslater* translater = getLanguageTranslater(choice);
	 if (translater != nullptr)
		 return translater->translate(text);
	 return text;
}

ILanguageTranslater* LanguageConverter::getLanguageTranslater(const std::string& languageName)
{
	if (languageName == "pigLatin")
		return &m_pigLatin;
	else if (languageName == "opish")
		return &m_opish;
	else if (languageName == "hex")
		return &m_hex;
	return NULL;
}

