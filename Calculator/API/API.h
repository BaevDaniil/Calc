#pragma once

#include "ExpressionElements.h"
#include <algorithm>

/**
* @brief singletone class for storage operations
*/
class OperationsDescription {
public:
  /**
  * @brief copy consructor (deleted)
  * @warning the method is deleted
  */
  OperationsDescription(const OperationsDescription&) = delete;

  /**
  * @brief move consructor (deleted)
  * @warning the method is deleted
  */
  OperationsDescription(OperationsDescription&&) = delete;

  /**
  * @brief copy operator (deleted)
  * @warning the operator is deleted
  */
  OperationsDescription& operator=(const OperationsDescription&) = delete;

  /**
  * @brief move operator (deleted)
  * @warning the operator is deleted
  */
  OperationsDescription& operator=(OperationsDescription&&) = delete;

  /**
  * @brief default destructor
  */
  ~OperationsDescription() = default;
 
  /**
  * @brief method of check validation function's name
  * @param[in] name - name of function
  * @return true if name is valid, false otherwise
  */
  static bool IsValidFunctionName(const std::string& name);

  /**
  * @brief method of check validation operator's name
  * @param[in] name - name of operator
  * @return true if name is valid, false otherwise
  */
  static bool IsValidOperatorName(const std::string& name);

  /**
  * @brief method of check validation bracket's name
  * @param[in] name - name of bracket
  * @return true if name is valid, false otherwise
  */
  static bool IsValidBracketName(const std::string& name);
  
  /**
  * @brief getter of exemplar of class
  * @return exemplar of class
  */
  static OperationsDescription& GetInstance(void);

  /**
  * @brief method of check availability of operation in internal storage
  * @param[in] name - name of operation
  * @return true if there is operation in internal storage, false otherwise
  */
  bool CheckOperation(const std::string& name) const;

  /**
  * @brief method of check availability of function in internal storage
  * @param[in] operation - name of function
  * @return true if there is function in internal storage, false otherwise
  */
  bool CheckFunction(const std::string& operation) const;
 
  /**
  * @brief method of check availability of operator in internal storage
  * @param[in] operation - name of operator
  * @return true if there is operator in internal storage, false otherwise
  */
  bool CheckOperator(const std::string& operation) const;

  /**
  * @brief method of check availability of bracket in internal storage
  * @param[in] operation - name of bracket
  * @return true if there is bracket in internal storage, false otherwise
  */
  bool CheckBracket(const std::string& operation) const;

  /**
  * @brief getter of function from internal storage
  * @param[in] operation - name of function
  * @return shared pointer to function
  */
  std::shared_ptr<Operation> GetFunction(const std::string& operation) const;

  /**
  * @brief getter of bracket from internal storage
  * @param[in] operation - name of bracket
  * @return shared pointer to bracket
  */
  std::shared_ptr<Operation> GetBracket(const std::string& operation) const;

  /**
  * @brief getter of operator from internal storage
  * @param[in] operation - name of operator
  * @return shared pointer to operator
  */
  std::shared_ptr<Operation> GetOperator(const std::string& operation, ElementType type) const;

  /**
  * @brief method of loading the operation into internal storage
  * @param[in] operation - shared pointer to operation, which you want to load
  */
  void LoadOperation(std::shared_ptr<Operation> operation);

  /**
  * @brief method of clearing internal storage
  * @warning make sure to call this method at the end of the program
  */
  void Clear(void);
private:
  /**
  * @brief default constructor
  */
  OperationsDescription() = default;

  /**
  * @brief method for checking the first character of a function name for validity
  * @param[in] symbol - first character of a function name
  * @return true if character is valid, false otherwise
  */
  static bool IsBeginigFunctionName(const char symbol);

  /**
  * @brief method for checking the first character of a operator name for validity
  * @param[in] symbol - first character of a operator name
  * @return true if character is valid, false otherwise
  */
  static bool IsBeginingOperatorName(const char symbol);

  /**
  * @brief method for checking the first character of a bracket name for validity
  * @param[in] symbol - first character of a bracket name
  * @return true if character is valid, false otherwise
  */
  static bool IsBeginingBracketName(const char symbol);

  /**
  * @brief method of loading the function into function's internal storage
  * @param[in] operation - shared pointer to function, which you want to load
  * @warning do not upload other type of operations here
  */
  void AddFunction(std::shared_ptr<Operation> operation);

