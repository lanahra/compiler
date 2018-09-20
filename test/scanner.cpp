#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Eq;
using ::testing::FloatEq;
using ::testing::StrEq;

extern "C" {
#include "../include/lex.yy.h"
#include "../include/parser.tab.h"

extern void free_tokens();
}

TEST(LexemeLineComment, DoesNotScanLineComment) {
    yy_scan_string("int// ignore comment\nfloat");
    EXPECT_EQ(INT, yylex());
    EXPECT_STREQ("int", yytext);
    EXPECT_EQ(FLOAT, yylex());
    EXPECT_STREQ("float", yytext);
    yylex_destroy();
}

TEST(LexemeBlockComment, DoesNotScanBlockComment) {
    yy_scan_string("int/* ignore comment\nfloat*/const");
    EXPECT_EQ(INT, yylex());
    EXPECT_STREQ("int", yytext);
    EXPECT_EQ(CONST, yylex());
    EXPECT_STREQ("const", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansIntKeyword) {
    yy_scan_string("int");
    EXPECT_EQ(INT, yylex());
    EXPECT_STREQ("int", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansFloatKeyword) {
    yy_scan_string("float");
    EXPECT_EQ(FLOAT, yylex());
    EXPECT_STREQ("float", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansBoolKeyword) {
    yy_scan_string("bool");
    EXPECT_EQ(BOOL, yylex());
    EXPECT_STREQ("bool", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansCharKeyword) {
    yy_scan_string("char");
    EXPECT_EQ(CHAR, yylex());
    EXPECT_STREQ("char", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansStringKeyword) {
    yy_scan_string("string");
    EXPECT_EQ(STRING, yylex());
    EXPECT_STREQ("string", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansIfKeyword) {
    yy_scan_string("if");
    EXPECT_EQ(IF, yylex());
    EXPECT_STREQ("if", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansThenKeyword) {
    yy_scan_string("then");
    EXPECT_EQ(THEN, yylex());
    EXPECT_STREQ("then", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansElseKeyword) {
    yy_scan_string("else");
    EXPECT_EQ(ELSE, yylex());
    EXPECT_STREQ("else", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansWhileKeyword) {
    yy_scan_string("while");
    EXPECT_EQ(WHILE, yylex());
    EXPECT_STREQ("while", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansDoKeyword) {
    yy_scan_string("do");
    EXPECT_EQ(DO, yylex());
    EXPECT_STREQ("do", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansInputKeyword) {
    yy_scan_string("input");
    EXPECT_EQ(INPUT, yylex());
    EXPECT_STREQ("input", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansOutputKeyword) {
    yy_scan_string("output");
    EXPECT_EQ(OUTPUT, yylex());
    EXPECT_STREQ("output", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansReturnKeyword) {
    yy_scan_string("return");
    EXPECT_EQ(RETURN, yylex());
    EXPECT_STREQ("return", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansConstKeyword) {
    yy_scan_string("const");
    EXPECT_EQ(CONST, yylex());
    EXPECT_STREQ("const", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansStaticKeyword) {
    yy_scan_string("static");
    EXPECT_EQ(STATIC, yylex());
    EXPECT_STREQ("static", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansForeachKeyword) {
    yy_scan_string("foreach");
    EXPECT_EQ(FOREACH, yylex());
    EXPECT_STREQ("foreach", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansForKeyword) {
    yy_scan_string("for");
    EXPECT_EQ(FOR, yylex());
    EXPECT_STREQ("for", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansSwitchKeyword) {
    yy_scan_string("switch");
    EXPECT_EQ(SWITCH, yylex());
    EXPECT_STREQ("switch", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansCaseKeyword) {
    yy_scan_string("case");
    EXPECT_EQ(CASE, yylex());
    EXPECT_STREQ("case", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansBreakKeyword) {
    yy_scan_string("break");
    EXPECT_EQ(BREAK, yylex());
    EXPECT_STREQ("break", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansContinueKeyword) {
    yy_scan_string("continue");
    EXPECT_EQ(CONTINUE, yylex());
    EXPECT_STREQ("continue", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansClassKeyword) {
    yy_scan_string("class");
    EXPECT_EQ(CLASS, yylex());
    EXPECT_STREQ("class", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansPrivateKeyword) {
    yy_scan_string("private");
    EXPECT_EQ(PRIVATE, yylex());
    EXPECT_STREQ("private", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansPublicKeyword) {
    yy_scan_string("public");
    EXPECT_EQ(PUBLIC, yylex());
    EXPECT_STREQ("public", yytext);
    yylex_destroy();
}

TEST(LexemeReservedKeyword, ScansProtectedKeyword) {
    yy_scan_string("protected");
    EXPECT_EQ(PROTECTED, yylex());
    EXPECT_STREQ("protected", yytext);
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansComma) {
    yy_scan_string(",");
    EXPECT_EQ(',', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansSemicolon) {
    yy_scan_string(";");
    EXPECT_EQ(';', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansColon) {
    yy_scan_string(":");
    EXPECT_EQ(':', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansOpenParenthesis) {
    yy_scan_string("(");
    EXPECT_EQ('(', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansCloseParenthesis) {
    yy_scan_string(")");
    EXPECT_EQ(')', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansOpenSquareBracket) {
    yy_scan_string("[");
    EXPECT_EQ('[', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansCloseSquareBracket) {
    yy_scan_string("]");
    EXPECT_EQ(']', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansOpenBracket) {
    yy_scan_string("{");
    EXPECT_EQ('{', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansCloseBracket) {
    yy_scan_string("}");
    EXPECT_EQ('}', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansPlusSign) {
    yy_scan_string("+");
    EXPECT_EQ('+', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansMinusSign) {
    yy_scan_string("-");
    EXPECT_EQ('-', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansPipe) {
    yy_scan_string("|");
    EXPECT_EQ('|', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansQuestionMark) {
    yy_scan_string("?");
    EXPECT_EQ('?', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansAsterisk) {
    yy_scan_string("*");
    EXPECT_EQ('*', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansSlash) {
    yy_scan_string("/");
    EXPECT_EQ('/', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansLess) {
    yy_scan_string("<");
    EXPECT_EQ('<', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansGreater) {
    yy_scan_string(">");
    EXPECT_EQ('>', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansEqual) {
    yy_scan_string("=");
    EXPECT_EQ('=', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansExclamationMark) {
    yy_scan_string("!");
    EXPECT_EQ('!', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansAmpersand) {
    yy_scan_string("&");
    EXPECT_EQ('&', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansPercentSign) {
    yy_scan_string("%");
    EXPECT_EQ('%', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansNumberSign) {
    yy_scan_string("#");
    EXPECT_EQ('#', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansCaret) {
    yy_scan_string("^");
    EXPECT_EQ('^', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansDot) {
    yy_scan_string(".");
    EXPECT_EQ('.', yylex());
    yylex_destroy();
}

TEST(LexemeSpecialCharacter, ScansDollarSign) {
    yy_scan_string("$");
    EXPECT_EQ('$', yylex());
    yylex_destroy();
}

TEST(LexemeOperator, ScansLessEqual) {
    yy_scan_string("<=");
    EXPECT_EQ(LE_OP, yylex());
    EXPECT_STREQ("<=", yytext);
    yylex_destroy();
}

TEST(LexemeOperator, ScansGreaterEqual) {
    yy_scan_string(">=");
    EXPECT_EQ(GE_OP, yylex());
    EXPECT_STREQ(">=", yytext);
    yylex_destroy();
}

TEST(LexemeOperator, ScansEqualEqual) {
    yy_scan_string("==");
    EXPECT_EQ(EQ_OP, yylex());
    EXPECT_STREQ("==", yytext);
    yylex_destroy();
}

TEST(LexemeOperator, ScansNotEqual) {
    yy_scan_string("!=");
    EXPECT_EQ(NE_OP, yylex());
    EXPECT_STREQ("!=", yytext);
    yylex_destroy();
}

TEST(LexemeOperator, ScansAnd) {
    yy_scan_string("&&");
    EXPECT_EQ(AND_OP, yylex());
    EXPECT_STREQ("&&", yytext);
    yylex_destroy();
}

TEST(LexemeOperator, ScansOr) {
    yy_scan_string("||");
    EXPECT_EQ(OR_OP, yylex());
    EXPECT_STREQ("||", yytext);
    yylex_destroy();
}

TEST(LexemeOperator, ScansShiftRight) {
    yy_scan_string(">>");
    EXPECT_EQ(SR_OP, yylex());
    EXPECT_STREQ(">>", yytext);
    yylex_destroy();
}

TEST(LexemeOperator, ScansShiftLeft) {
    yy_scan_string("<<");
    EXPECT_EQ(SL_OP, yylex());
    EXPECT_STREQ("<<", yytext);
    yylex_destroy();
}

TEST(LexemeOperator, ScansForwardPipe) {
    yy_scan_string("%>%");
    EXPECT_EQ(FORWARD_PIPE, yylex());
    EXPECT_STREQ("%>%", yytext);
    yylex_destroy();
}

TEST(LexemeOperator, ScansBashPipe) {
    yy_scan_string("%|%");
    EXPECT_EQ(BASH_PIPE, yylex());
    EXPECT_STREQ("%|%", yytext);
    yylex_destroy();
}

TEST(LexemeIntLiteral, ScansInteger) {
    yy_scan_string("102");
    EXPECT_EQ(INT_LITERAL, yylex());
    EXPECT_STREQ("102", yytext);
    yylex_destroy();
}

TEST(LexemeFloatLiteral, ScansFloat) {
    yy_scan_string("1.0");
    EXPECT_EQ(FLOAT_LITERAL, yylex());
    EXPECT_STREQ("1.0", yytext);
    yylex_destroy();
}

TEST(LexemeFloatLiteral, ScansFloatExpoent) {
    yy_scan_string("1.0e10");
    EXPECT_EQ(FLOAT_LITERAL, yylex());
    EXPECT_STREQ("1.0e10", yytext);
    yylex_destroy();
}

TEST(LexemeFloatLiteral, ScansFloatExpoentPlusSign) {
    yy_scan_string("1.0e+10");
    EXPECT_EQ(FLOAT_LITERAL, yylex());
    EXPECT_STREQ("1.0e+10", yytext);
    yylex_destroy();
}

TEST(LexemeFloatLiteral, ScansFloatExpoentMinusSign) {
    yy_scan_string("1.0e-10");
    EXPECT_EQ(FLOAT_LITERAL, yylex());
    EXPECT_STREQ("1.0e-10", yytext);
    yylex_destroy();
}

TEST(LexemeFloatLiteral, ScansFloatExpoentUpperCase) {
    yy_scan_string("1.0E-10");
    EXPECT_EQ(FLOAT_LITERAL, yylex());
    EXPECT_STREQ("1.0E-10", yytext);
    yylex_destroy();
}

TEST(LexemeFloatLiteral, DoesNotScanFloatWithoutIntegerPart) {
    yy_scan_string(".01");
    EXPECT_NE(FLOAT_LITERAL, yylex());
    EXPECT_STRNE(".01", yytext);
    yylex_destroy();
}

TEST(LexemeFloatLiteral, DoesNotScanFloatWithoutDecimalPart) {
    yy_scan_string("1.");
    EXPECT_NE(FLOAT_LITERAL, yylex());
    EXPECT_STRNE("1.", yytext);
    yylex_destroy();
}

TEST(LexemeBoolLiteral, ScansFalse) {
    yy_scan_string("false");
    EXPECT_EQ(FALSE, yylex());
    EXPECT_STREQ("false", yytext);
    yylex_destroy();
}

TEST(LexemeBoolLiteral, ScansTrue) {
    yy_scan_string("true");
    EXPECT_EQ(TRUE, yylex());
    EXPECT_STREQ("true", yytext);
    yylex_destroy();
}

TEST(LexemeCharLiteral, ScansChar) {
    yy_scan_string("'a'");
    EXPECT_EQ(CHAR_LITERAL, yylex());
    EXPECT_STREQ("'a'", yytext);
    yylex_destroy();
}

TEST(LexemeCharLiteral, DoesNotScanEmptyChar) {
    yy_scan_string("''");
    EXPECT_NE(CHAR_LITERAL, yylex());
    EXPECT_STRNE("''", yytext);
    yylex_destroy();
}

TEST(LexemeCharLiteral, DoesNotScanEscapedChar) {
    yy_scan_string("'\\n'");
    EXPECT_NE(CHAR_LITERAL, yylex());
    EXPECT_STRNE("'\\n'", yytext);
    yylex_destroy();
}

TEST(LexemeStringLiteral, ScansString) {
    yy_scan_string("\"a\"");
    EXPECT_EQ(STRING_LITERAL, yylex());
    EXPECT_STREQ("\"a\"", yytext);
    free(yylval.val.string_v);
    yylex_destroy();
}

TEST(LexemeStringLiteral, ScansEmptyString) {
    yy_scan_string("\"\"");
    EXPECT_EQ(STRING_LITERAL, yylex());
    EXPECT_STREQ("\"\"", yytext);
    free(yylval.val.string_v);
    yylex_destroy();
}

TEST(LexemeStringLiteral, ScansEscapedCharInString) {
    yy_scan_string("\"\\n\"");
    EXPECT_EQ(STRING_LITERAL, yylex());
    EXPECT_STREQ("\"\\n\"", yytext);
    free(yylval.val.string_v);
    yylex_destroy();
}

TEST(LexemeStringLiteral, ScansEscapedQuoteInString) {
    yy_scan_string("\"\\\"\"");
    EXPECT_EQ(STRING_LITERAL, yylex());
    EXPECT_STREQ("\"\\\"\"", yytext);
    free(yylval.val.string_v);
    yylex_destroy();
}

TEST(LexemeStringLiteral, DoesNotScanMultilineString) {
    yy_scan_string("\"a\\\nb\"");
    EXPECT_NE(STRING_LITERAL, yylex());
    EXPECT_STRNE("\"a\\\nb\"", yytext);
    yylex_destroy();
}

TEST(LexemeIdentifier, ScansIdentifier) {
    yy_scan_string("abc");
    EXPECT_EQ(ID, yylex());
    EXPECT_STREQ("abc", yytext);
    free(yylval.val.string_v);
    yylex_destroy();
}

TEST(LexemeIdentifier, ScansIdentifierWithDigit) {
    yy_scan_string("abc132");
    EXPECT_EQ(ID, yylex());
    EXPECT_STREQ("abc132", yytext);
    free(yylval.val.string_v);
    yylex_destroy();
}

TEST(LexemeIdentifier, ScansIdentifierWithUnderscore) {
    yy_scan_string("_abc_132_");
    EXPECT_EQ(ID, yylex());
    EXPECT_STREQ("_abc_132_", yytext);
    free(yylval.val.string_v);
    yylex_destroy();
}

TEST(LexemeIdentifier, DoesNotScanReservedKeyword) {
    yy_scan_string("intfloat");
    EXPECT_EQ(ID, yylex());
    EXPECT_STREQ("intfloat", yytext);
    free(yylval.val.string_v);
    yylex_destroy();
}

TEST(LexemeIdentifier, DoesNotScanStartWithDigit) {
    yy_scan_string("0abc");
    EXPECT_NE(ID, yylex());
    EXPECT_STRNE("0abc", yytext);
    yylex_destroy();
}

TEST(LexemeError, ScansErrorToken) {
    yy_scan_string("'aa'");
    EXPECT_EQ(ERROR, yylex());
    EXPECT_STREQ("'", yytext);
    yylex_destroy();
}

TEST(LexemeTokenValue, AssignsIntegerTokenValue) {
    yy_scan_string("142");
    EXPECT_THAT(yylex(), Eq(INT_LITERAL));
    EXPECT_THAT(yylval.val.int_v, Eq(142));
    yylex_destroy();
}

TEST(LexemeTokenValue, AssignsFloatTokenValue) {
    yy_scan_string("4.5");
    EXPECT_THAT(yylex(), Eq(FLOAT_LITERAL));
    EXPECT_THAT(yylval.val.float_v, FloatEq(4.5));
    yylex_destroy();
}

TEST(LexemeTokenValue, AssignsFloatWithExponentTokenValue) {
    yy_scan_string("4.5e-3");
    EXPECT_THAT(yylex(), Eq(FLOAT_LITERAL));
    EXPECT_THAT(yylval.val.float_v, FloatEq(4.5e-3));
    yylex_destroy();
}

TEST(LexemeTokenValue, AssignsCharTokenValue) {
    yy_scan_string("'a'");
    EXPECT_THAT(yylex(), Eq(CHAR_LITERAL));
    EXPECT_THAT(yylval.val.char_v, Eq('a'));
    yylex_destroy();
}

TEST(LexemeTokenValue, AssignsStringTokenValue) {
    yy_scan_string("\"a string\"");
    EXPECT_THAT(yylex(), Eq(STRING_LITERAL));
    EXPECT_THAT(yylval.val.string_v, StrEq("a string"));
    free(yylval.val.string_v);
    yylex_destroy();
}

TEST(LexemeTokenValue, AssignsFalseTokenValue) {
    yy_scan_string("false");
    EXPECT_THAT(yylex(), Eq(FALSE));
    EXPECT_THAT(yylval.val.bool_v, Eq(false));
    yylex_destroy();
}

TEST(LexemeTokenValue, AssignsTrueTokenValue) {
    yy_scan_string("true");
    EXPECT_THAT(yylex(), Eq(TRUE));
    EXPECT_THAT(yylval.val.bool_v, Eq(true));
    yylex_destroy();
}
