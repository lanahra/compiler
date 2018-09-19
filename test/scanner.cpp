#include <gtest/gtest.h>

extern "C" {
#include "../include/lex.yy.h"
#include "../include/parser.tab.h"
}

TEST(LexemeLineComment, DoesNotScanLineComment) {
    yy_scan_string("int// ignore comment\nfloat");
    EXPECT_EQ(INT, yylex());
    EXPECT_STREQ("int", yytext);
    EXPECT_EQ(FLOAT, yylex());
    EXPECT_STREQ("float", yytext);
}

TEST(LexemeBlockComment, DoesNotScanBlockComment) {
    yy_scan_string("int/* ignore comment\nfloat*/const");
    EXPECT_EQ(INT, yylex());
    EXPECT_STREQ("int", yytext);
    EXPECT_EQ(CONST, yylex());
    EXPECT_STREQ("const", yytext);
}

TEST(LexemeReservedKeyword, ScansIntKeyword) {
    yy_scan_string("int");
    EXPECT_EQ(INT, yylex());
    EXPECT_STREQ("int", yytext);
}

TEST(LexemeReservedKeyword, ScansFloatKeyword) {
    yy_scan_string("float");
    EXPECT_EQ(FLOAT, yylex());
    EXPECT_STREQ("float", yytext);
}

TEST(LexemeReservedKeyword, ScansBoolKeyword) {
    yy_scan_string("bool");
    EXPECT_EQ(BOOL, yylex());
    EXPECT_STREQ("bool", yytext);
}

TEST(LexemeReservedKeyword, ScansCharKeyword) {
    yy_scan_string("char");
    EXPECT_EQ(CHAR, yylex());
    EXPECT_STREQ("char", yytext);
}

TEST(LexemeReservedKeyword, ScansStringKeyword) {
    yy_scan_string("string");
    EXPECT_EQ(STRING, yylex());
    EXPECT_STREQ("string", yytext);
}

TEST(LexemeReservedKeyword, ScansIfKeyword) {
    yy_scan_string("if");
    EXPECT_EQ(IF, yylex());
    EXPECT_STREQ("if", yytext);
}

TEST(LexemeReservedKeyword, ScansThenKeyword) {
    yy_scan_string("then");
    EXPECT_EQ(THEN, yylex());
    EXPECT_STREQ("then", yytext);
}

TEST(LexemeReservedKeyword, ScansElseKeyword) {
    yy_scan_string("else");
    EXPECT_EQ(ELSE, yylex());
    EXPECT_STREQ("else", yytext);
}

TEST(LexemeReservedKeyword, ScansWhileKeyword) {
    yy_scan_string("while");
    EXPECT_EQ(WHILE, yylex());
    EXPECT_STREQ("while", yytext);
}

TEST(LexemeReservedKeyword, ScansDoKeyword) {
    yy_scan_string("do");
    EXPECT_EQ(DO, yylex());
    EXPECT_STREQ("do", yytext);
}

TEST(LexemeReservedKeyword, ScansInputKeyword) {
    yy_scan_string("input");
    EXPECT_EQ(INPUT, yylex());
    EXPECT_STREQ("input", yytext);
}

TEST(LexemeReservedKeyword, ScansOutputKeyword) {
    yy_scan_string("output");
    EXPECT_EQ(OUTPUT, yylex());
    EXPECT_STREQ("output", yytext);
}

TEST(LexemeReservedKeyword, ScansReturnKeyword) {
    yy_scan_string("return");
    EXPECT_EQ(RETURN, yylex());
    EXPECT_STREQ("return", yytext);
}

TEST(LexemeReservedKeyword, ScansConstKeyword) {
    yy_scan_string("const");
    EXPECT_EQ(CONST, yylex());
    EXPECT_STREQ("const", yytext);
}

TEST(LexemeReservedKeyword, ScansStaticKeyword) {
    yy_scan_string("static");
    EXPECT_EQ(STATIC, yylex());
    EXPECT_STREQ("static", yytext);
}

TEST(LexemeReservedKeyword, ScansForeachKeyword) {
    yy_scan_string("foreach");
    EXPECT_EQ(FOREACH, yylex());
    EXPECT_STREQ("foreach", yytext);
}

TEST(LexemeReservedKeyword, ScansForKeyword) {
    yy_scan_string("for");
    EXPECT_EQ(FOR, yylex());
    EXPECT_STREQ("for", yytext);
}