  /**
  * @brief method of loading the operator into operator's internal storage
  * @param[in] operation - shared pointer to operator, which you want to load
  * @warning do not upload other type of operations here
  */
  void AddOperator(std::shared_ptr<Operation> operation);

  /**
  * @brief method of loading the bracket into bracket's internal storage
  * @param[in] operation - shared pointer to bracket, which you want to load
  * @warning do not upload other type of operations here
  */
  void AddBracket(std::shared_ptr<Operation> operation);

  /**
  * @brief function's internal storage
  */
  std::map<std::string, std::shared_ptr<Operation>> functions;

  /**
  * @brief operators's internal storage
  */
  std::multimap<std::string, std::shared_ptr<Operation>> operators;

  /**
  * @brief brackets's internal storage
  */
  std::map<std::string, std::shared_ptr<Operation>> brackets;
};




/**
* @brief class of binary operator
*/
class BinaryOperator : public Operation {
public:
  /**
  * @brief enum class to denote operator associativity
  */
  enum class Associative {
    LEFT,     ///< left associative
    RIGHT,    ///< right associative
  };

  /**
  * @brief an internal type for storing a function that performs a specific operation
  */
  using DoBinaryOperation = std::shared_ptr<Literal>(*)(std::shared_ptr<Operand> a, std::shared_ptr<Operand> b);

  /**
  * @brief default consructor (deleted)
  * @warning the method is deleted
  */
  BinaryOperator() = delete;

  /**
  * @brief constructor
  * @param[in] name - the string by which the operator in the expression is recognized
  * @param[in] prioryty - operation priority
  * @param[in] operation - function that performs a specific operation
  * @param[in] associative - operator associativity
  */
  BinaryOperator(const std::string& name, int prioryty, DoBinaryOperation operation, Associative associative = Associative::LEFT) :
    name(name), prioryty(prioryty), doOperation(operation), assotiative(associative) {};

  /**
  * @brief default copy constructor
  */
  BinaryOperator(const BinaryOperator&) = default;

  /**
  * @brief default move constructor
  */
  BinaryOperator(BinaryOperator&&) = default;

  /**
  * @brief default copy operator
  */
  BinaryOperator& operator= (const BinaryOperator&) = default;

  /**
  * @brief default move operator
  */
  BinaryOperator& operator= (BinaryOperator&&) = default;

  /**
  * @brief default destructor
  */
  ~BinaryOperator() = default;

  /**
  * @brief getter of operator's priority
  * @return priority
  */
  int GetPriority(void) const {
    return prioryty;
  };

  /**
  * @brief getter of operator's assotiative
  * @return assotiative
  */
  Associative GetAssociative(void) const;

  /**
  * @brief getter of operation's type
  * @return ElementType::BINARY
  */
  ElementType GetType(void) const override final;

  /**
  * @brief getter of operator's name
  * @return the string by which the operator in the expression is recognized
  */
  std::string GetTokenName(void) const override final;

  /**
  * @brief method performing this operation interacting with the data stack
  * @param[in/out] dataStack - data stack, the result goes back to the top
  */
  void DoOperation(DataStack& dataStack) const override final;
private:
  /**
  * @brief function that performs a specific operation
  */
  DoBinaryOperation doOperation;

  /**
  * @brief the string by which the operator in the expression is recognized
  */
  const std::string name;

  /**
  * @brief operation priority
  */
  const int prioryty;

  /**
  * @brief operator associativity
  */
  const Associative assotiative;
};




/**
* @brief class of prefics operator
*/
class PreficsOperator : public Operation {
public:
  /**
  * @brief an internal type for storing a function that performs a specific operation
  */
  using DoPreficsOperation = std::shared_ptr<Literal>(*)(std::shared_ptr<Operand> a);

  /**
  * @brief default consructor (deleted)
  * @warning the method is deleted
  */
  PreficsOperator() = delete;

  /**
  * @brief constructor
  * @param[in] name - the string by which the operator in the expression is recognized
  * @param[in] prioryty - operation priority, affects interaction with binary operators
  * @param[in] operation - function that performs a specific operation
  */
  PreficsOperator(const std::string& name, int prioryty, DoPreficsOperation operation) :
    name(name), prioryty(prioryty), doOperation(operation) {};

