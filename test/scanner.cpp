#include <gtest/gtest.h>

extern "C" {
#include "../lex.yy.h"
#include "../tokens.h"
}

TEST(LexemeLineComment, ShouldNotScanLineComment) {
    yy_scan_string("int// ignore comment\nfloat");
    EXPECT_EQ(TK_PR_INT, yylex());
    EXPECT_STREQ("int", yytext);
    EXPECT_EQ(TK_PR_FLOAT, yylex());
    EXPECT_STREQ("float", yytext);
}

TEST(LexemeBlockComment, ShouldNotScanBlockComment) {
    yy_scan_string("int/* ignore comment\nfloat*/const");
    EXPECT_EQ(TK_PR_INT, yylex());
    EXPECT_STREQ("int", yytext);
    EXPECT_EQ(TK_PR_CONST, yylex());
    EXPECT_STREQ("const", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanIntKeyword) {
    yy_scan_string("int");
    EXPECT_EQ(TK_PR_INT, yylex());
    EXPECT_STREQ("int", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanFloatKeyword) {
    yy_scan_string("float");
    EXPECT_EQ(TK_PR_FLOAT, yylex());
    EXPECT_STREQ("float", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanBoolKeyword) {
    yy_scan_string("bool");
    EXPECT_EQ(TK_PR_BOOL, yylex());
    EXPECT_STREQ("bool", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanCharKeyword) {
    yy_scan_string("char");
    EXPECT_EQ(TK_PR_CHAR, yylex());
    EXPECT_STREQ("char", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanStringKeyword) {
    yy_scan_string("string");
    EXPECT_EQ(TK_PR_STRING, yylex());
    EXPECT_STREQ("string", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanIfKeyword) {
    yy_scan_string("if");
    EXPECT_EQ(TK_PR_IF, yylex());
    EXPECT_STREQ("if", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanThenKeyword) {
    yy_scan_string("then");
    EXPECT_EQ(TK_PR_THEN, yylex());
    EXPECT_STREQ("then", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanElseKeyword) {
    yy_scan_string("else");
    EXPECT_EQ(TK_PR_ELSE, yylex());
    EXPECT_STREQ("else", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanWhileKeyword) {
    yy_scan_string("while");
    EXPECT_EQ(TK_PR_WHILE, yylex());
    EXPECT_STREQ("while", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanDoKeyword) {
    yy_scan_string("do");
    EXPECT_EQ(TK_PR_DO, yylex());
    EXPECT_STREQ("do", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanInputKeyword) {
    yy_scan_string("input");
    EXPECT_EQ(TK_PR_INPUT, yylex());
    EXPECT_STREQ("input", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanOutputKeyword) {
    yy_scan_string("output");
    EXPECT_EQ(TK_PR_OUTPUT, yylex());
    EXPECT_STREQ("output", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanReturnKeyword) {
    yy_scan_string("return");
    EXPECT_EQ(TK_PR_RETURN, yylex());
    EXPECT_STREQ("return", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanConstKeyword) {
    yy_scan_string("const");
    EXPECT_EQ(TK_PR_CONST, yylex());
    EXPECT_STREQ("const", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanStaticKeyword) {
    yy_scan_string("static");
    EXPECT_EQ(TK_PR_STATIC, yylex());
    EXPECT_STREQ("static", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanForeachKeyword) {
    yy_scan_string("foreach");
    EXPECT_EQ(TK_PR_FOREACH, yylex());
    EXPECT_STREQ("foreach", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanForKeyword) {
    yy_scan_string("for");
    EXPECT_EQ(TK_PR_FOR, yylex());
    EXPECT_STREQ("for", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanSwitchKeyword) {
    yy_scan_string("switch");
    EXPECT_EQ(TK_PR_SWITCH, yylex());
    EXPECT_STREQ("switch", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanCaseKeyword) {
    yy_scan_string("case");
    EXPECT_EQ(TK_PR_CASE, yylex());
    EXPECT_STREQ("case", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanBreakKeyword) {
    yy_scan_string("break");
    EXPECT_EQ(TK_PR_BREAK, yylex());
    EXPECT_STREQ("break", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanContinueKeyword) {
    yy_scan_string("continue");
    EXPECT_EQ(TK_PR_CONTINUE, yylex());
    EXPECT_STREQ("continue", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanClassKeyword) {
    yy_scan_string("class");
    EXPECT_EQ(TK_PR_CLASS, yylex());
    EXPECT_STREQ("class", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanPrivateKeyword) {
    yy_scan_string("private");
    EXPECT_EQ(TK_PR_PRIVATE, yylex());
    EXPECT_STREQ("private", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanPublicKeyword) {
    yy_scan_string("public");
    EXPECT_EQ(TK_PR_PUBLIC, yylex());
    EXPECT_STREQ("public", yytext);
}

TEST(LexemeReservedKeyword, ShouldScanProtectedKeyword) {
    yy_scan_string("protected");
    EXPECT_EQ(TK_PR_PROTECTED, yylex());
    EXPECT_STREQ("protected", yytext);
}

TEST(LexemeSpecialCharacter, ShouldScanComma) {
    yy_scan_string(",");
    EXPECT_EQ(',', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanSemicolon) {
    yy_scan_string(";");
    EXPECT_EQ(';', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanColon) {
    yy_scan_string(":");
    EXPECT_EQ(':', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanOpenParenthesis) {
    yy_scan_string("(");
    EXPECT_EQ('(', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanCloseParenthesis) {
    yy_scan_string(")");
    EXPECT_EQ(')', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanOpenSquareBracket) {
    yy_scan_string("[");
    EXPECT_EQ('[', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanCloseSquareBracket) {
    yy_scan_string("]");
    EXPECT_EQ(']', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanOpenBracket) {
    yy_scan_string("{");
    EXPECT_EQ('{', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanCloseBracket) {
    yy_scan_string("}");
    EXPECT_EQ('}', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanPlusSign) {
    yy_scan_string("+");
    EXPECT_EQ('+', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanMinusSign) {
    yy_scan_string("-");
    EXPECT_EQ('-', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanPipe) {
    yy_scan_string("|");
    EXPECT_EQ('|', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanQuestionMark) {
    yy_scan_string("?");
    EXPECT_EQ('?', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanAsterisk) {
    yy_scan_string("*");
    EXPECT_EQ('*', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanSlash) {
    yy_scan_string("/");
    EXPECT_EQ('/', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanLess) {
    yy_scan_string("<");
    EXPECT_EQ('<', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanGreater) {
    yy_scan_string(">");
    EXPECT_EQ('>', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanEqual) {
    yy_scan_string("=");
    EXPECT_EQ('=', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanExclamationMark) {
    yy_scan_string("!");
    EXPECT_EQ('!', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanAmpersand) {
    yy_scan_string("&");
    EXPECT_EQ('&', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanPercentSign) {
    yy_scan_string("%");
    EXPECT_EQ('%', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanNumberSign) {
    yy_scan_string("#");
    EXPECT_EQ('#', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanCaret) {
    yy_scan_string("^");
    EXPECT_EQ('^', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanDot) {
    yy_scan_string(".");
    EXPECT_EQ('.', yylex());
}

TEST(LexemeSpecialCharacter, ShouldScanDollarSign) {
    yy_scan_string("$");
    EXPECT_EQ('$', yylex());
}

TEST(LexemeOperator, ShouldScanLessEqual) {
    yy_scan_string("<=");
    EXPECT_EQ(TK_OC_LE, yylex());
    EXPECT_STREQ("<=", yytext);
}

TEST(LexemeOperator, ShouldScanGreaterEqual) {
    yy_scan_string(">=");
    EXPECT_EQ(TK_OC_GE, yylex());
    EXPECT_STREQ(">=", yytext);
}

TEST(LexemeOperator, ShouldScanEqualEqual) {
    yy_scan_string("==");
    EXPECT_EQ(TK_OC_EQ, yylex());
    EXPECT_STREQ("==", yytext);
}

TEST(LexemeOperator, ShouldScanNotEqual) {
    yy_scan_string("!=");
    EXPECT_EQ(TK_OC_NE, yylex());
    EXPECT_STREQ("!=", yytext);
}

TEST(LexemeOperator, ShouldScanAnd) {
    yy_scan_string("&&");
    EXPECT_EQ(TK_OC_AND, yylex());
    EXPECT_STREQ("&&", yytext);
}

TEST(LexemeOperator, ShouldScanOr) {
    yy_scan_string("||");
    EXPECT_EQ(TK_OC_OR, yylex());
    EXPECT_STREQ("||", yytext);
}

TEST(LexemeOperator, ShouldScanShiftRight) {
    yy_scan_string(">>");
    EXPECT_EQ(TK_OC_SR, yylex());
    EXPECT_STREQ(">>", yytext);
}

TEST(LexemeOperator, ShouldScanShiftLeft) {
    yy_scan_string("<<");
    EXPECT_EQ(TK_OC_SL, yylex());
    EXPECT_STREQ("<<", yytext);
}

TEST(LexemeOperator, ShouldScanForwardPipe) {
    yy_scan_string("%>%");
    EXPECT_EQ(TK_OC_FORWARD_PIPE, yylex());
    EXPECT_STREQ("%>%", yytext);
}

TEST(LexemeOperator, ShouldScanBashPipe) {
    yy_scan_string("%|%");
    EXPECT_EQ(TK_OC_BASH_PIPE, yylex());
    EXPECT_STREQ("%|%", yytext);
}

TEST(LexemeIntLiteral, ShouldScanInteger) {
    yy_scan_string("102");
    EXPECT_EQ(TK_LIT_INT, yylex());
    EXPECT_STREQ("102", yytext);
}

TEST(LexemeIntLiteral, ShouldScanIntegerPlusSign) {
    yy_scan_string("+102");
    EXPECT_EQ(TK_LIT_INT, yylex());
    EXPECT_STREQ("+102", yytext);
}

TEST(LexemeIntLiteral, ShouldScanIntegerMinusSign) {
    yy_scan_string("-102");
    EXPECT_EQ(TK_LIT_INT, yylex());
    EXPECT_STREQ("-102", yytext);
}

TEST(LexemeFloatLiteral, ShouldScanFloat) {
    yy_scan_string("1.0");
    EXPECT_EQ(TK_LIT_FLOAT, yylex());
    EXPECT_STREQ("1.0", yytext);
}

TEST(LexemeFloatLiteral, ShouldScanFloatPlusSign) {
    yy_scan_string("+1.0");
    EXPECT_EQ(TK_LIT_FLOAT, yylex());
    EXPECT_STREQ("+1.0", yytext);
}

TEST(LexemeFloatLiteral, ShouldScanFloatMinusSign) {
    yy_scan_string("-1.0");
    EXPECT_EQ(TK_LIT_FLOAT, yylex());
    EXPECT_STREQ("-1.0", yytext);
}

TEST(LexemeFloatLiteral, ShouldScanFloatExpoent) {
    yy_scan_string("-1.0e10");
    EXPECT_EQ(TK_LIT_FLOAT, yylex());
    EXPECT_STREQ("-1.0e10", yytext);
}

TEST(LexemeFloatLiteral, ShouldScanFloatExpoentPlusSign) {
    yy_scan_string("-1.0e+10");
    EXPECT_EQ(TK_LIT_FLOAT, yylex());
    EXPECT_STREQ("-1.0e+10", yytext);
}

TEST(LexemeFloatLiteral, ShouldScanFloatExpoentMinusSign) {
    yy_scan_string("-1.0e-10");
    EXPECT_EQ(TK_LIT_FLOAT, yylex());
    EXPECT_STREQ("-1.0e-10", yytext);
}

TEST(LexemeFloatLiteral, ShouldScanFloatExpoentUpperCase) {
    yy_scan_string("-1.0E-10");
    EXPECT_EQ(TK_LIT_FLOAT, yylex());
    EXPECT_STREQ("-1.0E-10", yytext);
}

TEST(LexemeFloatLiteral, ShouldNotScanFloatWithoutIntegerPart) {
    yy_scan_string(".01");
    EXPECT_NE(TK_LIT_FLOAT, yylex());
    EXPECT_STRNE(".01", yytext);
}

TEST(LexemeFloatLiteral, ShouldNotScanFloatWithoutDecimalPart) {
    yy_scan_string("1.");
    EXPECT_NE(TK_LIT_FLOAT, yylex());
    EXPECT_STRNE("1.", yytext);
}

TEST(LexemeBoolLiteral, ShouldScanFalse) {
    yy_scan_string("false");
    EXPECT_EQ(TK_LIT_FALSE, yylex());
    EXPECT_STREQ("false", yytext);
}

TEST(LexemeBoolLiteral, ShouldScanTrue) {
    yy_scan_string("true");
    EXPECT_EQ(TK_LIT_TRUE, yylex());
    EXPECT_STREQ("true", yytext);
}

TEST(LexemeCharLiteral, ShouldScanChar) {
    yy_scan_string("'a'");
    EXPECT_EQ(TK_LIT_CHAR, yylex());
    EXPECT_STREQ("'a'", yytext);
}

TEST(LexemeCharLiteral, ShouldNotScanEmptyChar) {
    yy_scan_string("''");
    EXPECT_NE(TK_LIT_CHAR, yylex());
    EXPECT_STRNE("''", yytext);
}

TEST(LexemeCharLiteral, ShouldNotScanEscapedChar) {
    yy_scan_string("'\\n'");
    EXPECT_NE(TK_LIT_CHAR, yylex());
    EXPECT_STRNE("'\\n'", yytext);
}

TEST(LexemeStringLiteral, ShouldScanString) {
    yy_scan_string("\"a\"");
    EXPECT_EQ(TK_LIT_STRING, yylex());
    EXPECT_STREQ("\"a\"", yytext);
}

TEST(LexemeStringLiteral, ShouldScanEmptyString) {
    yy_scan_string("\"\"");
    EXPECT_EQ(TK_LIT_STRING, yylex());
    EXPECT_STREQ("\"\"", yytext);
}

TEST(LexemeStringLiteral, ShouldScanEscapedCharInString) {
    yy_scan_string("\"\\n\"");
    EXPECT_EQ(TK_LIT_STRING, yylex());
    EXPECT_STREQ("\"\\n\"", yytext);
}

TEST(LexemeStringLiteral, ShouldScanEscapedQuoteInString) {
    yy_scan_string("\"\\\"\"");
    EXPECT_EQ(TK_LIT_STRING, yylex());
    EXPECT_STREQ("\"\\\"\"", yytext);
}

TEST(LexemeStringLiteral, ShouldNotScanMultilineString) {
    yy_scan_string("\"a\\\nb\"");
    EXPECT_NE(TK_LIT_STRING, yylex());
    EXPECT_STRNE("\"a\\\nb\"", yytext);
}

TEST(LexemeIdentifier, ShouldScanIdentifier) {
    yy_scan_string("abc");
    EXPECT_EQ(TK_IDENTIFICADOR, yylex());
    EXPECT_STREQ("abc", yytext);
}

TEST(LexemeIdentifier, ShouldScanIdentifierWithDigit) {
    yy_scan_string("abc132");
    EXPECT_EQ(TK_IDENTIFICADOR, yylex());
    EXPECT_STREQ("abc132", yytext);
}

TEST(LexemeIdentifier, ShouldScanIdentifierWithUnderscore) {
    yy_scan_string("_abc_132_");
    EXPECT_EQ(TK_IDENTIFICADOR, yylex());
    EXPECT_STREQ("_abc_132_", yytext);
}

TEST(LexemeIdentifier, ShouldNotScanReservedKeyword) {
    yy_scan_string("intfloat");
    EXPECT_EQ(TK_IDENTIFICADOR, yylex());
    EXPECT_STREQ("intfloat", yytext);
}

TEST(LexemeIdentifier, ShouldNotScanStartWithDigit) {
    yy_scan_string("0abc");
    EXPECT_NE(TK_IDENTIFICADOR, yylex());
    EXPECT_STRNE("0abc", yytext);
}

TEST(LexemeError, ShouldScanErrorToken) {
    yy_scan_string("'aa'");
    EXPECT_EQ(TOKEN_ERRO, yylex());
    EXPECT_STREQ("'", yytext);
}