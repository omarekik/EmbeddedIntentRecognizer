add_executable(EmbeddedIntentRecognizer source/main.cpp
                                        source/CsvParser.cpp
                                        source/Intent.cpp
                                        source/IntentRecognizer.cpp)

target_link_libraries(EmbeddedIntentRecognizer Boost::boost Boost::program_options)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../config/intention.csv
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})