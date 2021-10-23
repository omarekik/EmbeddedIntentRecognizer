add_executable(EmbeddedIntentRecognizer source/main.cpp
                                        source/RowParser.cpp)

target_link_libraries(EmbeddedIntentRecognizer Boost::boost)

add_custom_command(TARGET EmbeddedIntentRecognizer
                    POST_BUILD
                    COMMAND EmbeddedIntentRecognizer)
