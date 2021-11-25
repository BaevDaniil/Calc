#pragma once

#include <string>
#include "..\..\Calculator\API\API.h"

/**
* @brief token class
*/
class Token {
public:
  enum class Type {
    DELIMETR_ARGS,    ///< argument separator in function call
    LITERAL,          ///< literal const (number)
    FUNCTION,         ///< function
    OPERATOR,         ///< some operator
    BRACKET,          ///< some bracket or SIMBOL_BEFORE_ARGS or SIMBOL_AFTER_ARGS
    VARIABLE          ///< variable
  };

  /**
  * @brief constructor
  * @param[in] type - token's type
  * @param[in] token = token string
  */
  Token(Type type, std::string token) : type(type), token(token) {};

  /**
  * @brief default copy constructor
  */
  Token(const Token&) = default;

  /**
  * @brief default move constructor
  */
  Token(Token&&) = default;

  /**
  * @brief default copy operator
  */
  Token& operator= (const Token&) = default;

  /**
  * @brief default move operator
  */
  Token& operator= (Token&&) = default;

  /**
  * @brief default destructor
  */
  ~Token() = default;

  /**
  * @brief getter operand type
  * @return token type
  */
  Type GetType() const {
    return type;
  };

  /**
  * @brief getter token string
  * @return token string
  */
  std::string GetName() const {
    return token;
  };
private:
  /**
  * @brief type of token
  */
  const Type type;

  /**
  * @brief token string
  */
  const std::string token;
};

/**
* @brief function of splitting an expression into tokens
* @param[in] expression - expression in string form
* @return expression in vector of token form
*/
std::vector<Token> Separate(const std::string& expression);