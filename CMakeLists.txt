cmake_minimum_required(VERSION 3.18)
project(FINENG)
file(GLOB helloworld_SRC
     "./src/*/*.cpp"
)
add_executable(exec ./src/main.cpp ${helloworld_SRC})

enable_testing()
add_subdirectory(tests)

