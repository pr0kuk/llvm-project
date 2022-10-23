cmake_minimum_required(VERSION 3.16)
project(llvm-project)
option(glut "GLUT or LOG loop" 1)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

execute_process(COMMAND llvm-config-10 --libs all
                OUTPUT_VARIABLE LLVM_LIBS2
                OUTPUT_STRIP_TRAILING_WHITESPACE)

if (WIN32)
    set(CMAKE_C_COMPILER gcc)
    link_directories(C:/Users/alex-/gcc/lib)
elseif (UNIX)
    set(CMAKE_C_COMPILER clang++)
    # include_directories(/home/alex/llvm-build/include)
    # include_directories(/usr/include/llvm-10)
    # include_directories(/usr/include/llvm-c-10)
endif()
set(LLVM_ENABLE_FFI TRUE)
set(EXECUTABLE_OUTPUT_PATH build)
set(LIBRARY_OUTPUT_PATH build)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# if (NOT glut)
#     message(Used logloop.cpp)
#     add_executable(launcher main.c interface.c logloop.c)
# else ()
#     message(Used glutloop.cpp)
#     add_executable(launcher main.c interface.c glutloop.c)
# endif()

# if (WIN32)
#     target_link_libraries(launcher PRIVATE freeglutd opengl32)
# elseif (UNIX)
#     target_link_libraries(launcher PRIVATE glut GLU GL) 
# endif()
# add_executable(demo DEMO_LLVM.cpp)
add_executable(codegen codegen.cpp main.c interface.c logloop.c)
llvm_map_components_to_libnames(
    llvm_libs
    support
    core
    irreader
    ExecutionEngine
)

# Link against LLVM libraries
target_link_libraries(codegen ${LLVM_LIBS2} glut GLU GL)
# target_link_libraries(demo ${LLVM_LIBS2})
#target_compile_definitions(demo PRIVATE ${LLVM_DEFINITIONS})