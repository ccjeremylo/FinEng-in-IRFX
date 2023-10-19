cmake_minimum_required(VERSION 3.18)
project(FINENG)
file(GLOB src_code
     "./src/*/*.cpp"
)
add_executable(exec ./src/main.cpp ${src_code})

enable_testing()
add_subdirectory(tests)

