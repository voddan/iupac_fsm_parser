add_executable(regular-fsm-tests
        test.cpp
        TestRegexTemplateCatalog.cpp
        Test_SyntaxTree&Node.cpp
        )

target_link_libraries(regular-fsm-tests regular-fsm catch)