add_library(regular-fsm
        RegexSyntaxTree
        RegexTemplateCatalog
        StateMachine
        SyntaxTree
        SyntaxTreeNode
        TextPosition
        RegexSyntaxTreeNode
        RegexParsers)

target_include_directories(regular-fsm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)

target_link_libraries(regular-fsm base_cpp)