#include "trigonometry.h"

std::shared_ptr<Literal> Sin(std::vector<std::shared_ptr<Operand>> args) {
  return std::make_shared<Literal>(sin(args[0]->GetValue()));
}

std::shared_ptr<Literal> Cos(std::vector<std::shared_ptr<Operand>> args) {
  return std::make_shared<Literal>(cos(args[0]->GetValue()));
}

std::shared_ptr<Literal> Tan(std::vector<std::shared_ptr<Operand>> args) {
  return std::make_shared<Literal>(tan(args[0]->GetValue()));
}

std::shared_ptr<Literal> Cot(std::vector<std::shared_ptr<Operand>> args) {
  return std::make_shared<Literal>(1 / tan(args[0]->GetValue()));
}

std::shared_ptr<Literal> Arcsin(std::vector<std::shared_ptr<Operand>> args) {
  return std::make_shared<Literal>(asin(args[0]->GetValue()));
}

std::shared_ptr<Literal> Arccos(std::vector<std::shared_ptr<Operand>> args) {
  return std::make_shared<Literal>(acos(args[0]->GetValue()));
}

std::shared_ptr<Literal> Arctan(std::vector<std::shared_ptr<Operand>> args) {
  return std::make_shared<Literal>(atan(args[0]->GetValue()));
}
std::shared_ptr<Literal> Arccot(std::vector<std::shared_ptr<Operand>> args) {
  return std::make_shared<Literal>(atan(-args[0]->GetValue()) + Pi/2);
}

std::shared_ptr<Literal> GetPi(std::vector<std::shared_ptr<Operand>> args) {
  return std::make_shared<Literal>(Pi);
}

extern "C" __declspec(dllexport) void __cdecl Load(OperationsDescription & dstr) {
  std::vector<Function> functions = { { "sin", 1, Sin },
                                      { "cos", 1, Cos },
                                      { "tan", 1, Tan },
                                      { "cot", 1, Cot },
                                      { "arcsin", 1, Arcsin},
                                      { "arccos", 1, Arccos },
                                      { "arctan", 1, Arctan },
                                      { "arccot", 1, Arccot },
                                      { "getPi", 0, GetPi } };
  for (auto func : functions)
    dstr.LoadOperation(std::make_shared<Function>(func));
}