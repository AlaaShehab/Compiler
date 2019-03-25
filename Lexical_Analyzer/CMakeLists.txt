cmake_minimum_required(VERSION 3.13)
project(Lexical_Analyzer)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lexical_Analyzer main.cpp Node.cpp Node.h Transition.cpp Transition.h DFANode.cpp DFANode.h LexicalRuleParser.cpp LexicalRuleParser.h TokenGenerator.cpp TokenGenerator.h Token.cpp Token.h)