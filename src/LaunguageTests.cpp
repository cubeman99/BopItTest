
#include <gtest/gtest.h>


TEST(Language, todo)
{
	EXPECT_TRUE(true);
	EXPECT_EQ(1, 1);
	EXPECT_NE(0, 1);
	EXPECT_GT(5, 3);
	EXPECT_FLOAT_EQ(3.14f, 3.14f);
}

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
    lg = langugaeConvert()
	EXPECT_TRUE(false, lg.checkValidChoice("monkey"));
}

TEST(Language, test _PigLatin)
{
    lg = langugaeConvert()
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    / examples of translations
    /   http://www.omniglot.com/language/phrases/piglatin.htm
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EXPECT_TRUE("Oodgay", lg.convertText("pigLatin","Good"));
}


TEST(Language, test_Opish)
{
    lg = langugaeConvert()
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    / examples of translations
    /   http://www.urbandictionary.com/define.php?term=opish
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EXPECT_TRUE("ellohop", lg.convertText("opish","hello"));
}

TEST(Language, test_Hex)
{
    lg = langugaeConvert()
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    / examples of translations
    /   http://codebeautify.org/string-hex-converter
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EXPECT_TRUE("68656c6c6f", lg.convertText("hex","hello"));
}
