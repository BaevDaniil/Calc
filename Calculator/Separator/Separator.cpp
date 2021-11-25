#include "Separator.h"

/**
* @brief function to separate the space character from the current position
* @param[in] expression - expression to separate
* @param[in] curPos - current position in expression to start separating
* @param[out] endOfTokenPos - token end position
*/
void SeparateSpace(const std::string& expression, const size_t curPos, size_t& endOfTokenPos) {
  for (curPos; isspace(expression[endOfTokenPos]); ++endOfTokenPos);
}

/**
* @brief function to separate the delimetr argument character from the current position
* @param[in] expression - expression to separate
* @param[in] curPos - current position in expression to start separating
* @param[out] endOfTokenPos - token end position
*/
Token SeparateDelimetrArgs(const std::string& expression, const size_t curPos, size_t& endOfTokenPos) {
  endOfTokenPos++;
  return Token(Token::Type::DELIMETR_ARGS, { DELIMETR_ARGS });
}

/**
* @brief function to separate the literal from the current position
* @param[in] expression - expression to separate
* @param[in] curPos - current position in expression to start separating
* @param[out] endOfTokenPos - token end position
*/
Token SeparateLiteral(const std::string& expression, const size_t curPos, size_t& endOfTokenPos) {
  size_t delta = 0;
  std::stod(expression.substr(curPos), &delta);
  endOfTokenPos += delta;
  return Token(Token::Type::LITERAL, expression.substr(curPos, endOfTokenPos - curPos));
}

/**
* @brief function to separate the named token from the current position
* @details FUNCTION, OPERATOR, BRACKET or VARIABLE are called named token
* @param[in] expression - expression to separate
* @param[in] curPos - current position in expression to start separating
* @param[out] endOfTokenPos - token end position
*/
Token SeparateNamedToken(const std::string& expression, const size_t curPos, size_t& endOfTokenPos) {
  OperationsDescription& operations = OperationsDescription::GetInstance();
  for (endOfTokenPos; endOfTokenPos < expression.size() && !isspace(expression[endOfTokenPos]); ++endOfTokenPos);
  for (endOfTokenPos; endOfTokenPos != curPos; endOfTokenPos--) {
    std::string expressionPart = expression.substr(curPos, endOfTokenPos - curPos);
    if (operations.CheckFunction(expressionPart))
      return Token(Token::Type::FUNCTION, expressionPart);
    if (operations.CheckOperator(expressionPart))
      return Token(Token::Type::OPERATOR, expressionPart);
    if (expressionPart == std::string{ SIMBOL_BEFORE_ARGS } || expressionPart == std::string{ SIMBOL_AFTER_ARGS } || 
        operations.CheckBracket(expressionPart))
      return Token(Token::Type::BRACKET, expressionPart);
    if (Variable::IsValidValueName(expressionPart))
      return Token(Token::Type::VARIABLE, expressionPart);
  }
  throw std::exception("Unknown identifier");
}

std::vector<Token> Separate(const std::string& expression) {
  OperationsDescription& operations = OperationsDescription::GetInstance();
  size_t curPos = 0;
  size_t endOfTokenPos = 0;
  std::vector<Token> tokens = {};

  for (curPos = 0; curPos < expression.size(); curPos = endOfTokenPos)
    if (isspace(expression[curPos]))
      SeparateSpace(expression, curPos, endOfTokenPos);
    else if (expression[curPos] == DELIMETR_ARGS)
      tokens.emplace_back(SeparateDelimetrArgs(expression, curPos, endOfTokenPos));
    else if (isdigit(expression[curPos]))
      tokens.emplace_back(SeparateLiteral(expression, curPos, endOfTokenPos));
    else
      tokens.emplace_back(SeparateNamedToken(expression, curPos, endOfTokenPos));
  
  return tokens;
}