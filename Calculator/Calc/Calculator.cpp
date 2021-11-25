#include "Calculator.h"

std::map<std::string, Variable>  VariableManager::variableMap = {};

VariableManager& VariableManager::GetInstance(void) {
  static VariableManager self;
  return self;
};

bool VariableManager::CheckVariable(const std::string& name) const {
  return variableMap.find(name) != variableMap.end();
}

void VariableManager::AddVariable(Variable var) {
  std::string name = var.GetName();
  if (!Variable::IsValidValueName(name) || OperationsDescription::GetInstance().CheckOperation(name))
    throw std::exception(("Invalid variable name " + name).c_str());
  variableMap.insert_or_assign(name, var);
}

Variable VariableManager::FindVariable(const std::string& name) const {
  auto result = variableMap.find(name);
  if (result == variableMap.end())
    throw std::exception("Unknown variable name");
  return result->second;
}

/**
* @brief operand stack type
*/
using OperandStack = std::stack<std::shared_ptr<Operand>>;

/**
* @brief operation stack type
*/
using OperationStack = std::stack<std::shared_ptr<Operation>>;

/**
* @brief function of resolving the token "bracket" and performing the necessary actions
* @param[in/out] operandStack - stack of operands
* @param[in/out] operationStack - stack of operations
* @param[in] operation - bracket's token
* @param[in] prevElementType - the type of the previous element
* @return resolved type
*/
ElementType ProcessBracket(OperandStack& operandStack, OperationStack& operationStack, const Token& operation, ElementType prevElementType) {
  auto& operations = OperationsDescription::GetInstance();
  if (operation.GetName() == std::string{ SIMBOL_BEFORE_ARGS } && prevElementType == ElementType::FUNCTION) {
    return ElementType::SIMBOL_BEFORE_ARGS;
  }
  std::string pare;   //pare bracket
  if (operations.CheckBracket(operation.GetName())){
    auto bracket = operations.GetBracket(operation.GetName());
    if (bracket->GetType() == ElementType::OPEN_BRACKET) {
      operationStack.push(bracket);
      return ElementType::OPEN_BRACKET;
    }
    pare = dynamic_cast<CloseBracket*>(bracket.get())->GetPare();
  }
  while (!operationStack.empty()) {
    if (operation.GetName() == std::string{ SIMBOL_AFTER_ARGS } && operationStack.top()->GetType() == ElementType::FUNCTION) {
      operationStack.top()->DoOperation(operandStack);
      operationStack.pop();
      return ElementType::SIMBOL_AFTER_ARGS;
    }
    else if (operationStack.top()->GetType() == ElementType::OPEN_BRACKET && operationStack.top()->GetTokenName() == pare) {
      operationStack.top()->DoOperation(operandStack);
      operationStack.pop();
      return ElementType::CLOSE_BRACKET;
    }
    else if (operationStack.top()->GetType() == ElementType::OPEN_BRACKET && operationStack.top()->GetTokenName() != pare ||
      operationStack.top()->GetType() == ElementType::FUNCTION)
      throw std::exception(("Unexpected bracket " + operationStack.top()->GetTokenName()).c_str());
    else {
      operationStack.top()->DoOperation(operandStack);
      operationStack.pop();
    }
  }
  throw std::exception(("Unexpected bracket " + operation.GetName()).c_str());
}

/**
* @brief function of checking the possible resolving of the operator as a prefix
* @param[in] prevElementType - the type of the previous element
* @return true if possible, false otherwise
*/
bool IsPreficsPossible(ElementType prevElementType) {
  return prevElementType == ElementType::BINARY || prevElementType == ElementType::DELIMETR_ARGS ||
         prevElementType == ElementType::OPEN_BRACKET || prevElementType == ElementType::PREFICS ||
         prevElementType == ElementType::SIMBOL_AFTER_ARGS;
}

/**
* @brief function of checking the possible resolving of the operator as a binary
* @param[in] prevElementType - the type of the previous element
* @return true if possible, false otherwise
*/
bool IsBinaryPossible(ElementType prevElementType) {
  return prevElementType == ElementType::CLOSE_BRACKET || prevElementType == ElementType::LITERAL ||
         prevElementType == ElementType::POSTFICS || prevElementType == ElementType::SIMBOL_AFTER_ARGS ||
         prevElementType == ElementType::VARIABLE;
}

/**
* @brief function of checking the possible resolving of the operator as a postfix
* @param[in] prevElementType - the type of the previous element
* @return true if possible, false otherwise
*/
bool IsPostficsPossible(ElementType prevElementType) {
  return prevElementType == ElementType::CLOSE_BRACKET || prevElementType == ElementType::LITERAL ||
         prevElementType == ElementType::POSTFICS || prevElementType == ElementType::SIMBOL_AFTER_ARGS ||
         prevElementType == ElementType::VARIABLE;
}

/**
* @brief function to check if an operation is to be popped off the stack
* @param[in] binaryOperator - the binary operator that is next to the top of the stack
* @param[in] other - operation need to be pushed out to be checked
* @return true if pop is necessary, false otherwise
*/
bool IsOperationPoped(const BinaryOperator& binaryOperator, std::shared_ptr<Operation> other) {
  if (other->GetType() == ElementType::PREFICS)
    return dynamic_cast<PreficsOperator*>(other.get())->GetPriority() > binaryOperator.GetPriority();
  else if (other->GetType() == ElementType::BINARY)
    if (dynamic_cast<BinaryOperator*>(other.get())->GetAssociative() == BinaryOperator::Associative::RIGHT)
      return dynamic_cast<BinaryOperator*>(other.get())->GetPriority() > binaryOperator.GetPriority();
    else
      return dynamic_cast<BinaryOperator*>(other.get())->GetPriority() == binaryOperator.GetPriority() || 
             dynamic_cast<BinaryOperator*>(other.get())->GetPriority() > binaryOperator.GetPriority();
  return false;
}

