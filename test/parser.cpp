#include <gtest/gtest.h>

extern "C" {
#include "../lex.yy.h"
#include "../parser.tab.h"
}

TEST(SyntaxGlobalVariable, ShouldAcceptVarDeclaration) {
    yy_scan_string("var int;");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxGlobalVariable, ShouldAcceptVarDeclarationStatic) {
    yy_scan_string("var static bool;");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxGlobalVariable, ShouldAcceptVarDeclarationArray) {
    yy_scan_string("var[12] char;");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxGlobalVariable, ShouldAcceptVarDeclarationStaticArray) {
    yy_scan_string("var[12] static float;");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxGlobalVariable, ShouldAcceptVarDeclarationUserType) {
    yy_scan_string("var[12] static new_type;");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxClassDefinition, ShouldAcceptClassDefinition) {
    yy_scan_string(
            "class new_class"
            "  [ string new_field"
            "  ];");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxClassDefinition, ShouldNotAcceptNoFields) {
    yy_scan_string("class new_class []");
    EXPECT_NE(0, yyparse());
}

TEST(SyntaxClassDefinition, ShouldAcceptPrivateModifier) {
    yy_scan_string(
            "class new_class"
            "  [ private string new_field"
            "  ];");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxClassDefinition, ShouldAcceptPublicModifier) {
    yy_scan_string(
            "class new_class"
            "  [ public string new_field"
            "  ];");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxClassDefinition, ShouldAcceptProtectedModifier) {
    yy_scan_string(
            "class new_class"
            "  [ protected string new_field"
            "  ];");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxClassDefinition, ShouldAcceptMultipleFields) {
    yy_scan_string(
            "class new_class"
            "  [ protected string new_field"
            "  : private float another_field"
            "  : int another_one"
            "  ];");
    EXPECT_EQ(0, yyparse());
}