  /**
  * @brief default copy constructor
  */
  PreficsOperator(const PreficsOperator&) = default;

  /**
  * @brief default move constructor
  */
  PreficsOperator(PreficsOperator&&) = default;

  /**
  * @brief default copy operator
  */
  PreficsOperator& operator= (const PreficsOperator&) = default;

  /**
  * @brief default move operator
  */
  PreficsOperator& operator= (PreficsOperator&&) = default;

  /**
  * @brief default destructor
  */
  ~PreficsOperator() = default;

  /**
  * @brief getter of operator's priority
  * @return priority
  */
  int GetPriority(void) const;

  /**
  * @brief getter of operation's type
  * @return ElementType::PREFICS
  */
  ElementType GetType(void) const override final;

  /**
  * @brief getter of operator's name
  * @return the string by which the operator in the expression is recognized
  */
  std::string GetTokenName(void) const override final;

  /**
  * @brief method performing this operation interacting with the data stack
  * @param[in/out] dataStack - data stack, the result goes back to the top
  */
  void DoOperation(DataStack& dataStack) const override final;
private:
  /**
  * @brief function that performs a specific operation
  */
  DoPreficsOperation doOperation;

  /**
  * @brief the string by which the operator in the expression is recognized
  */
  const std::string name;

  /**
  * @brief operation priority
  */
  const int prioryty;
};




/**
* @brief class of postfics operator
*/
class PostficsOperator : public Operation {
public:
  /**
  * @brief an internal type for storing a function that performs a specific operation
  */
  using DoPostficsOperation = std::shared_ptr<Literal>(*)(std::shared_ptr<Operand> a);
  
  /**
  * @brief default consructor (deleted)
  * @warning the method is deleted
  */
  PostficsOperator() = delete;

  /**
  * @brief constructor
  * @param[in] name - the string by which the operator in the expression is recognized
  * @param[in] operation - function that performs a specific operation
  */
  PostficsOperator(const std::string& name, DoPostficsOperation operation) :
    name(name), doOperation(operation) {};
  
  /**
  * @brief default copy constructor
  */
  PostficsOperator(const PostficsOperator&) = default;

  /**
  * @brief default move constructor
  */
  PostficsOperator(PostficsOperator&&) = default;

  /**
  * @brief default copy operator
  */
  PostficsOperator& operator= (const PostficsOperator&) = default;

  /**
  * @brief default move operator
  */
  PostficsOperator& operator= (PostficsOperator&&) = default;

  /**
  * @brief default destructor
  */
  ~PostficsOperator() = default;

  /**
  * @brief getter of operation's type
  * @return ElementType::POSTFICS
  */
  ElementType GetType(void) const override final;

  /**
  * @brief getter of operator's name
  * @return the string by which the operator in the expression is recognized
  */
  std::string GetTokenName(void) const override final;

  /**
  * @brief method performing this operation interacting with the data stack
  * @param[in/out] dataStack - data stack, the result goes back to the top
  */
  void DoOperation(DataStack& dataStack) const override final;
private:
  /**
  * @brief function that performs a specific operation
  */
  DoPostficsOperation doOperation;

  /**
  * @brief the string by which the operator in the expression is recognized
  */
  const std::string name;
};




/**
* @brief class of open bracket operator
*/
class OpenBracket : public Operation {
public:
  /**
  * @brief an internal type for storing a function that performs a specific operation
  */
  using DoFunc = std::shared_ptr<Literal>(*)(std::shared_ptr<Operand> a);
  
  /**
  * @brief default consructor (deleted)
  * @warning the method is deleted
  */
  OpenBracket() = delete;

  /**
  * @brief constructor
  * @param[in] name - the string by which the bracket in the expression is recognized
  * @param[in] operation - function that performs a specific operation
  */
  OpenBracket(const std::string& name, DoFunc operation) :
    name(name), doOperation(operation) {};

  /**
  * @brief default copy constructor
  */
  OpenBracket(const OpenBracket&) = default;

  /**
  * @brief default move constructor
  */
  OpenBracket(OpenBracket&&) = default;

  /**
  * @brief default copy operator
  */
  OpenBracket& operator= (const OpenBracket&) = default;

  /**
  * @brief default move operator
  */
  OpenBracket& operator= (OpenBracket&&) = default;

  /**
  * @brief default destructor
  */
  ~OpenBracket() = default;

