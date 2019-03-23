project(Lexical_Analyzer)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lexical_Analyzer main.cpp Node.cpp Node.h Transition.cpp Transition.h DFANode.cpp DFANode.h LexicalRuleParser.cpp LexicalRuleParser.h DFAGenerator.cpp DFAGenerator.h)