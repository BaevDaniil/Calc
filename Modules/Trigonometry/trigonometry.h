#pragma once

#include "..\..\Calculator\API\API.h"
#include <cmath>

extern "C" __declspec(dllexport) void __cdecl Load(OperationsDescription & dstr);

constexpr double Pi = 3.1415926535897932;

std::shared_ptr<Literal> Sin(std::vector<std::shared_ptr<Operand>> args);
std::shared_ptr<Literal> Cos(std::vector<std::shared_ptr<Operand>> args);
std::shared_ptr<Literal> Tan(std::vector<std::shared_ptr<Operand>> args);
std::shared_ptr<Literal> Cot(std::vector<std::shared_ptr<Operand>> args);

std::shared_ptr<Literal> Arcsin(std::vector<std::shared_ptr<Operand>> args);
std::shared_ptr<Literal> Arccos(std::vector<std::shared_ptr<Operand>> args);
std::shared_ptr<Literal> Arctan(std::vector<std::shared_ptr<Operand>> args);
std::shared_ptr<Literal> Arccot(std::vector<std::shared_ptr<Operand>> args);

std::shared_ptr<Literal> GetPi(std::vector<std::shared_ptr<Operand>> args);