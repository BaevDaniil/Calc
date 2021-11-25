#pragma once

#include "..\..\Calculator\API\API.h"
#include <cmath>

extern "C" __declspec(dllexport) void __cdecl Load(OperationsDescription & dstr);

constexpr double E = 2.7182818284590452;

std::shared_ptr<Literal> Ln(std::vector<std::shared_ptr<Operand>> args);
std::shared_ptr<Literal> Exp(std::vector<std::shared_ptr<Operand>> args);
std::shared_ptr<Literal> Log(std::vector<std::shared_ptr<Operand>> args);
std::shared_ptr<Literal> GetExp(std::vector<std::shared_ptr<Operand>> args);