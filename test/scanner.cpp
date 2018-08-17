#include <gtest/gtest.h>

extern "C" {
#include "../lex.yy.h"
#include "../tokens.h"
}

TEST(LexemeBoolLiteral, ShouldScanFalseLiteral) {
    yy_scan_string("false");
    EXPECT_EQ(TK_LIT_FALSE, yylex());
    EXPECT_STREQ("false", yytext);
}

TEST(LexemeBoolLiteral, ShouldScanTrueLiteral) {
    yy_scan_string("true");
    EXPECT_EQ(TK_LIT_TRUE, yylex());
    EXPECT_STREQ("true", yytext);
}
