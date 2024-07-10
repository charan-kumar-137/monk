cmake_minimum_required(VERSION 3.29.0)

project(Monk)

# set (CMAKE_CXX_STANDARD 20)

find_package(BISON)
find_package(FLEX)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})


# if($ENV{LLVM_ROOT} )
#   set(LLVM_ROOT $ENV{LLVM_ROOT})
#   message("LLVM_ROOT")
# endif()
# find_package(LLVM PATHS "${LLVM_ROOT}/lib/cmake/llvm" "$ENV{ProgramFiles}/lib/cmake/llvm")

# if( LLVM_FOUND )
#     set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${LLVM_DIR}")
#     message("LLVM_FOUND ${LLVM_DIR}")
# else()
#     message(FATAL_ERROR "LLVM installation not found. Set LLVM_ROOT to the installation root path.")
# endif()

# include(LLVMConfig)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
Block.cpp
Class.cpp
Condition.cpp
ExpressionStatement.cpp
Function.cpp
Identifier.cpp
Iteration.cpp
Node.cpp
Operation.cpp
Types.cpp
VarDecl.cpp
main.cpp
PrettyPrint.cpp
CodeGenContext.cpp
)  

set(HEADERS
Block.h
Class.h
Condition.h
ExpressionStatement.h
Function.h
Identifier.h
Iteration.h
Node.h
Operation.h
Types.h
VarDecl.h
Visitor.h
PrettyPrint.h
CodeGenContext.h
)

BISON_TARGET(Parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(Scanner tokens.l ${CMAKE_CURRENT_BINARY_DIR}/tokens.cpp)

ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

# include_directories("/home/charan/.local/include")

# add_compile_options("llvm-config --cxxflags --ldflags --system-libs --libs core")
add_executable(monk ${SOURCES} ${HEADERS} ${BISON_Parser_OUTPUTS} ${FLEX_Scanner_OUTPUTS})
llvm_map_components_to_libnames(llvm_libs support core irreader mcjit interpreter native ipo)
# target_include_directories(monk PRIVATE ${LLVM_INCLUDE_DIRS})
target_link_libraries(monk ${llvm_libs})
# target_compile_definitions(monk PRIVATE ${LLVM_DEFINITIONS})