TEST(LexemeReservedKeyword, ScansSwitchKeyword) {
    yy_scan_string("switch");
    EXPECT_EQ(SWITCH, yylex());
    EXPECT_STREQ("switch", yytext);
}

TEST(LexemeReservedKeyword, ScansCaseKeyword) {
    yy_scan_string("case");
    EXPECT_EQ(CASE, yylex());
    EXPECT_STREQ("case", yytext);
}

TEST(LexemeReservedKeyword, ScansBreakKeyword) {
    yy_scan_string("break");
    EXPECT_EQ(BREAK, yylex());
    EXPECT_STREQ("break", yytext);
}

TEST(LexemeReservedKeyword, ScansContinueKeyword) {
    yy_scan_string("continue");
    EXPECT_EQ(CONTINUE, yylex());
    EXPECT_STREQ("continue", yytext);
}

TEST(LexemeReservedKeyword, ScansClassKeyword) {
    yy_scan_string("class");
    EXPECT_EQ(CLASS, yylex());
    EXPECT_STREQ("class", yytext);
}

TEST(LexemeReservedKeyword, ScansPrivateKeyword) {
    yy_scan_string("private");
    EXPECT_EQ(PRIVATE, yylex());
    EXPECT_STREQ("private", yytext);
}

TEST(LexemeReservedKeyword, ScansPublicKeyword) {
    yy_scan_string("public");
    EXPECT_EQ(PUBLIC, yylex());
    EXPECT_STREQ("public", yytext);
}

TEST(LexemeReservedKeyword, ScansProtectedKeyword) {
    yy_scan_string("protected");
    EXPECT_EQ(PROTECTED, yylex());
    EXPECT_STREQ("protected", yytext);
}

TEST(LexemeSpecialCharacter, ScansComma) {
    yy_scan_string(",");
    EXPECT_EQ(',', yylex());
}

TEST(LexemeSpecialCharacter, ScansSemicolon) {
    yy_scan_string(";");
    EXPECT_EQ(';', yylex());
}

TEST(LexemeSpecialCharacter, ScansColon) {
    yy_scan_string(":");
    EXPECT_EQ(':', yylex());
}

TEST(LexemeSpecialCharacter, ScansOpenParenthesis) {
    yy_scan_string("(");
    EXPECT_EQ('(', yylex());
}

TEST(LexemeSpecialCharacter, ScansCloseParenthesis) {
    yy_scan_string(")");
    EXPECT_EQ(')', yylex());
}

TEST(LexemeSpecialCharacter, ScansOpenSquareBracket) {
    yy_scan_string("[");
    EXPECT_EQ('[', yylex());
}

TEST(LexemeSpecialCharacter, ScansCloseSquareBracket) {
    yy_scan_string("]");
    EXPECT_EQ(']', yylex());
}

TEST(LexemeSpecialCharacter, ScansOpenBracket) {
    yy_scan_string("{");
    EXPECT_EQ('{', yylex());
}

TEST(LexemeSpecialCharacter, ScansCloseBracket) {
    yy_scan_string("}");
    EXPECT_EQ('}', yylex());
}

TEST(LexemeSpecialCharacter, ScansPlusSign) {
    yy_scan_string("+");
    EXPECT_EQ('+', yylex());
}

TEST(LexemeSpecialCharacter, ScansMinusSign) {
    yy_scan_string("-");
    EXPECT_EQ('-', yylex());
}

TEST(LexemeSpecialCharacter, ScansPipe) {
    yy_scan_string("|");
    EXPECT_EQ('|', yylex());
}

TEST(LexemeSpecialCharacter, ScansQuestionMark) {
    yy_scan_string("?");
    EXPECT_EQ('?', yylex());
}

TEST(LexemeSpecialCharacter, ScansAsterisk) {
    yy_scan_string("*");
    EXPECT_EQ('*', yylex());
}

TEST(LexemeSpecialCharacter, ScansSlash) {
    yy_scan_string("/");
    EXPECT_EQ('/', yylex());
}

TEST(LexemeSpecialCharacter, ScansLess) {
    yy_scan_string("<");
    EXPECT_EQ('<', yylex());
}

TEST(LexemeSpecialCharacter, ScansGreater) {
    yy_scan_string(">");
    EXPECT_EQ('>', yylex());
}

