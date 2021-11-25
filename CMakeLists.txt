cmake_minimum_required (VERSION 3.8)

project ("Calc")

set(CMAKE_CXX_STANDARD 17)

add_executable (Calculator "Calculator/Main.cpp" 
                           "Calculator/API/ExpressionElements.h" "Calculator/API/ExpressionElements.cpp" "Calculator/API/API.h" "Calculator/API/API.cpp"
                           "Calculator/BaseOperations/BaseOperation.h" "Calculator/BaseOperations/BaseOperation.cpp"
                           "Calculator/Calc/Calculator.cpp" "Calculator/Calc/Calculator.h"
                           "Calculator/ModuleManager/ModuleManager.h" "Calculator/ModuleManager/ModuleManager.cpp"
                           "Calculator/Separator/Separator.h" "Calculator/Separator/Separator.cpp"  )

add_library(Pow SHARED "Modules/pow/pow.cpp" "Modules/pow/pow.h"
                       "Calculator/API/ExpressionElements.h" "Calculator/API/ExpressionElements.cpp" "Calculator/API/API.h" "Calculator/API/API.cpp")

add_library(Trigonometry SHARED "Modules/Trigonometry/trigonometry.cpp" "Modules/Trigonometry/trigonometry.h"
                                "Calculator/API/ExpressionElements.h" "Calculator/API/ExpressionElements.cpp" "Calculator/API/API.h" "Calculator/API/API.cpp")

add_library(Logarifms SHARED "Modules/Logarifms/logarifms.h" "Modules/Logarifms/logarifms.cpp"
                             "Calculator/API/ExpressionElements.h" "Calculator/API/ExpressionElements.cpp" "Calculator/API/API.h" "Calculator/API/API.cpp")

install (TARGETS Calculator)
install (TARGETS Pow DESTINATION modules)
install (TARGETS Trigonometry DESTINATION modules)
install (TARGETS Logarifms DESTINATION modules)