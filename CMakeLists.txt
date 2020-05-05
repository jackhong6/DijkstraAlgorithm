cmake_minimum_required(VERSION 3.15)
project(DijkstraAlgorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(DijkstraAlgorithm main.cpp Graph.cpp Graph.h ShortestPathAlgorithm.cpp ShortestPathAlgorithm.h)