TEST(LexemeSpecialCharacter, ScansEqual) {
    yy_scan_string("=");
    EXPECT_EQ('=', yylex());
}

TEST(LexemeSpecialCharacter, ScansExclamationMark) {
    yy_scan_string("!");
    EXPECT_EQ('!', yylex());
}

TEST(LexemeSpecialCharacter, ScansAmpersand) {
    yy_scan_string("&");
    EXPECT_EQ('&', yylex());
}

TEST(LexemeSpecialCharacter, ScansPercentSign) {
    yy_scan_string("%");
    EXPECT_EQ('%', yylex());
}

TEST(LexemeSpecialCharacter, ScansNumberSign) {
    yy_scan_string("#");
    EXPECT_EQ('#', yylex());
}

TEST(LexemeSpecialCharacter, ScansCaret) {
    yy_scan_string("^");
    EXPECT_EQ('^', yylex());
}

TEST(LexemeSpecialCharacter, ScansDot) {
    yy_scan_string(".");
    EXPECT_EQ('.', yylex());
}

TEST(LexemeSpecialCharacter, ScansDollarSign) {
    yy_scan_string("$");
    EXPECT_EQ('$', yylex());
}

TEST(LexemeOperator, ScansLessEqual) {
    yy_scan_string("<=");
    EXPECT_EQ(LE_OP, yylex());
    EXPECT_STREQ("<=", yytext);
}

TEST(LexemeOperator, ScansGreaterEqual) {
    yy_scan_string(">=");
    EXPECT_EQ(GE_OP, yylex());
    EXPECT_STREQ(">=", yytext);
}

TEST(LexemeOperator, ScansEqualEqual) {
    yy_scan_string("==");
    EXPECT_EQ(EQ_OP, yylex());
    EXPECT_STREQ("==", yytext);
}

TEST(LexemeOperator, ScansNotEqual) {
    yy_scan_string("!=");
    EXPECT_EQ(NE_OP, yylex());
    EXPECT_STREQ("!=", yytext);
}

TEST(LexemeOperator, ScansAnd) {
    yy_scan_string("&&");
    EXPECT_EQ(AND_OP, yylex());
    EXPECT_STREQ("&&", yytext);
}

TEST(LexemeOperator, ScansOr) {
    yy_scan_string("||");
    EXPECT_EQ(OR_OP, yylex());
    EXPECT_STREQ("||", yytext);
}

TEST(LexemeOperator, ScansShiftRight) {
    yy_scan_string(">>");
    EXPECT_EQ(SR_OP, yylex());
    EXPECT_STREQ(">>", yytext);
}

TEST(LexemeOperator, ScansShiftLeft) {
    yy_scan_string("<<");
    EXPECT_EQ(SL_OP, yylex());
    EXPECT_STREQ("<<", yytext);
}

TEST(LexemeOperator, ScansForwardPipe) {
    yy_scan_string("%>%");
    EXPECT_EQ(FORWARD_PIPE, yylex());
    EXPECT_STREQ("%>%", yytext);
}

TEST(LexemeOperator, ScansBashPipe) {
    yy_scan_string("%|%");
    EXPECT_EQ(BASH_PIPE, yylex());
    EXPECT_STREQ("%|%", yytext);
}

TEST(LexemeIntLiteral, ScansInteger) {
    yy_scan_string("102");
    EXPECT_EQ(INT_LITERAL, yylex());
    EXPECT_STREQ("102", yytext);
}

TEST(LexemeFloatLiteral, ScansFloat) {
    yy_scan_string("1.0");
    EXPECT_EQ(FLOAT_LITERAL, yylex());
    EXPECT_STREQ("1.0", yytext);
}

TEST(LexemeFloatLiteral, ScansFloatExpoent) {
    yy_scan_string("1.0e10");
    EXPECT_EQ(FLOAT_LITERAL, yylex());
    EXPECT_STREQ("1.0e10", yytext);
}

TEST(LexemeFloatLiteral, ScansFloatExpoentPlusSign) {
    yy_scan_string("1.0e+10");
    EXPECT_EQ(FLOAT_LITERAL, yylex());
    EXPECT_STREQ("1.0e+10", yytext);
}

TEST(LexemeFloatLiteral, ScansFloatExpoentMinusSign) {
    yy_scan_string("1.0e-10");
    EXPECT_EQ(FLOAT_LITERAL, yylex());
    EXPECT_STREQ("1.0e-10", yytext);
}

