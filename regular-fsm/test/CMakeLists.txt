add_executable(regular-fsm-tests
        test.cpp
        TestRegexTemplateCatalog.cpp
        )

target_link_libraries(regular-fsm-tests regular-fsm catch)