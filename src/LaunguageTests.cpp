
#include <gtest/gtest.h>
#include "Languages.h"


/*
test ifValidAudioChoice
*/
TEST(Language, checkValid)
{
	LanguageConverter lg;
	EXPECT_EQ(false, lg.checkValidChoice("monkey"));
}

TEST(Language, test_PigLatin)
{
	LanguageConverter lg;
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    / examples of translations
    /   http://www.omniglot.com/language/phrases/piglatin.htm
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EXPECT_EQ("Oodgay", lg.convertText("pigLatin","Good"));
}


TEST(Language, test_Opish)
{
	LanguageConverter lg;
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    / examples of translations
    /   http://www.urbandictionary.com/define.php?term=opish
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EXPECT_EQ("ellohop", lg.convertText("opish","hello"));
}

TEST(Language, test_Hex)
{
	LanguageConverter lg;
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    / examples of translations
    /   http://codebeautify.org/string-hex-converter
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	EXPECT_EQ("68656c6c6f", lg.convertText("hex","hello"));
}

