#include "BaseOperation.h"

/**
* @brief addition function
* @param[in] a - first term
* @param[in] b - second term
* @return the result of the addition in the literal container
*/
std::shared_ptr<Literal> Add(std::shared_ptr<Operand> a, std::shared_ptr<Operand> b) {
  return std::make_shared<Literal>(a->GetValue() + b->GetValue());
}

/**
* @brief subtraction function
* @param[in] a - minuend
* @param[in] b - subtrahend
* @return the result of the subtraction in the literal container
*/
std::shared_ptr<Literal> Sub(std::shared_ptr<Operand> a, std::shared_ptr<Operand> b) {
  return std::make_shared<Literal>(a->GetValue() - b->GetValue());
}

/**
* @brief multiplication function
* @param[in] a - first factor
* @param[in] b - second factor
* @return the result of the multiplication in the literal container
*/
std::shared_ptr<Literal> Mul(std::shared_ptr<Operand> a, std::shared_ptr<Operand> b) {
  return std::make_shared<Literal>(a->GetValue() * b->GetValue());
}

/**
* @brief division function
* @param[in] a - dividend
* @param[in] b - divider
* @return the result of the division in the literal container
*/
std::shared_ptr<Literal> Div(std::shared_ptr<Operand> a, std::shared_ptr<Operand> b) {
  return std::make_shared<Literal>(a->GetValue() / b->GetValue());
}

/**
* @brief value assignment function
* @param[in] a - variable for setting value
* @param[in] b - operand for getting value
* @return the result in the literal container
*/
std::shared_ptr<Literal> Assign(std::shared_ptr<Operand> a, std::shared_ptr<Operand> b) {
  if (a->GetType() != ElementType::VARIABLE)
    throw std::exception("Impossible to assign a value to a non-variable");
  std::shared_ptr<Variable> var = std::dynamic_pointer_cast<Variable>(a);
  var->SetValue(b->GetValue());
  return std::make_shared<Literal>(var->GetValue());
}

/**
* @brief unary minus function
* @param[in] a - variable for sign change
* @return the result of operation in the literal container
*/
std::shared_ptr<Literal> UnaryMinus(std::shared_ptr<Operand> a) {
  return std::make_shared<Literal>(-(a->GetValue()));
}

/**
* @brief prefics increment function for variable
* @param[in] a - variable
* @return new value of variable in the literal container
*/
std::shared_ptr<Literal> PrefixIncrement(std::shared_ptr<Operand> a) {
  if (a->GetType() != ElementType::VARIABLE)
    throw std::exception("Cannot apply increment to constant");
  std::shared_ptr<Variable> var = std::dynamic_pointer_cast<Variable>(a);
  var->SetValue(a->GetValue() + 1);
  return std::make_shared<Literal>(var->GetValue());
}

/**
* @brief prefics decrement function for variable
* @param[in] a - variable
* @return new value of variable in the literal container
*/
std::shared_ptr<Literal> PrefixDecrement(std::shared_ptr<Operand> a) {
  if (a->GetType() != ElementType::VARIABLE)
    throw std::exception("Cannot apply increment to constant");
  std::shared_ptr<Variable> var = std::dynamic_pointer_cast<Variable>(a);
  var->SetValue(a->GetValue() - 1);
  return std::make_shared<Literal>(var->GetValue());
}

/**
* @brief postfics increment function for variable
* @param[in] a - variable
* @return value of variable before operation in the literal container
*/
std::shared_ptr<Literal> PostfixIncrement(std::shared_ptr<Operand> a) {
  if (a->GetType() != ElementType::VARIABLE)
    throw std::exception("Cannot apply increment to constant");
  double result = a->GetValue();
  std::shared_ptr<Variable> var = std::dynamic_pointer_cast<Variable>(a);
  var->SetValue(a->GetValue() + 1);
  return std::make_shared<Literal>(result);
}

/**
* @brief postfics decrement function for variable
* @param[in] a - variable
* @return value of variable before operation in the literal container
*/
std::shared_ptr<Literal> PostfixDecrement(std::shared_ptr<Operand> a) {
  if (a->GetType() != ElementType::VARIABLE)
    throw std::exception("Cannot apply increment to constant");
  double result = a->GetValue();
  std::shared_ptr<Variable> var = std::dynamic_pointer_cast<Variable>(a);
  var->SetValue(a->GetValue() - 1);
  return std::make_shared<Literal>(result);
}

/**
* @brief function of maximum for 2 argumets
* @param[in] args - vector of operand
* @return maximum of two argument
*/
std::shared_ptr<Literal> Max(std::vector<std::shared_ptr<Operand>> args) {
  return std::make_shared<Literal>(args[0]->GetValue() > args[1]->GetValue() ? args[0]->GetValue() : args[1]->GetValue());
}

void LoadBase(OperationsDescription& dstr) {
  const BinaryOperator add = { "+", 1, Add };
  const BinaryOperator sub = { "-", 1, Sub };
  const BinaryOperator mul = { "*", 2, Mul };
  const BinaryOperator div = { "/", 2, Div };
  const BinaryOperator assign = { "=", 0, Assign };
  const PreficsOperator unaryMinus = { "-", 3, UnaryMinus };
  const PreficsOperator prefixIncrement = { "++", 5, PrefixIncrement };
  const PreficsOperator prefixDecrement = { "--", 5, PrefixDecrement };
  const PostficsOperator postfixIncrement = { "++", PostfixIncrement };
  const PostficsOperator postfixDecrement = { "--", PostfixDecrement };
  const OpenBracket openBracket = { "(", nullptr };
  const CloseBracket closeBracket = { ")", "(" };
  const Function max = { "max", 2, Max };

  dstr.LoadOperation(std::make_shared<BinaryOperator>(add));
  dstr.LoadOperation(std::make_shared<BinaryOperator>(sub));
  dstr.LoadOperation(std::make_shared<BinaryOperator>(mul));
  dstr.LoadOperation(std::make_shared<BinaryOperator>(div));
  dstr.LoadOperation(std::make_shared<BinaryOperator>(assign));
  dstr.LoadOperation(std::make_shared<PreficsOperator>(unaryMinus));
  dstr.LoadOperation(std::make_shared<PreficsOperator>(prefixIncrement));
  dstr.LoadOperation(std::make_shared<PreficsOperator>(prefixDecrement));
  dstr.LoadOperation(std::make_shared<PostficsOperator>(postfixIncrement));
  dstr.LoadOperation(std::make_shared<PostficsOperator>(postfixDecrement));
  dstr.LoadOperation(std::make_shared<OpenBracket>(openBracket));
  dstr.LoadOperation(std::make_shared<CloseBracket>(closeBracket));
  dstr.LoadOperation(std::make_shared<Function>(max));
}