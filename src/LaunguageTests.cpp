
#include <gtest/gtest.h>


/*
the idea i behind these test
class languageConverter{
    public:
        Bool checkValidChoice(int choice)
        string convertText(string choice, string word)

    private:
        string toPigLatin(string word)
        string toSpanglish(string word)
        string validLanguageChoices[..,..]
}
*/

/*
other languages Possible Langugaes
http://www.travelphrases.info/languages/languagegames.htm
*/




/*
test ifValidAudioChoice
*/
TEST(Language, checkValid)
{
	lg = langugaeConvert();
	EXPECT_EQ(false, lg.checkValidChoice("monkey"));
}

TEST(Language, test_PigLatin)
{
	lg = langugaeConvert();
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    / examples of translations
    /   http://www.omniglot.com/language/phrases/piglatin.htm
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EXPECT_EQ("Oodgay", lg.convertText("pigLatin","Good"));
}


TEST(Language, test_Opish)
{
	lg = langugaeConvert();
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    / examples of translations
    /   http://www.urbandictionary.com/define.php?term=opish
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EXPECT_EQ("ellohop", lg.convertText("opish","hello"));
}

TEST(Language, test_Hex)
{
	lg = langugaeConvert();
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    / examples of translations
    /   http://codebeautify.org/string-hex-converter
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EXPECT_EQ("68656c6c6f", lg.convertText("hex","hello"));
}

