# Protoc generates *.pb.cc file as source files and *.pb.h files as header
# files
FILE(GLOB src *.pb.cc *.pb.h)

find_package(Protobuf 2.5 REQUIRED)

add_library(serialization ${src})
target_link_libraries(serialization ${PROTOBUF_LIBRARIES})
target_include_directories(serialization PUBLIC ${PROTOBUF_INCLUDE_DIRS})