/**
* @brief function of resolving the token "operator" and performing the necessary actions
* @param[in/out] operandStack - stack of operands
* @param[in/out] operationStack - stack of operations
* @param[in] operation - operator's token
* @param[in] prevElementType - the type of the previous element
* @return resolved type
*/
ElementType ProcessOperator(OperandStack& operandStack, OperationStack& operationStack, const Token& operation, ElementType prevElementType) {
  auto& operations = OperationsDescription::GetInstance();
  std::shared_ptr<Operation> finalOperator = nullptr;
  if (IsPreficsPossible(prevElementType)) {
    finalOperator = operations.GetOperator(operation.GetName(), ElementType::PREFICS);
    if (finalOperator != nullptr) {
      operationStack.push(finalOperator);
      return ElementType::PREFICS;
    }
  }
  if (finalOperator.get() == nullptr && IsBinaryPossible(prevElementType)) {
    finalOperator = operations.GetOperator(operation.GetName(), ElementType::BINARY);
    if (finalOperator != nullptr) {
      while (!operationStack.empty() && IsOperationPoped(*dynamic_cast<BinaryOperator*>(finalOperator.get()), operationStack.top())) {
        operationStack.top()->DoOperation(operandStack);
        operationStack.pop();
      }
      operationStack.push(finalOperator);
      return ElementType::BINARY;
    }
  }
  if (finalOperator.get() == nullptr && IsPostficsPossible(prevElementType)) {
    finalOperator = operations.GetOperator(operation.GetName(), ElementType::POSTFICS);
    if (finalOperator != nullptr) {
      finalOperator->DoOperation(operandStack);
      return ElementType::POSTFICS;
    }
  }
}

/**
* @brief token handling function "variable"
* @param[in/out] operandStack - stack of operands for adding a variable
* @param[in] localVariable - local variable store
* @param[in] var - token
* @return shared pointer to variable
*/
std::shared_ptr<Variable> ProcessVariable(OperandStack& operandStack, std::map<std::string, std::shared_ptr<Variable>>& localVariable, const Token& var) {
  std::shared_ptr<Variable> variable;
  if (localVariable.find(var.GetName()) != localVariable.end())
    variable = std::make_shared<Variable>(*localVariable.find(var.GetName())->second);
  else if (VariableManager::GetInstance().CheckVariable(var.GetName())) {
    variable = std::make_shared<Variable>(VariableManager::GetInstance().FindVariable(var.GetName()));
  }
  else
    variable = std::make_shared<Variable>(Variable(var.GetName()));
  operandStack.push(variable);
  return variable;
}

double Calculate(const std::string& expression) {
  std::stack<std::shared_ptr<Operand>> operandStack;
  std::stack<std::shared_ptr<Operation>> operationStack;
  OperationsDescription& operations = OperationsDescription::GetInstance();

  ElementType prevElementType = ElementType::BINARY;

  std::vector<Token> separatedExpression = Separate(expression);

  std::map<std::string, std::shared_ptr<Variable>> localVariable;

  for (size_t i = 0; i < separatedExpression.size(); ++i) {
    switch (separatedExpression[i].GetType()) {
    case Token::Type::DELIMETR_ARGS:
      while (!operationStack.empty() && operationStack.top()->GetType() != ElementType::FUNCTION) {
        operationStack.top()->DoOperation(operandStack);
        operationStack.pop();
      }
      if (operationStack.top()->GetType() != ElementType::FUNCTION)
        throw std::exception("Unexpected " + DELIMETR_ARGS);
      prevElementType = ElementType::DELIMETR_ARGS;
      break;
    case Token::Type::LITERAL:
      operandStack.push(std::make_shared<Literal>(std::stod(separatedExpression[i].GetName())));
      prevElementType = ElementType::LITERAL;
      break;
    case Token::Type::FUNCTION:
      if (i + 1 >= separatedExpression.size() || separatedExpression[i + 1].GetName() != std::string{ SIMBOL_BEFORE_ARGS })
        throw std::exception{ "Function call expected" };
      operationStack.push(operations.GetFunction(separatedExpression[i].GetName()));
      prevElementType = ElementType::FUNCTION;
      break;
    case Token::Type::BRACKET:
      prevElementType = ProcessBracket(operandStack, operationStack, separatedExpression[i], prevElementType);
      break;
    case Token::Type::OPERATOR:
      prevElementType = ProcessOperator(operandStack, operationStack, separatedExpression[i], prevElementType);
      break;
    case Token::Type::VARIABLE:
      auto var = ProcessVariable(operandStack, localVariable, separatedExpression[i]);
      localVariable.insert_or_assign(var->GetName(), var);
      prevElementType = ElementType::VARIABLE;
      break;
    }
  }

  while (!operationStack.empty()) {
    if (operationStack.top()->GetType() == ElementType::OPEN_BRACKET)
      throw std::exception(("Unexpected bracket" + operationStack.top()->GetTokenName()).c_str());
    if (operationStack.top()->GetType() == ElementType::FUNCTION)
      throw std::exception(("Expected " + std::string{SIMBOL_AFTER_ARGS}).c_str());
    operationStack.top()->DoOperation(operandStack);
    operationStack.pop();
  }

  if (operandStack.size() != 1 || operationStack.size() != 0)
    throw std::exception("Error expression");

  for (auto& var : localVariable)
    VariableManager::GetInstance().AddVariable(*var.second);
  return operandStack.top()->GetValue();
}