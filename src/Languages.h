#ifndef _LANGUAGES_H_
#define _LANGUAGES_H_

#include <string>


//-----------------------------------------------------------------------------
// ILanguageTranslater
//-----------------------------------------------------------------------------
class ILanguageTranslater
{
public:
	// Translate an English word to this language.
    virtual std::string translate(const std::string& text) = 0;
};


//-----------------------------------------------------------------------------
// PigLatinTranslater
//-----------------------------------------------------------------------------
class PigLatinTranslater : public ILanguageTranslater
{
public:
	PigLatinTranslater() {}

    std::string translate(const std::string& text) override;
};

//-----------------------------------------------------------------------------
// OpishTranslater
//-----------------------------------------------------------------------------
class OpishTranslater : public ILanguageTranslater
{
public:
	OpishTranslater() {}

    std::string translate(const std::string& text) override;
};

//-----------------------------------------------------------------------------
// HexTranslater
//-----------------------------------------------------------------------------
class HexTranslater : public ILanguageTranslater
{
public:
	HexTranslater() {}

    std::string translate(const std::string& text) override;
};



//-----------------------------------------------------------------------------
// LanguageConverter
//-----------------------------------------------------------------------------
class LanguageConverter
{
public:
	LanguageConverter();

	// Check if the given language is valid to be translated to.
    bool checkValidChoice(const std::string& languageName);

	// Translate a single word to the given language of choice.
    std::string convertText(const std::string& choice, const std::string& text);


private:
	// Get the translater for the given language.
    ILanguageTranslater* getLanguageTranslater(const std::string& languageName);


private:
	PigLatinTranslater	m_pigLatin;
	OpishTranslater		m_opish;
	HexTranslater		m_hex;
};


// other languages Possible Langugaes
// http://www.travelphrases.info/languages/languagegames.htm



#endif // _LANGUAGES_H_