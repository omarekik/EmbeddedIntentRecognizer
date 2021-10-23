FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/8aa657ee397a3273f9d2bb14a10b39fd1d556a77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(Source ${CMAKE_SOURCE_DIR}/IntentRecognizer/source)

add_executable(mytest main.cpp 
                      test.cpp
                      ${Source}/RowParser.cpp)
target_link_libraries(mytest gtest_main Boost::boost)

add_test(NAME mytest
         COMMAND mytest)
         