add_library(client client.cpp)
include_directories("${PROJECT_SOURCE_DIR}/lib/logger")
include_directories("${PROJECT_SOURCE_DIR}/lib/utils")
include_directories("${PROJECT_SOURCE_DIR}/lib/socket")
include_directories("${PROJECT_SOURCE_DIR}/lib/client")
target_link_libraries(client PRIVATE logger)
target_link_libraries(client PRIVATE utils)
target_link_libraries(client PRIVATE socket)
