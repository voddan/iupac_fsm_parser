add_library(regular-fsm
        RegexSyntaxTree
        RegexTemplateCatalog
        StateMachine
        SyntaxTree)

target_include_directories(regular-fsm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)