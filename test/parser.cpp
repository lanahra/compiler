#include <gtest/gtest.h>

extern "C" {
#include "../include/lex.yy.h"
#include "../include/parser.tab.h"
}

TEST(SyntaxEmptyProgram, AcceptsEmptyProgram) {
    yy_scan_string("//this is an empty program");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxGlobalVariable, AcceptsVarDeclaration) {
    yy_scan_string("var int;");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxGlobalVariable, AcceptsVarDeclarationStatic) {
    yy_scan_string("var static bool;");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxGlobalVariable, AcceptsVarDeclarationArray) {
    yy_scan_string("var[12] char;");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxGlobalVariable, AcceptsVarDeclarationStaticArray) {
    yy_scan_string("var[12] static float;");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxGlobalVariable, AcceptsVarDeclarationUserType) {
    yy_scan_string("var new_type;");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxClassDefinition, AcceptsClassDefinition) {
    yy_scan_string(
            "class new_class"
            "  [ string new_field"
            "  ];");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxClassDefinition, DoesNotAcceptNoFields) {
    yy_scan_string("class new_class []");
    EXPECT_NE(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxClassDefinition, AcceptsPrivateModifier) {
    yy_scan_string(
            "class new_class"
            "  [ private string new_field"
            "  ];");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxClassDefinition, AcceptsPublicModifier) {
    yy_scan_string(
            "class new_class"
            "  [ public string new_field"
            "  ];");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxClassDefinition, AcceptsProtectedModifier) {
    yy_scan_string(
            "class new_class"
            "  [ protected string new_field"
            "  ];");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxClassDefinition, AcceptsMultipleFields) {
    yy_scan_string(
            "class new_class"
            "  [ protected string new_field"
            "  : private float another_field"
            "  : int another_one"
            "  ];");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxFunctionHeader, AcceptsFunctionHeaderNoParameters) {
    yy_scan_string("int new_function() {}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxFunctionHeader, AcceptsFunctionHeaderOneParameter) {
    yy_scan_string("float new_function(string new_parameter) {}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
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
    yylex_destroy();
}

TEST(SyntaxFunctionHeader, AcceptsFunctionHeaderStaticModifier) {
    yy_scan_string("static float new_function(string new_parameter) {}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxFunctionHeader, AcceptsFunctionHeaderUserType) {
    yy_scan_string("new_type new_function(other_type new_parameter) {}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxFunctionHeader, AcceptsFunctionBodyMultipleCommands) {
    yy_scan_string(
            "int main() {"
            "  int local_var;"
            "  float another_local_var;"
            "  char yet_another_local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxLocalVariable, AcceptsVarDeclaration) {
    yy_scan_string(
            "int main() {"
            "  int local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxLocalVariable, AcceptsStaticVarDeclaration) {
    yy_scan_string(
            "int main() {"
            "  static float local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxLocalVariable, AcceptsConstVarDeclaration) {
    yy_scan_string(
            "int main() {"
            "  const char local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxLocalVariable, AcceptsStaticConstVarDeclaration) {
    yy_scan_string(
            "int main() {"
            "  static const bool local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxLocalVariable, AcceptsVarInitialization) {
    yy_scan_string(
            "int main() {"
            "  bool local_var <= true;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxLocalVariable, AcceptsVarUserTypeDeclaration) {
    yy_scan_string(
            "int main() {"
            "  new_type local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxLocalVariable, DoesNotAcceptUserTypeVarInitialization) {
    yy_scan_string(
            "int main() {"
            "  new_type local_var <= 12;"
            "}");
    EXPECT_NE(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxVariableAttribution, AcceptsVarAttribution) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxVariableAttribution, AcceptsVarArrayAttribution) {
    yy_scan_string(
            "int main() {"
            "  local_var[expression] = expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxVariableAttribution, AcceptsVarUserTypeAttribution) {
    yy_scan_string(
            "int main() {"
            "  local_var$field = expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxVariableAttribution, AcceptsVarUserTypeArrayAttribution) {
    yy_scan_string(
            "int main() {"
            "  local_var[expression]$field = expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxShiftOp, AcceptsLeftShiftOp) {
    yy_scan_string(
            "int main() {"
            "  local_var << expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxShiftOp, AcceptsLeftShiftOpArray) {
    yy_scan_string(
            "int main() {"
            "  local_var[expression] << expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxShiftOp, AcceptsLeftShiftOpUserType) {
    yy_scan_string(
            "int main() {"
            "  local_var$field << expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxShiftOp, AcceptsLeftShiftOpArrayUserType) {
    yy_scan_string(
            "int main() {"
            "  local_var[expression]$field << expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxShiftOp, AcceptsRightShiftOp) {
    yy_scan_string(
            "int main() {"
            "  local_var >> expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxShiftOp, AcceptsRightShiftOpArray) {
    yy_scan_string(
            "int main() {"
            "  local_var[expression] >> expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxShiftOp, AcceptsRightShiftOpUserType) {
    yy_scan_string(
            "int main() {"
            "  local_var$field >> expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxShiftOp, AcceptsRightShiftOpArrayUserType) {
    yy_scan_string(
            "int main() {"
            "  local_var[expression]$field >> expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxReturn, AcceptsReturnStatement) {
    yy_scan_string(
            "int main() {"
            "  return local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxContinue, AcceptsContinueStatement) {
    yy_scan_string(
            "int main() {"
            "  continue;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxBreak, AcceptsBreakStatement) {
    yy_scan_string(
            "int main() {"
            "  break;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxCase, AcceptsCaseStatement) {
    yy_scan_string(
            "int main() {"
            "  case 0:"
            "  case 1:"
            "  case 2:"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxConditionalStatement, AcceptsIfThenStatement) {
    yy_scan_string(
            "int main() {"
            "  if (expressions) then {};"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxConditionalStatement, AcceptsIfThenElseStatement) {
    yy_scan_string(
            "int main() {"
            "  if (expressions) then {} else {};"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxInput, AcceptsInput) {
    yy_scan_string(
            "int main() {"
            "  input local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxOutput, AcceptsOutput) {
    yy_scan_string(
            "int main() {"
            "  output local_var;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxOutput, AcceptsOutputMultipleExpressions) {
    yy_scan_string(
            "int main() {"
            "  output local_var, another_one, yet_another;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxFunctionCall, AcceptsFunctionCall) {
    yy_scan_string(
            "int main() {"
            "  f();"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxFunctionCall, AcceptsFunctionCallDotArgument) {
    yy_scan_string(
            "int main() {"
            "  f(.);"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxFunctionCall, AcceptsFunctionCallArgument) {
    yy_scan_string(
            "int main() {"
            "  f(expression);"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxFunctionCall, AcceptsFunctionCallMultipleArguments) {
    yy_scan_string(
            "int main() {"
            "  f(expression, ., another_expression);"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxFunctionCall, AcceptsFunctionForwardPipe) {
    yy_scan_string(
            "int main() {"
            "  f(expression) \%>\% g(.);"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxFunctionCall, AcceptsFunctionBashPipe) {
    yy_scan_string(
            "int main() {"
            "  f(expression) \%|\% g(.);"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxFunctionCall, AcceptsFunctionMultiplePipes) {
    yy_scan_string(
            "int main() {"
            "  f(x) \%>\% g(.) \%|\% h(., z);"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxForeach, AcceptsForeach) {
    yy_scan_string(
            "int main() {"
            "  foreach (id : expression, another_expression) {};"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxFor, AcceptsFor) {
    yy_scan_string(
            "int main() {"
            "  for (i = 0, j = 0 : expression : i = i + 1, j = j + 1) {};"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxWhile, AcceptsWhile) {
    yy_scan_string(
            "int main() {"
            "  while (expression) do {};"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxDoWhile, AcceptsDoWhile) {
    yy_scan_string(
            "int main() {"
            "  do {} while (expression);"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxSwitch, AcceptsSwitch) {
    yy_scan_string(
            "int main() {"
            "  switch (expression) {};"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxCommandBlock, AcceptsCommandBlock) {
    yy_scan_string(
            "int main() {"
            "  {};"
            "  {{};};"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxOperand, AcceptsId) {
    yy_scan_string(
            "int main() {"
            "  local_var = id;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxOperand, AcceptsIdArray) {
    yy_scan_string(
            "int main() {"
            "  local_var = id[expression];"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxOperand, AcceptsIdUserType) {
    yy_scan_string(
            "int main() {"
            "  local_var = id$field;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxOperand, AcceptsIdUserTypeArray) {
    yy_scan_string(
            "int main() {"
            "  local_var = id[expression]$field;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxOperand, AcceptsLiteralInt) {
    yy_scan_string(
            "int main() {"
            "  local_var = 12;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxOperand, AcceptsLiteralFloat) {
    yy_scan_string(
            "int main() {"
            "  local_var = 12.23e-10;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxOperand, AcceptsFalse) {
    yy_scan_string(
            "int main() {"
            "  local_var = false;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxOperand, AcceptsTrue) {
    yy_scan_string(
            "int main() {"
            "  local_var = true;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxOperand, AcceptsLiteralChar) {
    yy_scan_string(
            "int main() {"
            "  local_var = 'a';"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxOperand, AcceptsLiteralString) {
    yy_scan_string(
            "int main() {"
            "  local_var = \"a string\";"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxOperand, AcceptsFunctionCall) {
    yy_scan_string(
            "int main() {"
            "  local_var = f();"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxOperand, AcceptsPipeFunctionCall) {
    yy_scan_string(
            "int main() {"
            "  local_var = f() \%>\% g(.) \%|\% h(., z);"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxUnaryOperator, AcceptsMinusOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = -expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxUnaryOperator, AcceptsNegationOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = !expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxUnaryOperator, AcceptsPointerOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = *expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxUnaryOperator, AcceptsAddressOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = &expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxUnaryOperator, AcceptsEvalOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = ?expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxUnaryOperator, AcceptsHashOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = #expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxBinaryOperator, AcceptsSumOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression + expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxBinaryOperator, AcceptsSubtractionOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression - expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxBinaryOperator, AcceptsMultiplicationOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression * expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxBinaryOperator, AcceptsDivisionOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression / expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxBinaryOperator, AcceptsModulusOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression \% expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxBinaryOperator, AcceptsExponentiationOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression ^ expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxBinaryOperator, AcceptsBitwiseOrOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression | expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxBinaryOperator, AcceptsBitwiseAndOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression & expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxBinaryOperator, AcceptsLessThanOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression < expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxBinaryOperator, AcceptsGreaterThanOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression > expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxBinaryOperator, AcceptsEqualOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression == expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxBinaryOperator, AcceptsNotEqualOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression != expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxBinaryOperator, AcceptsGreaterOrEqualThanOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression >= expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxBinaryOperator, AcceptsLessOrEqualThanOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression <= expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxBinaryOperator, AcceptsAndOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression && expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxBinaryOperator, AcceptsOrOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression || expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxTernaryOperator, AcceptsTernaryOperator) {
    yy_scan_string(
            "int main() {"
            "  local_var = expression ? expression : expression;"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxExpression, AcceptsSingleExpression) {
    yy_scan_string(
            "int main() {"
            "  local_var = (expression);"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}

TEST(SyntaxExpression, AcceptsCompoundExpression) {
    yy_scan_string(
            "int main() {"
            "  local_var = (expression + -(expression));"
            "}");
    EXPECT_EQ(0, yyparse());
    yylex_destroy();
}
