cmake_minimum_required(VERSION 3.9)
project(CSE231_Project)

set(CMAKE_CXX_STANDARD 11)

add_executable(CSE231_Project
        Guides/HOW_TO_COMPILE_LLVM_PASS.txt
        Guides/HOW_TO_IR.txt
        Guides/HOW_TO_RUN_LLVM_PASS.txt
        Output/README
        Output/test_pass_output.txt
        Passes/DFA/231DFA.h
        Passes/part1/BranchBias.cpp
        Passes/part1/CountDynamicInstructions.cpp
        Passes/part1/CountStaticInstructions.cpp
        Passes/part1/lib231.cpp
        Passes/testPass/TestPass.cpp
        Passes/CMakeLists.txt
        Tests/HelloWorld/HelloWorld.cpp
        Tests/test-example/test1-main.cpp
        Tests/test-example/test1.c
        Tests/test-example/test1.cpp
        Tests/test-example/test2.c
        mount_and_launch.sh
        windows_docker_command.txt)