TEST(LexemeFloatLiteral, ScansFloatExpoentUpperCase) {
    yy_scan_string("1.0E-10");
    EXPECT_EQ(FLOAT_LITERAL, yylex());
    EXPECT_STREQ("1.0E-10", yytext);
}

TEST(LexemeFloatLiteral, DoesNotScanFloatWithoutIntegerPart) {
    yy_scan_string(".01");
    EXPECT_NE(FLOAT_LITERAL, yylex());
    EXPECT_STRNE(".01", yytext);
}

TEST(LexemeFloatLiteral, DoesNotScanFloatWithoutDecimalPart) {
    yy_scan_string("1.");
    EXPECT_NE(FLOAT_LITERAL, yylex());
    EXPECT_STRNE("1.", yytext);
}

TEST(LexemeBoolLiteral, ScansFalse) {
    yy_scan_string("false");
    EXPECT_EQ(FALSE, yylex());
    EXPECT_STREQ("false", yytext);
}

TEST(LexemeBoolLiteral, ScansTrue) {
    yy_scan_string("true");
    EXPECT_EQ(TRUE, yylex());
    EXPECT_STREQ("true", yytext);
}

TEST(LexemeCharLiteral, ScansChar) {
    yy_scan_string("'a'");
    EXPECT_EQ(CHAR_LITERAL, yylex());
    EXPECT_STREQ("'a'", yytext);
}

TEST(LexemeCharLiteral, DoesNotScanEmptyChar) {
    yy_scan_string("''");
    EXPECT_NE(CHAR_LITERAL, yylex());
    EXPECT_STRNE("''", yytext);
}

TEST(LexemeCharLiteral, DoesNotScanEscapedChar) {
    yy_scan_string("'\\n'");
    EXPECT_NE(CHAR_LITERAL, yylex());
    EXPECT_STRNE("'\\n'", yytext);
}

TEST(LexemeStringLiteral, ScansString) {
    yy_scan_string("\"a\"");
    EXPECT_EQ(STRING_LITERAL, yylex());
    EXPECT_STREQ("\"a\"", yytext);
}

TEST(LexemeStringLiteral, ScansEmptyString) {
    yy_scan_string("\"\"");
    EXPECT_EQ(STRING_LITERAL, yylex());
    EXPECT_STREQ("\"\"", yytext);
}

TEST(LexemeStringLiteral, ScansEscapedCharInString) {
    yy_scan_string("\"\\n\"");
    EXPECT_EQ(STRING_LITERAL, yylex());
    EXPECT_STREQ("\"\\n\"", yytext);
}

TEST(LexemeStringLiteral, ScansEscapedQuoteInString) {
    yy_scan_string("\"\\\"\"");
    EXPECT_EQ(STRING_LITERAL, yylex());
    EXPECT_STREQ("\"\\\"\"", yytext);
}

TEST(LexemeStringLiteral, DoesNotScanMultilineString) {
    yy_scan_string("\"a\\\nb\"");
    EXPECT_NE(STRING_LITERAL, yylex());
    EXPECT_STRNE("\"a\\\nb\"", yytext);
}

TEST(LexemeIdentifier, ScansIdentifier) {
    yy_scan_string("abc");
    EXPECT_EQ(ID, yylex());
    EXPECT_STREQ("abc", yytext);
}

TEST(LexemeIdentifier, ScansIdentifierWithDigit) {
    yy_scan_string("abc132");
    EXPECT_EQ(ID, yylex());
    EXPECT_STREQ("abc132", yytext);
}

TEST(LexemeIdentifier, ScansIdentifierWithUnderscore) {
    yy_scan_string("_abc_132_");
    EXPECT_EQ(ID, yylex());
    EXPECT_STREQ("_abc_132_", yytext);
}

TEST(LexemeIdentifier, DoesNotScanReservedKeyword) {
    yy_scan_string("intfloat");
    EXPECT_EQ(ID, yylex());
    EXPECT_STREQ("intfloat", yytext);
}

TEST(LexemeIdentifier, DoesNotScanStartWithDigit) {
    yy_scan_string("0abc");
    EXPECT_NE(ID, yylex());
    EXPECT_STRNE("0abc", yytext);
}

TEST(LexemeError, ScansErrorToken) {
    yy_scan_string("'aa'");
    EXPECT_EQ(ERROR, yylex());
    EXPECT_STREQ("'", yytext);
}
