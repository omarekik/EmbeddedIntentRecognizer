include(FetchContent)

cmake_minimum_required(VERSION 3.14) # version can be different
project(EmbeddedIntentRecognizer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FetchContent_Declare(
    boost-cmake
    GIT_REPOSITORY  https://github.com/Orphis/boost-cmake.git
)
FetchContent_MakeAvailable(boost-cmake)

include_directories(IntentRecognizer/include)

add_subdirectory(IntentRecognizer)

enable_testing ()
add_subdirectory(UnitTest)
