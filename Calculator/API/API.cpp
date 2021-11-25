#include "API.h"

OperationsDescription& OperationsDescription::GetInstance(void) {
  static OperationsDescription self;
  return self;
}

bool OperationsDescription::IsBeginigFunctionName(const char symbol) {
  return isalpha(symbol) && symbol != DELIMETR_ARGS && symbol != SIMBOL_BEFORE_ARGS && symbol != SIMBOL_AFTER_ARGS;
}

bool OperationsDescription::IsBeginingOperatorName(const char symbol) {
  return (isalpha(symbol) || ispunct(symbol)) && symbol != DELIMETR_ARGS && symbol != SIMBOL_BEFORE_ARGS && symbol != SIMBOL_AFTER_ARGS;
}

bool OperationsDescription::IsBeginingBracketName(const char symbol) {
  return (isalpha(symbol) || ispunct(symbol)) && symbol != DELIMETR_ARGS;
}

bool OperationsDescription::IsValidFunctionName(const std::string& name) {
  if (!IsBeginigFunctionName(name[0]))
    return false;
  for (int i = 1; i < name.size(); i++)
    if (!isalnum(name[i]) || name[i] == DELIMETR_ARGS || name[i] == SIMBOL_BEFORE_ARGS || name[i] == SIMBOL_AFTER_ARGS)
      return false;
  return true;
}

bool OperationsDescription::IsValidOperatorName(const std::string& name) {
  if (!IsBeginingOperatorName(name[0]))
    return false;
  for (int i = 1; i < name.size(); i++)
    if (!(isalnum(name[i]) || ispunct(name[i])) || name[i] == DELIMETR_ARGS || name[i] == SIMBOL_BEFORE_ARGS || name[i] == SIMBOL_AFTER_ARGS)
      return false;
  return true;
}

bool OperationsDescription::IsValidBracketName(const std::string& name) {
  if (!IsBeginingBracketName(name[0]))
    return false;
  for (int i = 1; i < name.size(); i++)
    if (!(isalnum(name[i]) || ispunct(name[i])) || name[i] == DELIMETR_ARGS)
      return false;
  return true;
}

bool OperationsDescription::CheckOperation(const std::string& name) const {
  if (!IsValidBracketName(name) && !IsValidFunctionName(name) && !IsValidOperatorName(name))
    return false;
  return functions.find(name) != functions.end() || operators.find(name) != operators.end() || brackets.find(name) != brackets.end();
}

bool OperationsDescription::CheckFunction(const std::string& operation) const {
  if (!IsValidFunctionName(operation))
    return false;
  return functions.find(operation) != functions.end();
}

bool OperationsDescription::CheckOperator(const std::string& operation) const {
  if (!IsValidOperatorName(operation))
    return false;
  return operators.find(operation) != operators.end();
};

bool OperationsDescription::CheckBracket(const std::string& operation) const {
  if (!IsValidBracketName(operation))
    return false;
  return brackets.find(operation) != brackets.end();
};

std::shared_ptr<Operation>  OperationsDescription::GetFunction(const std::string& operation) const {
  return functions.find(operation)->second;
};

std::shared_ptr<Operation>  OperationsDescription::GetBracket(const std::string& operation) const {
  return brackets.find(operation)->second;
};

std::shared_ptr<Operation>  OperationsDescription::GetOperator(const std::string& operation, ElementType type) const {
  auto result = operators.find(operation);
  for (result; result != operators.end() && result->first == operation; result++) {
    if (result->second->GetType() == type)
      return result->second;
  }
  return nullptr;
}

void OperationsDescription::AddFunction(std::shared_ptr<Operation> operation) {
  if (functions.find(operation->GetTokenName()) != functions.end() ||
      operators.find(operation->GetTokenName()) != operators.end() ||
      brackets.find(operation->GetTokenName()) != brackets.end())
    throw std::exception(("Trying to override a function or operator " + operation->GetTokenName()).c_str());

  if (!IsValidFunctionName(operation->GetTokenName()))
    throw std::exception(("\"" + operation->GetTokenName() + "\"" + " - invalid name for function").c_str());

  functions.insert(std::pair(operation->GetTokenName(), operation));
}

void OperationsDescription::AddOperator(std::shared_ptr<Operation> operation) {
  if (brackets.find(operation->GetTokenName()) != brackets.end() ||
      functions.find(operation->GetTokenName()) != functions.end())
    throw std::exception(("Unable to add operator " + operation->GetTokenName()).c_str());
  if (operation->GetType() == ElementType::PREFICS &&
      this->GetOperator(operation->GetTokenName(), ElementType::PREFICS) != nullptr)
    throw std::exception(("Unable to add operator " + operation->GetTokenName()).c_str());
  if ((operation->GetType() == ElementType::BINARY || operation->GetType() == ElementType::POSTFICS) &&
      (this->GetOperator(operation->GetTokenName(), ElementType::BINARY) != nullptr || this->GetOperator(operation->GetTokenName(), ElementType::POSTFICS) != nullptr))
    throw std::exception(("Unable to add operator " + operation->GetTokenName()).c_str());
  if (!IsValidOperatorName(operation->GetTokenName()))
    throw std::exception((operation->GetTokenName() + " - invalid name for operator").c_str());
  operators.insert(std::pair(operation->GetTokenName(), operation));
}

