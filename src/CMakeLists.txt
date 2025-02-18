file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp")

add_library(gbraylib STATIC ${SOURCES})
target_include_directories(gbraylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(gbray ${CMAKE_CURRENT_SOURCE_DIR}/exec/main.cpp)
target_link_libraries(gbray PRIVATE gbraylib)

