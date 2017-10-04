add_executable(regular-fsm-tests
        test.cpp
        Test_RegexTemplateCatalog.cpp
        Test_SyntaxTree&Node.cpp
        Test_RegexSyntaxTree_&_Node.cpp
        )

target_link_libraries(regular-fsm-tests regular-fsm catch)