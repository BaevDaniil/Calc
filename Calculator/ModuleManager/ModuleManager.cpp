#include "ModuleManager.h"

std::vector<HINSTANCE> ModuleManager::linkedLibraries = {};

ModuleManager& ModuleManager::GetInstance() {
  static ModuleManager moduleManager;
  return moduleManager;
}

void ModuleManager::LoadDll(OperationsDescription& dstr) {
  HMODULE hdll = nullptr;

  for (auto& dll : std::filesystem::directory_iterator(std::filesystem::current_path().string() + "\\" + path)) {
    if (dll.path().extension() == ".dll") {
      hdll = LoadLibrary(dll.path().string().c_str());
      if (hdll) {
        linkedLibraries.push_back(hdll);

        auto func = (Func)(GetProcAddress(hdll, LPCSTR(funcName.c_str())));
        if (func)
          func(dstr);
        else
          throw std::exception(("Unable to load operations from " + dll.path().filename().string()).c_str());
      }
    }
  }
};