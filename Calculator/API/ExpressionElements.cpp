#include "ExpressionElements.h"

double Literal::GetValue(void) const{
  return value;
}

ElementType Literal::GetType(void) const {
  return ElementType::LITERAL;
}

bool Variable::IsBeginingValueName(const char symbol) {
  return isalpha(symbol) && symbol != DELIMETR_ARGS && symbol != SIMBOL_BEFORE_ARGS && symbol != SIMBOL_AFTER_ARGS;
}

bool Variable::IsValidValueName(const std::string& name) {
  if (!IsBeginingValueName(name[0]))
    return false;
  for (int i = 1; i < name.size(); i++)
    if (!isalnum(name[i]) || name[i] == DELIMETR_ARGS || name[i] == SIMBOL_BEFORE_ARGS || name[i] == SIMBOL_AFTER_ARGS)
      return false;
  return true;
}

double Variable::GetValue(void) const{
  if (isInit != true)
    throw std::exception(("Variable " + name + " not init").c_str());
  return value;
}

ElementType Variable::GetType(void) const {
  return ElementType::VARIABLE;
}

std::string Variable::GetName(void) const {
  return name;
}

bool Variable::IsInit(void) const {
  return isInit;
};

void Variable::SetValue(const double value) {
  this->value = value;
  isInit = true;
};