cmake_minimum_required(VERSION 3.16)
project(llvm-project)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
set(CMAKE_C_COMPILER clang++)

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

execute_process(COMMAND llvm-config-10 --libs all
                OUTPUT_VARIABLE LLVM_LIBS2
                OUTPUT_STRIP_TRAILING_WHITESPACE)


llvm_map_components_to_libnames(
    llvm_libs
    support
    core
    irreader
    ExecutionEngine
)

# Link against LLVM libraries
add_executable(pars lex.yy.c grammar.tab.c)
target_link_libraries(pars ${LLVM_LIBS2})
