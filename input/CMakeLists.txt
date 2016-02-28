FILE(GLOB src *.cpp *.hpp)

add_library(input ${src})
target_link_libraries(input tank)
