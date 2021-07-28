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
        Fedora/Fedora.cpp Fedora/Headers/Token.h Fedora/Headers/Exceptions/FException.h Fedora/Headers/StaticUtils.h Fedora/Source/StaticUtils.cpp Fedora/Headers/Analyzers/AnalyticBasic.h Fedora/Headers/Analyzers/AnalyticUtils.h Fedora/Headers/Analyzers/ReadKeyWord.h Fedora/Headers/Analyzers/ReadName.h Fedora/Headers/Analyzers/ReadForceArgs.h Fedora/Headers/Analyzers/ReadFunArgs.h Fedora/Headers/Analyzers/ReadResult.h Fedora/Source/Analyzers/ReadForceArgs.cpp Fedora/Headers/Analyzers/AnalyzerStrategy.h Fedora/Source/Analyzers/AnalyticUtils.cpp Fedora/Source/Analyzers/AnalyzerStrategy.cpp Fedora/Source/Analyzers/ReadFunArgs.cpp Fedora/Source/Analyzers/ReadKeyWord.cpp Fedora/Source/Analyzers/ReadName.cpp Fedora/Source/Analyzers/ReadResult.cpp Fedora/Headers/Exceptions/AnalyzerException.h Fedora/Headers/KeyWords.h Fedora/Source/KeyWords.cpp Fedora/Headers/Utils/TokensHolder.h Fedora/Headers/Analyzers/ReadList.h Fedora/Source/Analyzers/ReadList.cpp Fedora/Source/Analyzers/AnalyticBasic.cpp Fedora/Headers/Utils/SettingsSingleton.h Fedora/Headers/Exceptions/SettingsException.h Fedora/Headers/Utils/Logger.h)

