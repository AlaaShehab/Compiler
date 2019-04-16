cmake_minimum_required(VERSION 3.13)
project(Lexical_Analyzer)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lexical_Analyzer main.cpp Lexical/Node.cpp Lexical/Node.h Lexical/Transition.cpp Lexical/Transition.h Lexical/DFANode.cpp Lexical/DFANode.h Lexical/LexicalRuleParser.cpp Lexical/LexicalRuleParser.h Lexical/TokenGenerator.cpp Lexical/TokenGenerator.h Lexical/Token.cpp Lexical/Token.h Lexical/DFAGenerator.cpp Lexical/DFAGenerator.h Lexical/minimization.cpp Lexical/minimization.h Lexical/Group.cpp Lexical/Group.h)