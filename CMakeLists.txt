cmake_minimum_required(VERSION 3.10)
project(fedora)

set(CMAKE_CXX_STANDARD 14)

include_directories(Fedora/Headers)
include_directories(Fedora/Headers/Function)
include_directories(Fedora/Headers/Types)

add_executable(fedora
        Fedora/Headers/Function/Arguments.h
        Fedora/Headers/Function/Context.h
        Fedora/Headers/Function/FunCall.h
        Fedora/Headers/Function/Function.h
        Fedora/Headers/Function/Returnable.h
        Fedora/Headers/Types/BasicType.h
        Fedora/Headers/Types/List.h
        Fedora/Headers/Types/Number.h
        Fedora/Headers/Types/String.h
        Fedora/Headers/Parser.h
        Fedora/Source/List.cpp
        Fedora/Source/Number.cpp
        Fedora/Source/Parser.cpp
        Fedora/Source/String.cpp
        Fedora/Fedora.cpp Fedora/Headers/Analyzer.h Fedora/Source/Analyzer.cpp Fedora/Headers/Token.h Fedora/Headers/FException.h Fedora/Headers/StaticUtils.h Fedora/Source/StaticUtils.cpp)
