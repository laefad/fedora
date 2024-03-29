cmake_minimum_required(VERSION 3.10)
project(fedora)

set(CMAKE_CXX_STANDARD 20)

# Позволяет опускать префикс при добавлении заголовочных файлов
include_directories(Fedora/Headers)

add_executable(fedora
	Fedora/Headers/Runtime.h
	Fedora/Headers/StaticUtils.h
	Fedora/Headers/Analyzers/AnalyticBasic.h
	Fedora/Headers/Analyzers/AnalyzerStrategy.h
	Fedora/Headers/Analyzers/ReadAfterListEnd.h
	Fedora/Headers/Analyzers/ReadAfterReturnableFunName.h
	Fedora/Headers/Analyzers/ReadForceArgs.h
	Fedora/Headers/Analyzers/ReadFunArgs.h
	Fedora/Headers/Analyzers/ReadKeyWord.h
	Fedora/Headers/Analyzers/ReadList.h
	Fedora/Headers/Analyzers/ReadName.h
	Fedora/Headers/Analyzers/ReadResult.h
	Fedora/Headers/Builder/BuildableFunCall.h
	Fedora/Headers/Builder/BuildableFunction.h
	Fedora/Headers/Builder/ContextBuilder.h
	Fedora/Headers/Builder/ForceCallDeclarator.h
	Fedora/Headers/Builder/FunctionDeclarator.h
	Fedora/Headers/Context/ContextualComplement.h
	Fedora/Headers/Context/Function/BuiltinFunction.h
	Fedora/Headers/Context/Function/FeFunction.h
	Fedora/Headers/Context/Function/Function.h
	Fedora/Headers/Context/Function/FunctionRelation.h
	Fedora/Headers/Exceptions/AnalyzerException.h
	Fedora/Headers/Exceptions/BuilderException.h
	Fedora/Headers/Exceptions/FException.h
	Fedora/Headers/Exceptions/ParserException.h
	Fedora/Headers/Exceptions/SettingsException.h
	Fedora/Headers/Exceptions/Utf8istreamException.h
	Fedora/Headers/Parser/Parser.h
	Fedora/Headers/Parser/ParserUtils.h
	Fedora/Headers/Parser/Token.h
	Fedora/Headers/Parser/TokenPriority.h
	Fedora/Headers/Parser/TokensHolder.h
	Fedora/Headers/Parser/TokenType.h
	Fedora/Headers/Parser/Utf8istream.h
	Fedora/Headers/Stack/StackHolder.h
	Fedora/Headers/Types/BasicType.h
	Fedora/Headers/Types/BindedFunCall.h
	Fedora/Headers/Types/FunCall.h
	Fedora/Headers/Types/List.h
	Fedora/Headers/Types/Null.h
	Fedora/Headers/Types/Number.h
	Fedora/Headers/Types/String.h
	Fedora/Headers/Types/Type.h
	Fedora/Headers/Types/UnbindedFunCall.h
	Fedora/Headers/Utils/BasicSingleton.h
	Fedora/Headers/Utils/Logger.h
	Fedora/Headers/Utils/SettingsSingleton.h
	Fedora/Headers/Utils/SingletonsCleaner.h
	Fedora/Fedora.cpp
	Fedora/Source/StaticUtils.cpp
	Fedora/Source/Analyzers/AnalyticBasic.cpp
	Fedora/Source/Analyzers/AnalyzerStrategy.cpp
	Fedora/Source/Analyzers/ReadAfterListEnd.cpp
	Fedora/Source/Analyzers/ReadAfterReturnableFunName.cpp
	Fedora/Source/Analyzers/ReadForceArgs.cpp
	Fedora/Source/Analyzers/ReadFunArgs.cpp
	Fedora/Source/Analyzers/ReadKeyWord.cpp
	Fedora/Source/Analyzers/ReadList.cpp
	Fedora/Source/Analyzers/ReadName.cpp
	Fedora/Source/Analyzers/ReadResult.cpp
	Fedora/Source/Builder/ContextBuilder.cpp
	Fedora/Source/Context/ContextualComplement.cpp
	Fedora/Source/Context/Function/BuiltinFunction.cpp
	Fedora/Source/Context/Function/FeFunction.cpp
	Fedora/Source/Context/Function/Function.cpp
	Fedora/Source/Exceptions/FException.cpp
	Fedora/Source/Parser/Parser.cpp
	Fedora/Source/Parser/ParserUtils.cpp
	Fedora/Source/Parser/Token.cpp
	Fedora/Source/Parser/TokensHolder.cpp
	Fedora/Source/Parser/Utf8istream.cpp
	Fedora/Source/Stack/StackHolder.cpp
	Fedora/Source/Types/BindedFunCall.cpp
	Fedora/Source/Types/FunCall.cpp
	Fedora/Source/Types/List.cpp
	Fedora/Source/Types/Null.cpp
	Fedora/Source/Types/Number.cpp
	Fedora/Source/Types/String.cpp
	Fedora/Source/Types/UnbindedFunCall.cpp
	Fedora/Source/Utils/BasicSingleton.cpp
	Fedora/Source/Utils/Logger.cpp
	Fedora/Source/Utils/SettingsSingleton.cpp
	Fedora/Source/Utils/SingletonsCleaner.cpp
)

