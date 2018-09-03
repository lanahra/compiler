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
            "  input local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxOutput, AcceptsOutput) {
    yy_scan_string(
            "int main() {"
            "  output local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxOutput, AcceptsOutputMultipleExpressions) {
    yy_scan_string(
            "int main() {"
            "  output local_var, another_one, yet_another;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxFunctionCall, AcceptsFunctionCall) {
    yy_scan_string(
            "int main() {"
            "  f();"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxFunctionCall, AcceptsFunctionCallDotArgument) {
    yy_scan_string(
            "int main() {"
            "  f(.);"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxFunctionCall, AcceptsFunctionCallArgument) {
    yy_scan_string(
            "int main() {"
            "  f(expression);"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxFunctionCall, AcceptsFunctionCallMultipleArguments) {
    yy_scan_string(
            "int main() {"
            "  f(expression, ., another_expression);"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxFunctionCall, AcceptsFunctionForwardPipe) {
    yy_scan_string(
            "int main() {"
            "  f(expression) \%>\% g(.);"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxFunctionCall, AcceptsFunctionBashPipe) {
    yy_scan_string(
            "int main() {"
            "  f(expression) \%|\% g(.);"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxFunctionCall, AcceptsFunctionMultiplePipes) {
    yy_scan_string(
            "int main() {"
            "  f(x) \%>\% g(.) \%|\% h(., z);"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxForeach, AcceptsForeach) {
    yy_scan_string(
            "int main() {"
            "  foreach (id : expression, another_expression) {}"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxWhile, AcceptsWhile) {
    yy_scan_string(
            "int main() {"
            "  while (expression) do {}"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxDoWhile, AcceptsDoWhile) {
    yy_scan_string(
            "int main() {"
            "  do {} while (expression);"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxSwitch, AcceptsSwitch) {
    yy_scan_string(
            "int main() {"
            "  switch (expression) {}"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxOperand, AcceptsId) {
    yy_scan_string(
            "int main() {"
            "  local_var = id;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxOperand, AcceptsLiteralInt) {
    yy_scan_string(
            "int main() {"
            "  local_var = 12;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxOperand, AcceptsLiteralFloat) {
    yy_scan_string(
            "int main() {"
            "  local_var = 12.23e-10;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxOperand, AcceptsFalse) {
    yy_scan_string(
            "int main() {"
            "  local_var = false;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxOperand, AcceptsTrue) {
    yy_scan_string(
            "int main() {"
            "  local_var = true;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxOperand, AcceptsLiteralChar) {
    yy_scan_string(
            "int main() {"
            "  local_var = 'a';"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxOperand, AcceptsLiteralString) {
    yy_scan_string(
            "int main() {"
            "  local_var = \"a string\";"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxOperand, AcceptsFunctionCall) {
    yy_scan_string(
            "int main() {"
            "  local_var = f();"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxOperand, AcceptsPipeFunctionCall) {
    yy_scan_string(
            "int main() {"
            "  local_var = f() \%>\% g(.) %|% h(., z);"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxUnaryOperator, AcceptsMinusOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = -expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxUnaryOperator, AcceptsNegationOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = !expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxUnaryOperator, AcceptsPointerOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = *expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxUnaryOperator, AcceptsAddressOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = &expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxBinaryOperator, AcceptsSumOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression + expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxBinaryOperator, AcceptsSubtractionOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression - expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxBinaryOperator, AcceptsMultiplicationOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression * expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxBinaryOperator, AcceptsDivisionOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression / expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxBinaryOperator, AcceptsModulusOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression \% expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxBinaryOperator, AcceptsExponentiationOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression ^ expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxBinaryOperator, AcceptsBitwiseOrOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression | expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxBinaryOperator, AcceptsBitwiseAndOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression & expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxBinaryOperator, AcceptsLessThanOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression < expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxBinaryOperator, AcceptsGreaterThanOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression > expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxBinaryOperator, AcceptsEqualOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression == expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxBinaryOperator, AcceptsNotEqualOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression != expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxBinaryOperator, AcceptsGreaterOrEqualThanOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression >= expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxBinaryOperator, AcceptsLessOrEqualThanOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression <= expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxBinaryOperator, AcceptsAndOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression && expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}

TEST(SyntaxBinaryOperator, AcceptsOrOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression || expression;"
            "}");
    EXPECT_EQ(0, yyparse());
}
