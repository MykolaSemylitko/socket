add_library(utils utils.cpp)
include_directories("${PROJECT_SOURCE_DIR}/lib/logger")
include_directories("${PROJECT_SOURCE_DIR}/lib/utils")
target_link_libraries(utils PRIVATE logger)
