#include "Calc/Calculator.h"
#include "BaseOperations/BaseOperation.h"
#include "ModuleManager/ModuleManager.h"
#include <iostream>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main(){
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

  OperationsDescription& dstr = OperationsDescription::GetInstance();
  try {
    LoadBase(dstr);
    ModuleManager::GetInstance().LoadDll(dstr);
  }
  catch (const std::exception& except) {
    std::cout << except.what() << std::endl;
  }

  std::string str;
  while (std::getline(std::cin, str) && str != "exit") {
    try{
      if (str == "exit")
        return 0;
      std::cout << std::setiosflags(std::ios_base::fixed) << std::setprecision(6) << Calculate(str) << std::endl;
    }
    catch (const std::exception& except) {
      std::cout << except.what() << std::endl;
    }
    catch (...) {
      std::cout << "Unknown error" << std::endl;
    }
  }
  dstr.Clear();
  return 0;
}