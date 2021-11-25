#pragma once

#include "..\..\Calculator\API\API.h"

extern "C" __declspec(dllexport) void __cdecl Load(OperationsDescription & dstr);

std::shared_ptr<Literal> Pow(std::shared_ptr<Operand> a, std::shared_ptr<Operand> b);