#pragma once

#include "../API/API.h"
#include "../Separator/Separator.h"

/**
* @brief singleton class for managing global variables
*/
class VariableManager {
public:
  /**
  * @brief copy consructor (deleted)
  * @warning the method is deleted
  */
  VariableManager(const VariableManager&) = delete;

  /**
  * @brief move consructor (deleted)
  * @warning the method is deleted
  */
  VariableManager(VariableManager&&) = delete;

  /**
  * @brief copy operator (deleted)
  * @warning the operator is deleted
  */
  VariableManager operator=(const VariableManager&) = delete;

  /**
  * @brief move operator (deleted)
  * @warning the operator is deleted
  */
  VariableManager operator=(VariableManager&&) = delete;

  /**
  * @brief default destructor
  */
  ~VariableManager() = default;

  /**
  * @brief getter of exemplar of class
  * @return exemplar of class
  */
  static VariableManager& GetInstance(void);

  /**
  * @brief method of check availability of variable in internal storage
  * @param[in] name - name of variable
  * @return true if there is variable in internal storage, false otherwise
  */
  bool CheckVariable(const std::string& name) const;

  /**
  * @brief method of loading the variable into internal storage
  * @param[in] var - variable, which you want to load
  */
  void AddVariable(Variable var);

  /**
 * @brief getter of variable from internal storage
 * @param[in] name - name of variable
 * @return variable
 */
  Variable FindVariable(const std::string& name) const;
private:
  /**
  * @brief default constructor
  */
  VariableManager() = default;

  /**
  * @brief variable's internal storage
  */
  static std::map<std::string, Variable> variableMap;
};

/**
* @brief expression calculating function
* @param[in] expression - expression for calculating
* @return result of calculating
*/
double Calculate(const std::string& expression);