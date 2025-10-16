cmake_minimum_required(VERSION 3.28)
project(Ex4)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ex4 main.cpp
        Matrix.cpp
        Activation.cpp
        Dense.cpp
        MlpNetwork.cpp
        Test_1.cpp)
