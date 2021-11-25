#include "pow.h"
#include <cmath>

std::shared_ptr<Literal> Pow(std::shared_ptr<Operand> a, std::shared_ptr<Operand> b) {
  return std::make_shared<Literal>(pow(a->GetValue(), b->GetValue()));
}

extern "C" __declspec(dllexport) void __cdecl Load(OperationsDescription & dstr) {
  //OperationsDescription& dstr = OperationsDescription::GetInstance();
  const BinaryOperator pow = { "^", 4, Pow, BinaryOperator::Associative::LEFT};

  dstr.LoadOperation(std::make_shared<BinaryOperator>(pow));
}