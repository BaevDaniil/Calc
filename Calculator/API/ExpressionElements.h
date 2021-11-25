#pragma once

#include <string>
#include <vector>
#include <stack>
#include <map>
#include <memory>
#include <exception>

/**
* @brief argument separator in function call
*/
constexpr char DELIMETR_ARGS = ',';

/**
* @brief character after the function name indicating the beginning of passing arguments
*/
constexpr char SIMBOL_BEFORE_ARGS = '(';

/**
* @brief character denoting the end of argument passing to a function
*/
constexpr char SIMBOL_AFTER_ARGS = ')';


/*
* @brief expression element type
*/
enum class ElementType {
  PREFICS,                ///< prefics operator
  POSTFICS,               ///< postfics operator
  BINARY,                 ///< binary operator
  FUNCTION,               ///< function
  OPEN_BRACKET,           ///< open bracket
  CLOSE_BRACKET,          ///< close bracket
  LITERAL,                ///< literal const (number)
  VARIABLE,               ///< variable
  DELIMETR_ARGS,          ///< argument separator in function call
  SIMBOL_BEFORE_ARGS,     ///< character after the function name indicating the beginning of passing arguments
  SIMBOL_AFTER_ARGS,      ///< character denoting the end of argument passing to a function
};

/**
* @brief base class for operand
*/
class Operand {
public:
  /**
  * @brief default virtual desructor
  */
  virtual ~Operand() = default;

  /**
  * @brief getter operand values
  * @return operand value
  */
  virtual double GetValue(void) const = 0;

  /**
  * @brief getter operand type
  * @return operand type
  */
  virtual ElementType GetType(void) const = 0;
};




/**
* @brief class for literal const
*/
class Literal : public Operand {
public:
  /**
  * @brief default consructor (deleted)
  * @warning the method is deleted
  */
  Literal() = delete;

  /**
  * @brief consructor
  * @param[in] value - literal constant value
  */
  Literal(double value) : value(value) {};

  /**
  * @brief default copy constructor
  */
  Literal(Literal const& it) = default;

  /**
  * @brief default move constructor
  */
  Literal(Literal&& it) = default;

  /**
  * @brief default copy operator
  */
  Literal& operator=(const Literal& other) = default;

  /**
  * @brief default move operator
  */
  Literal& operator=(Literal&&) = default;

  /**
  * @brief default destructor
  */
  ~Literal() = default;

  /**
  * @brief getter operand values
  * @return literal value
  */
  double GetValue(void) const override final;

  /**
  * @brief getter operand type
  * @return ElementType::LITERAL
  */
  ElementType GetType(void) const override final;
private:
  /**
  * @brief literal value
  */
  const double value;
};




/**
* @brief class for variable
*/
class Variable : public Operand {
public:
  /**
  * @brief default consructor (deleted)
  * @warning the method is deleted
  */
  Variable() = delete;
  
  /**
  * @brief consructor
  * @param[in] name - name of variable
  */
  Variable(const std::string& name) : isInit(false), name(name) {};

  /**
  * @brief default copy constructor
  */
  Variable(Variable const& it) = default;

  /**
  * @brief default move constructor
  */
  Variable(Variable&& it) = default;

  /**
  * @brief default copy operator
  */
  Variable& operator=(const Variable& other) = default;

  /**
  * @brief default move operator
  */
  Variable& operator=(Variable&&) = default;

  /**
  * @brief default destructor
  */
  ~Variable() = default;

  /**
  * @brief method of check validation variable's name
  * @param[in] name - name of variable
  * @return true if name is valid, false otherwise
  */
  static bool IsValidValueName(const std::string& name);

  /**
  * @brief getter variable values
  * @return variable value
  */
  double GetValue(void) const override final;

  /**
  * @brief getter operand type
  * @return ElementType::VARIABLE
  */
  ElementType GetType(void) const override final;

  /**
  * @brief getter of value's name
  * @return the string by which the value in the expression is recognized
  */
  std::string GetName(void) const;

  /**
  * @brief getter of init's state
  * @return true if value is init, false otherwise
  */
  bool IsInit(void) const;

  /**
  * @brief setter value of variable
  * @param[in] value - new value of variable
  */
  void SetValue(const double value);
private:
  /**
  * @brief method for checking the first character of a variable name for validity
  * @param[in] symbol - first character of a variable name
  * @return true if character is valid, false otherwise
  */
  static bool IsBeginingValueName(const char symbol);

  /**
  * @brief value of variable
  */
  double value;

  /**
  * @brief bool init state
  */
  bool isInit;

  /**
  * @brief name of variable
  */
  std::string name;
};




/**
* @brief base class for operation
*/
class Operation {
public:
  /**
  * @brief internal type for naming the stack of operations
  */
  using DataStack = std::stack<std::shared_ptr<Operand>>;

  /**
  * @brief getter of operation's name
  * @return the string by which the operation in the expression is recognized
  */
  virtual std::string GetTokenName(void) const = 0;

  /**
  * @brief getter of operation's type
  * @return type of element
  */
  virtual ElementType GetType(void) const = 0;

  /**
  * @brief virtual default destructor
  */
  virtual ~Operation() = default;

  /**
  * @brief method performing this operation interacting with the data stack
  * @param[in/out] dataStack - data stack, the result goes back to the top
  */
  virtual void DoOperation(DataStack& dataStack) const = 0;
};