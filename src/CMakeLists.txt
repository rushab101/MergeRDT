cmake_minimum_required(VERSION 3.10)

project(crdt VERSION 1.0.0 LANGUAGES CXX)

add_library(crdt STATIC
    CrdtHandle.cpp
    CrdtObject.cpp
    Server.cpp
)

#target_include_directories(crdt PRIVATE include)
