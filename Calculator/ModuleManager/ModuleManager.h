#pragma once

#include <filesystem>
#include <windows.h>
#include <iostream>

#include "..\API\API.h"

/**
* @brief singletone class for managing loaded dll
*/
class ModuleManager {
public:
  /**
  * @brief internal type to define a pluggable function
  */
  using Func = void(*)(OperationsDescription& dstr);

  /**
  * @brief copy consructor (deleted)
  * @warning the method is deleted
  */
  ModuleManager(const ModuleManager&) = delete;

  /**
  * @brief move consructor (deleted)
  * @warning the method is deleted
  */
  ModuleManager(ModuleManager&&) = delete;

  /**
  * @brief copy operator (deleted)
  * @warning the operator is deleted
  */
  ModuleManager& operator= (const ModuleManager&) = delete;

  /**
  * @brief move operator (deleted)
  * @warning the operator is deleted
  */
  ModuleManager& operator= (ModuleManager&&) = delete;

  /**
  * @brief default destructor
  */
  ~ModuleManager() = default;

  /**
  * @brief getter of exemplar of class
  * @return exemplar of class
  */
  static ModuleManager& GetInstance();

  /**
  * @brief function for loadeing all dll from "path"
  * @param[in/out] dstr - storage of operations for loading in it operations from dll
  */
  void LoadDll(OperationsDescription& dstr);
private:
  /**
  * @brief default constructor
  */
  ModuleManager() = default;

  /**
  * @brief dll search path
  */
  const std::string path{ "..\\modules" };

  /**
  * @brief imported function's name
  */
  const std::string funcName = "Load";

  /**
  * @brief plug-in descriptor store
  */
  static std::vector<HINSTANCE> linkedLibraries;
};