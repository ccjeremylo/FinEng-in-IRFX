cmake_minimum_required(VERSION 3.18)
project(FINENG)

file(GLOB src_code
     "./src/*/*.cpp"
)
add_executable(exec ./src/main.cpp ${src_code})

# this creates a .a file
add_library(fineng_code STATIC ${src_code})
set_target_properties(fineng_code PROPERTIES POSITION_INDEPENDENT_CODE ON CXX_STANDARD 17)

add_subdirectory(pybind11)
pybind11_add_module(fineng_irfx ./src/binder.cpp)
target_link_libraries(fineng_irfx PRIVATE fineng_code)

enable_testing()
add_subdirectory(tests)


