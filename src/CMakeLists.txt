file(GLOB sources *.cpp)
file(GLOB headers *.hpp)

add_executable(${CMAKE_PROJECT_NAME} ${sources} ${headers})

target_link_libraries(${CMAKE_PROJECT_NAME} tank graphs input serialization)

#set(EXEPATH ${CMAKE_CURRENT_BINARY_DIR} PARENT_SCOPE)
