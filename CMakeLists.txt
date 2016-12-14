cmake_minimum_required(VERSION 3.6)
project(lab4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp WTANeuron.h NPoint.h NeuralNet.h Zipped.h AllData.h)
add_executable(lab4 ${SOURCE_FILES})