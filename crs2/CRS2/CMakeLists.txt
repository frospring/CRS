cmake_minimum_required(VERSION 4.1.1)

#https://github.com/Kitware/CMake/blob/v4.1.1/Help/dev/experimental.rst

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_MODULE_STD ON)

cmake_minimum_required(VERSION 4.1.1)
project(course_selection LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 模块文件列表
set(MODULE_FILES
    course.cppm
    student.cppm
    teacher.cppm
    datamanager.cppm
    enrollment.cppm
    system.cppm
)

add_executable(course_selection main.cpp)

target_sources(course_selection PRIVATE FILE_SET cxx_modules TYPE CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${MODULE_FILES}
)

find_package(PostgreSQL REQUIRED)
target_include_directories(course_selection PRIVATE ${PostgreSQL_INCLUDE_DIRS})
target_link_libraries(course_selection PRIVATE ${PostgreSQL_LIBRARIES} pthread)









































# target_link_directories(CRS2 PRIVATE /opt/utils/lib)  # -L /opt/utils/lib 设置链接路径
# target_link_libraries(CRS2 PRIVATE utils)             # -lutils           设置链接库名

# set_target_properties(CRS2 PROPERTIES
#     INSTALL_RPATH_USE_LINK_PATH  True                           # 使用链接路径作为安装文件的RPath，等价于"-Wl,-rpath=/opt/utils/lib"
# )

#add_library(CRS2 SHARED
#  utils.cpp
#)

#set_target_properties( CRS2 PROPERTIES
#    PUBLIC_HEADER utils.cppm
#    VERSION   2.5.1
#    SOVERSION 2
#    LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/lib"
#)

#install(TARGETS CRS2
#    LIBRARY DESTINATION /opt/utils/lib
#    PUBLIC_HEADER DESTINATION  /opt/utils/modules
#)

#add_custom_command(TARGET CRS2
#    POST_BUILD
#    COMMAND cmake --install "${CMAKE_CURRENT_BINARY_DIR}"
#)
