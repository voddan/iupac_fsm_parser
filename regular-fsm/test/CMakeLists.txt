add_executable(regular-fsm-tests
        Test_RegexTemplateCatalog.cpp
        Test_SyntaxTree&Node.cpp
        Test_RegexSyntaxTree_&_Node.cpp
        Test_TextPosition.cpp
        )

target_link_libraries(regular-fsm-tests regular-fsm gtest gtest_main)

add_test(all-GT-tests regular-fsm-tests)