void OperationsDescription::AddBracket(std::shared_ptr<Operation> operation) {
  if (functions.find(operation->GetTokenName()) != functions.end() ||
      operators.find(operation->GetTokenName()) != operators.end() ||
      brackets.find(operation->GetTokenName()) != brackets.end())
    throw std::exception(("Unable to add bracket " + operation->GetTokenName()).c_str());
  if(!IsValidBracketName(operation->GetTokenName()))
    throw std::exception((operation->GetTokenName() + " - invalid name for bracket").c_str());
  brackets.insert(std::pair(operation->GetTokenName(), operation));
}

void OperationsDescription::LoadOperation(std::shared_ptr<Operation> operation) {
  if (operation->GetType() == ElementType::FUNCTION)
    AddFunction(operation);
  else if (operation->GetType() == ElementType::BINARY || operation->GetType() == ElementType::PREFICS || operation->GetType() == ElementType::POSTFICS)
    AddOperator(operation);
  else if (operation->GetType() == ElementType::OPEN_BRACKET || operation->GetType() == ElementType::CLOSE_BRACKET)
    AddBracket(operation);
}

void OperationsDescription::Clear(void) {
  functions.clear();
  operators.clear();
  brackets.clear();
}

BinaryOperator::Associative BinaryOperator::GetAssociative(void) const {
  return assotiative;
}

ElementType BinaryOperator::GetType(void) const {
  return ElementType::BINARY;
};

std::string BinaryOperator::GetTokenName(void) const {
  return name;
}

void BinaryOperator::DoOperation(DataStack& dataStack) const {
  if (dataStack.size() < 2)
    throw std::exception("Unexpected number of arguments");
  else {
    std::shared_ptr<Operand> b = dataStack.top();
    dataStack.pop();
    std::shared_ptr<Operand> a = dataStack.top();
    dataStack.pop();
    dataStack.push(doOperation(a, b));
  }
}



int PreficsOperator::GetPriority(void) const {
  return prioryty;
};

ElementType PreficsOperator::GetType(void) const {
  return ElementType::PREFICS;
};

std::string PreficsOperator::GetTokenName(void) const {
  return name;
}

void PreficsOperator::DoOperation(DataStack& dataStack) const{
  if (dataStack.size() < 1)
    throw std::exception("Unexpected number of arguments");
  else {
    std::shared_ptr<Operand> a = dataStack.top();
    dataStack.pop();
    dataStack.push(doOperation(a));
  }
};



ElementType PostficsOperator::GetType(void) const {
  return ElementType::POSTFICS;
};

std::string PostficsOperator::GetTokenName(void) const {
  return name;
}

void PostficsOperator::DoOperation(DataStack& dataStack) const {
  if (dataStack.size() < 1)
    throw std::exception("Unexpected number of arguments");
  else {
    std::shared_ptr<Operand> a = dataStack.top();
    dataStack.pop();
    dataStack.push(doOperation(a));
  }
};



ElementType OpenBracket::GetType(void) const {
  return ElementType::OPEN_BRACKET;
};

std::string OpenBracket::GetTokenName(void) const {
  return name;
};

void OpenBracket::DoOperation(DataStack& dataStack) const {
  if (dataStack.size() < 1)
    throw std::exception("Unexpected number of arguments");
  else if (doOperation != nullptr) {
    std::shared_ptr<Operand> a = dataStack.top();
    dataStack.pop();
    dataStack.push(doOperation(a));
  }
};



std::string CloseBracket::GetPare(void) const {
  return pare;
};

std::string CloseBracket::GetTokenName(void) const {
  return name;
};

ElementType CloseBracket::GetType(void) const {
  return ElementType::CLOSE_BRACKET;
}

void CloseBracket::DoOperation(DataStack& dataStack) const {
  //do nothing
}



std::string Function::GetTokenName(void) const {
  return name;
};

ElementType Function::GetType(void) const {
  return ElementType::FUNCTION;
};

void Function::DoOperation(DataStack& dataStack) const {
  if (dataStack.size() < argsNum)
    throw std::exception("Unexpected number of arguments");
  else {
    std::vector<std::shared_ptr<Operand>> args;
    for (int i = 0; i < argsNum; i++) {
      std::shared_ptr<Operand> a = dataStack.top();
      dataStack.pop();
      args.push_back(a);
    }
    std::reverse(args.begin(), args.end());
    dataStack.push(doOperation(args));
  }
}