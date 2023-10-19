include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB lecture1_src
     "../src/*/*.cpp"
)
add_executable(unit_test main.cpp lecture1_test.cpp ${lecture1_src})
target_link_libraries(unit_test GTest::gtest_main)
add_test(NAME example_test COMMAND unit_test)

include(GoogleTest)
gtest_discover_tests(unit_test)