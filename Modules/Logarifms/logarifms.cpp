#include "logarifms.h"

std::shared_ptr<Literal> Ln(std::vector<std::shared_ptr<Operand>> args) {
  return std::make_shared<Literal>(log(args[0]->GetValue()));
}

std::shared_ptr<Literal> Exp(std::vector<std::shared_ptr<Operand>> args) {
  return std::make_shared<Literal>(exp(args[0]->GetValue()));
}

std::shared_ptr<Literal> Log(std::vector<std::shared_ptr<Operand>> args) {
  return std::make_shared<Literal>(log(args[1]->GetValue()) / log(args[0]->GetValue()));
}

std::shared_ptr<Literal> GetExp(std::vector<std::shared_ptr<Operand>> args) {
  return std::make_shared<Literal>(E);
}

extern "C" __declspec(dllexport) void __cdecl Load(OperationsDescription & dstr) {
  std::vector<Function> functions = { { "ln", 1, Ln },
                                      { "exp", 1, Exp },
                                      { "log", 2, Log },
                                      {"getExp", 0, GetExp} };
  for (auto func : functions)
    dstr.LoadOperation(std::make_shared<Function>(func));
}