  /**
  * @brief getter of operation's type
  * @return ElementType::OPEN_BRACKET
  */
  ElementType GetType(void) const override final;

  /**
  * @brief getter of bracket's name
  * @return the string by which the bracket in the expression is recognized
  */
  std::string GetTokenName(void) const override final;

  /**
  * @brief method performing this operation interacting with the data stack
  * @param[in/out] dataStack - data stack, the result goes back to the top
  */
  void DoOperation(DataStack& dataStack) const override final;
private:
  /**
  * @brief function that performs a specific operation
  */
  DoFunc doOperation;

  /**
  * @brief the string by which the operator in the expression is recognized
  */
  const std::string name;
};




/**
* @brief class of close bracket operator
*/
class CloseBracket : public Operation {
public:
  /**
  * @brief default consructor (deleted)
  * @warning the method is deleted
  */
  CloseBracket() = delete;

  /**
  * @brief constructor
  * @param[in] name - the string by which the bracket in the expression is recognized
  * @param[in] pare - the string by which the matching open bracket is recognized
  */
  CloseBracket(std::string name, std::string pare) :
    name(name), pare(pare) {};

  /**
  * @brief default copy constructor
  */
  CloseBracket(const CloseBracket&) = default;

  /**
  * @brief default move constructor
  */
  CloseBracket(CloseBracket&&) = default;

  /**
  * @brief default copy operator
  */
  CloseBracket& operator= (const CloseBracket&) = default;

  /**
  * @brief default move operator
  */
  CloseBracket& operator= (CloseBracket&&) = default;

  /**
  * @brief default destructor
  */
  ~CloseBracket() = default;

  /**
  * @brief getter of pare's name
  * @return the string by which the matching open bracket is recognized
  */
  std::string GetPare(void) const;

  /**
  * @brief getter of bracket's name
  * @return the string by which the bracket in the expression is recognized
  */
  std::string GetTokenName(void) const override final;

  /**
  * @brief getter of operation's type
  * @return ElementType::CLOSE_BRACKET
  */
  ElementType GetType(void) const override final;

  /**
  * @brief method performing this operation interacting with the data stack
  * @param[in/out] dataStack - data stack, the result goes back to the top
  * @warning in this class method do nothing
  */
  void DoOperation(DataStack& dataStack) const override final;
private:
  /**
  * @brief the string by which the bracket in the expression is recognized
  */
  const std::string name;

  /**
  * @brief the string by which the matching open bracket is recognized
  */
  const std::string pare;
};




/**
* @brief class of functions in expression
*/
class Function : public Operation {
public:
  /**
  * @brief an internal type for storing a function that performs a specific operation
  */
  using DoFunc = std::shared_ptr<Literal>(*)(std::vector<std::shared_ptr<Operand>> args);

  /**
  * @brief default consructor (deleted)
  * @warning the method is deleted
  */
  Function() = delete;

  /**
  * @brief constructor
  * @param[in] name - the string by which the function in the expression is recognized
  * @param[in] argsNum - the number of arguments this function works with
  * @param[in] operation - function that performs a specific operation
  */
  Function(std::string name, int argsNum, DoFunc operation) :
    name(name), argsNum(argsNum), doOperation(operation) {};

  /**
  * @brief default copy constructor
  */
  Function(const Function&) = default;

  /**
  * @brief default move constructor
  */
  Function(Function&&) = default;

  /**
  * @brief default copy operator
  */
  Function& operator= (const Function&) = default;

  /**
 * @brief default move operator
 */
  Function& operator= (Function&&) = default;

  /**
  * @brief default destructor
  */
  ~Function() = default;

  /**
  * @brief getter of function's name
  * @return the string by which the function in the expression is recognized
  */
  std::string GetTokenName(void) const override final;

  /**
  * @brief getter of operation's type
  * @return ElementType::FUNCTION
  */
  ElementType GetType(void) const override final;

  /**
  * @brief method performing this operation interacting with the data stack
  * @param[in/out] dataStack - data stack, the result goes back to the top
  */
  void DoOperation(DataStack& dataStack) const override final;
private:
  /**
  * @brief function that performs a specific operation
  */
  DoFunc doOperation;

  /**
  * @brief the string by which the function in the expression is recognized
  */
  const std::string name;

  /**
  * @brief the number of arguments this function works with
  */
  const int argsNum;
};