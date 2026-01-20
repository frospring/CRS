# ==== 实验性模块支持必须放在最前面 ====
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_MODULE_STD ON)

cmake_minimum_required(VERSION 4.1.1)
project(CRS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 模块文件列表
set(MODULE_FILES
    Course.cppm
    Student.cppm
    teacher.cppm
    psql.cppm
    StudentCourse.cppm
    Registrar.cppm
)

add_executable(CRS main.cpp)

target_sources(CRS PRIVATE FILE_SET cxx_modules TYPE CXX_MODULES
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${MODULE_FILES}
)

find_package(PostgreSQL REQUIRED)
target_include_directories(CRS PRIVATE ${PostgreSQL_INCLUDE_DIRS})
target_link_libraries(CRS PRIVATE ${PostgreSQL_LIBRARIES} pthread)
