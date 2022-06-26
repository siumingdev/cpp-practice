cmake_minimum_required(VERSION 3.11)
project(cpp-practice VERSION 0.1.0
                     LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(json
URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz
)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
FetchContent_Populate(json)
add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_subdirectory(src)

add_executable(app app/main.cpp)
target_link_libraries(app PUBLIC myvector)
target_compile_features(app PUBLIC cxx_std_17)

target_link_libraries(app PRIVATE nlohmann_json::nlohmann_json)


include(CTest)
enable_testing()


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


