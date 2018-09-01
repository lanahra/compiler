#include <gtest/gtest.h>

extern "C" {
#include "../lex.yy.h"
#include "../parser.tab.h"
}

TEST(SyntaxGlobalVariable, AcceptsVarDeclaration) {
    yy_scan_string("var int;");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxGlobalVariable, AcceptsVarDeclarationStatic) {
    yy_scan_string("var static bool;");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxGlobalVariable, AcceptsVarDeclarationArray) {
    yy_scan_string("var[12] char;");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxGlobalVariable, AcceptsVarDeclarationStaticArray) {
    yy_scan_string("var[12] static float;");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxGlobalVariable, AcceptsVarDeclarationUserType) {
    yy_scan_string("var new_type;");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxClassDefinition, AcceptsClassDefinition) {
    yy_scan_string(
            "class new_class"
            "  [ string new_field"
            "  ];");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxClassDefinition, DoesNotAcceptNoFields) {
    yy_scan_string("class new_class []");
    EXPECT_NE(0, yyparse());
}

TEST(SyntaxClassDefinition, AcceptsPrivateModifier) {
    yy_scan_string(
            "class new_class"
            "  [ private string new_field"
            "  ];");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxClassDefinition, AcceptsPublicModifier) {
    yy_scan_string(
            "class new_class"
            "  [ public string new_field"
            "  ];");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxClassDefinition, AcceptsProtectedModifier) {
    yy_scan_string(
            "class new_class"
            "  [ protected string new_field"
            "  ];");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxClassDefinition, AcceptsMultipleFields) {
    yy_scan_string(
            "class new_class"
            "  [ protected string new_field"
            "  : private float another_field"
            "  : int another_one"
            "  ];");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxFunctionHeader, AcceptsFunctionHeaderNoParameters) {
    yy_scan_string("int new_function() {}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxFunctionHeader, AcceptsFunctionHeaderOneParameter) {
    yy_scan_string("float new_function(string new_parameter) {}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxFunctionHeader, AcceptsFunctionHeaderMultipleParameters) {
    yy_scan_string(
            "char new_function"
            "  ( string new_parameter"
            "  , float another_parameter"
            "  , char another_one"
            "  , some_type yet_another"
            "  ) {}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxFunctionHeader, AcceptsFunctionHeaderStaticModifier) {
    yy_scan_string("static float new_function(string new_parameter) {}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxFunctionHeader, AcceptsFunctionHeaderUserType) {
    yy_scan_string("new_type new_function(other_type new_parameter) {}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxFunctionHeader, AcceptsFunctionBodyMultipleCommands) {
    yy_scan_string(
            "int main() {"
            "  int local_var;"
            "  float another_local_var;"
            "  char yet_another_local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxLocalVariable, AcceptsVarDeclaration) {
    yy_scan_string(
            "int main() {"
            "  int local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxLocalVariable, AcceptsStaticVarDeclaration) {
    yy_scan_string(
            "int main() {"
            "  static float local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxLocalVariable, AcceptsConstVarDeclaration) {
    yy_scan_string(
            "int main() {"
            "  const char local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxLocalVariable, AcceptsStaticConstVarDeclaration) {
    yy_scan_string(
            "int main() {"
            "  static const bool local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxLocalVariable, AcceptsVarInitialization) {
    yy_scan_string(
            "int main() {"
            "  bool local_var <= true;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxLocalVariable, AcceptsVarUserTypeDeclaration) {
    yy_scan_string(
            "int main() {"
            "  new_type local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxLocalVariable, DoesNotAcceptUserTypeVarInitialization) {
    yy_scan_string(
            "int main() {"
            "  new_type local_var <= 12;"
            "}");
    EXPECT_NE(0, yyparse());
}

TEST(SyntaxVariableAttribution, AcceptsVarAttribution) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxVariableAttribution, AcceptsVarArrayAttribution) {
    yy_scan_string(
            "int main() {"
            "  local_var[expression] = expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxVariableAttribution, AcceptsVarUserTypeAttribution) {
    yy_scan_string(
            "int main() {"
            "  local_var$field = expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxShiftOp, AcceptsLeftShiftOp) {
    yy_scan_string(
            "int main() {"
            "  local_var << 8;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxShiftOp, AcceptsRightShiftOp) {
    yy_scan_string(
            "int main() {"
            "  local_var >> 8;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxReturn, AcceptsReturnStatement) {
    yy_scan_string(
            "int main() {"
            "  return local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxContinue, AcceptsContinueStatement) {
    yy_scan_string(
            "int main() {"
            "  continue;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxBreak, AcceptsBreakStatement) {
    yy_scan_string(
            "int main() {"
            "  break;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxCase, AcceptsCaseStatement) {
    yy_scan_string(
            "int main() {"
            "  case 0:"
            "  case 1:"
            "  case 2:"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxConditionalStatement, AcceptsIfThenStatement) {
    yy_scan_string(
            "int main() {"
            "  if (expressions) then {}"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxConditionalStatement, AcceptsIfThenElseStatement) {
    yy_scan_string(
            "int main() {"
            "  if (expressions) then {} else {}"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxInput, AcceptsInput) {
    yy_scan_string(
            "int main() {"
            " input local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxOutput, AcceptsOutput) {
    yy_scan_string(
            "int main() {"
            " output local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxOutput, AcceptsOutputMultipleExpressions) {
    yy_scan_string(
            "int main() {"
            " output local_var, another_one, yet_another;"
            "}");
    EXPECT_EQ(0, yyparse());
}
