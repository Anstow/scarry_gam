FILE(GLOB src *.cpp *.hpp)
find_package(SFML 2.0 REQUIRED system window graphics audio)

find_package(SFML 2.0 REQUIRED system window graphics audio)

add_executable("graph_viewer" ${src})

target_include_directories("graph_viewer" PUBLIC ${SFML_INCLUDE_DIR})

target_link_libraries("graph_viewer" ${SFML_LIBRARIES} graphs)
