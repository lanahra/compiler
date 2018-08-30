#include <gtest/gtest.h>

extern "C" {
#include "../lex.yy.h"
#include "../parser.tab.h"
}

TEST(SyntaxGlobalVariable, ShouldAcceptVarDeclaration) {
    yy_scan_string("int var;");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxGlobalVariable, ShouldAcceptVarDeclarationStatic) {
    yy_scan_string("static bool var;");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxGlobalVariable, ShouldAcceptVarDeclarationArray) {
    yy_scan_string("char var[12];");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxGlobalVariable, ShouldAcceptVarDeclarationStaticArray) {
    yy_scan_string("static float var[12];");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxGlobalVariable, ShouldAcceptVarDeclarationUserType) {
    yy_scan_string("static new_type var[12];");
    EXPECT_EQ(0, yyparse());
}
