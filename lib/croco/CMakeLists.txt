find_package(Protobuf REQUIRED)
protobuf_generate_cpp(NGT_PROTO_SRCS NGT_PROTO_HDRS repository.proto)

message(STATUS ${PROTOBUF_LIBRARY})

file(GLOB NGT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

add_library(croco-ngt-shared SHARED ${NGT_SOURCES} ${NGT_PROTO_SRCS})
add_library(croco-ngt-static STATIC ${NGT_SOURCES} ${NGT_PROTO_SRCS})
set_target_properties(croco-ngt-shared PROPERTIES OUTPUT_NAME croco_ngt) 
set_target_properties(croco-ngt-static PROPERTIES OUTPUT_NAME croco_ngt) 

target_link_libraries(croco-ngt-shared
	pthread
	${PROTOBUF_LIBRARY}
	${ngt-shared}
)

install (TARGETS croco-ngt-shared LIBRARY DESTINATION lib)
install (TARGETS croco-ngt-static ARCHIVE DESTINATION lib)

install(FILES
	${CMAKE_SOURCE_DIR}/include/croco/c_api.h
	${CMAKE_SOURCE_DIR}/include/croco/Index.h
	${CMAKE_SOURCE_DIR}/include/json.hpp
	${NGT_PROTO_HDRS}
    DESTINATION include/croco/ngt
)
